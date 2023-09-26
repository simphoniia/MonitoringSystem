#ifndef SRC_AGENT_INCLUDES_CPU_AGENT_H_
#define SRC_AGENT_INCLUDES_CPU_AGENT_H_

#include "base_agent.h"

namespace s21 {
class CpuAgent : public s21::BaseAgent {
 public:
  void RefreshData(std::ofstream& file, std::chrono::steady_clock::time_point time) override;
  bool IsSetConfig() override;
  void SetConfigFile(Config* config) override;
 private:
  std::chrono::steady_clock::time_point time_delta = std::chrono::steady_clock::now();
  Config* config_{};
  double cpu_loading_{};
  size_t process_count_{};
  int update_time_{3};
};

extern "C" {
s21::CpuAgent* CreateObject();
}

};  // namespace s21

#endif  //  SRC_AGENT_INCLUDES_CPU_AGENT_H_