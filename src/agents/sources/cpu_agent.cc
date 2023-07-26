#include "../includes/cpu_agent.h"

#include "Utils/sub_functions.h"

using namespace std::chrono;

s21::CpuAgent* s21::CreateObject() { return new s21::CpuAgent; }

void s21::CpuAgent::RefreshData(std::ofstream& file) {
  if (!file.is_open()) return;
  static std::string get_usage_percent =
      "top -l 1 | grep -o -E '\\d{1,9}.\\d{0,9}% idle'";
  static std::string get_process_count =
      "hostinfo | grep -o -E '\\d{1,9} tasks'";

  std::string usage_percent =
      SubFunctions::ExecCommand(get_usage_percent.c_str());
  std::string process_count =
      SubFunctions::ExecCommand(get_process_count.c_str());

  if (!process_count.empty())
    process_count = SubFunctions::GetOnlyDigits(process_count);

  if (!usage_percent.empty())
    usage_percent = SubFunctions::GetOnlyDigits(usage_percent);

  try {
    cpu_loading_ = 100.0 - std::stod(usage_percent);
    process_count_ = std::stoi(process_count);
  } catch (...) {
    std::cerr << "convertaion error!";
  }
  file << "cpu_agent: cpu: " << cpu_loading_
       << " | processes: " << process_count_ << '\n';
  if (IsSetConfig()) {
    config_->SetCurrentCPU(cpu_loading_, process_count_);
  }
}

inline bool s21::CpuAgent::IsSetConfig() { return config_; }

inline void s21::CpuAgent::SetConfigFile(Config* config) { config_ = config; }