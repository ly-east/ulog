#include "ulog/ulog.h"

int main() {
  ulog::setFileLogger(spdlog::level::info, "ulog");

  ulg.error("ul{}{}", 0, "g");

  return 0;
}
