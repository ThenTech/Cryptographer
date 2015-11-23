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

			static void displayTypeNames() {
				for (size_t t = 0; t < (int) EncryptionType::MAX; t++)
				   cout << "\t" << (t + 1) << "\t" << EncryptionTypeNames[t] << endl;
			}

			static EncryptionType getTypeFromInput(size_t in) {
				if (!typeChoiceInBounds(in))
					throw Exceptions::OutOfBoundsException(in);

				return EncryptionType(in);
			}

			static IEncryptionType* newAlgorithm(EncryptionType t) {
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

			static IEncryptionType* newAlgorithm(size_t in) {
			    return newAlgorithm(getTypeFromInput(in));
			}
	};

}
#endif // ENCRYPTIONTYPEFACTORY_H

