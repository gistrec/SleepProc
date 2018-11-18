#include "process.h"
#include "process_table_model.h"

// 1. Получаем дескриптор открытого процесса
// 2. Получаем все модули процесса
// 3. Получаем имя процесса
// 4. Вызываем функцию refresh() для обновления данных
Process::Process(uint id) {
    // Получаем название процесса
    TCHAR processName[MAX_PATH] = TEXT("<unknown>");

    // Получаем дескриптор открытого процесса
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, id);

    if (hProcess != NULL) {
        HMODULE hMod;
        DWORD cbNeeded;

        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
            GetModuleBaseName(hProcess, hMod, processName, sizeof(processName)/sizeof(TCHAR));
        }
    }
    name = QString::fromWCharArray(processName);

    CloseHandle( hProcess ); // Освобождаем дескриптор процесса
    refresh(); // Обновляем CPUUsage и MemoryUsage
}

// 1. Получаем дескриптор открытого процесса
// 2. Получаем все модули процесса
// 3. Получаем RAM Usage
// 4. Получаем CPU Usage
bool Process::refresh() {
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, id);
    if (hProcess == NULL) return false;

    HMODULE hMod;
    DWORD cbNeeded;

    if (!EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) return false;

    // RAM Usage
    PROCESS_MEMORY_COUNTERS memCounter;
    GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter));
    MemoryUsage = memCounter.WorkingSetSize;

    // TODO: Получить информацию о CPU Usage
    return true;
}

const QString& Process::getName() const {
    return name;
}

uint Process::getId() const {
    return id;
}

uint Process::getCPUUsage() const {
    return CPUUsage;
}
uint Process::getMemoryUsage() const {
    return MemoryUsage;
}
