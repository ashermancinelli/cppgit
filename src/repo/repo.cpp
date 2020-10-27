#include "repo.hpp"
#include <exception>
#include <iostream>

namespace cppgit
{

Repo::Repo(std::string repo_path, bool force)
{
  worktree = bfs::path(repo_path);

  gitdir = worktree / ".git";
  if (!bfs::is_directory(gitdir))
  {
    if (!force)
      throw std::runtime_error("Repository does not exist.");
    bfs::create_directory(gitdir);
  }

  if (bfs::exists(gitdir / bfs::path("config")))
  {
    try
    {
      bptree::ini_parser::read_ini(
          (gitdir / bfs::path("config")).string(),
          conf);
      int version = conf.get<int>("core.repositoryformatversion");
      if (version != 0)
        throw std::runtime_error("Invalid core.repositoryformatversion found in config file.");
    }
    catch (const std::exception& e)
    {
      std::cerr << "Could not parse node core.repositoryformatversion from "
        << "config. Writing default values to config file.\n";
      write_default_config();
    }
  }
  else
  { 
    if (!force)
      throw std::runtime_error("Configuration file missing.");
    write_default_config();
  }
}

void Repo::create()
{
#define CREATE_DIR(path) \
  if (!bfs::is_directory(path)) \
  { \
    std::cout << "Creating directory: " << path.string() << "\n"; \
    bfs::create_directory(path); \
  }

  bfs::path p = gitdir / "branches";
  CREATE_DIR(p);
  p = gitdir / "objects";
  CREATE_DIR(p);
  p = gitdir / "objects";
  CREATE_DIR(p);
  p = gitdir / "refs";
  CREATE_DIR(p);
  p = gitdir / "refs" / "tags";
  CREATE_DIR(p);
  p = gitdir / "refs" / "heads";
  CREATE_DIR(p);

#undef CREATE_DIR

  // Create .git/description
  {
    bfs::path p{gitdir / "description"};
    if (!bfs::exists(p))
    {
      std::ofstream f{p.string()};
      f << "Unnamed repository; edit this file 'description' to name the "
        << "repository.\n";
    }
  }

  // Create .git/HEAD
  {
    bfs::path p{gitdir / "HEAD"};
    if (!bfs::exists(p))
    {
      std::ofstream f{p.string()};
      f << "ref: refs/heads/master\n";
    }
  }
}

void Repo::write_config()
{
  bfs::path p{gitdir / "config"};
  bptree::write_ini(p.string(), conf);
}

Repo::~Repo()
{
  write_config();
}

void Repo::write_default_config()
{
  conf.put("core.repositoryformatversion", 0);
  conf.put("core.filemode", "false");
  conf.put("core.bare", "false");
  write_config();
}

}
