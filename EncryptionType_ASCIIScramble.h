#ifndef ENCRYPTIONTYPE_ASCIISCRAMBLE_H
#define ENCRYPTIONTYPE_ASCIISCRAMBLE_H

#include <cstdlib>
#include "IEncryptionType.h"

using namespace std;

namespace Cryptography {

	class EncryptionType_ASCIIScramble : public IEncryptionType {
	public:
		~EncryptionType_ASCIIScramble() {}

		Data<string>* encrypt(Data<string> *source, longInt key) {
			string *en = alloc::allocVar<string>();
			srand(abs(key));

			for (char16_t c : source->toString())
				*en += char16_t(c + ((rand() % 163 - 83)) * (key < 0 ? -1 : key == 0 ? 0 : 1));

			return new DataString(en);
		}

		string toString() {
			return "IEncryptionType:EncryptionType_ASCIIScramble";
		}
	};

}

#endif // ENCRYPTIONTYPE_ASCIISCRAMBLE_H

