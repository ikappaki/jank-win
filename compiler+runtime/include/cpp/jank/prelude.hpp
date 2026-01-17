#pragma once

/* This file is turned into a pre-compiled header which is included at run-time
 * to provide fast access to jank's C++ API. */

#ifdef __MINGW64__
// Workaround to make the std::ifstream(const char*) constructor
// available to jank
#include <fstream>
std::ifstream __jank_mingw64_ifs("");
std::ofstream __jank_mingw64_ofs;
#endif

#include <jank/runtime/convert/builtin.hpp>
#include <jank/runtime/visit.hpp>
#include <jank/runtime/context.hpp>
#include <jank/runtime/core/truthy.hpp>
#include <jank/runtime/core/seq.hpp>
#include <jank/runtime/core.hpp>
#include <jank/util/scope_exit.hpp>
