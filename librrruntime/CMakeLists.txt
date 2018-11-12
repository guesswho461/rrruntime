set(BUILD_TITLE rrruntime)
add_library(${BUILD_TITLE} SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rrruntime.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/cRRRuntime.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/cRRMsgFramework.cpp
  )
target_compile_definitions(${BUILD_TITLE} PRIVATE _DLL_EXPORTS_)
target_include_directories(${BUILD_TITLE} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/inc
  )
target_link_libraries(${BUILD_TITLE}
  dl pthread
  /home/rabd/RADSRobotics/inc/fmt/lib/libfmt.so
  /home/rabd/RADSRobotics/inc/cppfs/lib/libcppassist.so
  /home/rabd/RADSRobotics/inc/cppfs/lib/libcppfs.so
  )
