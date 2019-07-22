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
 
project(Memory) 

#--------------------------------------------------------------------------------------------------#
set (SRCS  
	./src/Memory.c
) 

include_directories (   
	./inc 
)    

#--------------------------------------------------------------------------------------------------#

if(NOT TARGET Memory)
	add_library(Memory STATIC ${SRCS} )  
endif()    

#--------------------------------------------------------------------------------------------------#

# # add a target to generate API documentation with Doxygen
# find_package(Doxygen)
# if(DOXYGEN_FOUND)
# configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
# add_custom_target(docMemory
# ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
# WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
# COMMENT "Generating API documentation with Doxygen" VERBATIM
# )
# endif(DOXYGEN_FOUND)

#--------------------------------------------------------------------------------------------------#
