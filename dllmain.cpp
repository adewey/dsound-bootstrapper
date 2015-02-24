#include <windows.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
int APIENTRY DllMain(HMODULE hDLL, DWORD Reason, LPVOID Reserved)
{
	switch (Reason)
	{
	case DLL_PROCESS_ATTACH:
	{
		std::ofstream myFile;
		myFile.open("gemini/loader_log.txt");
		myFile << "Log: Loader Loaded!" << std::endl;
		char ini_path[MAX_PATH] = { 0 };
		char * temp_path;
		struct stat buffer;
		/* get our current path so that we can load stuff from our settings */
		GetModuleFileNameA(hDLL, ini_path, MAX_PATH);
		temp_path = strrchr(ini_path, '\\');
		temp_path[1] = '\0';
		myFile << "Log: INI Path: " << temp_path << std::endl;
		strcat_s(ini_path, MAX_PATH, "\\bootstrap.ini");
		char bootstrap_dll[MAX_PATH] = { 0 };
		GetPrivateProfileStringA("bootstrap", "dll", NULL, bootstrap_dll, MAX_PATH, ini_path);
		myFile << "Log: BootStrap DLL - " << bootstrap_dll << std::endl;
		/* at this point we should be in process. we should load our bootstrapped dll here and unload ourselves */
		if (bootstrap_dll != NULL && bootstrap_dll[0] != NULL){
			if (stat(bootstrap_dll, &buffer) == 0){
				myFile << "Log: Should have injected the game " << std::endl;
				LoadLibraryA(bootstrap_dll);
			}
			else{
				myFile << "Log: stat() NEQ 0" << std::endl;
			}
		}
		else{
			myFile << "Log: Bootstrap DLL is NULL" << std::endl;
		}
	}
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}

	return TRUE;
}
