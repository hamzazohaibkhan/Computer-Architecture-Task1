#include <iostream>
 #include <thread>
 #include <windows.h>

 void clientWorker() {
 Sleep(500); // Wait for the pipe server to get ready
 HANDLE hClient = CreateFileA("\\\\.\\pipe\\TestPipe",
 GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
 if (hClient != INVALID_HANDLE_VALUE) {
 const char msg[] = "Hello through Named Pipe!";
 DWORD written = 0;
 WriteFile(hClient, msg, sizeof(msg), &written, nullptr);
 CloseHandle(hClient);
 }
 }

 int main() {
 HANDLE hServer = CreateNamedPipeA("\\\\.\\pipe\\TestPipe",
 PIPE_ACCESS_INBOUND,
 PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
 1, 512, 512, 0, nullptr);

 std::thread client(clientWorker);
 ConnectNamedPipe(hServer, nullptr); // Wait for incoming connection

 char buffer[128] = {};
 DWORD readBytes = 0;
 ReadFile(hServer, buffer, sizeof(buffer) - 1, &readBytes, nullptr);
 std::cout << "Server received: " << buffer << "\n";

 client.join();
 DisconnectNamedPipe(hServer);
 CloseHandle(hServer);
 return 0;
 }