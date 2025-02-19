#include "execution/plans/abstract_plan.h"
#include "optimizer/optimizer.h"

// Note for 2023 Spring: You can add all optimizer rule implementations and apply the rules as you want in this file.
// Note that for some test cases, we force using starter rules, so that the configuration here won't take effects.
// Starter rule can be forcibly enabled by `set force_optimizer_starter_rule=yes`.

namespace bustub {

auto Optimizer::OptimizeCustom(const AbstractPlanNodeRef &plan) -> AbstractPlanNodeRef {
  auto p = plan;
  p = OptimizeMergeProjection(p);     // projection
  p = OptimizeMergeFilterNLJ(p);      // filter + nlj -> nlj'
  p = OptimizeNLJAsHashJoin(p);       // nlj -> hash_join
  p = OptimizeOrderByAsIndexScan(p);  // order-by -> index_scan
  p = OptimizeSortLimitAsTopN(p);     // sort + limit -> topn
  p = OptimizeMergeFilterScan(p);     // filter+seq_scan -> seq_scan(filter)
                                      // 谓词下推到scan
  return p;
}

}  // namespace bustub
