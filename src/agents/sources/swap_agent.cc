#include "../includes/swap_agent.h"

#include "Utils/sub_functions.h"

void s21::SwapAgent::RefreshData() {
  const std::string get_total_swap{
      "sysctl vm.swapusage | awk '{printf(\"%lf\", $4)}'"};
  const std::string get_used_swap{
      "sysctl vm.swapusage | awk '{printf(\"%lf\", $7)}'"};
  const std::string get_proc_queue_length{
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
    std::cerr << "convertaion error!";
  }
}