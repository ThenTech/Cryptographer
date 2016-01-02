#include "EncryptionTypeFactory.h"

using namespace Cryptography;

//inline bool EncryptionAlgoFactory::typeChoiceInBounds(int i) {
//	return i > 0 && i <= (int) EncryptionType::MAX;
//}

void EncryptionAlgoFactory::displayTypeNames() {
	for (size_t t = 0; t < (int) EncryptionType::MAX; t++)
	   cout << "\t" << (t + 1) << "\t" << Cryptography::EncryptionTypeNames[t] << endl;
}

EncryptionType EncryptionAlgoFactory::getTypeFromInput(size_t in) {
	if (!EncryptionAlgoFactory::typeChoiceInBounds(in))
		throw Exceptions::OutOfBoundsException(in);

	return EncryptionType(in);
}

IEncryptionType* EncryptionAlgoFactory::newAlgorithm(EncryptionType t) {
	switch (t) {
		case EncryptionType::ASCIIScramble:
			return new EncryptionType_ASCIIScramble;
		case EncryptionType::StrShift:
			return new EncryptionType_StrShift;
		case EncryptionType::SimpleHash:
			return new EncryptionType_SimpleHash;
		case EncryptionType::SimpleReversibleHash:
			return new EncryptionType_SimpleReversibleHash;
		default:
			return nullptr;
	}
}

IEncryptionType* EncryptionAlgoFactory::newAlgorithm(size_t in) {
	return newAlgorithm(EncryptionAlgoFactory::getTypeFromInput(in));
}
