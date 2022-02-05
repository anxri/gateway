cmake_minimum_required(VERSION 3.18.4)

project(lacus-server)

set(CMAKE_BINARY_DIR ../../dist/dyn_dns_server)

set(CMAKE_CXX_STANDARD 17)

file(
        GLOB HEADER_FILES

        "./*.h" ,
        "../../include/*.h" ,
        "../*.h" ,
)

file(
        GLOB SOURCE_FILES

        "./*.cpp" ,
        "../../include/*.cpp" ,
)

include_directories(
        lacus-server PUBLIC

        ${CMAKE_CURRENT_SOURCE_DIR}
        ../../include
)


add_executable(lacus-server ./main.cpp ${HEADER_FILES} ${SOURCE_FILES} ../../include/aes.hpp ../../include/aes.c)
target_link_libraries(lacus-server stdc++fs)

