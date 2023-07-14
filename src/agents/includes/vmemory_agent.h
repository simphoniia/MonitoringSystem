#ifndef SRC_AGENT_INCLUDES_VMEMORY_AGENT_H_
#define SRC_AGENT_INCLUDES_VMEMORY_AGENT_H_

#include <algorithm>
#include <array>
#include <iostream>
#include <memory>

namespace s21 {
class VmemoryAgent {
 public:
  double GetVirtualMemVolume() { return virtual_mem_volume_; };
  double GetVirtualMemFree() { return virtual_mem_free_; };
  void RefreshData();

 private:
  double virtual_mem_volume_{};
  double virtual_mem_free_{};
};
};  // namespace s21

#endif  //  SRC_AGENT_INCLUDES_VMEMORY_AGENT_H_