#ifndef SRC_AGENT_INCLUDES_CPU_AGENT_H_
#define SRC_AGENT_INCLUDES_CPU_AGENT_H_

#include "base_agent.h"

namespace s21 {
class CpuAgent : public s21::BaseAgent {
 public:
  void RefreshData(std::ofstream &file) override;

 private:
  double cpu_loading_{};
  size_t process_count_{};
};
};  // namespace s21

#endif  //  SRC_AGENT_INCLUDES_CPU_AGENT_H_