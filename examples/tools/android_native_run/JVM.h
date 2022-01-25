#pragma once
#include "Options.h"

#include <iostream>
#include <jni.h>
#include <string>
#include <utility>

std::pair<JavaVM *, JNIEnv *> createJVM(JavaOption const &);
