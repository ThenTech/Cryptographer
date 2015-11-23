#ifndef UTILS
#define UTILS

#include <iostream>
#include <typeinfo>
#include <cxxabi.h>
#include <limits>

//#define type2name(o)	std::string(typeid(o).name())
//#define type2name(o) std::string(abi::__cxa_demangle(typeid(o).name(),nullptr,nullptr,nullptr))

using longInt = signed long long int;

namespace std {
	static inline void strReplaceAll(string &str, const string& from, const string& to) {
		size_t start_pos = 0;
		while((start_pos = str.find(from, start_pos)) != std::string::npos) {
			str.replace(start_pos, from.length(), to);
			start_pos += to.length();
		}
	}

	template <class T>
	static inline const string type2name(T o) {
		string s = string(abi::__cxa_demangle(typeid(o).name(),nullptr,nullptr,nullptr));
		strReplaceAll(s, string("std::"), string(""));			// Remove std:: from output
		strReplaceAll(s, string("Cryptography::"), string("")); // Remove Cryptography:: from output
		return s;
	}
}

namespace alloc {
	/**
	 *	Overloaded methods to allocate an array of T of size x, y, z.
	 */
	template <class T>
	static T* allocVar() {
		return new T();
	}

	template <class T>
	static T* allocArray(size_t x) {
		return new T[x]();
	}

	template <class T>
	static T** allocArray(size_t x, size_t y) {
		T **arr = new T*[x];
		for(size_t i = 0; i < x; i++) arr[i] = alloc::allocArray<T>(y);
		return arr;
	}

	template <class T>
	static T*** allocArray(size_t x, size_t y, size_t z) {
		T ***arr = new T**[x];
		for(size_t i = 0; i < x; i++) arr[i] = alloc::allocArray<T>(y, z);
		return arr;
	}
}


#endif // UTILS

