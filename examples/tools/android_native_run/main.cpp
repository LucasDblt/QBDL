#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dlfcn.h>
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <jni.h>
#include <sstream>
#include <stdarg.h>
#include <string>
#include <unistd.h>
#include <utility>
#include <vector>

#include <LIEF/LIEF.hpp>
#include <QBDL/Engine.hpp>
#include <QBDL/engines/Native.hpp>
#include <QBDL/loaders/ELF.hpp>

#include "JVM.h"
#include "classpath.h"
#include "myfunctions.h"
#include "options.h"
#include "path.h"

using namespace QBDL;
using namespace std;

namespace {

struct FinalTargetSystem : public Engines::Native::TargetSystem {
  using Engines::Native::TargetSystem::TargetSystem;
  inline static void *libc_hdl = dlopen("libc.so.6", RTLD_NOW);

  uint64_t symlink(Loader &loader, const LIEF::Symbol &sym) override {
    printf("%s\n", sym.name().c_str());

    if (sym.name() == "__strlen_chk") {
      return reinterpret_cast<uint64_t>(my_strlen);
    }
    if (sym.name() == "android_set_abort_message") {
      return reinterpret_cast<uint64_t>(my_android_set_abort_message);
    }
    if (sym.name() == "__android_log_print") {
      return reinterpret_cast<uint64_t>(my_android_log_print);
    }
    return reinterpret_cast<uint64_t>(dlsym(libc_hdl, sym.name().c_str()));
  }
};

} // namespace

int main(int argc, char **argv) {

  cout << "coucou\n";

  string javaOption = options(argc, argv, 0, 0, 0);

  pair jvm = JVM(javaOption);

  /*
  JavaVMOption jvmopt[1];
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
    jmethodID methodId = jniEnv->GetStaticMethodID(jcls, "greet",
  "(Ljava/lang/String;)V"); if (methodId != NULL) { jstring str =
  jniEnv->NewStringUTF("salut\n"); cout << "salut2" << endl;
      jniEnv->CallStaticVoidMethod(jcls, methodId, str);
      if (jniEnv->ExceptionCheck()) {
        jniEnv->ExceptionDescribe();
        jniEnv->ExceptionClear();
      }
    }
  }
  */

  JavaVM *javaVM = &(jvm.first);
  JNIEnv *jniEnv = &(jvm.second);

  auto mem = std::make_unique<Engines::Native::TargetMemory>();
  auto system = std::make_unique<FinalTargetSystem>(*mem);

  const char *path = argv[1];

  std::unique_ptr<Loaders::ELF> loader =
      Loaders::ELF::from_file(path, *system, Loader::BIND::NOW);
  if (!loader) {
    fprintf(stderr, "unable to load binary!\n");
    return EXIT_FAILURE;
  }
  using add_fcn_t = int (*)(void *, void *, int, int);
  auto add = reinterpret_cast<add_fcn_t>(
      loader->get_address("Java_com_example_myapplication_MainActivity_add"));
  if (add == nullptr) {
    fprintf(stderr, "Can't find symbol 'add'\n");
    return 1;
  }
  int s = add(nullptr, nullptr, 2, 9);

  cout << "result : " << s << endl;

  using nativeMul_fcn_t = int (*)(JNIEnv *, void *, int, int);
  auto nativeMul = reinterpret_cast<nativeMul_fcn_t>(loader->get_address(
      "Java_com_example_myapplication_MainActivity_nativeMul"));
  if (nativeMul == nullptr) {
    fprintf(stderr, "Can't find symbol 'nativeMul'\n");
    return 1;
  }

  int t = nativeMul(jniEnv, nullptr, 2, 9);

  cout << "result : " << t << endl;

  javaVM->DestroyJavaVM();
  return 0;
}
