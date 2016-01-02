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

			virtual Data<string>* encrypt(Data<string>*, longInt);

			virtual Data<fstream>* encrypt(Data<fstream> *source, longInt key);

			virtual Data<string>* decrypt(Data<string> *encrypted, longInt key);

			virtual Data<fstream>* decrypt(Data<fstream> *encrypted, longInt key);

			virtual string toString();

			// Call with object itself gives type of data
			friend ostream& operator<<(ostream &os, IEncryptionType& ie) {
				return os << ie.toString();
			}

			// Call with pointer to object gives type of data
			friend ostream& operator<<(ostream &os, IEncryptionType *ie) {
				return os << *ie;
			}
	};

}

#endif // IENCRYPTIONTYPE_H
