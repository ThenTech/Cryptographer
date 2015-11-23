#include "DataString.h"

using namespace Cryptography;

//string* DataString::getData() {
//	return (string*) this->DATA;
//}

DataString::~DataString() {}

string DataString::toString() {
	return *this->getData();
}

string DataString::toStringType() {
	//return type2name(this);
	return Data::toStringType() + "::DataString";
}
