#include <iostream>
 #include <windows.h>

 int main() {
 HANDLE hFile = CreateFileA("async.bin", GENERIC_WRITE, 0, nullptr,
 CREATE_ALWAYS, FILE_FLAG_OVERLAPPED, nullptr);
 if (hFile == INVALID_HANDLE_VALUE) return 1;

 OVERLAPPED ol{};
 ol.hEvent = CreateEventA(nullptr, TRUE, FALSE, nullptr);
 char buffer[1024] = "Asynchronous file write data packet.";

 // Non-blocking write: immediately hands control back to CPU
 WriteFile(hFile, buffer, sizeof(buffer), nullptr, &ol);
 std::cout << "I/O initiated. Doing computation in parallel...\n";

 // Wait only when we actually require confirmation from disk
 WaitForSingleObject(ol.hEvent, INFINITE);
 std::cout << "Asynchronous write fully committed.\n";

 CloseHandle(ol.hEvent);
 CloseHandle(hFile);
 return 0;
 }