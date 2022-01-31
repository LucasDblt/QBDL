
#include "JVM.h"
#include <iostream>
#include <jni.h>
#include <utility>

using namespace std;

pair<javaVM, jniEnv> JVM(javaOption) {

  JavaVMOption jvmopt[1];
  jvmopt[0].optionString = const_cast<char *>(javaOption.c_str());
  JavaVMInitArgs vmArgs;
  vmArgs.version = JNI_VERSION_1_6;
  vmArgs.nOptions = 1;
  vmArgs.options = jvmopt;
  vmArgs.ignoreUnrecognized = JNI_TRUE;

  // Create the JVM
  JavaVM *javaVM;
  JNIEnv *jniEnv;
  long flag = JNI_CreateJavaVM(&javaVM, (void **)&jniEnv, &vmArgs);
  if (flag == JNI_ERR) {
    cout << "Error creating VM. Exiting...";
    return 1;
  }

  jclass jcls = jniEnv->FindClass("com/example/myapplication/MainActivity");
  // jclass jcls = jniEnv->FindClass("org/jnijvm/Tata");
  if (jcls == NULL) {
    jniEnv->ExceptionDescribe();
    javaVM->DestroyJavaVM();
    cout << "salut1" << endl;
    return 1;
  }
  if (jcls != NULL) {
    jmethodID methodId =
        jniEnv->GetStaticMethodID(jcls, "greet", "(Ljava/lang/String;)V");
    if (methodId != NULL) {
      jstring str = jniEnv->NewStringUTF("salut\n");
      cout << "salut2" << endl;
      jniEnv->CallStaticVoidMethod(jcls, methodId, str);
      if (jniEnv->ExceptionCheck()) {
        jniEnv->ExceptionDescribe();
        jniEnv->ExceptionClear();
      }
    }
  }
  pair<JavaVM, JNIEnv> PAIR1;
  PAIR1.first = javaVM;
  PAIR1.second = jniEnv;
  return PAIR1;
}
