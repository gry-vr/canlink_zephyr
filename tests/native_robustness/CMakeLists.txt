cmake_minimum_required(VERSION 3.20.0)
get_filename_component(CANLINK_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../.." ABSOLUTE)
set(KCONFIG_ROOT ${CANLINK_SOURCE_DIR}/Kconfig)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(canlink_robustness)
target_sources(app PRIVATE src/main.cpp
 ${CANLINK_SOURCE_DIR}/src/reacher_build.cpp
 ${CANLINK_SOURCE_DIR}/src/reacher_store.cpp
 ${CANLINK_SOURCE_DIR}/src/reacher_codec.cpp
 ${CANLINK_SOURCE_DIR}/src/reacher_validate.cpp)
target_include_directories(app PRIVATE ${CANLINK_SOURCE_DIR}/include)
target_compile_options(app PRIVATE -Wframe-larger-than=4096)

if(EXISTS ${CANLINK_SOURCE_DIR}/src/can_diagnostics.cpp)
  target_sources(app PRIVATE ${CANLINK_SOURCE_DIR}/src/can_diagnostics.cpp)
endif()
