#ifndef IENCRYPTIONTYPE_H
#define IENCRYPTIONTYPE_H

#include <iostream>
#include <typeinfo>
#include "Data.h"
#include "DataFile.h"
#include "utils.h"

using namespace std;

namespace Cryptography {

	class IEncryptionType {
		public:
			virtual ~IEncryptionType() {}

			virtual Data<string>* encrypt(Data<string>*, longInt)
				{ return nullptr; }

			virtual Data<fstream>* encrypt(Data<fstream> *source, longInt key){
				return DataFile::getFileFromString(
							this->encrypt(((DataFile* )source)->getDataString(), key)
							->toString());
			}

			virtual Data<string>* decrypt(Data<string> *encrypted, longInt key) {
				return this->encrypt(encrypted, -key);
			}

			virtual Data<fstream>* decrypt(Data<fstream> *encrypted, longInt key)  {
				return DataFile::getFileFromString(
							this->decrypt(((DataFile* )encrypted)->getDataString(), key)
							->toString());
			}

			virtual string toString(){
				return type2name(*this);
			}
	};

}

#endif // IENCRYPTIONTYPE_H
