cmake_minimum_required(VERSION 2.8)
set (CMAKE_ECLIPSE_VERSION 4.5.1)   
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -ggdb -O0 -Wunreachable-code")

set(CMAKE_C_OUTPUT_EXTENSION_REPLACE 1) 

# Options
option(COVERAGE "Enable code coverage" OFF)

if (COVERAGE)
    add_definitions(--coverage)    
endif()

#--------------------------------------------------------------------------------------------------#
 
project(Icmp) 

#--------------------------------------------------------------------------------------------------#
set (SRCS  
	./src/Icmp.c
)

set (TI_SRCS 
	./test/TI_Icmp.c
	./test/stub/LAN9250.c
	./test/stub/LAN9250_SPI.c
	./test/stub/Memory.c
)  

set (TV_SRCS 
	./test/TV_Icmp.c
) 

include_directories ( 
	./inc  
)
 
add_subdirectory(../driver_LAN9250 Build_Driver)  
add_subdirectory(../Memory_lib Build_Lib) 

#--------------------------------------------------------------------------------------------------# 
add_executable(TI_Icmp ${SRCS} ${TI_SRCS})  
target_include_directories (TI_Icmp PRIVATE
							./test/stub/
							../Memory_lib/inc
							../driver_LAN9250/inc  )  	
target_link_libraries(TI_Icmp --coverage)	  

set_target_properties(TI_Icmp PROPERTIES EXCLUDE_FROM_ALL TRUE)    
 
#--------------------------------------------------------------------------------------------------#

add_library(Lib_Icmp STATIC ${SRCS} )   
target_include_directories (Lib_Icmp PRIVATE
							../driver_LAN9250/inc ) 
target_link_libraries(Lib_Icmp LAN9250 m )   

target_include_directories (Lib_Icmp PRIVATE
							../Memory_lib/inc ) 
target_link_libraries(Lib_Icmp Memory m )  

#--------------------------------------------------------------------------------------------------#

# # add a target to generate API documentation with Doxygen
# find_package(Doxygen)
# if(DOXYGEN_FOUND)
# configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
# add_custom_target(docIcmp
# ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
# WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
# COMMENT "Generating API documentation with Doxygen" VERBATIM
# )
# endif(DOXYGEN_FOUND)

#--------------------------------------------------------------------------------------------------# 
