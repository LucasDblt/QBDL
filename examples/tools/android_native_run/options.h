#pragma once

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
#include <vector>
#include <fstream>
#include <getopt.h>


#include <LIEF/LIEF.hpp>
#include <QBDL/Engine.hpp>
#include <QBDL/engines/Native.hpp>
#include <QBDL/loaders/ELF.hpp>

using namespace std;

string options (int argc, char **argv, const char *shortopts, const struct long_options *longopts, int *indexptr);