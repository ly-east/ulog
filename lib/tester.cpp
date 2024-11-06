#include "ulog/ulog.h"

int main() {
  ulog::setFileLogger("ulog", spdlog::level::info);

  ulg.error("ul{}{}", 0, "g");

  return 0;
}
