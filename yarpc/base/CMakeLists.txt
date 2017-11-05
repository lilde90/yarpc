cmake_minimum_required(VERSION 2.6)
set (base_src
  )
add_library(yarpc_base ${base_src})
target_link_libraries(yarpc_base pthread rt)

