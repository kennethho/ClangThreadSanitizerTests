#include <future>

#ifndef USE_BOOST_ATOMIC

#include <memory>
#include <atomic>
using std::shared_ptr;
using std::make_shared;
using std::atomic_load;
using std::atomic_compare_exchange_strong;

#else

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
using boost::shared_ptr;
using boost::make_shared;
using boost::atomic_load;
using boost::shared_ptr;
using boost::make_shared;
using boost::atomic_load;

template <class T>
bool atomic_compare_exchange_strong(shared_ptr<T> * p, shared_ptr<T> * v, shared_ptr<T> w)
{
  return boost::atomic_compare_exchange(p, v, w);
}

#endif

size_t const loop = 99999;

shared_ptr<int> foo(shared_ptr<int>& x)
{
  for(size_t n = 0; ; ++n)
  {
    auto expected = atomic_load(&x);
    auto desired = make_shared<int>(*expected);
    atomic_compare_exchange_strong(
      &x,
      &expected,
      desired);

    if(n == loop)
      return desired;
  }
}

int main()
{
  auto x = make_shared<int>(1);
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
