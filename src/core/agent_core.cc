#include "agent_core.h"

s21::AgentCore::AgentCore() { CheckNewAgents(); }

void s21::AgentCore::UpdateMetrics() {
  LogFileCreation();
  ChangeTimestamp();
  std::thread check_agents{&AgentCore::CheckNewAgents, this};
  std::thread write_to_log(&AgentCore::WriteToLog, this);

  check_agents.join();
  write_to_log.join();
  file_.close();
}

void s21::AgentCore::CheckNewAgents() {
  static std::string folderPath = "objects";  // Путь к папке
  // /Users/sullustd/MonitoringSystem/src/core/agent_core.cc
  try {
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
      if (entry.is_regular_file()) {
        std::string filePath = entry.path().string();
        if (std::filesystem::path(filePath).extension() == ".dylib") {
          new_agents_.insert(filePath);
        }
      }
    }
  } catch (const std::exception& e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
  }
  DylibCompile();
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

void s21::AgentCore::ChangeTimestamp() {
  auto now = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(now);
  std::stringstream stream;
  stream << std::put_time(std::localtime(&time), "%H:%M:%S");
  file_ << "TIMASTAMP: <" << stream.str() << ">\n";
}

void s21::AgentCore::WriteToLog() {
  for (auto it = agents_.begin(); it != agents_.end(); ++it) {
    if ((*it).second.first == true) {
      (*it).second.second->RefreshData(file_);
    }
  }
}

void s21::AgentCore::DylibCompile() {
  for (auto it = new_agents_.begin(); it != new_agents_.end(); ++it) {
    void* libraryHandle = dlopen((*it).c_str(), RTLD_LAZY);
    if (!libraryHandle) {
      throw std::out_of_range("NO FILE");
    }
    s21::BaseAgent* (*createFunction)() =
        reinterpret_cast<s21::BaseAgent* (*)()>(
            dlsym(libraryHandle, "CreateObject"));
    if (!createFunction) {
      throw std::out_of_range(
          "Не удалось найти функцию создания объекта в библиотеке");
      dlclose(libraryHandle);
    }
    std::shared_ptr<s21::BaseAgent> ptr{createFunction()};
    agents_.insert({*it, {true, ptr}});
  }
}
