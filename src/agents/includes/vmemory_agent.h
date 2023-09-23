#ifndef SRC_AGENT_INCLUDES_VMEMORY_AGENT_H_
#define SRC_AGENT_INCLUDES_VMEMORY_AGENT_H_

#include "base_agent.h"

namespace s21 {
class VmemoryAgent : public s21::BaseAgent {
 public:
  void RefreshData(std::ofstream& file) override;
  bool IsSetConfig() override;
  void SetConfigFile(Config* config) override;
 private:
  Config* config_{};
  double virtual_mem_volume_{};
  double virtual_mem_free_{};
};

extern "C" {
s21::VmemoryAgent* CreateObject();
}

};  // namespace s21

#endif  //  SRC_AGENT_INCLUDES_VMEMORY_AGENT_H_