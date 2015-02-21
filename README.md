# dsound-bootstrapper
An easy way to load a specified DLL file into the memory of a program that loads dsound.dll by default but doesn't use it.


usage:

build and put dsound.dll and bootstrap.ini in the folder your program would load from
edit bootstrap.ini under `[bootstrap]` change `dll=some_other_dll.dll` to your dll name you want to load
