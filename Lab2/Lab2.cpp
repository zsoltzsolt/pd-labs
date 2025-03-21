#include <windows.h>
#include <stdio.h>

int main() {
    SIZE_T dwSize = 1024 * 1024;

    // Alocare virtual memory
    // Documentation: https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualalloc
    LPVOID lpMemory = VirtualAlloc(NULL, dwSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (lpMemory == NULL) {
        printf("Memory allocation failed");
        return 1;
    }

    // Eliberare virtual memory
    // Documentation: https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualfree
    if (!VirtualFree(lpMemory, 0, MEM_RELEASE)) {
        printf("Memory deallocation failed");
        return 1;
    }

    return 0;
}
