#pragma once

#include <iostream>
#include <string>
#include <vector>

struct JavaOption {
  std::string classPath;
  std::string libraryPath;
  std::string ldPath;
  std::vector<std::string> otherLibraries;
};

JavaOption options(int argc, char **argv, const char *shortopts,
                   const struct longOptions *longopts, int *indexptr);