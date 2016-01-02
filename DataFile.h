#ifndef DATAFILE_H
#define DATAFILE_H

#include "Data.h"
#include "DataString.h"

using namespace std;

namespace Cryptography {

	class DataFile : public Data<fstream> {
		private:
			DataString *stringData;
		public:
			DataFile(fstream *data = nullptr);
			~DataFile();

			static string* getStringFromFile(fstream *file);
			static DataFile* getFileFromString(string str);

			DataString *getDataString();
			string toString();
			string toStringType();

			// Call with object itself gives internal data
			friend ostream& operator<<(ostream &os, DataFile& d) {
				return os << d.toString();
			}

			// Call with pointer to object gives type of data
			friend ostream& operator<<(ostream &os, DataFile *d) {
				return os << d->toStringType();
			}
	};

}

#endif // DATAFILE_H
