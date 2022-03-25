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


	// test
	//auto p = NewLogic();
	//std::cout << p << std::endl;
	//LogicPush(p, 1);
	//LogicPush(p, 2);
	//std::cout << LogicSize(p) << std::endl;
	//DeleteLogic(p);




//#include <iostream>
//
//int Fibonacci(int number)
//{
//	if (number <= 1)
//	{
//		return 1;
//	}
//	else
//	{
//		return Fibonacci(number - 2) + Fibonacci(number - 1);
//	}
//}
//
//#include <chrono>
//
//int main() {
//	auto tp = std::chrono::system_clock::now();
//	std::cout << Fibonacci(35) << std::endl;
//	auto tp2 = std::chrono::system_clock::now();
//	std::cout << std::chrono::duration_cast< std::chrono::milliseconds> (tp2 - tp).count() << std::endl;
//}





//#include <array>
//#include <string>
//#include <memory>
//#include <utility>
//#include <iostream>
//
//// ѭ�������ܹ��ߺ���
//inline static void strings_restore(std::string& tar, std::string const& key) {
//	int siz = (int)key.size();
//	auto buf = key.c_str();
//	int i = 0;
//	for (auto& c : tar) {
//		c ^= buf[i++];
//		if (i >= siz) i = 0;
//	}
//}
//
///***************************************************************************************/
//// ������
//
//// ȫ�־�̬ cstring ������
//inline static char const* CSTRINGS_a = nullptr;
//// ...
//
//// ������ѭ����� key string
//inline static std::string string_decode_key = "!@#$%^&*()";
//
//// ȫ�־�̬ string �洢��( ���ݸ��� key �������, ע�Ͳ���Ϊԭʼ�� )
//inline static std::string STRINGS_a = std::string("@");	// a
//// ...
//
//// ����ڴ�������һ�εĽ��ܺ���
//inline static void strings_restore() {
//	strings_restore(STRINGS_a, string_decode_key);
//	CSTRINGS_a = STRINGS_a.c_str();
//	// ...
//}
//
///***************************************************************************************/
//
//
//
//int main() {
//	strings_restore();
//
//	std::cout << CSTRINGS_a << std::endl;
//}
//





//#include <memory_resource>
//#include <memory>
//#include <vector>
//#include <algorithm>
//#include <iostream>
//#include <numeric>
//#include <array>
//
//namespace std {
//    template <class T, class A, class... Args>
//    shared_ptr<T> make_shared_pma(A&& a, Args&&... args) {
//        return std::allocate_shared<T, std::pmr::polymorphic_allocator<T>>(std::forward<A>(a), std::forward<Args>(args)...);
//    }
//}
//
//struct Foo {
//    std::string s;
//};
//
//int main() {
//    std::array<char, 256> buf;
//    buf.fill('_');
//
//    std::pmr::monotonic_buffer_resource pool(buf.data(), buf.size());
//
//    auto v = std::make_shared_pma<std::pmr::vector<char>>(&pool);
//
//    for (auto c = 'a'; c <= 'z'; ++c) {
//        v->push_back(c);
//    }
//    std::cout << "buffer contents:\n";
//    std::for_each(buf.begin(), buf.end(), [idx = 0](auto x) mutable { std::cout << (idx++) << "=" << x << ", "; });
//    std::cout << "\nvector contents:\n";
//    std::for_each(v->begin(), v->end(), [](auto x) mutable { std::cout << x ; });
//}






//#include <memory_resource>
//#include <memory>
//#include <vector>
//#include <algorithm>
//#include <iostream>
//#include <numeric>
//
//namespace std {
//    template <class T, class A, class... Args>
//    shared_ptr<T> make_shared_pma(A&& a, Args&&... args) {
//        return std::allocate_shared<T, std::pmr::polymorphic_allocator<T>>(std::forward<A>(a), std::forward<Args>(args)...);
//    }
//}
//
//int main() {
//    auto buffer_size = 2;
//    auto backup_size = 256;
//
//    auto buffer = std::make_unique<char[]>(buffer_size);
//    auto backup = std::make_unique<char[]>(backup_size);
//
//    std::fill_n(buffer.get(), buffer_size, '_');
//    std::fill_n(backup.get(), backup_size, '_');
//
//    auto upst = std::pmr::monotonic_buffer_resource(backup.get(), backup_size);
//    auto pool = std::pmr::monotonic_buffer_resource(buffer.get(), buffer_size, &upst);
//
//    auto v = std::make_shared_pma<std::pmr::vector<char>>(&pool);
//
//    for (auto c = 'a'; c <= 'z'; ++c) {
//        v->push_back(c);
//    }
//    std::cout << "main buffer contents:\n";
//    std::for_each_n(buffer.get(), buffer_size, [idx = 0](auto x) mutable { std::cout << (idx++) << " " << x << ", "; });
//    std::cout << "\nbackup buffer contents:\n";
//    std::for_each_n(backup.get(), backup_size, [idx = 0](auto x) mutable { std::cout << (idx++) << " " << x << ", "; });
//    std::cout << "\nvector contents:\n";
//    std::for_each(v->begin(), v->end(), [idx = 0](auto x) mutable { std::cout << (idx++) << " " << x << ", "; });
//}
