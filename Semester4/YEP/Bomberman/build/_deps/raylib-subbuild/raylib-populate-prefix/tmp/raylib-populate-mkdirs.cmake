# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/johan/Epitech/tek2/B4/YEP/Bomberman/build/_deps/raylib-src"
  "/Users/johan/Epitech/tek2/B4/YEP/Bomberman/build/_deps/raylib-build"
  "/Users/johan/Epitech/tek2/B4/YEP/Bomberman/build/_deps/raylib-subbuild/raylib-populate-prefix"
  "/Users/johan/Epitech/tek2/B4/YEP/Bomberman/build/_deps/raylib-subbuild/raylib-populate-prefix/tmp"
  "/Users/johan/Epitech/tek2/B4/YEP/Bomberman/build/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp"
  "/Users/johan/Epitech/tek2/B4/YEP/Bomberman/build/_deps/raylib-subbuild/raylib-populate-prefix/src"
  "/Users/johan/Epitech/tek2/B4/YEP/Bomberman/build/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/johan/Epitech/tek2/B4/YEP/Bomberman/build/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/${subDir}")
endforeach()
