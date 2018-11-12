cmake_minimum_required(VERSION 2.8)

project(rrruntime)

# options
# verbos makefile option
option(VERBOS_MAKEFILE "verbose makefile" OFF)
# release build option
option(RELEASE_BUILD "build with -O3" OFF)

# set the position independent code property on all targets
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# manage the dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
# set verbose makefile
set(CMAKE_VERBOSE_MAKEFILE VERBOS_MAKEFILE)
# add global include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common/inc)
# add global link path
link_directories(${OUTPUT_DIR})
# set compiler option
if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  message("config for gnu toolchain")
  if(RELEASE_BUILD)
    add_definitions(-O3)
    set(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin/linux/release)
  else()
    add_definitions(-g3)
    set(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin/linux/debug)
  endif()
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=gnu++11)
  set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -std=c99)
  add_definitions(
    -D_USING_LINUX_
    -D_ARCH_X86_64_
    -D_USING_GNU_
    -D_LUA_REDIRECTION_
    -fpack-struct=16 # 16 bytes alignment
    -Wall # enables all the warnings
    -malign-double
    )
else()
  message(FATAL_ERROR "un-support tool chain")
endif()

# set output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
message("set output directory to " ${OUTPUT_DIR})

# add sub directories
add_subdirectory(librrruntime)
add_subdirectory(rrruntimeMain)
add_subdirectory(tests)
add_subdirectory(rrruntimeExts)
