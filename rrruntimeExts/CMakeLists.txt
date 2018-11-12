# set output path of rrruntime extensions
set(EXT_OUTPUT_DIR ${OUTPUT_DIR}/exts)
# set output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXT_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${EXT_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${EXT_OUTPUT_DIR})
message("set extensions output directory to " ${EXT_OUTPUT_DIR})
# set include header
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/inc
  )
# add sub directories
add_subdirectory(test)


