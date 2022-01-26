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
#include <sstream>


#include <LIEF/LIEF.hpp>
#include <QBDL/Engine.hpp>
#include <QBDL/engines/Native.hpp>
#include <QBDL/loaders/ELF.hpp>


#include "path.h"

using namespace QBDL;
using namespace std;

int my_strlen(const char *s, size_t)
{
  return strlen(s);
}
void my_android_set_abort_message(const char* msg)
{

}
void my_android_log_print(int prio, const char *tag, const char *fmt ...)
{
  va_list argp;
  va_start(argp, fmt);
  vprintf(fmt, argp);
  va_end(argp);
}



namespace {

struct FinalTargetSystem: public Engines::Native::TargetSystem {
  using Engines::Native::TargetSystem::TargetSystem;
  inline static void* libc_hdl = dlopen("libc.so.6", RTLD_NOW);

  uint64_t symlink(Loader &loader, const LIEF::Symbol &sym) override {
    printf("%s\n", sym.name().c_str());
    /*
    if (dlsym(libc_hdl, sym.name().c_str()) == 0)
    {
      cout << "non" << endl;
    }
    else
    {
      cout << "oui" << endl;
    }
    */
    if (sym.name()=="__strlen_chk")
    {
      return reinterpret_cast<uint64_t>(my_strlen);
    }
    if (sym.name()=="android_set_abort_message")
    {
      return reinterpret_cast<uint64_t>(my_android_set_abort_message);
    }
    if (sym.name()=="__android_log_print")
    {
      return reinterpret_cast<uint64_t>(my_android_log_print);
    }
    return reinterpret_cast<uint64_t>(dlsym(libc_hdl, sym.name().c_str()));
  }
};

}



int main(int argc, char **argv) {
  cout << "coucou\n";
  string tabClasses[4]={"/home/lucas/dev/example-android-native-app/app/build/intermediates/javac/debug/classes", SOURCE_PATH, "/home/lucas/.gradle/caches/transforms-3/d18bfc700c6d6b2046e9ad58467e8155/transformed/appcompat-1.2.0-runtime.jar", "/home/lucas/.gradle/caches/transforms-3/76daf7c648fcd60b1fa8502269df1152/transformed/versionedparcelable-1.1.0/aidl"};
  
  JavaVMOption jvmopt[1];
  string javaOption = string{"-Djava.class.path="};
  for (int i=0; i<4; i++)
  {

    //javaOption = javaOption + ".:" + tabClasses[i];
    ///*
    if (i!=0)
    {
      javaOption = javaOption + ":" + tabClasses[i];
    }
    else
    {
      javaOption = javaOption + tabClasses[i];
    }
    //*/
  }
  cout << javaOption << endl;
  
  jvmopt[0].optionString = const_cast<char*>(javaOption.c_str());
  JavaVMInitArgs vmArgs;
  vmArgs.version = JNI_VERSION_1_6;
  vmArgs.nOptions = 1;
  vmArgs.options = jvmopt;
  vmArgs.ignoreUnrecognized = JNI_TRUE;

  // Create the JVM
  JavaVM *javaVM;
  JNIEnv *jniEnv;
  long flag = JNI_CreateJavaVM(&javaVM, (void**)
     &jniEnv, &vmArgs);
  if (flag == JNI_ERR) {
     cout << "Error creating VM. Exiting...";
     return 1;
  }

  jclass jcls = jniEnv->FindClass("com/example/myapplication/MainActivity");
  //jclass jcls = jniEnv->FindClass("org/jnijvm/Tata");
  if (jcls == NULL) {
  jniEnv->ExceptionDescribe();
  javaVM->DestroyJavaVM();
  cout << "salut1" << endl;
    return 1;
  }
  if (jcls != NULL) {
    jmethodID methodId = jniEnv->GetStaticMethodID(jcls, "greet", "(Ljava/lang/String;)V");
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


  auto mem = std::make_unique<Engines::Native::TargetMemory>();
  auto system = std::make_unique<FinalTargetSystem>(*mem);

  const char *path = argv[1];

  std::unique_ptr<Loaders::ELF> loader = Loaders::ELF::from_file(
      path, *system, Loader::BIND::NOW);
  if (!loader) {
    fprintf(stderr, "unable to load binary!\n");
    return EXIT_FAILURE;
  }
  using add_fcn_t = int(*)(void*, void*, int, int);
  auto add = reinterpret_cast<add_fcn_t>(loader->get_address("Java_com_example_myapplication_MainActivity_add"));
  if (add == nullptr) {
    fprintf(stderr, "Can't find symbol 'add'\n");
    return 1;
  }
  int s = add(nullptr, nullptr, 2, 9);
 
  cout << "result : " << s << endl;

  using nativeMul_fcn_t = int(*)(JNIEnv*, void*, int, int);
  auto nativeMul = reinterpret_cast<nativeMul_fcn_t>(loader->get_address("Java_com_example_myapplication_MainActivity_nativeMul"));
  if (nativeMul == nullptr) {
    fprintf(stderr, "Can't find symbol 'nativeMul'\n");
    return 1;
  }

  int t = nativeMul(jniEnv, nullptr, 2, 9);

  cout << "result : " << t << endl;

  
  javaVM->DestroyJavaVM();
  return 0;
}


