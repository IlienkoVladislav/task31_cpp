#include <windows.h>
#include <iostream>
#include <tchar.h>

void ПомилкаВиходу(const std::string& повідомлення) {
    std::cerr << повідомлення << " (error code: " << GetLastError() << ")" << std::endl;
    exit(EXIT_FAILURE);
}

int main() {
    HANDLE ВхіднийФайл = CreateFile(
        TEXT("D:\\Univer\\cpp\\task31\\input.txt"), 
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (ВхіднийФайл == INVALID_HANDLE_VALUE) {
        ПомилкаВиходу("Cant to open");
    }

    HANDLE ВихіднийФайл = CreateFile(
        TEXT("output.txt"),
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (ВихіднийФайл == INVALID_HANDLE_VALUE) {
        CloseHandle(ВхіднийФайл);
        ПомилкаВиходу("cannot create file");
    }

    const DWORD РозмірБуфера = 4096;
    char Буфер[РозмірБуфера];
    DWORD Прочитано = 0, Записано = 0;

    while (ReadFile(ВхіднийФайл, Буфер, РозмірБуфера, &Прочитано, NULL) && Прочитано > 0) {
        if (!WriteFile(ВихіднийФайл, Буфер, Прочитано, &Записано, NULL)) {
            CloseHandle(ВхіднийФайл);
            CloseHandle(ВихіднийФайл);
            ПомилкаВиходу("failed is read");
        }
    }

    if (GetLastError() != ERROR_SUCCESS && GetLastError() != ERROR_HANDLE_EOF) {
        CloseHandle(ВхіднийФайл);
        CloseHandle(ВихіднийФайл);
        ПомилкаВиходу("failed is input read");
    }

    CloseHandle(ВхіднийФайл);
    CloseHandle(ВихіднийФайл);

    std::cout << "file is created" << std::endl;
    return 0;
}
