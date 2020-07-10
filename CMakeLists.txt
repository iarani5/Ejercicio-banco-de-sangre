cmake_minimum_required(VERSION 3.12)
project(FINAL)

set(CMAKE_CXX_STANDARD 14)
include_directories(/usr/local/include/StanfordCPPLib/)

add_executable(FINAL main.cpp Persona.cpp Persona.h Receptor.cpp Receptor.h Donante.cpp Donante.h Validacion.cpp Validacion.h LinkedList.cpp LinkedList.h)
target_link_libraries(FINAL /usr/local/lib/libStanfordCPPLib.a)

