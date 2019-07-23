# Ethernet ICMP Library for ping

# Integration tests

An Integration file inside test directory is created.
His name is TI_Icmp.c.
This file contain the "main" to test and validate module.
The executable generated is the integration test executable.

## Cmake Usage

To create Cmake files, launch shell command :
```	
terminal$ cd build
terminal$ cmake .. 
```

## Compilation

launch shell command :
```	
terminal$ make all 
```

## Execution	

A new Library is created LibIcmp.a 

## Test	

A new Integration test is created TI_Icmp
```	
terminal$ cd build
terminal$ make TI_ICMP 
terminal$ ./TI_Icmp 
```

