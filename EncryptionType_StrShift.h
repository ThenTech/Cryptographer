#ifndef ENCRYPTIONTYPE_STRSHIFT_H
#define ENCRYPTIONTYPE_STRSHIFT_H

#include "IEncryptionType.h"

using namespace std;

namespace Cryptography {

	class EncryptionType_StrShift : public IEncryptionType {
		public:
			~EncryptionType_StrShift() {}

			Data<string>* encrypt(Data<string> *source, longInt key) {
				string *en = alloc::allocVar<string>();

				for (char c : source->toString())
					*en += (c + key);

				return new DataString(en);
			}

			string toString() {
				return IEncryptionType::toString() + "::EncryptionType_StrShift";
			}
	};

}

#endif // ENCRYPTIONTYPE_STRSHIFT_H

