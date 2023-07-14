#ifndef SRC_AGENT_INCLUDES_CPU_SPECIAL_AGENT_H_
#define SRC_AGENT_INCLUDES_CPU_SPECIAL_AGENT_H_

#include "base_agent.h"

namespace s21 {
class CpuSpecialAgent : public s21::BaseAgent {
 public:
  double GetCpuIdleUsage() { return cpu_idle_usage_; };
  double GetCpuUserUsage() { return cpu_user_usage_; };
  double GetCpuPrivelegedUsage() { return cpu_priveleged_usage_; };
  void RefreshData(std::ofstream &file) override;

 private:
  double cpu_idle_usage_{};
  double cpu_user_usage_{};
  double cpu_priveleged_usage_{};
  double cpu_dpc_usage_{};
  double cpu_interrapt_usage_{};
};
};  // namespace s21

#endif  //  SRC_AGENT_INCLUDES_CPU_SPECIAL_AGENT_H_