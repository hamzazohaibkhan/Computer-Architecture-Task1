#include <iostream>
 #include <windows.h>

 int main() {
 char* page = (char*)VirtualAlloc(nullptr, 4096,
 MEM_COMMIT, PAGE_READWRITE);
 page[0] = ’A’; // Normal write works fine

 // Downgrade page permissions to READ-ONLY at the hardware level
 DWORD oldProtect;
 VirtualProtect(page, 4096, PAGE_READONLY, &oldProtect);

 __try {
 page[0] = ’B’; // CPU intercepts illegal write!
 }
 __except (EXCEPTION_EXECUTE_HANDLER) {
 std::cout << "Hardware memory protection trap caught!\n";
 }

 VirtualFree(page, 0, MEM_RELEASE);
 return 0;
 }