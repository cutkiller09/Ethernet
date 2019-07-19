cmake_minimum_required(VERSION 2.8)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

# Options
option(COVERAGE "Enable code coverage" OFF)

if (COVERAGE)
    add_definitions(--coverage)    
endif()

#--------------------------------------------------------------------------------------------------#
 
project(Service_BatteryManager) 

set (SRCS  
	./src/Service_BatteryManager.c
	../../02_Middleware/Library_StdLib/src/Library_StdLib.c
)

set (TI_SRCS 
	./test/TI_Service_BatteryManager.c
	./test/stub/Driver_SerialDriver.c
)  

set (TV_SRCS 
	./test/TV_Service_BatteryManager.c
) 

include_directories (
	../../02_Middleware/Library_StdLib/inc   
	../../02_Middleware/Library_LibBatMngBmv700/inc   
	./inc 
)
  
add_subdirectory(../../02_Middleware Build_Middleware)  

#--------------------------------------------------------------------------------------------------# 

add_executable(TI_SrvBatMngBmv700 ${SRCS} ${TI_SRCS})  
target_include_directories (TI_SrvBatMngBmv700 PRIVATE
							./test/stub/ )  	
target_link_libraries(TI_SrvBatMngBmv700 
						Lib_LibBatMngBmv700
						--coverage)	 		
set_target_properties(TI_SrvBatMngBmv700 PROPERTIES EXCLUDE_FROM_ALL TRUE)  

add_executable(TV_SrvBatMngBmv700 ${SRCS} ${TV_SRCS})  
target_include_directories (TV_SrvBatMngBmv700 PRIVATE
							Lib_LibBatMngBmv700
							../../03_Driver/Driver_SerialDriver/inc )  
target_link_libraries(TV_SrvBatMngBmv700 
						Lib_SerialDriver 
						m 
						Lib_LibBatMngBmv700
						--coverage)	 	 				
set_target_properties(TV_SrvBatMngBmv700 PROPERTIES EXCLUDE_FROM_ALL TRUE)   

#--------------------------------------------------------------------------------------------------#

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(docBatteryManager
${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)

#--------------------------------------------------------------------------------------------------#
