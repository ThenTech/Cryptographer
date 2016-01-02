#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <fstream>
#include <streambuf>

#include "utils.h"

using namespace std;

namespace Cryptography {

	template <class T>
	class Data {
		private:
			T *DATA;
		public:
			Data(T *data = nullptr) : DATA(data) {}
			virtual ~Data();

			T *getData();

			virtual string toString();
			virtual string toStringType();

			// Call with object itself gives internal data
			friend ostream& operator<<(ostream &os, Data& d) {
				return os << d.toString();
			}

			// Call with pointer to object gives type of data
			friend ostream& operator<<(ostream &os, Data *d) {
				return os << d->toStringType();
			}
	};

}
#endif // DATA_H
