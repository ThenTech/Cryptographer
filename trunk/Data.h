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
			Data(T *data) : DATA(data) {}
			virtual ~Data();

			T *getData();

			virtual string toString();
			virtual string toStringType();
	};

}
#endif // DATA_H
