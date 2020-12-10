#include <iostream>
#include <vector>

int main() {
  int nblocks, r;
  std::cin >> nblocks >> r;

  uint64_t total = 0;
  for (int i = 0; i < nblocks; i++) {
    uint64_t w, h, d;
    std::cin >> w >> h >> d;

    total += static_cast<uint64_t>(w * h * d * r);
  }
  std::cout << total << std::endl;
}
