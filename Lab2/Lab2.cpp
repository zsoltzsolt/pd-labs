#include <windows.h>
#include <stdio.h>

int main() {
    int numBlocks = 0;

    printf("Cate blocuri de 1MB vrei sa aloci? ");
    if (scanf_s("%d", &numBlocks) != 1 || numBlocks <= 0) {
        printf("Input invalid.\n");
        return 1;
    }

    SIZE_T blockSize = 1024 * 1024; // 1MB
    SIZE_T totalSize = blockSize * numBlocks;

    // Alocare memorie -> https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualalloc
    LPVOID lpMemory = VirtualAlloc(NULL, totalSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (lpMemory == NULL) {
        printf("Eroare la alocarea memoriei (%lu bytes)\n", totalSize);
        return 1;
    }

    printf("Am alocat %d MB de memorie la adresa: %p\n", numBlocks, lpMemory);

    // Eliberare memorie -> https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualfree
    if (!VirtualFree(lpMemory, 0, MEM_RELEASE)) {
        printf("Eroare la eliberarea memoriei.\n");
        return 1;
    }

    printf("Memoria a fost eliberata cu succes.\n");

    return 0;
}
