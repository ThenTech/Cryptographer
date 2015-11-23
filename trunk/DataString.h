#ifndef DATASTRING_H
#define DATASTRING_H

#include "Data.h"

using namespace std;

namespace Cryptography {

	class DataString : public Data<string> {
		private:
		public:
			DataString(string *data) : Data(data) {}
			~DataString();

			string toString();
			string toStringType();
	};
}

#endif // DATASTRING_H
