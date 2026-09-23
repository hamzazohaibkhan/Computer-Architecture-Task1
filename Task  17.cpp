#include <iostream>
#include <thread>
#include <vector>
 #include <windows.h>

 HANDLE startEvent;

 void worker(int id) {
 // All workers sleep here at the barrier until the signal is set.
 WaitForSingleObject(startEvent, INFINITE);
 std::cout << "Worker " << id << " triggered!\n";
 }

 int main() {
 // bManualReset = TRUE (stays open), bInitialState = FALSE (starts locked)
 startEvent = CreateEventA(nullptr, TRUE, FALSE, nullptr);

 std::vector<std::thread> workers;
 for (int i = 1; i <= 3; ++i) {
 workers.emplace_back(worker, i);
 }

 std::cout << "Waiting 1 second before broadcasting start signal...\n";
 Sleep(1000);

 // Turn green: wakes ALL waiting threads simultaneously
 SetEvent(startEvent);

 for (auto& t : workers) {
 t.join();
 }

 CloseHandle(startEvent);
 return 0;
 }