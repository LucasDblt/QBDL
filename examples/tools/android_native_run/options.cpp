#include "options.h"
#include "classpath.h"
#include <getopt.h>
#include <iostream>

// string options (int argc, char **argv)
string options(int argc, char **argv, const char *shortopts,
               const struct long_options *longopts, int *indexptr) {
  string javaOption;
  // char option = getopt(argc, argv, "d:");

  static struct option long_options[] = {
      {"dependencies", no_argument, 0, 'd'},
  };
  int option_index = 0;

  char option = getopt_long(argc, argv, "d:", long_options, &option_index);

  switch (option) {
  case 'd':
    javaOption = string{"-Djava.class.path="} + GetClassPath(optarg);
    // cout << javaOption << endl;
    return javaOption;
  default:
    cout << "erreur" << endl;
    return "\0";
  }
}