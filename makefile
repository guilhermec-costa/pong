default:
	@cmake -S . -B build && cmake --build build && ./build/bin/pong