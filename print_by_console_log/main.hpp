#pragma once
#include "xx_consolelog.hpp"

extern "C" {
	inline void EMSCRIPTEN_KEEPALIVE TestConsoleLog() {
        xx::ConsoleLog("hello", " js! ", 1.23, " ", 0xFFFFFFFFFFFFFFFFu, " ", 0x7FFFFFFFFFFFFFFF);
	}
}
