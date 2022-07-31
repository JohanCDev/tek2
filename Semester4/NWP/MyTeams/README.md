MyTeams
[![Build](https://img.shields.io/github/workflow/status/MisterPeModder/MyTeams/CI)](https://github.com/MisterPeModder/MyTeams/actions/workflows/ci.yml)
[![License](https://img.shields.io/github/license/MisterPeModder/MyTeams)](https://github.com/MisterPeModder/MyTeams)
====

# Building

## Command Line (via CMake)

Required tools:
- CMake 3.17 (minimum)

on Linux:
```sh
# Create the build directory
mkdir build && cd build 

# Configure the project
cmake .. -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=Release

# Build the executable and libraries
cmake --build .

# Return to previous directory
cd -
```

# Documentation

## Local

Required tools:
- Doxygen

on Linux:
```sh
# Run at the root of the project
doxygen

# Open the genrated pages
xdg-open doc/generated/html/index.html
```
