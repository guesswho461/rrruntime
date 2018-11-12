# set google test src directory path
set(GTEST_SRC_DIR /usr/src/googletest/googletest)
set(GTEST_HEADER_DIR /usr/src/googletest/googletest/include)
include_directories(
  ${GTEST_SRC_DIR}
  ${GTEST_HEADER_DIR}
  )
# add sub directories
add_subdirectory(rrruntime)


