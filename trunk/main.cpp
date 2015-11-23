/*██████████████████████████████████████████████████████████████████████████████████████
████ Cryptographer main class ██████████████████████████████████████████████████████████
████████████████████████████████████████████████████████████████████████████████████████
████ TO-DO █████████████████████████████████████████████████████████████████████████████
████████ * Cryptographer<source_type, key_type> 							   █████████
████████	== e.g. Cryptographer<string, int>, Cryptographer<fstream, string> █████████
████████	Maybe an extra object to contain key? 							   █████████
████████			=> with template and toString/Number functions (hash?)	   █████████
████████																	   █████████
████████████████████████████████████████████████████████████████████████████████████████*/
#include <iostream>
#include "display.h"
#include "Cryptography.h"

#define	NDEBUG			// uncomment to disable debugging and assertion
#include "UnitTest.h"

using namespace std;
using namespace Cryptography;

int main() {
	Screen_init();

#ifndef NDEBUG
	runTests();
#else
	string test = "";
	longInt key = 0;
	int algoChoice = 0;
	Cryptographer<string> c(nullptr, nullptr, key);

	while(1) {
		try {
			/*██████████████████████████████████████████████████████████████████████████████████████
			████ Enter and set encryption string ███████████████████████████████████████████████████
			████████████████████████████████████████████████████████████████████████████████████████*/
			cout << "Enter a string to encrypt : ";
			cin.clear(); cin.sync();
			getline(cin, test);
			c.setSource(new DataString(&test));

			/*██████████████████████████████████████████████████████████████████████████████████████
			████ Enter and set encryption key ██████████████████████████████████████████████████████
			████████████████████████████████████████████████████████████████████████████████████████*/
			do {
				cout << "Enter a key for encryption: ";
				cin.clear(); cin.sync();
			} while (!(cin >> key) || !Cryptography::keyInBounds(key));
			c.setKey(key);

			/*██████████████████████████████████████████████████████████████████████████████████████
			████ Display and select encryption algorithm ███████████████████████████████████████████
			████████████████████████████████████████████████████████████████████████████████████████*/
			cout << "Possible encryption algorithms:" << endl << endl;
			EncryptionAlgoFactory::displayTypeNames();
			cout << endl;

			do {
				cout << "Enter the number of the algorithm you want to use: ";
				cin.clear(); cin.sync();
			} while (!(cin >> algoChoice) || !EncryptionAlgoFactory::typeChoiceInBounds(algoChoice));

			c.setAlgorithm(EncryptionAlgoFactory::newAlgorithm(algoChoice));
			cout << endl;

			/*██████████████████████████████████████████████████████████████████████████████████████
			████ Display info and start en- & decryption ███████████████████████████████████████████
			████████████████████████████████████████████████████████████████████████████████████████*/
			cout <<  "Source: " << c.getSource()->toStringType()	<< " =" << endl << endl
								<< c.getSource()->toString()		<< endl << endl;

			cout <<  "  Algo: " << c.getAlgorithm()->toString()		<< endl << endl;

			cout <<  "  Encr: " << c.getEncrypted()->toStringType() << " =" << endl << endl
								<< c.getEncrypted()->toString()		<< endl << endl;

			cout <<  "  Decr: " << c.getDecrypted()->toStringType() << " =" << endl << endl
								<< c.getDecrypted()->toString()		<< endl << endl;

			system("PAUSE");
			system("CLS");
		} catch (Exceptions::Exception const &e) {
			err(e.getMessage());
		} catch (...) {
			err("Unknown exception caught.");
		}
	}
#endif

	//system("PAUSE");
	return 0;
}

