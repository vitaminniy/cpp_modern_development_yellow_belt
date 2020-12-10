#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int ndays;
  std::cin >> ndays;

  std::vector<int> days(ndays);

  long int sum = 0;
  for (int i = 0; i < ndays; i++) {
    std::cin >> days[i];
    sum += days[i];
  }

  long int avg = sum / ndays;
  auto count =
      std::count_if(days.begin(), days.end(), [avg](int i) { return i > avg; });

  std::cout << count << std::endl;
  for (size_t i = 0; i < days.size(); i++) {
    if (days[i] > avg)
      std::cout << i << " ";
  }
  std::cout << std::endl;
}
