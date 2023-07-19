#ifndef SRC_AGENT_INCLUDES_BASE_AGENT_H_
#define SRC_AGENT_INCLUDES_BASE_AGENT_H_

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

namespace s21 {
class BaseAgent {
 public:
  virtual void RefreshData(std::ofstream& file) = 0;
};
};  // namespace s21

#endif  //  SRC_AGENT_INCLUDES_BASE_AGENT_H_