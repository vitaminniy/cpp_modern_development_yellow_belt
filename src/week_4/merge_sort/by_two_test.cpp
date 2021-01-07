#include <vector>

#include "merge_by_two.cpp"
#include "test_runner.h"

void TestMergeSort() {
  std::vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(v.begin(), v.end());
  AssertEqual(std::vector<int>{0, 1, 4, 4, 4, 6, 6, 7}, v);
}

int main() {
  TestRunner runner;
  runner.RunTest(TestMergeSort, "TestMergeSort");

  return 0;
}
