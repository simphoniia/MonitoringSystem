#include "../includes/memory_agent.h"

#include "Utils/sub_functions.h"

double GetRamTotal(const std::string& command);
double GetRamUsage(const std::string& command);

void s21::MemoryAgent::RefreshData() {

    static std::string get_ram_total = "sysctl hw.memsize | grep -o -E \"\\d{1,20}\"";
    static std::string get_ram_usage = "top -l 1 | grep -o -E 'PhysMem: \\d{1,9}'";
    static std::string get_hard_usage = "";
    static std::string get_hard_io_usage = "";
    static std::string get_hard_throughput = "";


    ram_total_ = ::GetRamTotal(get_ram_total);
    ram_usage_ = ::GetRamUsage(get_ram_usage);

}

double GetRamTotal(const std::string& command) {
    std::string result = SubFunctions::ExecCommand(command.c_str());
    
    if (!result.empty())
        result = SubFunctions::GetOnlyDigits(result);

    // Translate to gigabytes;
    double res = std::stod(result);
    res = res / 1024 / 1024;
    return res;
}

double GetRamUsage(const std::string& command) {
    std::string result = SubFunctions::ExecCommand(command.c_str());

    if (!result.empty())
        result = SubFunctions::GetOnlyDigits(result);

    return std::stoi(result);
}
