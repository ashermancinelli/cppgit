
#include "handlers.hpp"
#include <repo.hpp>
#include <map>

namespace cppgit
{

void handle_init(std::vector<std::string> args)
{
  bfs::path p(".");
  bool force=false;

  for(const auto& arg : args)
  {
    if (arg == "-f" || arg == "--force") force = true;
    else
      p = bfs::path(arg);
  }

  if (!bfs::exists(p))
  {
    throw std::runtime_error("Must provide valid path to cppgit init.");
  }
  
  if (args.size() > 2 && (args[2] == "--force" || args[2] == "-f"))
  {
    force = true;
  }

  Repo r(p.string(), force);
  r.create();
}

}
