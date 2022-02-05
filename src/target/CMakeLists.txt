cmake_minimum_required(VERSION 3.18.4)
project(lacus-target)

set(CMAKE_BINARY_DIR ../../dist/lacus-target)

set(CMAKE_CXX_STANDARD 17)

file(
        GLOB HEADER_FILES

        "./*.h" ,
        "../../include/*.h" ,
)

file(
        GLOB SOURCE_FILES

        "./*.cpp" ,
        "../../include/*.cpp" ,
)

include_directories(
        lacus-target PUBLIC

        ${CMAKE_CURRENT_SOURCE_DIR}
        ../../include
)


add_executable(lacus-target ./main.cpp ${HEADER_FILES} ${SOURCE_FILES} ../../include/aes.hpp ../../include/aes.c)
target_link_libraries(lacus-target stdc++fs -lpthread)
