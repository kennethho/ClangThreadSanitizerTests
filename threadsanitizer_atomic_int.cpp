#include <future>

#ifndef USE_BOOST_ATOMIC

#include <atomic>
using std::atomic;

#else

#include <boost/atomic.hpp>
using boost::atomic;

#endif

size_t const loop = 99999;

int foo(atomic<int>& x)
{
  for(size_t n = 0; ; ++n)
  {
    auto expected = x.load();
    auto desired = 0;
    x.compare_exchange_strong(
      expected,
      desired);

    if(n == loop)
      return desired;
  }
}

int main()
{
  atomic<int> x{1};
#ifndef USE_THREAD
  auto ret = std::async(std::launch::async,
                        [&] {
                          return foo(x);
                        });
#else
  auto t = std::thread([&] {
                         return foo(x);
                       });
#endif

  foo(x);

#ifndef USE_THREAD
  ret.get();
#else
  t.join();
#endif
  return 0;
}
