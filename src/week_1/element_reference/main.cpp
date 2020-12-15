#include <map>
#include <stdexcept>

template <class Key, class Value>
Value& GetRefStrict(std::map<Key, Value>& m, Key k) {
  const auto count = m.count(k);
  if (count == 0)
    throw std::runtime_error("missing key");

  return m[k];
}
