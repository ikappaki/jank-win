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
    : fd{ mf.fd }
    , head{ mf.head }
    , size{ mf.size }
  {
    mf.fd = -1;
    mf.head = nullptr;
  }

  mapped_file::mapped_file(int const f, char const * const h, size_t const s)
    : fd{ f }
    , head{ h }
    , size{ s }
  {
  }

  mapped_file::~mapped_file()
  {
    if(head != nullptr)
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast): I want const everywhere else.
    {
      // munmap(reinterpret_cast<void *>(const_cast<char *>(head)), size);
    }
    if(fd >= 0)
    {
      ::close(fd);
    }
  }

  result<mapped_file, native_persistent_string> map_file(native_transient_string const &path)
  {
    if(!boost::filesystem::exists(path.data()))
    {
      return err("file doesn't exist");
    }
    auto const file_size(boost::filesystem::file_size(path.data()));
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
    auto const fd(::open(path.data(), O_RDONLY));
    if(fd < 0)
    {
      return err("unable to open file");
    }

    std::cout << ":mapping " << path.data() << std::endl;
    char* buffer = new char[file_size];
    if (read(fd, buffer, file_size) == -1)
      {
        return err("unable to read file");
      }

    char const * const head(buffer);
    // char const * const head(nullptr);
      // reinterpret_cast<char const *>(nullptr// mmap(nullptr, file_size, PROT_READ, MAP_PRIVATE, fd, 0)
      //                                ));

    /* MAP_FAILED is a macro which does a C-style cast. */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast,performance-no-int-to-ptr)
    // if(head == MAP_FAILED)
    if(head == nullptr)
#pragma clang diagnostic pop
    {
      return err("unable to map file");
    }

    return ok(jank::util::mapped_file{ fd, head, file_size });
  }
}
