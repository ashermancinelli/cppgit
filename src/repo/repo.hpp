#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace bfs = boost::filesystem;
namespace bptree = boost::property_tree;

namespace cppgit
{

class Repo
{
  private:
    bfs::path worktree;
    bfs::path gitdir;
    bptree::ptree conf;
    void write_config();

  public:
    Repo(std::string path, bool force=false);
    ~Repo();
    void create();
    void write_default_config();
};

}
