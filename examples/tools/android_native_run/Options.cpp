#include "Options.h"


#include <fstream>
#include <sstream>
#include <getopt.h>
#include <iostream>
#include <vector>

using namespace std;

namespace
{
  string GetClassPath(string const &optarg) {
  ifstream dependencies(optarg);
  string line;
  stringstream paths;
  while (getline(dependencies, line)) {
    paths << line << ":";
  }
  return paths.str();
  }

  vector<string> otherLibraries(string const &optarg) {
  ifstream librariesStream(optarg);
  string line;
  vector<string> tabOtherLibraries;
  while (getline(librariesStream, line))
  {
    tabOtherLibraries.emplace_back(line);
  }

  return tabOtherLibraries;
  }
}

static int verboseFlag;

JavaOption options(int argc, char **argv, const char *shortopts,
                   const struct longOptions *longopts, int *indexptr) {
  int option;
  JavaOption opt;

  while (1) {
    static struct option longOptions[] = {
        {"dependencies", required_argument, 0, 'd'},
        {"libraries", required_argument, 0, 'l'},
        {"input", required_argument, 0, 'i'},
        {0, 0, 0, 0}};
    /* getopt_long stores the option index here. */
    int optionIndex = 0;

    option = getopt_long(argc, argv, "l:d:i:", longOptions, &optionIndex);

    /* Detect the end of the options. */
    if (option == -1)
      break;

    switch (option) {
    case 0:
      /* If this option set a flag, do nothing else now. */
      if (longOptions[optionIndex].flag != 0)
        break;
      if (optarg)
        printf("\n");
      break;

    case 'l':
      opt.otherLibraries = otherLibraries(optarg);
      break;

    case 'd':
      opt.classPath = string{"-Djava.class.path="} + GetClassPath(optarg);
      break;

    case 'i':
      opt.ldPath = string{optarg};
      break;

    case '?':
      /* getopt_long already printed an error message. */
      break;

    default:
      cerr << "error" << endl;
      abort();
    }
  }
  return opt;
}
