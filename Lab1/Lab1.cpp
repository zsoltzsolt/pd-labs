#include <windows.h>
#include <tchar.h>
#include <stdio.h>

void PrintImagePaths() {
    HKEY hKey, hSubKey;
    TCHAR subKeyName[256];
    DWORD subKeySize=256;
    DWORD index = 0;
    FILETIME ftLastWriteTime;

    // Doc -> https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regopenkeyexa 
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services"), 0L, KEY_READ, &hKey) != ERROR_SUCCESS) {
        printf("Eroare deaschidere registry!\n");
        return;
    }

    // Doc -> https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regenumkeyexa 
    while ((RegEnumKeyEx(hKey, index++, subKeyName, &subKeySize, NULL, NULL, NULL, &ftLastWriteTime)) != ERROR_NO_MORE_ITEMS) {
        subKeySize = 256;

        // Doc -> https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regopenkeyexa 
        if (RegOpenKeyEx(hKey, subKeyName, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS) {
            TCHAR imagePath[512];
            DWORD imagePathSize = sizeof(imagePath);
            DWORD type;
            TCHAR typeData[512];

            // Doc -> https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regqueryvalueexa 
            if (RegQueryValueEx(hSubKey, TEXT("ImagePath"), NULL, &type, (LPBYTE)imagePath, &imagePathSize) == ERROR_SUCCESS) {
                _tprintf(TEXT("Subcheie: %s\nImagePath: %s\n\n"), subKeyName, imagePath);
            }
            RegCloseKey(hSubKey);
        }
    }
    RegCloseKey(hKey);
}

int _tmain(void) {
    PrintImagePaths();
    return 0;
}
