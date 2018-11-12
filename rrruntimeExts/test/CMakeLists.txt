set(BUILD_TITLE rrruntimeexttest)
add_library(${BUILD_TITLE} SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rrruntimeexttest.cpp
  )
target_compile_definitions(${BUILD_TITLE} PRIVATE _DLL_EXPORTS_)
