#ifndef SRC_AGENT_INCLUDES_SYSTEM_AGENT_H_
#define SRC_AGENT_INCLUDES_SYSTEM_AGENT_H_

#include "base_agent.h"

namespace s21 {
class SystemAgent {
 public:
  long GetInodes() const { return inodes_; };
  double GetHardReadTime() const { return hard_read_time_; };
  int GetSystemErrors() const { return system_errors_; };
  int GetUSerAuths() const { return user_auths_; };
  void RefreshData();

 private:
  long inodes_{};
  double hard_read_time_{};
  int system_errors_{};
  int user_auths_{};
  int number_of_disks_{};
};
};  // namespace s21

#endif  //  SRC_AGENT_INCLUDES_SYSTEM_AGENT_H_