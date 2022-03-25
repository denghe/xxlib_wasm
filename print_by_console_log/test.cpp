#include "main.hpp"
#include <iostream>
#include <chrono>

inline char* __clib;
inline char* __clob;

extern "C" {
	inline int I64ToStr(int64_t v) {
		return sprintf_s(__clib, 32, "%lld", v);
	};
	inline int U64ToStr(uint64_t v) {
		return sprintf_s(__clib, 32, "%llu", v);
	};
	inline int DblToStr(double v) {
		return sprintf_s(__clib, 32, "%.16g", v);
	};
	inline void CLStr(int v) {
		std::cout << std::string_view(__clob, v) << std::endl;
	};
	inline double DateNow() { using namespace std::chrono; return (double)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count(); };
}

int main() {
	__clib = (char*)GetCLIB();
	__clob = (char*)GetCLOB();

	TestConsoleLog();
}
