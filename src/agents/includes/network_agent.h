#ifndef SRC_AGENT_INCLUDES_NETWORK_AGENT_H_
#define SRC_AGENT_INCLUDES_NETWORK_AGENT_H_

// [int : 0 -> не доступен, 1 -> доступен] доступность адреса (<url>)
// [double] пропускная способность используемых сетевых интерфейсов (inet_throughput)

#include "base_agent.h"

#include "../sources/Utils/sub_functions.h"
namespace s21 {
class NetworkAgent : BaseAgent{
    public:
        bool GetAccessToSite(std::string& site);
        double GetInetThroughput();
        void RefreshData(std::ofstream &file);
};
};

#endif  //  SRC_AGENT_INCLUDES_NETWORK_AGENT_H_