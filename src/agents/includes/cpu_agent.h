#ifndef SRC_AGENT_INCLUDES_CPU_AGENT_H_
#define SRC_AGENT_INCLUDES_CPU_AGENT_H_

#include <algorithm>
#include <array>
#include <iostream>
#include <memory>

namespace s21 {
class CpuAgent {
 public:
  double GetCpuLoading() { return cpu_loading_; }
  int GetProcessCount() { return process_count_; }
  void RefreshData();

 private:
  double cpu_loading_{};
  size_t process_count_{};
};
};  // namespace s21

#endif  //  SRC_AGENT_INCLUDES_CPU_AGENT_H_