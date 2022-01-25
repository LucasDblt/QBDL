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

#include "path.h"

using namespace QBDL;
using namespace std;


namespace {

struct FinalTargetSystem: public Engines::Native::TargetSystem {
  using Engines::Native::TargetSystem::TargetSystem;
  inline static void* libc_hdl = dlopen("libc.so.6", RTLD_NOW);

  uint64_t symlink(Loader &loader, const LIEF::Symbol &sym) override {
    printf("%s  ", sym.name().c_str());
    if (dlsym(libc_hdl, sym.name().c_str()) == 0)
    {
      cout << "non" << endl;
    }
    else
    {
      cout << "oui" << endl;
    }

    return reinterpret_cast<uint64_t>(dlsym(libc_hdl, sym.name().c_str()));
  }
};

}



int main(int argc, char **argv) {
  cout << "coucou\n";
  JavaVMOption jvmopt[1];
  string javaOption = string{"-Djava.class.path="} + SOURCE_PATH;
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


  jclass jcls = jniEnv->FindClass("org/jnijvm/Tata");
  if (jcls == NULL) {
  jniEnv->ExceptionDescribe();
  javaVM->DestroyJavaVM();
    return 1;
  }
  if (jcls != NULL) {
    jmethodID methodId = jniEnv->GetStaticMethodID(jcls, "greet", "(Ljava/lang/String;)V");
    if (methodId != NULL) {
      jstring str = jniEnv->NewStringUTF("salut\n");
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
  

  
  javaVM->DestroyJavaVM();
  return 0;
}
