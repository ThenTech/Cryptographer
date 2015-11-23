#ifndef UNITTEST_H
#define UNITTEST_H

//#define NDEBUG	// uncomment to disable debugging and assertion

#ifndef NDEBUG	// ifndef NDEBUG

#include <cassert>			// Debug assertion
#include "display.h"		// Logging
#include "Cryptography.h"

using namespace Cryptography;

static string decstr = "Hello World!";
static string encstr = "Ifmmp!Xpsme\"";

static Data<string>		*dataStr_str		= nullptr;
static Data<string>		*datastring_str		= nullptr;
static Data<fstream>	*datafile_test		= nullptr;
static Data<fstream>	*datafile_hw		= nullptr;

static IEncryptionType		 *encrypt_algo	= nullptr;

static Cryptographer<string> *crypto_string	= nullptr;
static Cryptographer<fstream> *crypto_file	= nullptr;

void test_init() {
	log("Initialising...\n");

	dataStr_str		= new Data<string>(&decstr);
	datastring_str	= new DataString(&decstr);
	datafile_test	= new DataFile(new fstream("test.txt"));
	datafile_hw		= new DataFile(new fstream("HelloWorld.txt"));

	encrypt_algo	= new EncryptionType_StrShift;

	crypto_string	= new Cryptographer<string>(datastring_str, encrypt_algo, 1);
	crypto_file		= new Cryptographer<fstream>(datafile_hw, encrypt_algo, 1);
}

void test_Data(void) {
	log("test_Data ::");

	assert(dataStr_str != nullptr);
	log("New data object of " + dataStr_str->toStringType());

	assert(dataStr_str->getData() != nullptr);
	assert(*dataStr_str->getData() == decstr);
	log("Raw data: " + *dataStr_str->getData());

	//assert(dataStr_str->toString() == decstr);
	log("toString: " + dataStr_str->toString());
}

void test_DataString(void) {
	log("test_DataString ::");

	assert(datastring_str != nullptr);
	log("New data object of " + datastring_str->toStringType());

	assert(datastring_str->getData() != nullptr);
	assert(*datastring_str->getData() == decstr);
	log("Raw data: " + *datastring_str->getData());

	assert(datastring_str->toString() == decstr);
	log("toString: " + datastring_str->toString());
}

void test_DataFile() {
	log("test_DataFile :: test.txt");
	assert(datafile_test != nullptr);
	log("New data object of\n" + datafile_test->toStringType());

	assert(datafile_test->getData() != nullptr);
	log("Raw data:\n" + datafile_test->toString());

	log("test_DataFile :: HelloWorld.txt");
	assert(datafile_hw != nullptr);
	log("New data object of\n" + datafile_hw->toStringType());

	assert(datafile_hw->getData() != nullptr);
	assert(datafile_hw->toString() == decstr);
	log("Raw data:\n" + datafile_hw->toString());
}

void test_IEncryptionStr(void) {
#define NORMAL_CASE
	log("test_IEncryption :: DataString");

#ifdef NORMAL_CASE
	int key = 1;
#else
	int key = -42;
#endif
	assert(encrypt_algo != nullptr);
	log("New data object of " + encrypt_algo->toString());

	Data<string> *encrypted = encrypt_algo->encrypt(datastring_str, key);

	assert(encrypted != nullptr);
	assert(encrypted->getData() != nullptr);
#ifdef NORMAL_CASE
	assert(encrypted->toString() == encstr);
	// static call:
	//assert(EncryptionType_StrShift::encrypt(datastring_str, 1)->toString() == encstr);
#endif
	log("Encrypted: " + encrypted->toString());

	Data<string> *decrypted = encrypt_algo->decrypt(encrypted, key);

	assert(decrypted != nullptr);
	assert(decrypted->getData() != nullptr);
	assert(decrypted->toString() == datastring_str->toString());
#ifdef NORMAL_CASE
	assert(decrypted->toString() == decstr);
#endif
	log("Decrypted: " + decrypted->toString());

	delete encrypted;
	delete decrypted;
#undef	NORMAL_CASE
}

void test_IEncryptionFile(void) {
#define NORMAL_CASE
	log("test_IEncryption :: DataFile");

#ifdef NORMAL_CASE
	int key = 1;
#else
	int key = -42;
#endif
	assert(encrypt_algo != nullptr);
	log("New data object of " + encrypt_algo->toString());

	Data<fstream> *encrypted = encrypt_algo->encrypt(datafile_hw, key);

	assert(encrypted != nullptr);
	assert(encrypted->getData() != nullptr);
#ifdef NORMAL_CASE
	assert(encrypted->toString() == encstr);
#endif
	log("Encrypted: " + encrypted->toString());

	Data<fstream> *decrypted = encrypt_algo->decrypt(encrypted, key);

	assert(decrypted != nullptr);
	assert(decrypted->getData() != nullptr);
	assert(decrypted->toString() == datafile_hw->toString());
#ifdef NORMAL_CASE
	assert(decrypted->toString() == decstr);
#endif
	log("Decrypted: " + decrypted->toString());

	delete encrypted;
	delete decrypted;
#undef	NORMAL_CASE
}

void test_BasicCryptoStr(void) {
	log("test_BasicCryptoStr :: Data<string>, StrShift");

	assert(*datastring_str->getData() == *crypto_string->getSource()->getData());
	log("   Source: " + *crypto_string->getSource()->getData());

	assert(crypto_string->getAlgorithm() == encrypt_algo);
	log("Algorithm: " + crypto_string->getAlgorithm()->toString());

	assert(crypto_string->getKey() == 1);
	log("      Key: " + to_string(crypto_string->getKey()));

	assert(crypto_string->getEncrypted()->toString() ==  encstr);
	log("Encrypted: " + crypto_string->getEncrypted()->toString());

	assert(crypto_string->getDecrypted()->toString() ==  decstr);
	log("Decrypted: " + crypto_string->getDecrypted()->toString());
}

void test_BasicCryptoFile(void) {
	log("test_BasicCryptoFile :: Data<File>, StrShift");

	assert(datafile_hw->toString() == crypto_file->getSource()->toString());
	log("   Source: " + crypto_file->getSource()->toString());

	assert(crypto_file->getAlgorithm() == encrypt_algo);
	log("Algorithm: " + crypto_file->getAlgorithm()->toString());

	assert(crypto_file->getKey() == 1);
	log("      Key: " + to_string(crypto_file->getKey()));

	assert(crypto_file->getEncrypted()->toString() ==  encstr);
	log("Encrypted: " + crypto_file->getEncrypted()->toString());

	assert(crypto_file->getDecrypted()->toString() ==  decstr);
	log("Decrypted: " + crypto_file->getDecrypted()->toString());
}

void test_BasicCryptoFileExtra(void) {
	log("test_BasicCryptoFile :: Data<File>, StrShift");

	crypto_file->setSource(datafile_test);

	assert(datafile_test->toString() == crypto_file->getSource()->toString());
	log("   Source: " + crypto_file->getSource()->toString());

	assert(crypto_file->getAlgorithm() == encrypt_algo);
	log("Algorithm: " + crypto_file->getAlgorithm()->toString());

	assert(crypto_file->getKey() == 1);
	log("      Key: " + to_string(crypto_file->getKey()));

	//assert(crypto_file->getEncrypted()->toString() ==  encstr);
	log("Encrypted: \n" + crypto_file->getEncrypted()->toString());

	assert(crypto_file->getDecrypted()->toString() ==  datafile_test->toString());
	log("Decrypted: \n" + crypto_file->getDecrypted()->toString());
}

void test_deinit() {
	log("Deleting pointers...\n");

	delete dataStr_str;
	delete datastring_str;

//// Deleted through crypto destructor
//	delete datafile_hw;
//	delete encrypt_algo;

//	delete crypto_string;
	delete crypto_file;
}

void runTests(void) {
	test_init();			err("");
	test_Data();			err("");
	test_DataString();		err("");
	test_DataFile();		err("");
	test_IEncryptionStr();	err("");
	test_IEncryptionFile();	err("");

	test_BasicCryptoStr();	err("");
	test_BasicCryptoFile();	err("");
	test_BasicCryptoFileExtra(); err("");

	test_deinit();
}


#endif // ifndef NDEBUG

#endif // UNITTEST_H

