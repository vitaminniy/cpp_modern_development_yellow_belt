#include <algorithm>
#include <iterator>
#include <vector>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  const auto distance = std::distance(range_begin, range_end);
  if (distance < 2)
    return;

  const auto border = distance / 3;
  std::vector<typename RandomIt::value_type> left(range_begin,
                                                  range_begin + border);
  std::vector<typename RandomIt::value_type> middle(
      range_begin + border, range_begin + border + border);
  std::vector<typename RandomIt::value_type> right(
      range_begin + border + border, range_end);

  MergeSort(left.begin(), left.end());
  MergeSort(middle.begin(), middle.end());
  MergeSort(right.begin(), right.end());

  std::vector<typename RandomIt::value_type> tmp;
  tmp.reserve(border * 2);
  std::merge(left.begin(), left.end(), middle.begin(), middle.end(),
             std::back_inserter(tmp));
  std::merge(tmp.begin(), tmp.end(), right.begin(), right.end(), range_begin);
}
