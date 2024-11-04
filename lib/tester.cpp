#include "ulog.h"

int main() {
  ulog::setFileLogger("ulog");

  ul.error("ul{}{}", 0, "g");

  return 0;
}
