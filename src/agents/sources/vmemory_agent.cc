#include "../includes/vmemory_agent.h"

#include "Utils/sub_functions.h"

s21::VmemoryAgent* s21::CreateObject() { return new s21::VmemoryAgent; }

double GetPage(const std::string& command);

void s21::VmemoryAgent::RefreshData(std::ofstream& file,
                                    std::chrono::steady_clock::time_point time,
                                    const std::string& timestamp) {
  if (!file.is_open()) return;
  if (!IsSetConfig()) return;
  if (std::chrono::duration_cast<std::chrono::seconds>(time - time_delta)
          .count() < config_->VMEM)
    return;
  static const std::string get_virtual_page_size{
      "vm_stat | grep 'page size' | awk '{print $8}'"};
  static const std::string get_pages_free{
      "vm_stat | grep 'Pages free' | awk '{printf(\"%lf\", $3)}'"};
  static const std::string get_pages_active{
      "vm_stat | grep 'Pages active' | awk '{printf(\"%lf\", $3)}'"};
  static const std::string get_pages_inactive{
      "vm_stat | grep 'Pages inactive' | awk '{printf(\"%lf\", $3)}'"};
  static const std::string get_pages_speculative{
      "vm_stat | grep 'Pages speculative' | awk '{printf(\"%lf\", $3)}'"};
  static const std::string get_pages_wired_down{
      "vm_stat | grep 'Pages wired down' | awk '{printf(\"%lf\", $4)}'"};

  double page_size = GetPage(get_virtual_page_size);
  double pages_free = GetPage(get_pages_free);
  double pages_active = GetPage(get_pages_active);
  double pages_inactive = GetPage(get_pages_inactive);
  double pages_speculative = GetPage(get_pages_speculative);
  double pages_wired_down = GetPage(get_pages_wired_down);

  virtual_mem_free_ = (page_size * pages_free) / 1024 / 1024;
  virtual_mem_volume_ = (pages_free + pages_active + pages_inactive +
                         pages_speculative + pages_wired_down) *
                        page_size / 1024 / 1024;
  file << "[<" << timestamp << ">]   "
       << "v_memory_agent: virtual_mem_volume: " << virtual_mem_volume_ << " MB"
       << " | virtual_mem_free: " << virtual_mem_free_ << " MB\n";
  config_->SetCurrentVMemory(virtual_mem_volume_, virtual_mem_free_);
  time_delta = time;
}

double GetPage(const std::string& command) {
  std::string result = SubFunctions::ExecCommand(command.c_str());
  return stod(result);
}

inline bool s21::VmemoryAgent::IsSetConfig() { return config_; }

inline void s21::VmemoryAgent::SetConfigFile(Config* config) {
  config_ = config;
}