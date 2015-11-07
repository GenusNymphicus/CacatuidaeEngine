#Cockatoo/
cmake_minimum_required(VERSION 2.8.11)
project(Cockatoo)

SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Wall ")
SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -Wall")


add_definitions(-DGLM_FORCE_RADIANS)

FIND_PACKAGE(OpenAL REQUIRED)

set(TEST_HEADER)

set(HEADER_FILES ${HEADER_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/include )  
set(LIBRARIES ${LIBRARIES}  ${OPENGL_glu_LIBRARY} ${OPENGL_gl_LIBRARY} pthread asound rt)

add_subdirectory(external)
add_subdirectory(src)



if(RUN_TESTS)
add_subdirectory(tests)
endif(RUN_TESTS)

set(HEADER_FILES ${HEADER_FILES} PARENT_SCOPE)	    
set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)
set(LIBRARIES ${LIBRARIES} PARENT_SCOPE)



 
