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
#define	NDEBUG			// comment to enable debugging (also in DataFile.cpp)

#include <iostream>
#include "display.h"
#include "Cryptographer.h"

#ifndef NDEBUG
#include "UnitTest.h"
#endif

using namespace std;
using namespace Cryptography;

int main() {
	Screen_init();

#ifndef NDEBUG
	runTests();
#else
	string test = "";
	longInt key = 0;

	typedef enum {STRING = 1, FILE = 2} dataChoice;
	int dChoice = 0;
	int algoChoice = 0;
	Cryptographer<string>	*cs = nullptr;
	Cryptographer<fstream>	*cf = nullptr;

	while(1) {
		try {			
			/*██████████████████████████████████████████████████████████████████████████████████████
			████ Enter and set encryption string or file ███████████████████████████████████████████
			████████████████████████████████████████████████████████████████████████████████████████*/

			cout << "Encrypt data from:"			<< endl << endl;
			cout << "\t" << 1 << "\t" << "String"	<< endl;
			cout << "\t" << 2 << "\t" << "File"		<< endl << endl;

			do {
				cout << "Enter the number of the method you want to use: ";
				cin.clear(); cin.sync();
			} while (!(cin >> dChoice) || dChoice < STRING || dChoice > FILE);

			switch (dChoice) {
				case STRING:
					cout << "Enter a string to encrypt : ";
					cin.clear(); cin.sync();
					getline(cin, test);
					cs = new Cryptographer<string>(new DataString(&test), nullptr, key);
					break;
				case FILE:
					cout << "Enter the path to the file to encrypt: ";
					cin.clear(); cin.sync();
					getline(cin, test);
					cf = new Cryptographer<fstream>(new DataFile(new fstream(test)), nullptr, key);
					break;
				default:
					throw Exceptions::Exception("ERROR: No valid entry.");
			}

			/*██████████████████████████████████████████████████████████████████████████████████████
			████ Enter and set encryption key ██████████████████████████████████████████████████████
			████████████████████████████████████████████████████████████████████████████████████████*/
			do {
				cout << "Enter a key for encryption: ";
				cin.clear(); cin.sync();
			} while (!(cin >> key) || !Cryptography::keyInBounds(key));
			dChoice == STRING ? cs->setKey(key) : cf->setKey(key);

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

			dChoice == STRING ? cs->setAlgorithm(EncryptionAlgoFactory::newAlgorithm(algoChoice))
							  : cf->setAlgorithm(EncryptionAlgoFactory::newAlgorithm(algoChoice));
			cout << endl;

			/*██████████████████████████████████████████████████████████████████████████████████████
			████ Display info and start en- & decryption ███████████████████████████████████████████
			████████████████████████████████████████████████████████████████████████████████████████*/
			dChoice == STRING ? cout << cs : cout << cf;

			system("PAUSE");
			system("CLS");

			delete cs;
			delete cf;
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

