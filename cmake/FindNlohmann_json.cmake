
#[[

This cmake file is only used if nlohmann_json cannot be found via the defualt
cmake package finder.

#]]

add_library(nlohmann_json INTERFACE)

if(NOT CONAN_INCLUDE_DIRS_nlohmann_json)
  message(FATAL_ERROR "Could not find nlohmann_json include dirs!")
endif()
target_include_directories(nlohmann_json INTERFACE ${CONAN_INCLUDE_DIRS_nlohmann_json})
