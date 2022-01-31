find_package (JNI REQUIRED)



add_executable(android_native_run
 main.cpp
 classpath.cpp
 classpath.h
 options.cpp
 options.h
 JVM.cpp
 JVM.h
 myfunctions.h
 myfunctions.cpp
 )


configure_file(path.h.in ${CMAKE_CURRENT_BINARY_DIR}/path.h @ONLY)


target_link_libraries(android_native_run PRIVATE QBDL dl ${JNI_LIBRARIES})


set_target_properties(android_native_run PROPERTIES  POSITION_INDEPENDENT_CODE ON)
target_include_directories(android_native_run PUBLIC ${JNI_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})




