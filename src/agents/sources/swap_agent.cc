#include "../includes/swap_agent.h"

#include "Utils/sub_functions.h"

s21::SwapAgent* s21::CreateObject() { return new s21::SwapAgent; }

void s21::SwapAgent::RefreshData(std::ofstream& file,
                                 std::chrono::steady_clock::time_point time,
                                 const std::string& timestamp) {
  if (!file.is_open()) return;
  if (!IsSetConfig()) return;
  if (std::chrono::duration_cast<std::chrono::seconds>(time - time_delta)
          .count() < config_->SWAP)
    return;
  static const std::string get_total_swap{
      "sysctl vm.swapusage | awk '{printf(\"%lf\", $4)}'"};
  static const std::string get_used_swap{
      "sysctl vm.swapusage | awk '{printf(\"%lf\", $7)}'"};
  static const std::string get_proc_queue_length{
      "top -l 1 | head -n 10 | grep \"Processes:\" | awk '{print $6}'"};

  std::string total_swap = SubFunctions::ExecCommand(get_total_swap.c_str());
  std::string used_swap = SubFunctions::ExecCommand(get_used_swap.c_str());
  std::string proc_queue_length =
      SubFunctions::ExecCommand(get_proc_queue_length.c_str());

  if (!total_swap.empty()) total_swap = SubFunctions::GetOnlyDigits(total_swap);
  if (!used_swap.empty()) used_swap = SubFunctions::GetOnlyDigits(used_swap);
  if (!proc_queue_length.empty())
    proc_queue_length = SubFunctions::GetOnlyDigits(proc_queue_length);

  try {
    total_swap_ = std::stod(total_swap);
    used_swap_ = std::stod(used_swap);
    proc_queue_length_ = std::stoi(proc_queue_length);
  } catch (...) {
    std::cerr << "convertation error!";
  }
  file << "[<" << timestamp << ">]   "
       << "swap_agent: total_swap: " << total_swap_
       << " | used_swap: " << used_swap_
       << " | proc_queue_length: " << proc_queue_length_ << '\n';
  config_->SetCurrentSwap(total_swap_, used_swap_, proc_queue_length_);
  time_delta = time;
}

inline bool s21::SwapAgent::IsSetConfig() { return config_; }

inline void s21::SwapAgent::SetConfigFile(Config* config) { config_ = config; }