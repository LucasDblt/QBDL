#pragma once

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dlfcn.h>
#include <unistd.h>
#include <stdarg.h>
#include <iostream>


#include <LIEF/LIEF.hpp>
#include <QBDL/Engine.hpp>
#include <QBDL/engines/Native.hpp>
#include <QBDL/loaders/ELF.hpp>


using namespace QBDL;
using namespace std;

int my_strlen(const char*, size_t);
void my_android_set_abort_message(const char* );
void my_android_log_print(int, const char*, const char* ...);