#include <iostream>
 #include <future>
 #include <chrono>
 #include <thread>

 int main() {
 // Dispatch work to run in the background
 std::future<double> task = std::async(std::launch::async, []() {
 std::this_thread::sleep_for(std::chrono::seconds(1));
 return 3.14159;
 });

 std::cout << "Main thread continues work while async task computes...\n";

 // .get() pauses execution only until the result is ready
 double result = task.get();
 std::cout << "Result received: " << result << "\n";
 return 0;
 }