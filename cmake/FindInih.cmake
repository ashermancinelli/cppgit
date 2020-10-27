
#[[

Inih is a tiny library we pull as a submodule by default. This just creates
a target for the submodule.

Exports target `inih`

#]]

set(inih_ROOT_DIR ${PROJECT_SOURCE_DIR}/third_party/inih/)
mark_as_advanced(inih_ROOT_DIR)

set_source_files_properties(${inih_ROOT_DIR}/ini.c PROPERTIES LANGUAGE CXX )

add_library(inih
  STATIC
  ${inih_ROOT_DIR}/cpp/INIReader.cpp
  ${inih_ROOT_DIR}/ini.c
  )

target_include_directories(inih
  PUBLIC
  ${inih_ROOT_DIR}/cpp
  ${inih_ROOT_DIR}
  )
