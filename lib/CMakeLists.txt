# ===================================================================
# ulog dynamic link library

add_library(ulog SHARED ulog.cpp)

target_compile_definitions(ulog PUBLIC ULOG_DLL=1)
target_include_directories(ulog PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(ulog
  spdlog
)

install(TARGETS ulog)

# ===================================================================
# tester executable

if (ULOG_ENABLE_TESTER)
  add_executable(tester tester.cpp)
  target_include_directories(tester PUBLIC ${CMAKE_SOURCE_DIR}/include)

  target_link_libraries(tester
    ulog
  )

  install(TARGETS tester)
endif(ULOG_ENABLE_TESTER)
