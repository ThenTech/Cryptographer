#include "Data.h"
#include "utils.h"

using namespace Cryptography;

//template <class T>
//Data<T>::Data(T *data) {
//	this->DATA = data;
//}

template <class T>
Data<T>::~Data() {
	//delete this->getData();
}

template <class T>
T *Data<T>::getData() {
	return this->DATA;
}

template <class T>
string Data<T>::toString() {
	return "Raw " + this->toStringType();
}

template <class T>
string Data<T>::toStringType() {
	return type2name(*this);
}

// template class fix
template class Data<fstream>;
template class Data<string>;

