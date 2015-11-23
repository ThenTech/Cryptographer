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
			DataFile(fstream *data);
			~DataFile();

			static string* getStringFromFile(fstream *file);
			static DataFile* getFileFromString(string str);

			DataString *getDataString();
			string toString();
			string toStringType();
	};

}

#endif // DATAFILE_H
