#ifndef SRC_AGENT_INCLUDES_MEMORY_AGENT_H_
#define SRC_AGENT_INCLUDES_MEMORY_AGENT_H_

// [double] общий объем оперативной памяти (ram_total)
// [double] загрузка оперативной памяти в процентах (ram),
// [double] использование объема жесткого диска (hard_volume),
// [int] количество операций ввода-вывода для жесткого диска в секунду
// (hard_ops) [double] пропускная способность жесткого диска (hard_throughput)

#include "base_agent.h"

namespace s21 {
class MemoryAgent : public s21::BaseAgent {
 public:
  void RefreshData(std::ofstream &file) override;

 private:
  double ram_total_{};
  double ram_usage_{};
  double hard_usage_{};
  size_t hard_io_persec_{};
  double hard_throughput_{};
};
};  // namespace s21

#endif  //  SRC_AGENT_INCLUDES_MEMORY_AGENT_H_