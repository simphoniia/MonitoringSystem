#include "../includes/network_agent.h"

double InetThroughputInfo();
bool IsSiteConnectionUp(const char* site);

s21::NetworkAgent* s21::CreateObject() { return new s21::NetworkAgent; }

void s21::NetworkAgent::RefreshData(std::ofstream& file) {
  if (!file.is_open()) return;

  static std::string get_access_ping = "ping -t 1 -c 1 ";
  static std::string get_info_from_ping =
      " | tail -n 2 | head -n 1 | awk '{print $7}'";

  site_access_ = IsSiteConnectionUp(site);
  inet_throughput_ = InetThroughputInfo();

  file << "network_agent: site_connection: ";

  if (site_access_)
    file << "1";
  else
    file << "0";

  file << " | inet_throughput: " << inet_throughput_ << "\n";
}

double InetThroughputInfo() {
  static std::string get_inet_throughput =
      "netstat -bI en0 | awk '{print ($7+$10)}' | tail -1";
  std::string res = SubFunctions::ExecCommand(get_inet_throughput.c_str());
  double download_speed{};

  try {
    if (!res.empty())
      download_speed = std::stod(SubFunctions::GetOnlyDigits(res));
    download_speed /= 1024;
    download_speed /= 1024;
    download_speed /= 1024;
  } catch (...) {
    std::cout << "Internet throughput cast error.\n";
  }

  return download_speed;
}

bool IsSiteConnectionUp(const char* site) {
  static std::string get_access_ping = "ping -t 1 -c 1 ";
  static std::string get_info_from_ping =
      " | tail -n 2 | head -n 1 | awk '{print $7}'";

  static std::string res = get_access_ping + site + get_info_from_ping;
  std::string result = SubFunctions::ExecCommand(res.c_str());

  bool connection = SubFunctions::GetOnlyDigits(result).empty();

  return !connection;
}