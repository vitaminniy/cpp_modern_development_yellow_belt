#pragma once

#include "node.h"

#include <iostream>
#include <memory>

using namespace std;

shared_ptr<Node> ParseCondition(istream &is);

void TestParseCondition();
