#ifndef ENCRYPTIONTYPE_SIMPLEHASH_H
#define ENCRYPTIONTYPE_SIMPLEHASH_H

#include "IEncryptionType.h"

#include <functional>

using namespace std;

namespace Cryptography {

	class EncryptionType_SimpleHash : public IEncryptionType {
	public:
		~EncryptionType_SimpleHash() {}

		Data<string>* encrypt(Data<string> *source, longInt key) {
			string *en = alloc::allocVar<string>();

			hash<string> str_hash;

			*en = to_string(str_hash(source->toString()) ^ key);

			return new DataString(en);
		}

		string toString() {
			return "IEncryptionType:EncryptionType_SimpleHash";
		}
	};

}

#endif // ENCRYPTIONTYPE_SIMPLEHASH_H

