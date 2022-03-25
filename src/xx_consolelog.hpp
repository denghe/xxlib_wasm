#pragma once
#include <xx_em.hpp>

// for data exchange
inline char __consoleLogInBuf[32];
inline char __consoleLogOutBuf[16384];

// Requires functions provided by the environment
extern "C" {
	extern int DblToStr(double);
	extern int U64ToStr(uint64_t);
	extern int I64ToStr(int64_t);
	extern void CLStr(int);
	extern double DateNow();

	inline void* EMSCRIPTEN_KEEPALIVE GetCLIB() { return __consoleLogInBuf; }
	inline void* EMSCRIPTEN_KEEPALIVE GetCLOB() { return __consoleLogOutBuf; }
}

namespace xx {
	namespace Detail {

		template<typename T, typename ENABLED = void>
		struct Appends {
			static inline void Append(int& len, T&& v) {
				assert(false);
			}
		};

		template<typename T>
		void Append(int& len, T&& v) {
			Appends<T>::Append(len, std::forward<T>(v));
		}

		//   ≈‰ literal char[len] string
		template<typename T>
		struct Appends<T, std::enable_if_t<xx::IsLiteral_v<T>>> {
			static inline void Append(int& len, T const& v) {
				memcpy(__consoleLogOutBuf + len, v, sizeof(v) - 1);
				len += sizeof(v) - 1;
			}
		};

		//   ≈‰ std::string[_view]
		template<typename T>
		struct Appends<T, std::enable_if_t<std::is_base_of_v<std::string, T> || std::is_base_of_v<std::string_view, T>>> {
			static inline void Append(int& len, T const& v) {
				memcpy(__consoleLogOutBuf + len, v.data(), v.size());
				len += v.size();
			}
		};

		//   ≈‰À˘”– ˝◊÷
		template<typename T>
		struct Appends<T, std::enable_if_t<std::is_arithmetic_v<T>>> {
			static inline void Append(int& len, T const& v) {
				if constexpr (std::is_same_v<bool, T>) {
					if (v) {
						memcpy(__consoleLogOutBuf + len, "true", 4);
						len += 4;
					}
					else {
						memcpy(__consoleLogOutBuf + len, "false", 5);
						len += 5;
					}
				}
				else if constexpr (std::is_same_v<char, T>) {
					__consoleLogOutBuf[len++] = v;
				}
				else if constexpr (std::is_floating_point_v<T> || (std::is_integral_v<T> && sizeof(T) < 8)) {
					int siz = DblToStr(v);
					memcpy(__consoleLogOutBuf + len, __consoleLogInBuf, siz);
					len += siz;
				}
				else {
					int siz;
					if constexpr (std::is_signed_v<T>) {
						siz = I64ToStr(v);
					}
					else {
						siz = U64ToStr(v);
					}
					memcpy(__consoleLogOutBuf + len, __consoleLogInBuf, siz);
					len += siz;
				}
			}
		};
	}

	template<typename...Args>
	inline void ConsoleLog(Args&&...args) {
		int len = 0;
		(Detail::Append(len, std::forward<Args>(args)), ...);
		CLStr(len);
	}
}

/*

=============================================================
js env
=============================================================

const td = new TextDecoder();
const te = new TextEncoder();

let memRoot = null;
let clib = null;
let clob = null;

const n2s = (n) => {
	let a = te.encode(n.toString());
	clib.set(a, 0, a.byteLength);
	return a.byteLength;
};

const imo = {
	env: {
		DblToStr: n2s,
		I64ToStr: n2s,
		U64ToStr: (n) => {
			return n2s(BigInt.asUintN(64, n));
		},
		CLStr: (len) => {
			console.log(td.decode(clob.slice(0, len)));
		},
		DateNow: function() {
			return Date.now();
		},
	},
};

const wa = (await WebAssembly.instantiateStreaming(fetch('main.wasm'), imo)).instance.exports;

memRoot = wa.memory.buffer;
clib = new Uint8Array(memRoot, wa.GetCLIB(), 32);
clob = new Uint8Array(memRoot, wa.GetCLOB(), 16384);

=============================================================
cpp env
=============================================================

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

init() {
	__clib = (char*)GetCLIB();
	__clob = (char*)GetCLOB();
}

*/