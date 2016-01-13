#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <iostream>


void PrintProcessNameAndID(DWORD processID)
{
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

	
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);

	if (NULL != hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;

		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
			&cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, szProcessName,
				sizeof(szProcessName) / sizeof(TCHAR));
		}
	}

	
	_tprintf(TEXT("%s  (PID: %u)\n"), szProcessName, processID);
	if (!SetPriorityClass(hProcess, BELOW_NORMAL_PRIORITY_CLASS) == 0) std::cout << " <Error> ";
	else std::cout << " <- Priority is changed!";
	// Release the handle to the process.

	CloseHandle(hProcess);
}

int main(void)
{
	// Get the list of process identifiers.

	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;
	while (true){
		if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
		{
			return 1;
		}


		
		cProcesses = cbNeeded / sizeof(DWORD);

		
		for (i = 0; i < cProcesses; i++)
		{
			if (aProcesses[i] != 0)
			{


				PrintProcessNameAndID(aProcesses[i]);


			}
		}
		Sleep(5000);
	}
	system("pause");
	return 0;
}
