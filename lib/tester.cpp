#include "ulog/ulog.h"

int main() {
	ulog::Logger::setFileLogger("ulog", ulog::Level::Info);

	ulg.info("hello from {}", "ulog");
	ulg.error("failed to write {}", "test.txt");

	return 0;
}
