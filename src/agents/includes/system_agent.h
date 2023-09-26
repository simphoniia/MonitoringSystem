#ifndef SRC_AGENT_INCLUDES_SYSTEM_AGENT_H_
#define SRC_AGENT_INCLUDES_SYSTEM_AGENT_H_

#include "base_agent.h"

namespace s21 {
class SystemAgent : public s21::BaseAgent {
 public:
  void RefreshData(std::ofstream& file, std::chrono::steady_clock::time_point time) override;
  bool IsSetConfig() override;
  void SetConfigFile(Config* config) override;
 private:
 std::chrono::steady_clock::time_point time_delta = std::chrono::steady_clock::now();
  Config* config_{};
  long inodes_{};
  double hard_read_time_{};
  int system_errors_{};
  int user_auths_{};
  int number_of_disks_{};
  int update_time_{3};
};

extern "C" {
s21::SystemAgent* CreateObject();
}

};  // namespace s21

#endif  //  SRC_AGENT_INCLUDES_SYSTEM_AGENT_H_