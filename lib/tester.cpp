#include "ulog/ulog.h"
#include <Windows.h>

int main() {
  ulog::setFileLogger("ulog");

  ulg.error("ul{}{}", 0, "g");

  return 0;
}
