#include <dlfcn.h>

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <thread>

#include "../agents/includes/base_agent.h"
#include "../configs/config_parser.h"

namespace s21 {
class AgentCore {
 public:
  AgentCore();
  void SetConfigFile(Config* config);
  ~AgentCore();
  void UpdateMetrics();
  void CheckNewAgents();
  int NumberOfActiveAgents();
  void DisableAgent(const std::string &filepath);
  void EnableAgent(const std::string &filepath);

 private:
  std::ofstream file_;
  std::string timestamp_;
  std::map<std::string, std::pair<bool, std::shared_ptr<s21::BaseAgent>>>
      agents_;
  std::set<std::string> new_agents_;
  std::vector<void*> libs_;
  Config* config_;
  void LogFileCreation();
  void ChangeTimestamp();
  void WriteToLog();
  void DylibCompile();
};
}  // namespace s21
