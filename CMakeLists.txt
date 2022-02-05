cmake_minimum_required(VERSION 3.21)
project(dyn_dns)

add_subdirectory(src/server)
add_subdirectory(src/target)

target_link_libraries(dyn_dns_target stdc++fs -lpthread )