
#include "JVM.h"
#include <iostream>
#include <jni.h>
#include <utility>

using namespace std;

pair<JavaVM *, JNIEnv *> createJVM(JavaOption const &opt) {

  JavaVMOption jVMOpt[2];
  jVMOpt[0].optionString = const_cast<char *>(opt.classPath.c_str());
  jVMOpt[1].optionString = const_cast<char *>(opt.libraryPath.c_str());
  JavaVMInitArgs vmArgs;
  vmArgs.version = JNI_VERSION_1_6;
  vmArgs.nOptions = 2;
  vmArgs.options = jVMOpt;
  vmArgs.ignoreUnrecognized = JNI_TRUE;

  // Create the JVM
  JavaVM *javaVM;
  JNIEnv *jniEnv;
  long flag = JNI_CreateJavaVM(&javaVM, (void **)&jniEnv, &vmArgs);
  if (flag == JNI_ERR) {
    cout << "Error creating VM. Exiting...";
    abort();
  }

  return {javaVM, jniEnv};
}
