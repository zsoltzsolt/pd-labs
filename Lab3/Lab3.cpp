#include <windows.h>
#include <setupapi.h>
#include <initguid.h>
#include <devguid.h>
#include <regstr.h>
#include <iostream>
#include <string>
#include <cfgmgr32.h>

#pragma comment(lib, "cfgmgr32.lib")
#pragma comment(lib, "setupapi.lib")

#define MAX_DEVICE_ID_LEN 200

int main() {
    HDEVINFO deviceInfoSet = SetupDiGetClassDevs(
        NULL,
        L"USB",
        NULL,
        DIGCF_PRESENT | DIGCF_ALLCLASSES
    );

    if (deviceInfoSet == INVALID_HANDLE_VALUE) {
        std::cerr << "Eroare la SetupDiGetClassDevs\n";
        return 1;
    }

    SP_DEVINFO_DATA devInfoData;
    devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    TCHAR deviceInstanceId[MAX_DEVICE_ID_LEN];
    DWORD deviceIndex = 0;

    while (SetupDiEnumDeviceInfo(deviceInfoSet, deviceIndex, &devInfoData)) {
        deviceIndex++;

        if (CM_Get_Device_ID(devInfoData.DevInst, deviceInstanceId, MAX_DEVICE_ID_LEN, 0) != CR_SUCCESS)
            continue;

        std::wcout << L"\nDispozitiv [" << deviceIndex << L"] - ID: " << deviceInstanceId << std::endl;

        TCHAR buffer[1024];
        if (SetupDiGetDeviceRegistryProperty(
            deviceInfoSet,
            &devInfoData,
            SPDRP_FRIENDLYNAME,
            NULL,
            (PBYTE)buffer,
            sizeof(buffer),
            NULL)) {
            std::wcout << L"  Friendly name: " << buffer << std::endl;
        }
        else if (SetupDiGetDeviceRegistryProperty(
            deviceInfoSet,
            &devInfoData,
            SPDRP_DEVICEDESC,
            NULL,
            (PBYTE)buffer,
            sizeof(buffer),
            NULL)) {
            std::wcout << L"  Device description: " << buffer << std::endl;
        }
        else {
            std::wcout << L"  [!] Nume necunoscut." << std::endl;
        }
    }

    SetupDiDestroyDeviceInfoList(deviceInfoSet);
    return 0;
}
