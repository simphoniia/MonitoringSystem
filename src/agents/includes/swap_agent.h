#ifndef SRC_AGENT_INCLUDES_SWAP_AGENT_H_
#define SRC_AGENT_INCLUDES_SWAP_AGENT_H_

#include "base_agent.h"

namespace s21 {
class SwapAgent : public s21::BaseAgent {
 public:
  void RefreshData(std::ofstream &file) override;

 private:
  double total_swap_{};
  double used_swap_{};
  int proc_queue_length_{};
};
};  // namespace s21

#endif  //  SRC_AGENT_INCLUDES_SWAP_AGENT_H_