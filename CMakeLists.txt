cmake_minimum_required(VERSION 3.10.2)

project(GrowtopiaServer CXX)

set(CMAKE_CXX_STANDARD 14)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

file (GLOB srcfiles
        api/api.h
	src/*.c* src/*.h*)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

add_library(GrowtopiaServerModule MODULE ${srcfiles})

target_compile_options(GrowtopiaServerModule PRIVATE -shared-libgcc -fPIC -shared -rdynamic)

target_link_libraries(GrowtopiaServerModule ${CMAKE_DL_LIBS})
