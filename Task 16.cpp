#include <iostream>
 #include <thread>
 #include <vector>
 #include <windows.h>

 HANDLE sem;

 void worker(int id) {
 // Decrement counter by 1. If counter reaches 0, thread sleeps here.
 WaitForSingleObject(sem, INFINITE);
 std::cout << "Thread " << id << " acquired resource.\n";

 Sleep(1000); // Simulate work using the shared resource

 std::cout << "Thread " << id << " releasing resource.\n";
 // Increment counter by 1 to wake up a waiting thread.
 ReleaseSemaphore(sem, 1, nullptr);
 }

 int main() {
 // Initial count = 2, Maximum count = 2
 sem = CreateSemaphoreA(nullptr, 2, 2, nullptr);

 std::vector<std::thread> threads;
 for (int i = 1; i <= 4; ++i) {
 threads.emplace_back(worker, i);
 }

 for (auto& t : threads) {
 t.join();
 }

 CloseHandle(sem);
 return 0;
 }