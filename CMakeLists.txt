cmake_minimum_required(VERSION 3.20.0)

list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Zephyr REQUIRED HINTS ${ZEPHYR_BASE})
project(canlink)

target_sources(app PRIVATE
  src/duramax_codec.cpp
  src/duramax_store.cpp
  src/main.cpp

)

target_include_directories(app PRIVATE
  include
)
