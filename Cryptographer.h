#ifndef CRYPTOGRAPHER_H
#define CRYPTOGRAPHER_H

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

			Data<T> *source				= nullptr;
			Data<T> *decrypted			= nullptr;
			Data<T> *encrypted			= nullptr;
			IEncryptionType *algorithm	= nullptr;

			void encrypt();

		public:
			Cryptographer(Data<T> *source = nullptr, IEncryptionType *algorithm = nullptr, longInt key = 0);
			~Cryptographer();

			void setSource(Data<T> *source);
			Data<T> *getSource(void);

			void setAlgorithm(IEncryptionType *algorithm);
			IEncryptionType *getAlgorithm(void);

			void setKey(longInt key);
			longInt getKey(void);

			Data<T> *getEncrypted(void);
			Data<T> *getDecrypted(void);

			// If defined outside class:  Error: Must take jsut one argument
			friend ostream& operator<<(ostream &os, Cryptographer& c) {
				os <<  "Source: "	<<	c.getSource()		<< " =" << endl << endl
									<< *c.getSource()		<< endl << endl;
				os <<  "  Algo: "	<<	c.getAlgorithm()	<< endl << endl;
				os <<  "  Encr: "	<<	c.getEncrypted()	<< " =" << endl << endl
									<< *c.getEncrypted()	<< endl << endl;
				os <<  "  Decr: "	<<	c.getDecrypted()	<< " =" << endl << endl
									<< *c.getDecrypted()	<< endl << endl;
				return os;
			}

			friend ostream& operator<<(ostream &os, Cryptographer *c) {
				return os << *c;
			}
	};

}

#endif // CRYPTOGRAPHER_H

