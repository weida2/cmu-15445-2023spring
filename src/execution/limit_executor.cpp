//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// limit_executor.cpp
//
// Identification: src/execution/limit_executor.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "execution/executors/limit_executor.h"

namespace bustub {

LimitExecutor::LimitExecutor(ExecutorContext *exec_ctx, const LimitPlanNode *plan,
                             std::unique_ptr<AbstractExecutor> &&child_executor)
    : AbstractExecutor(exec_ctx), plan_(plan), child_executor_(std::move(child_executor)) {}

void LimitExecutor::Init() {
  // throw NotImplementedException("LimitExecutor is not implemented");
  child_executor_->Init();
  already_emits_ = 0;
}

auto LimitExecutor::Next(Tuple *tuple, RID *rid) -> bool {
  while (already_emits_ < plan_->limit_ && child_executor_->Next(tuple, rid)) {
    already_emits_++;
    return true;
  }
  return false;
}

}  // namespace bustub
