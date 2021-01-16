#pragma once

#include "date.h"

#include <memory>
#include <string>

enum class Comparison {
  Less,
  LessOrEqual,
  Greater,
  GreaterOrEqual,
  Equal,
  NotEqual,
};

enum class LogicalOperation {
  Or,
  And,
};

struct Node {
  Node() = default;
  virtual bool Evaluate(const Date &date, const std::string &event) const = 0;
};

struct EmptyNode final : public Node {
  EmptyNode() = default;

  virtual inline bool Evaluate(const Date &,
                               const std::string &) const override {
    return true;
  }
};

class LogicalOperationNode final : public Node {
public:
  LogicalOperationNode(LogicalOperation op, std::shared_ptr<const Node> left,
                       std::shared_ptr<const Node> right);

  virtual bool Evaluate(const Date &date,
                        const std::string &event) const override;

private:
  const LogicalOperation op_{};
  const std::shared_ptr<const Node> left_{}, right_{};
};

class DateComparisonNode final : public Node {
public:
  DateComparisonNode(Comparison cmp, const Date &date);

  virtual bool Evaluate(const Date &date,
                        const std::string &event) const override;

private:
  const Comparison cmp_{};
  const Date date_{};
};

class EventComparisonNode final : public Node {
public:
  EventComparisonNode(Comparison cmp, const std::string &event);

  virtual bool Evaluate(const Date &date,
                        const std::string &event) const override;

private:
  const Comparison cmp_{};
  const std::string event_{};
};
