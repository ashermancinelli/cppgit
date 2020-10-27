
#[[

cppgit: side-project implementation of Git in C++, based on the blog post
"Write yourself a git" in python. Link: 
https://github.com/thblt/write-yourself-a-git/blob/master/libwyag.py

#]]

cmake_minimum_required (VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(cppgit CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Download conan cmake definitions if not already downloaded
if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
    "${PROJECT_BINARY_DIR}/conan.cmake")
endif()
include(${PROJECT_BINARY_DIR}/conan.cmake)

# Add bincrafters remote for conan
conan_add_remote(
  NAME
  bincrafters
  URL
  https://api.bintray.com/conan/bincrafters/public-conan
  )

conan_cmake_run(
  REQUIRES ${CONAN_EXTRA_REQUIRES}
  nlohmann_json/3.9.1
  boost/1.69.0@conan/stable
  OPTIONS ${CONAN_EXTRA_OPTIONS}
  BASIC_SETUP
  CMAKE_TARGETS
  BUILD missing
  )

include(${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

message(STATUS "Conan installed libraries: ${CONAN_LIBS}")

#[[

External Libraries

Some of these were easier to add via conan than as a git submodule or vice
versa. Each is labeled with the source of the external library.

#]]

# Git submodules
include(cmake/FindInih.cmake)

# Conan
set(Boost_DIR ${CONAN_BOOST_ROOT})
find_package(Boost 1.69.0 EXACT REQUIRED COMPONENTS filesystem)
set(Boost_USE_STATIC_LIBS ON)

# Conan
# set(nlohmann_json_DIR ${CONAN_NLOHMANN_JSON_INSTALL_DIR})
# find_package(nlohmann_json 3.9.1 EXACT REQUIRED)

add_subdirectory(src)
