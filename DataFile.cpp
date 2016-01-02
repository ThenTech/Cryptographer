#define	NDEBUG			// comment to enable debugging

#include "DataFile.h"
#include "Exceptions.h"

using namespace Cryptography;

DataFile::DataFile(fstream *data) : Data(data) {
	this->stringData = new DataString(this->getStringFromFile(data));
}

DataFile::~DataFile() {
	delete this->stringData;
}

string* DataFile::getStringFromFile(fstream *file) {
	string *str = alloc::allocVar<string>();

	try {
		file->seekg(0, std::ios::end);
		str->reserve(file->tellg());
		file->seekg(0, std::ios::beg);

		str->assign((std::istreambuf_iterator<char>(*file)),
					 std::istreambuf_iterator<char>());
	} catch (...) {
		throw Exceptions::FileReadException();
	}

	return str;
}

DataFile* DataFile::getFileFromString(string str) {
	// Temporary ------------------------------------------
	string name = "output";
#ifdef NDEBUG
	cout << "Enter a name for the output file: ";
	cin.clear(); cin.sync();
	getline(cin, name);
#endif
	// Temporary ------------------------------------------

	ofstream file(name + ".txt"); // output.txt

	try {
		file << str;
		file.close();
	} catch (...) {
		throw Exceptions::FileWriteException();
	}

	return new DataFile(new fstream(name + ".txt")); // output.txt
}

DataString *DataFile::getDataString() {
	return this->stringData;
}

string DataFile::toString() {
	return *this->stringData->getData();
}

string DataFile::toStringType() {
	return Data::toStringType() + "::DataFile";
}
