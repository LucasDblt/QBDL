find_package (JNI REQUIRED)

add_executable(toto  main.cpp)
target_link_libraries(toto PRIVATE QBDL dl ${JNI_LIBRARIES})
set_target_properties(toto PROPERTIES  POSITION_INDEPENDENT_CODE ON)
target_include_directories(toto PUBLIC ${JNI_INCLUDE_DIRS})
