// #include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <memoryapi.h>

#include <iostream>

#include <boost/filesystem.hpp>

#include <jank/util/mapped_file.hpp>
#include <jank/option.hpp>

namespace jank::util
{
  mapped_file::mapped_file(mapped_file &&mf) noexcept
    : mfs{ std::move(mf.mfs) }
    , head{ mf.head }
    , size{ mf.size }
  {
    mf.mfs = boost::iostreams::mapped_file_source();
    mf.head = nullptr;
  }

  mapped_file::mapped_file(boost::iostreams::mapped_file_source mfs, char const * const h, size_t const s)
    : mfs{ std::move(mfs) }
    , head{ h }
    , size{ s }
  {
  }

  mapped_file::~mapped_file()
  {
    if (mfs.is_open())
      {
        mfs.close();
      }
  }

  result<mapped_file, native_persistent_string> map_file(native_transient_string const &path)
  {
    if(!boost::filesystem::exists(path.data()))
    {
      return err("file doesn't exist");
    }
    boost::iostreams::mapped_file_source file;
    file.open(path.data());
    if(!file.is_open())
    {
      return err("unable to open file");
    }

    return ok(jank::util::mapped_file{ std::move(file), file.data(), file.size() });
  }
}
