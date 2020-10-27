
add_subdirectory(repo)
add_subdirectory(handlers)

add_executable(cppgit driver/main.cpp)
target_link_libraries(cppgit
  PRIVATE
  cppgit.repo
  cppgit.handlers
  ${CONAN_LIBS}
  inih
  )
