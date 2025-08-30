BUILD_DIR = build
EXEC_RELEASE = $(BUILD_DIR)/release/bin/pong
EXEC_DEBUG = $(BUILD_DIR)/debug/bin/pong

buildr:
	@cmake -S . -B $(BUILD_DIR)/release -DCMAKE_BUILD_TYPE=Release
	@cmake --build $(BUILD_DIR)/release

runr:
	@$(EXEC_RELEASE)

buildd:
	@cmake -S . -B $(BUILD_DIR)/debug -DCMAKE_BUILD_TYPE=Debug
	@cmake --build $(BUILD_DIR)/debug

rund:
	@$(EXEC_DEBUG)
