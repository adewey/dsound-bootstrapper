#include <windows.h>

int APIENTRY DllMain(HMODULE hDLL, DWORD Reason, LPVOID Reserved)
{
	switch (Reason)
	{
	case DLL_PROCESS_ATTACH:
		{
			char ini_path[MAX_PATH] = { 0 };
			char * temp_path;
			/* get our current path so that we can load stuff from our settings */
			GetModuleFileNameA(hDLL, ini_path, MAX_PATH);
			temp_path = strrchr(ini_path, '\\');
			temp_path[1] = '\0';
			strcat_s(ini_path, MAX_PATH, "\\bootstrap.ini");
			char bootstrap_dll[MAX_PATH] = { 0 };
			GetPrivateProfileStringA("bootstrap", "dll", NULL, bootstrap_dll, MAX_PATH, ini_path);
			/* at this point we should be in process. we should load our bootstrapped dll here and unload ourselves */
			if (bootstrap_dll != NULL && bootstrap_dll[0] != NULL)
				LoadLibraryA(bootstrap_dll);
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
