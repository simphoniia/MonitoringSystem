#include "../includes/network_agent.h"

bool s21::NetworkAgent::GetAccessToSite(std::string& site) {
    static std::string get_access_ping = "ping -t 1 -c 1 ";
    static std::string get_info_from_ping = " | tail -n 2 | head -n 1 | awk '{print $7}'";

    static std::string res = get_access_ping + site + get_info_from_ping;
    std::string result = SubFunctions::ExecCommand(res.c_str());

    if (SubFunctions::GetOnlyDigits(result).empty()) return false;
    return true;
}

double s21::NetworkAgent::GetInetThroughput() {

}

void s21::NetworkAgent::RefreshData(std::ofstream &file) {
    if (!file.is_open()) return;

   

}