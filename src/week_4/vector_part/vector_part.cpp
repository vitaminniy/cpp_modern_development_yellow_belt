#include <algorithm>
#include <iostream>
#include <vector>

void PrintVectorPart(std::ostream &dst, const std::vector<int> &numbers) {
  auto it = find_if(numbers.begin(), numbers.end(),
                    [](const int n) -> bool { return n < 0; });

  auto begin = numbers.begin();
  auto i = 0;
  while (it != begin) {
    it--;

    if (i++ > 0) {
      dst << " ";
    }
    dst << *it;
  }
}

void PrintVectorPart(const std::vector<int> &numbers) {
  PrintVectorPart(std::cout, numbers);
}
