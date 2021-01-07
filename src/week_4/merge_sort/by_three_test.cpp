#include <vector>

#include "merge_by_three.cpp"
#include "test_runner.h"

void TestMergeSort() {
  std::vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
  MergeSort(v.begin(), v.end());
  AssertEqual(std::vector<int>{0, 1, 4, 4, 4, 5, 6, 6, 7}, v);
}

int main() {
  TestRunner runner;
  runner.RunTest(TestMergeSort, "TestMergeSort");

  return 0;
}
