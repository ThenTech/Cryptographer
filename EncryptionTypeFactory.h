#ifndef ENCRYPTIONTYPEFACTORY_H
#define ENCRYPTIONTYPEFACTORY_H

#include "Exceptions.h"
#include "IEncryptionType.h"

#include "EncryptionType_ASCIIScramble.h"
#include "EncryptionType_StrShift.h"
#include "EncryptionType_SimpleHash.h"
#include "EncryptionType_SimpleReversibleHash.h"

namespace Cryptography {

	enum class EncryptionType { ASCIIScramble = 1, StrShift, SimpleHash, SimpleReversibleHash,
								MAX = SimpleReversibleHash};
	static const string EncryptionTypeNames[] = { "ASCII Scramble", "String shift", "Simple Hash", "Simple Reversible Hash"};


	class EncryptionAlgoFactory {
		public:
			static inline bool typeChoiceInBounds(int i) {
				return i > 0 && i <= (int) EncryptionType::MAX;
			}

			static void displayTypeNames();

			static EncryptionType getTypeFromInput(size_t in);

			static IEncryptionType* newAlgorithm(EncryptionType t);

			static IEncryptionType* newAlgorithm(size_t in);
	};

}
#endif // ENCRYPTIONTYPEFACTORY_H

