#ifndef ENCRYPTIONTYPE_SIMPLEREVERSIBLEHASH_H
#define ENCRYPTIONTYPE_SIMPLEREVERSIBLEHASH_H

#include "IEncryptionType.h"

using namespace std;

namespace Cryptography {

	class EncryptionType_SimpleReversibleHash : public IEncryptionType {
	public:
		~EncryptionType_SimpleReversibleHash() {}

		Data<string>* encrypt(Data<string> *source, longInt key) {
			string *en = alloc::allocVar<string>();

			for (char c : source->toString()) {
				if (key > 0) c += --key;	// Shift char to prevent visible repetition.

				c = char(((0x0F & c) << 4) | ((0xF0 & c) >> 4));

				if (key < 0) c += ++key;

				*en += c;
			}

			return new DataString(en);
		}

		string toString() {
			return "IEncryptionType:EncryptionType_SimpleReversibleHash";
		}
	};

}

#endif // ENCRYPTIONTYPE_SIMPLEREVERSIBLEHASH_H
