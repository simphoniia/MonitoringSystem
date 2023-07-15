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
  for (auto it = agents_.begin(); it != agents_.end(); ++it) {
    if ((*it).first == true) (*it).second->RefreshData(file_);
  }

  file_.close();
}

void s21::AgentCore::CheckNewAgents() {}

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