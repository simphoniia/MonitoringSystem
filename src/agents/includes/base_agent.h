#ifndef SRC_AGENT_INCLUDES_BASE_AGENT_H_
#define SRC_AGENT_INCLUDES_BASE_AGENT_H_

#include <algorithm>
#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "../../configs/config_parser.h"

namespace s21 {
class BaseAgent {
 public:
  virtual void RefreshData(std::ofstream& file,
                           std::chrono::steady_clock::time_point time,
                           const std::string& timestamp) = 0;

  virtual bool IsSetConfig() = 0;
  virtual void SetConfigFile(Config* config) = 0;
  virtual int GetAgentType() = 0;
};
};  // namespace s21

#endif  //  SRC_AGENT_INCLUDES_BASE_AGENT_H_