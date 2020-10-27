add_library(cppgit.handlers STATIC handlers.cpp)
target_include_directories(cppgit.handlers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(cppgit.handlers PUBLIC cppgit.repo)
