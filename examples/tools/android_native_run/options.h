#pragma once

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
#include <vector>

#include <LIEF/LIEF.hpp>
#include <QBDL/Engine.hpp>
#include <QBDL/engines/Native.hpp>
#include <QBDL/loaders/ELF.hpp>

using namespace std;

// string options (int argc, char **argv);
string options(int argc, char **argv, const char *shortopts,
               const struct long_options *longopts, int *indexptr);