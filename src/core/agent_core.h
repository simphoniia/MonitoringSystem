#include <dlfcn.h>

#include <map>
#include <memory>
#include <set>
#include <string>

#include "../agents/includes/base_agent.h"
#include "../configs/config_parser.h"

namespace s21 {
class DylibCompiler {
 public:
  ~DylibCompiler();
  std::map<std::string, std::pair<bool, std::shared_ptr<s21::BaseAgent>>>
  DylibCompile(std::set<std::string> new_agents);

 private:
  std::vector<void*> libs_;
};

class TimestampChanger {
 public:
  std::string GetTimestamp() {
    ChangeTimestamp();
    return timestamp_;
  };

 private:
  void ChangeTimestamp();
  std::string timestamp_;
};

class AgentCore {
 public:
  AgentCore();
  void SetConfigFile(Config* config);
  void UpdateMetrics();
  void CheckNewAgents();
  int NumberOfActiveAgents();
  void DisableAgent(const std::string& filepath);
  void EnableAgent(const std::string& filepath);

 private:
  TimestampChanger time_changer_;
  DylibCompiler compilier_;
  std::ofstream file_;
  std::map<std::string, std::pair<bool, std::shared_ptr<s21::BaseAgent>>>
      agents_;
  std::set<std::string> new_agents_;
  Config* config_{};
  void LogFileCreation();
  void WriteToLog();
};
}  // namespace s21
