#include <iostream>
 #include <thread>
 #include <vector>

 // Each thread receives its own completely independent copy of localVal
 thread_local int localVal = 0;

 void run(int offset) {
 localVal += offset; // Modifies only THIS thread’s private copy
 std::cout << "Thread ID: " << std::this_thread::get_id()
 << " | localVal = " << localVal << "\n";
 }

 int main() {
 std::thread t1(run, 10);
 std::thread t2(run, 20);
 std::thread t3(run, 30);

 t1.join();
 t2.join();
 t3.join();
 return 0;
 }