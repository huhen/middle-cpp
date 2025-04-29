#include <windows.h>
#include <print>
#include <processthreadsapi.h>
#include <handleapi.h>
#include <wil/resource.h>

void test() {
    wil::unique_process_handle hProcess(OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId()));

    // HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
    // if (hProcess) {
    //     CloseHandle(hProcess);
    // }
}

int main() {
    std::print("Hello!\n");
    test();
    std::print("Exit\n");

    return 0;
}


