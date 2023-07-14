#ifndef SRC_AGENT_INCLUDES_SWAP_AGENT_H_
#define SRC_AGENT_INCLUDES_SWAP_AGENT_H_

#include <algorithm>
#include <array>
#include <iostream>
#include <memory>

namespace s21 {
class SwapAgent {
 public:
  double GetTotalSwap() const { return total_swap_; };
  double GetUsedSwap() const { return used_swap_; };
  int GetProcQueueLength() const { return proc_queue_length_; };
  void RefreshData();

 private:
  double total_swap_{};
  double used_swap_{};
  int proc_queue_length_{};
};
};  // namespace s21

#endif  //  SRC_AGENT_INCLUDES_SWAP_AGENT_H_