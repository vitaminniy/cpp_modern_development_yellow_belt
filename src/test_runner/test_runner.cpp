#include "test_runner.h"
#include <stdexcept>

void Assert(bool b, const std::string &hint) { AssertEqual(b, true, hint); }

void AssertFalse(const std::string& hint) { throw std::runtime_error(hint); }

TestRunner::~TestRunner() {
  if (fail_count > 0) {
    std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
    exit(1);
  }
}
