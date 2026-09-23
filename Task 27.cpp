#include <iostream>
 #include <windows.h>

 int main() {
 volatile long count = 0;
 for (long i = 0; i < 200000000; ++i) { count += i; }

 FILETIME createTime, exitTime, kernelTime, userTime;
 GetProcessTimes(GetCurrentProcess(),
 &createTime, &exitTime, &kernelTime, &userTime);

 ULARGE_INTEGER kTime, uTime;
 kTime.LowPart = kernelTime.dwLowDateTime;
 kTime.HighPart = kernelTime.dwHighDateTime;
 uTime.LowPart = userTime.dwLowDateTime;
 uTime.HighPart = userTime.dwHighDateTime;

 // Convert 100-nanosecond units to milliseconds (/ 10,000)
 std::cout << "Kernel Time (Ring 0): "
 << kTime.QuadPart / 10000 << " ms\n";
 std::cout << "User Time (Ring 3): "
 << uTime.QuadPart / 10000 << " ms\n";
 return 0;
 }