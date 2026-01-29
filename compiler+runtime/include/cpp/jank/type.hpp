#pragma once

#include <map>
#include <set>
#include <string_view>
#include <unordered_map>
#include <deque>
#include <list>

#ifdef JANK_GC_ENABLE

#include <gc/gc_cpp.h>
#include <gc/gc_allocator.h>

#include <immer/heap/gc_heap.hpp>

#define JANK_NEW_GC new(GC)

#else // fall back to malloc/free

#include <immer/heap/malloc_heap.hpp>

#define JANK_NEW_GC new

#define GC_init() ((void)0)
#define GC_enable() ((void)0)
#define GC_enable_incremental(x) ((void)0)
#define GC_set_all_interior_pointers(x) ((void)0)

#include <cstdlib>

#define GC_malloc(sz)        std::malloc(sz)
#define GC_malloc_atomic(sz) std::malloc(sz)
#define GC_realloc(p, sz)    std::realloc(p, sz)
#define GC_free(p)           std::free(p)
#endif

#include <immer/heap/heap_policy.hpp>
#include <immer/memory_policy.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <folly/FBVector.h>

#include <jtl/primitive.hpp>

namespace jank
{
  template <typename T>
#ifdef JANK_GC_ENABLE
  using native_allocator = gc_allocator<T>;
  using heap_policy = immer::gc_heap;
  using transience_policy = immer::gc_transience_policy;
#else
  using native_allocator = std::allocator<T>;
  using heap_policy = immer::malloc_heap;
  using transience_policy = immer::no_transience_policy;
#endif
  using memory_policy = immer::memory_policy<immer::heap_policy<heap_policy>,
                                             immer::no_refcount_policy,
                                             immer::default_lock_policy,
                                             transience_policy,
                                             false>;

  using native_persistent_string_view = std::string_view;
  using native_big_integer
    = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<>>;
  using native_big_decimal
    = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<100>,
                                    boost::multiprecision::et_off>;

  template <typename T>
  using native_vector = folly::fbvector<T, native_allocator<T>>;
  template <typename T>
  using native_deque = std::deque<T, native_allocator<T>>;
  template <typename T>
  using native_list = std::list<T, native_allocator<T>>;
  template <typename K, typename V>
  using native_map = std::map<K, V, std::less<K>, native_allocator<std::pair<K const, V>>>;
  template <typename T>
  using native_set = std::set<T, std::less<T>, native_allocator<T>>;

  template <typename K, typename V, typename Hash = std::hash<K>, typename Pred = std::equal_to<K>>
  using native_unordered_map
    = std::unordered_map<K, V, Hash, Pred, native_allocator<std::pair<K const, V>>>;

  /* TODO: This will leak if it's stored in a GC-tracked object. */
  using native_transient_string = std::string;
}

#include <jank/hash.hpp>

/* NOTE: jtl::immutable_string.hpp includes this file to learn about integer
 * types, but we also include it to forward our string type. Pragma once allows
 * this to work, but we need to make sure the order is right. */
#include <jtl/immutable_string.hpp>
