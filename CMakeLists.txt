cmake_minimum_required(VERSION 3.20)

project(SistemaElectoral)

set(CMAKE_CXX_STANDARD 20)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(SistemaElectoral
        main.cpp
)

target_link_libraries(SistemaElectoral PRIVATE cryptopp)