#include <dlfcn.h>

#include <chrono>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

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

 private:
  s21::CpuAgent cpu_agent_;
  s21::CpuSpecialAgent cpu_special_agent_;
  s21::MemoryAgent memory_agent_;
  s21::SwapAgent swap_agent_;
  s21::SystemAgent system_agent_;
  s21::VmemoryAgent vmemory_agent_;
  std::ofstream file_;
  std::string timestamp_;

  void LogFileCreation();
  void InsertToFile();
  void ChangeTimestamp();
};
}  // namespace s21
