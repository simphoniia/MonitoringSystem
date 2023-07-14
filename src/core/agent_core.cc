#include "agent_core.h"

/*
Создать виртуальный класс BaseAgent с одним виртуальным методом RefreshData().
Унаследовать от него все готовые агенты.
Перенести всю логику записи данных в файл внутрь методов RefreshData().
Создать в Ядре std::map<?, BaseAgent> пушить/удалять в неё новых/старых агентов
*/

void s21::AgentCore::UpdateMetrics() {
  LogFileCreation();
  ChangeTimestamp();

  cpu_agent_.RefreshData();
  system_agent_.RefreshData();
  swap_agent_.RefreshData();
  memory_agent_.RefreshData();
  cpu_special_agent_.RefreshData(file_);
  vmemory_agent_.RefreshData();

  InsertToFile();
  file_.close();
}

void s21::AgentCore::LogFileCreation() {
  auto now = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(now);
  std::stringstream stream;
  stream << std::put_time(std::localtime(&time), "%Y-%m-%d");
  std::string date_string = stream.str();

  std::string fname =
      "logs/" + date_string + ".txt";  // путь к файлу (изменить!)
  file_.open(fname, std::ios::app);
}

void s21::AgentCore::InsertToFile() {
  file_ << "[<" << timestamp_ << ">]"
        << " | cpu: " << cpu_agent_.GetCpuLoading()
        << " | processes: " << cpu_agent_.GetProcessCount() << " | ram_total "
        << memory_agent_.GetRamTotal()
        << " | ram: " << memory_agent_.GetRamUsage()
        << " | hard_volume: " << memory_agent_.GetHardUsage()
        << " | hard_ops: " << memory_agent_.GetHardIOoperations()
        << " | hard_throughput: " << memory_agent_.GetHardThroughput()
        << " | total_swap: " << swap_agent_.GetTotalSwap()
        << " | used_swap: " << swap_agent_.GetUsedSwap()
        << " | proc_queue_length: " << swap_agent_.GetProcQueueLength()
        << " | virtual_mem_volume: " << vmemory_agent_.GetVirtualMemVolume()
        << " MB"
        << " | virtual_mem_free: " << vmemory_agent_.GetVirtualMemFree()
        << " MB"
        << " | inodes: " << system_agent_.GetInodes()
        << " | system_errors: " << system_agent_.GetSystemErrors()
        << " | user_auths: " << system_agent_.GetUSerAuths()
        << " | hard_read_time: " << system_agent_.GetHardReadTime()
        << " MB/s\n";
}

void s21::AgentCore::ChangeTimestamp() {
  auto now = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(now);
  std::stringstream stream;
  stream << std::put_time(std::localtime(&time), "%H:%M:%S");
  timestamp_ = stream.str();
}