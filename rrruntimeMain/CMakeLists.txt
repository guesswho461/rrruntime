set(BUILD_TITLE rrruntimeMain)
add_executable(${BUILD_TITLE}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  )
target_include_directories(${BUILD_TITLE} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/inc
  )
target_link_libraries(${BUILD_TITLE}
  pthread gflags glog fmt
  rrruntime
  )
