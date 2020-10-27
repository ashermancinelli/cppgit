add_library(cppgit.repo STATIC repo.cpp)
target_include_directories(cppgit.repo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(cppgit.repo PRIVATE inih ${CONAN_LIBS})
