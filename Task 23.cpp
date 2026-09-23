#include <iostream>
 #include <windows.h>

 int main() {
 int x = 10; // Variable allocated on the stack
 MEMORY_BASIC_INFORMATION mbi{};

 // Ask the kernel for metadata about the page holding variable x
 if (VirtualQuery(&x, &mbi, sizeof(mbi)) != 0) {
 std::cout << "Address: " << mbi.BaseAddress << "\n";
 std::cout << "Region Size: " << mbi.RegionSize << " bytes\n";

 std::cout << "State: "
 << (mbi.State == MEM_COMMIT ? "MEM_COMMIT" : "OTHER")
 << "\n";
 }
 return 0;
 }