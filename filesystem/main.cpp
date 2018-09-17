#include <iostream>
#include <filesystem>
#include <sstream>
#include <iomanip>

using namespace std;
namespace fs = std::filesystem;

char fs_type(fs::file_type t) noexcept
{
   switch(t) {
      case fs::file_type::regular   : return 'f';
      case fs::file_type::directory : return 'd';
      case fs::file_type::symlink   : return 'l';
      case fs::file_type::block     : return 'b';
      case fs::file_type::character : return 'c';
      case fs::file_type::fifo      : return 'p';
      case fs::file_type::socket    : return 's';

      case fs::file_type::unknown   :
      case fs::file_type::not_found :
      case fs::file_type::none      : 
      default                       : break;
   }
   return '?';
}

string fs_rwx(fs::perms p)
{
   const auto check = [p](fs::perms bit, char c) noexcept {
      return (p & bit) == fs::perms::none ? '-' : c;
   };
   ostringstream oss;
   oss   << check(fs::perms::owner_read,     'r')
         << check(fs::perms::owner_write,    'w')
         << check(fs::perms::owner_exec,     'x')
         << check(fs::perms::group_read,     'r')
         << check(fs::perms::group_write,    'w')
         << check(fs::perms::group_exec,     'x')
         << check(fs::perms::others_read,    'r')
         << check(fs::perms::others_write,   'w')
         << check(fs::perms::others_exec,    'x');
   return oss.str();
}

string fs_size(uintmax_t s)
{
   ostringstream oss;
   if(1'000'000'000 <= s)
      oss << s/1'000'000'000 << 'G';
   else if(1'000'000 <= s)
      oss << s/1'000'000 << 'M';
   else if(1'000 <= s)
      oss << s/1'000 << 'K';
   else
      oss << s << 'B';
   return oss.str();
}

using fs_entity = pair<fs::path,fs::file_status>;

void display(const fs_entity& e)
{
   const auto& [path,status] = e;
   cout  << fs_type(status.type())
         << fs_rwx(status.permissions()) << " "
         << setw(4) << right
         << fs_size(fs::file_size(path)) << " "
         << path 
         << endl; 
}

void fs_process(const fs_entity& e)
{
   const auto& [path,status] = e;

   if(status.type()==fs::file_type::not_found) {
      cout << path << " does not exist" << endl;
      return;
   }

   display(e);
   if(status.type()==fs::file_type::directory) {
      for(const auto& i: fs::directory_iterator{path})
         fs_process({i,i.status()});
      return;
   }
}

void fs_process(const fs::path& p)
{
   fs_process({p,fs::status(p)});
}

int main(int argc, char *argv[])
{
   if(argc != 2) {
      cout << "Usage: " << argv[0] << " <path>" << endl;
      return 1;
   }

   try {
      fs_process(argv[1]);
   }
   catch(const exception& e) {
      cout << e.what() << endl;
      return 2;
   }
   return 0;
}
