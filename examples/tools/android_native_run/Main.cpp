#include "JVM.h"
#include "Options.h"

#include <dlfcn.h>

#include <LIEF/LIEF.hpp>
#include <QBDL/engines/Native.hpp>
#include <QBDL/loaders/ELF.hpp>

using namespace QBDL;
using namespace std;



namespace {

struct FinalTargetSystem : public Engines::Native::TargetSystem {
  void* lastLib;

  FinalTargetSystem(TargetMemory &mem, vector<string> const &otherLibraries) : Engines::Native::TargetSystem(mem)
  {
    for (auto const &lib : otherLibraries)
    {
      lastLib = dlopen(lib.c_str(), RTLD_NOW);
      if (!lastLib)
      {
        cerr << "can't open library " << lib << endl;
        exit(1);
      }
    }

  }
  
  
  uint64_t symlink(Loader &loader, const LIEF::Symbol &sym) override {
    auto symbol = dlsym(lastLib, sym.name().c_str());
    if (dlerror())
    {
      cout << "error while looking up the symbol " << sym.name() << " in the libraries" << endl;
    }
    

    return reinterpret_cast<uint64_t>(symbol); 
  }
};



int multiplication(JNIEnv* jniEnv, Loaders::ELF* loader)
{
  using nativeMul_fcn_t = int (*)(JNIEnv *, void *, int, int);
  auto nativeMul = reinterpret_cast<nativeMul_fcn_t>(loader->get_address(
      "Java_com_example_myapplication_MainActivity_nativeMul"));
  if (nativeMul == nullptr) {
    cerr << "Can't find symbol 'nativeMul'" << endl;
    return 1;
  }

  return nativeMul(jniEnv, nullptr, 2, 9);
}




int addition(Loaders::ELF* loader)
{
  using add_fcn_t = int (*)(void *, void *, int, int);
  auto add = reinterpret_cast<add_fcn_t>(
      loader->get_address("Java_com_example_myapplication_MainActivity_add"));
  if (add == nullptr) {
    cerr << "Can't find symbol 'add'\n";
    return 1;
  }
  return add(nullptr, nullptr, 2, 9);
}




void greet_method(JNIEnv* jniEnv)
{

  jclass jcls = jniEnv->FindClass("com/example/myapplication/MainActivity");
  if (!jcls) {
    jniEnv->ExceptionDescribe();
    cerr << "can't find class MainActivity" << endl;
    return;
  }

  jmethodID methodId = jniEnv->GetStaticMethodID(jcls, "greet", "(Ljava/lang/String;)V");
  if (methodId != NULL) {
    jstring str = jniEnv->NewStringUTF("Hello\n");
    jniEnv->CallStaticVoidMethod(jcls, methodId, str);
    if (jniEnv->ExceptionCheck()) {
      jniEnv->ExceptionDescribe();
      jniEnv->ExceptionClear();
    }
  }
}


} // namespace





int main(int argc, char **argv) {

  JavaOption opt = options(argc, argv, 0, 0, 0);

  auto mem = std::make_unique<Engines::Native::TargetMemory>();
  auto system = std::make_unique<FinalTargetSystem>(*mem, opt.otherLibraries);
  const string path = opt.ldPath;

  std::unique_ptr<Loaders::ELF> loader =
      Loaders::ELF::from_file(path.c_str(), *system, Loader::BIND::NOW);
  if (!loader) {
    cerr << "unable to load binary!" << endl;
    return EXIT_FAILURE;
  }
  auto [javaVM, jniEnv] = createJVM(opt);

  greet_method(jniEnv);

  cout << "calling add : " << addition(loader.get()) << endl;

  
  cout << "calling mul : " << multiplication(jniEnv, loader.get()) << endl;

  javaVM->DestroyJavaVM();
  return 0;
}
