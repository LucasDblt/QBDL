#include "myfunctions.h"

int my_strlen(const char *s, size_t)
{
  return strlen(s);
}
void my_android_set_abort_message(const char* msg)
{

}
void my_android_log_print(int prio, const char *tag, const char *fmt ...)
{
  va_list argp;
  va_start(argp, fmt);
  vprintf(fmt, argp);
  va_end(argp);
}