#include "ulog/ulog.h"

int main() {
	ulog::Logger::setFileLogger("ulog", ulog::Level::Info);

	ulg.info("hello from ulog");

	return 0;
}
