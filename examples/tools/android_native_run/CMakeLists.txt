find_package (JNI REQUIRED)
add_executable(android_native_run
 Main.cpp
 Options.cpp
 JVM.cpp
 )

add_subdirectory(android_symbols)
target_link_libraries(android_native_run PRIVATE QBDL dl AndroidSymbols ${JNI_LIBRARIES})
set_target_properties(android_native_run PROPERTIES  POSITION_INDEPENDENT_CODE ON)
target_include_directories(android_native_run PUBLIC ${JNI_INCLUDE_DIRS})




