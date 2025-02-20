#include <jank/util/process_location.hpp>

#include <string>

#include <boost/filesystem.hpp>

#include <jank/option.hpp>

#include <windows.h>

#include <iostream>


namespace jank::util
{

  std::string process_loc_win()
  {
    char path[MAX_PATH];
    DWORD size = GetModuleFileNameA(NULL, path, MAX_PATH);

    if (size == 0) {
        // Handle error
      return std::string();
    }
    std::string spath(path, size);
    std::cout << ":process-loc-win " << spath << std::endl;

    return spath;
  }
}
