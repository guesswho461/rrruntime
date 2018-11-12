set(BUILD_TITLE rrruntimeTest)
add_executable(${BUILD_TITLE}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${GTEST_SRC_DIR}/src/gtest-all.cc
  )
target_include_directories(${BUILD_TITLE} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/inc
  )
target_link_libraries(${BUILD_TITLE}
  rrruntime
  )
