#ifndef DATASTRING_H
#define DATASTRING_H

#include "Data.h"

using namespace std;

namespace Cryptography {

	class DataString : public Data<string> {
		private:
		public:
			DataString(string *data = nullptr) : Data(data) {}
			~DataString();

			string toString();
			string toStringType();

			// Call with object itself gives internal data
			friend ostream& operator<<(ostream &os, DataString& d) {
				return os << d.toString();
			}

			// Call with pointer to object gives type of data
			friend ostream& operator<<(ostream &os, DataString *d) {
				return os << d->toStringType();
			}
	};
}

#endif // DATASTRING_H
