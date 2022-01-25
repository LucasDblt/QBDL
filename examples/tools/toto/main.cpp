#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dlfcn.h>
#include <unistd.h>
#include <stdarg.h>
#include <iostream>
#include <jni.h>
#include <string>



#include <LIEF/LIEF.hpp>
#include <QBDL/Engine.hpp>
#include <QBDL/engines/Native.hpp>
#include <QBDL/loaders/ELF.hpp>

using namespace QBDL;
using namespace std;


int main(int argc, char **argv) {
  cout << "coucou\n";
  JavaVMOption jvmopt[1];
  string javaOption = string{"-Djava.class.path=\"/home/lucas/dev/QBDL/examples/tools/toto/\""};
  jvmopt[0].optionString = const_cast<char*>(javaOption.c_str());
  JavaVMInitArgs vmArgs;
  vmArgs.version = JNI_VERSION_1_2;
  vmArgs.nOptions = 1;
  vmArgs.options = jvmopt;
  vmArgs.ignoreUnrecognized = JNI_TRUE;

  // Create the JVM
  JavaVM *javaVM;
  JNIEnv *jniEnv;
  long flag = JNI_CreateJavaVM(&javaVM, (void**)
     &jniEnv, &vmArgs);
  if (flag == JNI_ERR) {
     cout << "Error creating VM. Exiting...n";
     return 1;
  }


  jclass jcls = jniEnv->FindClass("org/jnijvm/Tata");
  if (jcls == NULL) {
  jniEnv->ExceptionDescribe();
  javaVM->DestroyJavaVM();
    return 1;
  }
  if (jcls != NULL) {
    jmethodID methodId = jniEnv->GetStaticMethodID(jcls, "greet", "(Ljava/lang/String;)V");
    if (methodId != NULL) {
      jstring str = jniEnv->NewStringUTF("salut");
      jniEnv->CallStaticVoidMethod(jcls, methodId, str);
      if (jniEnv->ExceptionCheck()) {
        jniEnv->ExceptionDescribe();
        jniEnv->ExceptionClear();
      }
    }
  }
  javaVM->DestroyJavaVM();
  return 0;
}
