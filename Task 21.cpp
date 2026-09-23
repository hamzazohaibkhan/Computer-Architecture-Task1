#include <iostream>
 #include <thread>
 #include <windows.h>

 void pinnedWorker() {
 // Bitmask: bit 0 = Core 0 (value 1), bit 1 = Core 1 (value 2), etc.
 DWORD_PTR mask = 1;
 DWORD_PTR prev = SetThreadAffinityMask(GetCurrentThread(), mask);
 if (prev != 0) {
 std::cout << "Thread successfully bound to Core 0.\n";
 }
 }

 int main() {
 std::cout << "Available hardware cores: "
 << std::thread::hardware_concurrency() << "\n";

 std::thread t(pinnedWorker);
 t.join();
 return 0;
 }