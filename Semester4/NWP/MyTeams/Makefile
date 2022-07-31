##
## EPITECH PROJECT, 2022
## MyTeams
## File description:
## makefile
##

TARGET_CLIENT := myteams_cli
TARGET_SERVER := myteams_server
BUILD_DIR := build
CONFIG_FLAGS := -G"Unix Makefiles" -B$(BUILD_DIR)

CONFIG_FLAGS_RELEASE := -DCMAKE_BUILD_TYPE=Release -DBUILD_TEST_SUITE=TRUE \
$(CONFIG_FLAGS)
CONFIG_FLAGS_DEBUG := -DCMAKE_BUILD_TYPE=Debug -DBUILD_TEST_SUITE=TRUE \
-DUSE_GCOV=TRUE $(CONFIG_FLAGS)

BUILD_FLAGS_RELEASE := --config Release
BUILD_FLAGS_DEBUG := --config Debug

TEST_FLAGS := -T test --output-on-failure --output-log test.log

CMAKE := $(shell which cmake)

# Build Targets
all: $(TARGET_CLIENT) $(TARGET_SERVER)

$(TARGET_CLIENT) $(TARGET_SERVER):
	cp -R libs2/ libs/ || true
	$(CMAKE) $(CONFIG_FLAGS_RELEASE)
	$(CMAKE) --build $(BUILD_DIR) $(BUILD_FLAGS_RELEASE) --target $@
	cp -R libs/ libs2/
	rm -rf libs/

# Remove Target's Build Files
clean:
	cp -R libs2/ libs/ || true
	rm -rf $(BUILD_DIR)/CMakeFiles
	rm -rf $(BUILD_DIR)/src/CMakeFiles
	cp -R libs/ libs2/
	rm -rf libs/

# Remove Targets
fclean:
	cp -R libs2/ libs/ || true
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET_CLIENT) $(TARGET_SERVER)
	cp -R libs/ libs2/
	rm -rf libs/

# Recompile all
re: fclean all

# Build Targets in debug mode
debug:
	cp -R libs2/ libs/ || true
	$(CMAKE) $(CONFIG_FLAGS_DEBUG)
	$(CMAKE) --build $(BUILD_DIR) $(BUILD_FLAGS_DEBUG)
	cp -R libs/ libs2/
	rm -rf libs/

# Run Unit Tests
run_tests: fclean debug
	cp -R libs2/ libs/ || true
	(cd $(BUILD_DIR) && ctest $(TEST_FLAGS)) || true
	cp -R libs/ libs2/
	rm -rf libs/
run_test: run_tests
tests_run: run_tests
test_run: run_test

# Display Code Coverage
coverage:
	gcovr .
	gcovr --branch .

.PHONY: \
	all \
	clean fclean re \
	debug \
	run_tests run_test tests_run test_run coverage
