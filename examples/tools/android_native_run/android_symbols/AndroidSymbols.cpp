#include <stdarg.h>
#include <stdio.h>
#include <string.h>


extern "C"{

  int __strlen_chk(const char *s, size_t) { return strlen(s); }
  void android_set_abort_message(const char *msg) {}
  void __android_log_print(int prio, const char *tag, const char *fmt...) {
    va_list argp;
    va_start(argp, fmt);
    vprintf(fmt, argp);
    va_end(argp);
}

}