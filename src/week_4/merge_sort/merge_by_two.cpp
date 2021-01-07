#include <algorithm>
#include <iterator>
#include <vector>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  const auto distance = std::distance(range_begin, range_end);
  if (distance < 2)
    return;

  const auto half = distance / 2;
  std::vector<typename RandomIt::value_type> left(range_begin,
                                                  range_begin + half);
  std::vector<typename RandomIt::value_type> right(range_begin + half,
                                                   range_end);

  MergeSort(left.begin(), left.end());
  MergeSort(right.begin(), right.end());

  std::merge(left.begin(), left.end(), right.begin(), right.end(), range_begin);
}
