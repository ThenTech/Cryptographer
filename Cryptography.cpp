#include "Cryptography.h"
#include "Exceptions.h"

using namespace std;
using namespace Cryptography;

template <class T>
Cryptographer<T>::Cryptographer(Data<T> *source, IEncryptionType *algorithm, longInt key) {
	this->setSource(source);
	this->setKey(key);
	this->setAlgorithm(algorithm);
}

template <class T>
Cryptographer<T>::~Cryptographer() {
	delete this->source;
	delete this->decrypted; //?
	delete this->encrypted;
	delete this->algorithm; //?   -|> already deleted from reference before this call
}

template <class T>
void Cryptographer<T>::setSource(Data<T> *source) {
	delete this->source;
	this->source = source;
	delete this->decrypted;
	this->decrypted = nullptr;
	delete this->encrypted;
	this->encrypted = nullptr;
}

template <class T>
Data<T> *Cryptographer<T>::getSource() {
	return this->source;
}

template <class T>
void Cryptographer<T>::setAlgorithm(IEncryptionType *algorithm) {
	delete this->algorithm;
	this->algorithm = algorithm;
	delete this->decrypted;
	this->decrypted = nullptr;
	delete this->encrypted;
	this->encrypted = nullptr;
}

template <class T>
IEncryptionType *Cryptographer<T>::getAlgorithm() {
	return this->algorithm;
}

template <class T>
void Cryptographer<T>::setKey(longInt key) {
	this->key = key;
	delete this->decrypted;
	this->decrypted = nullptr;
	delete this->encrypted;
	this->encrypted = nullptr;
}

template <class T>
longInt Cryptographer<T>::getKey() {
	return this->key;
}

template <class T>
void Cryptographer<T>::encrypt() {
	if (this->getAlgorithm() == nullptr)
		throw Exceptions::NullPointerException("getAlgorithm");
	if (this->getSource() == nullptr)
		throw Exceptions::NullPointerException("getSource");

	// threaded?
	this->encrypted = this->getAlgorithm()->encrypt(this->getSource(), this->getKey());
}

template <class T>
Data<T> *Cryptographer<T>::getDecrypted() {
	if (this->decrypted == nullptr) {
		this->decrypted = this->getAlgorithm()->decrypt(this->getEncrypted() == nullptr ?
								this->getSource() : this->getEncrypted(), this->getKey());
	}
	return this->decrypted;
}

template <class T>
Data<T> *Cryptographer<T>::getEncrypted() {
	if (this->encrypted == nullptr) {
		this->encrypt();
	}
	return this->encrypted;
}

template class Cryptographer<fstream>;
template class Cryptographer<string>;

