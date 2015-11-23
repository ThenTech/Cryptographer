#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include <iostream>

#include "Data.h"
#include "IEncryptionType.h"
#include "EncryptionTypeFactory.h"
#include "utils.h"

using namespace std;


namespace Cryptography {

	static inline bool keyInBounds(longInt key) {
		return key <= LLONG_MAX && key >= LLONG_MIN;
	}

	template <class T>	// <class SourceType, class KeyType>
	class Cryptographer {
		private:
			longInt key;	// KeyType key;

			Data<T> *source = nullptr;
			Data<T> *decrypted = nullptr;
			Data<T> *encrypted = nullptr;
			IEncryptionType *algorithm = nullptr;

			void encrypt();

		public:
			Cryptographer(Data<T> *source, IEncryptionType *algorithm, longInt key);
			~Cryptographer();

			void setSource(Data<T> *source);
			Data<T> *getSource(void);

			void setAlgorithm(IEncryptionType *algorithm);
			IEncryptionType *getAlgorithm(void);

			void setKey(longInt key);
			longInt getKey(void);

			Data<T> *getEncrypted(void);
			Data<T> *getDecrypted(void);
	};

}

#endif // CRYPTOGRAPHY_H

