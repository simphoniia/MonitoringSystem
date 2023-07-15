#include <dlfcn.h>

#include <chrono>
#include <fstream>
#include <iomanip>
#include <set>
#include <sstream>
#include <string>

#include "../agents/includes/base_agent.h"
#include "../agents/includes/cpu_agent.h"
#include "../agents/includes/cpu_special_agent.h"
#include "../agents/includes/memory_agent.h"
#include "../agents/includes/network_agent.h"
#include "../agents/includes/swap_agent.h"
#include "../agents/includes/system_agent.h"
#include "../agents/includes/vmemory_agent.h"

namespace s21 {
class AgentCore {
 public:
  void UpdateMetrics();
  void CheckNewAgents();

 private:
  std::ofstream file_;
  std::string timestamp_;
  std::set<std::pair<bool, s21::BaseAgent*>> agents_ = {
      {true, new s21::CpuAgent},    {true, new s21::CpuSpecialAgent},
      {true, new s21::MemoryAgent}, {true, new s21::NetworkAgent},
      {true, new s21::SwapAgent},   {true, new s21::SystemAgent},
      {true, new s21::VmemoryAgent}};

  void LogFileCreation();
  void ChangeTimestamp();
};
}  // namespace s21
