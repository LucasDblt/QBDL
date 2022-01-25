# Support for Android native libraries to QBDL


The goal of this project was to launch a Java Virtual Machine which is able to support the unknown android symbols. 
For our application, we are using some code from android studio. The c++ program will then start the JVM in which
the Java code from android studio will be able to compil thanks to the imported libraries.


## How to use it :


### Android symbols

As said before, the goal is to run some Android symbols. The program is basically going to search into the libc first and then looking into other libraries. What you have to do here is to recreate the missing symbols in the AndroidSymbols.cpp file and then write their names into "MissingSymb.txt". The program will directly replace the native symbol by yours.


### Java classes

To compile the code, you will need to know the paths to the Java classes. Then create a .txt document in which you can gather all these paths. To do so, you can use this command :

```
find ~/.gradle/caches -name "*-runtime.jar" > dependencies.txt
```

It will find all the java dependencies ending with "runtime.jar" which are necessary for the code to be well executed. Other files are required also. You have to include these two paths into the same file :

- The Android runtime, which you can normally find in your android's SDK installation followed by `/platforms/android-32/android.jar`.

- The directory where the Java classes using the native libraries are compiled; on my setup it was here:
`~/dev/example-android-native-app/app/build/intermediates/javac/debug/classes`

It is also possible that some other dependencies are required for you to execute the program. Then just add them in the .txt file.


### LD_LIBRARY_PATH

When the code called by the JNI is loading, it is loading itself the native library. Therefore the right LD_LIBRARY_PATH has to set so that it finds the necessary libraries.

You can now export the LD_LIBRARY_PATH using `export LD_LIBRARY_PATH=path/to/libc.so:/path/to/libmyapplication.so`


### Options to execute

Now after compilation, you will have to execute the code with these options :

`-d` path to the .txt with the java dependencies

`-l` path to the .txt with the other libraries to add

`-i` ld_path, we are using here "libmyapplication.so"


## Explanation on the different parts of the code


#### __Options section__

This section is gathering the arguments typed in the terminal and will give them to the other functions of the code.

##### __ClassPath section__ 

We are here creating a vector with the different Java classes from the txt file with all the dependences (imported from the option `-d`), to use them in an other part.

##### __OtherLibraries section__

This section works a bit like the classpath section but with the libraries. It create a vector from the informations in Other_libraries.txt.

#### __JVM section__

This section is dedicated to the launch of the JVM. We are importing the class_path and the library_path thanks to the 2 lines :

```
jvmopt[0].optionString = const_cast<char *>(opt.class_path.c_str());
jvmopt[1].optionString = const_cast<char *>(opt.library_path.c_str());
```
Now the JVM has all the needed informations to start and to call the JNI !

#### __AndroidSymbols section__

Here is grouped all the unknown functions which we are going to replace. When a symbol is not recognized (not present in the basic libc), the program will look into this library to find a remplacement function.

#### __Main section__

The most important part since this section will reunify every part for the program to work.

The first `namespace{...}` part is using the otherLibraries section to open and load every of these libraries. Then calling the Java functions add and nativeMul from the JNI. This second part is just an application of the project but the program can be modified to be used with any other functions created with android studio. The last part of the namespace is dedicated to the call of the java's greet method.

The `int main(int argc, char **argv) {...}` part is firstly calling the Option section to use or redistibute them and then calling the functions in the previous namespace.


## Removing unused libraries

We had an issue during the project with some symbols in the liblog library. Since liblog is useless in our project, we have decide to remove the library. To do that, we have use the advice given on this project : https://blog.quarkslab.com/when-sidechannelmarvels-meet-lief.html, adapted to our case :

```
import lief
libnative = lief.parse("./libmyapplication.so")

liblog     = libnative.get_library("liblog.so")
liblog.tag = lief.ELF.DYNAMIC_TAGS.NULL

libnative.write("libmyapplication-fixed.so")
```

## Example 

### __This is an example of me using the program with the test application (add/multiply) :__

Add being a basic native function and multiply a native function calling the JNI to execute some Java.

#### Export the LD_LIBRARY_PATH 

```
lucas@lucasPC:~/dev/QBDL/build$ export LD_LIBRARY_PATH=/home/lucas/Android/Sdk/ndk/23.1.7779620/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/lib/x86_64-linux-android/31/:/home/lucas/dev/example-android-native-app/app/build/intermediates/cmake/debug/obj/x86_64
```

#### Execute the code with the options 

```
lucas@lucasPC:~/dev/QBDL/build$ ./examples/tools/android_native_run/android_native_run  -d ./examples/tools/android_native_run/dependencies.txt -i libmyapplication.so -l ../examples/tools/android_native_run/Other_libraries.txt
```

#### Result

```
Loading libmyapplication.so
error while looking up the symbol __sF in the libraries
Adding 2 and 9
result : 11
Multiply on 2 and 9
Multiply on 2 and 9
result : 18
```





