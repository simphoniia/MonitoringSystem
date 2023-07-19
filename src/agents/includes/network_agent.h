#ifndef SRC_AGENT_INCLUDES_NETWORK_AGENT_H_
#define SRC_AGENT_INCLUDES_NETWORK_AGENT_H_

// [int : 0 -> не доступен, 1 -> доступен] доступность адреса (<url>)
// [double] пропускная способность используемых сетевых интерфейсов
// (inet_throughput)

#include "../sources/Utils/sub_functions.h"
#include "base_agent.h"
namespace s21 {
class NetworkAgent : public s21::BaseAgent {
 public:
  bool GetAccessToSite() { return site_access_; }
  double GetInetThroughput() { return inet_throughput_; }
  void RefreshData(std::ofstream& file) override;

 private:
  bool site_access_{};
  double inet_throughput_{};
  const char* site = "2ip.ru";
};

extern "C" {
s21::NetworkAgent* CreateObject();
}

};  // namespace s21

#endif  //  SRC_AGENT_INCLUDES_NETWORK_AGENT_H_