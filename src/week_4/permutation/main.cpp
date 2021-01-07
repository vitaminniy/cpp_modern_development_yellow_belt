#include <algorithm>
#include <iostream>
#include <vector>

constexpr int factorial(int n) {
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

void print(const std::vector<int> &numbers) {
  int i = 0;
  for (const auto n : numbers) {
    if (i++ > 0)
      std::cout << ' ';
    std::cout << n;
  }
}

int main() {
  int n;
  std::cin >> n;

  std::vector<int> numbers(n);
  for (auto i = 0; i < n; ++i) {
    numbers[i] = i + 1;
  }

  std::vector<std::vector<int>> permutations;
  permutations.reserve(factorial(n));
  do {
    permutations.push_back(std::vector(numbers));
  } while (std::next_permutation(numbers.begin(), numbers.end()));

  std::sort(
      permutations.begin(), permutations.end(),
      [](const std::vector<int> &lhs, const std::vector<int> &rhs) -> bool {
        return std::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(),
                                            lhs.end());
      });

  for (const auto &p : permutations) {
    print(p);
    std::cout << std::endl;
  }

  return 0;
}
