cmake_minimum_required(VERSION 3.20.0)
if(NOT CANLINK_SOURCE_DIR)
  get_filename_component(CANLINK_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../.." ABSOLUTE)
endif()
if(EXISTS ${CANLINK_SOURCE_DIR}/Kconfig)
  set(KCONFIG_ROOT ${CANLINK_SOURCE_DIR}/Kconfig)
endif()
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(canlink_native_integration)
set(CANLINK_SOURCES
  duramax_build.cpp duramax_codec.cpp duramax_store.cpp duramax_validate.cpp
  reacher_build.cpp reacher_codec.cpp reacher_store.cpp reacher_validate.cpp)
foreach(source IN LISTS CANLINK_SOURCES)
  target_sources(app PRIVATE ${CANLINK_SOURCE_DIR}/src/${source})
endforeach()
target_sources(app PRIVATE ${CANLINK_SOURCE_DIR}/src/main.cpp src/gateway_test.cpp)
set_source_files_properties(${CANLINK_SOURCE_DIR}/src/main.cpp PROPERTIES
  COMPILE_DEFINITIONS "main=canlink_gateway_main")
target_include_directories(app PRIVATE ${CANLINK_SOURCE_DIR}/include)
target_compile_options(app PRIVATE -Wframe-larger-than=4096)

if(EXISTS ${CANLINK_SOURCE_DIR}/src/can_diagnostics.cpp)
  target_sources(app PRIVATE ${CANLINK_SOURCE_DIR}/src/can_diagnostics.cpp)
endif()
