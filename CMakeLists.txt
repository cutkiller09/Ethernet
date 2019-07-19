cmake_minimum_required(VERSION 2.8)
set (CMAKE_ECLIPSE_VERSION 4.5.1)   
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(CMAKE_C_OUTPUT_EXTENSION_REPLACE 1) 

# Options
option(COVERAGE "Enable code coverage" OFF)

if (COVERAGE)
    add_definitions(--coverage)    
endif()

#--------------------------------------------------------------------------------------------------#
 
project(Library_LibBatMngBmv700) 

#--------------------------------------------------------------------------------------------------#
set (SRCS  
	./src/Library_LibBatMngBmv700.c
)

set (TI_SRCS 
	./test/TI_Library_LibBatMngBmv700.c
	./test/stub/Driver_SerialDriver.c
)  

set (TV_SRCS 
	./test/TV_Library_LibBatMngBmv700.c
) 

include_directories (
	../../02_Middleware/Library_StdLib/inc   
	./inc 
)
 
add_subdirectory(../../03_Driver Build_Driver) 

#--------------------------------------------------------------------------------------------------# 
add_executable(TI_LibBatMngBmv700 ${SRCS} ${TI_SRCS})  
target_include_directories (TI_LibBatMngBmv700 PRIVATE
							./test/stub/ )  	
target_link_libraries(TI_LibBatMngBmv700 --coverage)	 		
set_target_properties(TI_LibBatMngBmv700 PROPERTIES EXCLUDE_FROM_ALL TRUE)  

add_executable(TV_LibBatMngBmv700 ${SRCS} ${TV_SRCS})  
target_include_directories (TV_LibBatMngBmv700 PRIVATE
							../../03_Driver/Driver_SerialDriver/inc )  
target_link_libraries(TV_LibBatMngBmv700 Lib_SerialDriver m --coverage)	 				
set_target_properties(TV_LibBatMngBmv700 PROPERTIES EXCLUDE_FROM_ALL TRUE)  
 
#--------------------------------------------------------------------------------------------------#

add_library(Lib_LibBatMngBmv700 STATIC ${SRCS} )   
target_include_directories (Lib_LibBatMngBmv700 PRIVATE
							../../03_Driver/Driver_SerialDriver/inc ) 
target_link_libraries(Lib_LibBatMngBmv700 Lib_SerialDriver m )  

#--------------------------------------------------------------------------------------------------#

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(docLibBatMngBmv700
${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)

#--------------------------------------------------------------------------------------------------# 
