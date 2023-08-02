#ifndef SRC_AGENT_INCLUDES_NETWORK_AGENT_H_
#define SRC_AGENT_INCLUDES_NETWORK_AGENT_H_

#include "../sources/Utils/sub_functions.h"
#include "base_agent.h"
namespace s21 {
class NetworkAgent : public s21::BaseAgent {
 public:
  bool GetAccessToSite() { return site_access_; }
  double GetInetThroughput() { return inet_throughput_; }
  void RefreshData(std::ofstream& file) override;
  bool IsSetConfig() override;
  void SetConfigFile(Config* config) override;
  void SetSiteToGetAccess(const std::string& site);

 private:
  Config* config_{};
  bool site_access_{};
  double inet_throughput_{};
  std::string site_;
};

extern "C" {
s21::NetworkAgent* CreateObject();
}

};  // namespace s21

#endif  //  SRC_AGENT_INCLUDES_NETWORK_AGENT_H_