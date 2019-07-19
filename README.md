#Ethernet ICMP Library for ping

#Integration tests

An Integration file inside test directory is created.
His name is TI_Service_BatteryManager.c.
This file contain the "main" to test and validate module. 
The executable generated is the integration test executable.

##Cmake Usage

To create Cmake files, launch shell command :
	terminal$ cd build
	terminal$ cmake -G Eclipse\ CDT4\ -\ Unix\ Makefiles ..

##Compilation

launch shell command :
	terminal$ make all

##Execution	

A new Executable is created under build directory, launch it using shell command 
	terminal$ ./BatteryManagerService

##Documentation	

To Generate html and latex documentatin from doxygen code tags, launch it using shell command
	terminal$ make docBatteryManager
