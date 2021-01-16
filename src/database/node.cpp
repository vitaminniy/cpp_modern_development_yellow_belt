#include "node.h"
#include "date.h"
#include <memory>

LogicalOperationNode::LogicalOperationNode(LogicalOperation op,
                                           std::shared_ptr<const Node> left,
                                           std::shared_ptr<const Node> right)
    : op_(op), left_(left), right_(right) {}

bool LogicalOperationNode::Evaluate(const Date &date,
                                    const std::string &event) const {
  switch (op_) {
  case LogicalOperation::Or:
    return left_->Evaluate(date, event) || right_->Evaluate(date, event);
  case LogicalOperation::And:
    return left_->Evaluate(date, event) && right_->Evaluate(date, event);
  }
  return false;
}

DateComparisonNode::DateComparisonNode(Comparison cmp, const Date &date)
    : cmp_(cmp), date_(date) {}

bool DateComparisonNode::Evaluate(const Date &date,
                                  const std::string & /*event*/) const {
  switch (cmp_) {
  case Comparison::Equal:
    return date == date_;
  case Comparison::NotEqual:
    return date != date_;
  case Comparison::Less:
    return date < date_;
  case Comparison::LessOrEqual:
    return date <= date_;
  case Comparison::Greater:
    return date > date_;
  case Comparison::GreaterOrEqual:
    return date >= date_;
  }
  return false;
}

EventComparisonNode::EventComparisonNode(Comparison cmp,
                                         const std::string &event)
    : cmp_(cmp), event_(event) {}

bool EventComparisonNode::Evaluate(const Date & /*date*/,
                                   const std::string &event) const {
  switch (cmp_) {
  case Comparison::Equal:
    return event == event_;
  case Comparison::NotEqual:
    return event != event_;
  case Comparison::Less:
    return event < event_;
  case Comparison::LessOrEqual:
    return event <= event_;
  case Comparison::Greater:
    return event > event_;
  case Comparison::GreaterOrEqual:
    return event >= event_;
  }
  return false;
}
