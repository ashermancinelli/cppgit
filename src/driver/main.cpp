#include <iostream>
#include <handlers.hpp>
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <nlohmann/json.hpp>
#include <repo.hpp>

using namespace cppgit;

int usage(string bin)
{
  std::cout << "Usage:\n"
    << "\t" << bin << " init [path]\n";
  return 0;
}

int main(int argc, char** argv)
{
  vector<string> args(argv, argv+argc);
  
  if (args.size() == 1) return usage(args[0]);

  if (args[1] == "init") handle_init(vector(args.begin()+2, args.end()));
  else usage(args[0]);
  /*
  else if (args[0] == "cat-file") cmd_cat_file(args);
  else if (args[0] == "cat-file") cmd_cat_file(args);
  else if (args[0] == "cat-file") cmd_cat_file(args);
  else if (args[0] == "cat-file") cmd_cat_file(args);
  else if (args[0] == "cat-file") cmd_cat_file(args);
  else if (args[0] == "cat-file") cmd_cat_file(args);
  */

  return 0;
}
