#ifndef SRC_AGENT_INCLUDES_NETWORK_AGENT_H_
#define SRC_AGENT_INCLUDES_NETWORK_AGENT_H_

#include "base_agent.h"
namespace s21 {
class NetworkAgent : public s21::BaseAgent {
 public:
  bool GetAccessToSite() { return site_access_; }
  double GetInetThroughput() { return inet_throughput_; }
  void RefreshData(std::ofstream& file,
                   std::chrono::steady_clock::time_point time,
                   const std::string& timestamp) override;
  void SetSiteToGetAccess(const std::string& site);
  bool IsSetConfig() override;
  void SetConfigFile(Config* config) override;
  int GetAgentType() override;

 private:
  std::chrono::steady_clock::time_point time_delta =
      std::chrono::steady_clock::now();
  Config* config_{};
  bool site_access_{};
  double inet_throughput_{};
  std::string site_;
  int update_time_{3};
};

extern "C" {
s21::NetworkAgent* CreateObject();
}

};  // namespace s21

#endif  //  SRC_AGENT_INCLUDES_NETWORK_AGENT_H_