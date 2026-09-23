#include <iostream>
 #include <windows.h>

 int main() {
 HANDLE hFile = CreateFileA("guard_test.txt",
 GENERIC_READ | GENERIC_WRITE,
 FILE_SHARE_READ | FILE_SHARE_WRITE,
 nullptr, CREATE_ALWAYS, 0, nullptr);
 if (hFile == INVALID_HANDLE_VALUE) return 1;

 // Lock bytes 0 through 100 exclusively

 if (LockFile(hFile, 0, 0, 100, 0)) {
 std::cout << "Byte range [0-100] locked successfully.\n";

 // Perform modifications safely here...

 UnlockFile(hFile, 0, 0, 100, 0);
 std::cout << "Byte range unlocked.\n";
 }
 CloseHandle(hFile);
 return 0;
 }