#include "IEncryptionType.h"

using namespace Cryptography;

/*
 *	Only method to be overrided in reversible encryption.
 */
Data<string>* IEncryptionType::encrypt(Data<string>*, longInt) {
	return nullptr;
}

Data<fstream>* IEncryptionType::encrypt(Data<fstream> *source, longInt key){
	return DataFile::getFileFromString(
				this->encrypt(((DataFile* )source)->getDataString(), key)
				->toString());
}

Data<string>* IEncryptionType::decrypt(Data<string> *encrypted, longInt key) {
	return this->encrypt(encrypted, -key);
}

Data<fstream>* IEncryptionType::decrypt(Data<fstream> *encrypted, longInt key)  {
	return DataFile::getFileFromString(
				this->decrypt(((DataFile* )encrypted)->getDataString(), key)
				->toString());
}

string IEncryptionType::toString(){
	return type2name(*this);
}



/*
 *	Template garbage.
 */
//// template class fix
//template class IEncryptionType<string>;
//template class IEncryptionType<fstream>;

//template <>
//DataString *Cryptography::IEncryptionType::encrypt(Data<string> source, longInt key);
//template <>
//DataString *Cryptography::IEncryptionType::decrypt(Data<string> encrypted, longInt key);

//template <class T>
//Data<T> *IEncryptionType::encrypt(Data<T> source, longInt key) {
//	return nullptr;
//}

//template <class T>
//Data<T> *IEncryptionType::decrypt(Data<T> *encrypted, longInt key) {
//	return nullptr;
//}

//DataString *IEncryptionType::encrypt(DataString source, longInt key) {
//	return nullptr;
//}

//DataString *IEncryptionType::decrypt(DataString *encrypted, longInt key) {
//	return nullptr;
//}
