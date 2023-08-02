#include "../includes/memory_agent.h"

#include "Utils/sub_functions.h"

s21::MemoryAgent* s21::CreateObject() { return new s21::MemoryAgent; }

double GetRamTotal(const std::string& command);
double GetRamUsage(const std::string& command);
double GetHardUsage(const std::string& command);
int GetHardIOUsage(const std::string& command);
double GetHardThroughput(const std::string& command);

void s21::MemoryAgent::RefreshData(std::ofstream& file) {
  if (!file.is_open()) return;
  if (!IsSetConfig()) return;
  static std::string get_ram_total =
      "sysctl hw.memsize | grep -o -E \"\\d{1,20}\"";
  static std::string get_ram_usage =
      "top -l 1 | grep -o -E 'PhysMem: \\d{1,9}'";
  static std::string get_hard_usage = "df -h ./ | awk '{print $3}' | tail -1";
  static std::string get_hard_io_usage =
      "iostat -c 2 | awk '{print $2}' | tail -1";
  static std::string get_hard_throughput =
      "dd if=/dev/zero of=/tmp/test.img bs=300000000 count=1 2>>output.txt";

  ram_total_ = ::GetRamTotal(get_ram_total);
  ram_usage_ = ::GetRamUsage(get_ram_usage);
  hard_usage_ = ::GetHardUsage(get_hard_usage);
  hard_io_persec_ = ::GetHardIOUsage(get_hard_io_usage);
  hard_throughput_ = ::GetHardThroughput(get_hard_throughput);
  file << "memory_agent: ram_total " << ram_total_ << " | ram: " << ram_usage_
       << " | hard_volume: " << hard_usage_
       << " | hard_ops: " << hard_io_persec_
       << " | hard_throughput: " << hard_throughput_ << '\n';

  config_->SetCurrentMemory(ram_total_, ram_usage_, hard_usage_, hard_io_persec_, hard_throughput_);
}

double GetRamTotal(const std::string& command) {
  std::string result = SubFunctions::ExecCommand(command.c_str());

  if (!result.empty()) result = SubFunctions::GetOnlyDigits(result);

  // Translate to megabytes;
  double res = std::stod(result);
  res = res / 1024 / 1024;
  return res;
}

double GetRamUsage(const std::string& command) {
  std::string result = SubFunctions::ExecCommand(command.c_str());

  if (!result.empty()) result = SubFunctions::GetOnlyDigits(result);

  return std::stoi(result);
}

double GetHardUsage(const std::string& command) {
  std::string result = SubFunctions::ExecCommand(command.c_str());

  if (!result.empty()) result = SubFunctions::GetOnlyDigits(result);

  return std::stod(result);
}

int GetHardIOUsage(const std::string& command) {
  std::string result = SubFunctions::ExecCommand(command.c_str());

  if (!result.empty()) result = SubFunctions::GetOnlyDigits(result);

  return std::stoi(result);
}

double GetHardThroughput(const std::string& command) {
  SubFunctions::ExecCommand(command.c_str());

  std::string result =
      SubFunctions::ExecCommand("cat output.txt | tail -1 | awk '{print $7}'");
  SubFunctions::ExecCommand("rm -rf output.txt | rm -rf /tmp/test.img");

  if (!result.empty()) result = SubFunctions::GetOnlyDigits(result);

  // Translate to megabytes
  double res = std::stod(result);
  res = res / 1024 / 1024;

  return res;
}

inline bool s21::MemoryAgent::IsSetConfig() { return config_; }

inline void s21::MemoryAgent::SetConfigFile(Config* config) { config_ = config; }