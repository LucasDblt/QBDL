#include "classpath.h"
#include "path.h"

using namespace std;

string GetClassPath(string optarg)
{

  //ifstream dependencies("/home/lucas/dev/QBDL/build/examples/tools/android_native_run/dependencies.txt");
  
  ifstream dependencies(optarg);
  string line;
  vector <string> ArrayOfPaths{
    "/home/lucas/dev/example-android-native-app/app/build/intermediates/javac/debug/classes",
    SOURCE_PATH,
    "/home/lucas/.gradle/caches/transforms-3/d18bfc700c6d6b2046e9ad58467e8155/transformed/appcompat-1.2.0-runtime.jar",
    "/home/lucas/.gradle/caches/transforms-3/ef6a0bc1faa09020a3bfd9e98080f026/transformed/core-1.3.1-runtime.jar"
  };
  

  stringstream Paths;
  for (auto &p : ArrayOfPaths)
  {
    Paths << p << ":";
  }
  while (getline(dependencies, line))
  {
    Paths << line << ":";
  }
  return Paths.str();
}