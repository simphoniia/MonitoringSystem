#ifndef SRC_CONFIGS_CONFIG_PARSER_H_
#define SRC_CONFIGS_CONFIG_PARSER_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <filesystem>
#include <set>
#include <map>

#include "../agents/sources/Utils/sub_functions.h"

enum kCompareType {
    kEqual,
    kNotEqual,
    kEqualGreater,
    kEqualLess,
    kGreater,
    kLess,
    kNone
};

bool Compare(size_t val1, size_t val2, kCompareType& statement);
bool Compare(int val1, int val2, kCompareType& statement);
bool Compare(double val1, double val2, kCompareType& statement);
bool Compare(long val1, long val2, kCompareType& statement);

struct CPUAgentConfig {
    std::string name;
    float update_time;
    std::pair<double, kCompareType> load;
    std::pair<size_t, kCompareType> proc_num;

    int Compare(double load, size_t procnum) {
        int result = 0;

        if (::Compare(this->load.first, load, this->load.second) == false)
            result = 1;
        else if (::Compare(proc_num.first, procnum, proc_num.second) == false)
            result = 2;

        return result;
    }
};

struct MemoryAgentConfig {
    std::string name;
    float update_time;
    std::pair<double, kCompareType> ram;
    std::pair<double, kCompareType> usage;
    std::pair<double, kCompareType> volume;
    std::pair<size_t, kCompareType> hardops;
    std::pair<double, kCompareType> throughput;

    int Compare(double ram, double usage, double volume, size_t ops, double throughput) {
        int result = 0;

        if (::Compare(this->ram.first, ram, this->ram.second) == false) 
            result = 1;
        if (::Compare(this->usage.first, usage, this->usage.second) == false) 
            result = 2;
        if (::Compare(this->volume.first, volume, this->volume.second) == false) 
            result = 3;
        if (::Compare(this->hardops.first, ops, this->hardops.second) == false) 
            result = 4;
        if (::Compare(this->throughput.first, throughput, this->throughput.second) == true) 
            result = 5;

        return result;
    }
};

struct NetworkAgentConfig {
    std::string name;
    float update_time{};

    std::string network_url;
    bool is_site_up{true};
    std::pair<size_t, kCompareType> inet_throughput;

    int Compare(size_t inet_throughput) {
        int result = 0;

        if (::Compare(this->inet_throughput.first, inet_throughput, this->inet_throughput.second) == false) 
            result = 1;
        if (!is_site_up)
            result = 2;

        return result;
    }
};

struct CPUSpecialAgentConfig {
    std::string name;
    float update_time{};

    std::pair<double, kCompareType> idle;
    std::pair<double, kCompareType> user;
    std::pair<double, kCompareType> priveleged;

    int Compare(double idle, double user, double priveleged) {
        int result = 0;

        if (::Compare(this->idle.first, idle, this->idle.second) == false)
            result = 1;
        if (::Compare(this->user.first, user, this->user.second) == false)
            result = 2;
        if (::Compare(this->priveleged.first, priveleged, this->priveleged.second) == false)
            result = 3;

        return result;
    }
};

struct SwapAgentConfig {
    std::string name;
    float update_time;
    std::pair<double, kCompareType> swap;
    std::pair<double, kCompareType> used;
    std::pair<double, kCompareType> proc_queue;

    int Compare(double swap, double used, double proc_queue) {
        int result = 0;

        if (::Compare(this->swap.first, swap, this->swap.second) == false)
            result = 1;
        else if (::Compare(this->used.first, used, this->used.second) == false)
            result = 2;
        else if (::Compare(this->proc_queue.first, proc_queue, this->proc_queue.second) == false)
            result = 3;

        return result;
    }
};

struct SystemConfig {
    std::string name;
    float update_time;
    std::pair<long, kCompareType> inodes;
    std::pair<double, kCompareType> HRtime;
    std::pair<int, kCompareType> system_errors;
    std::pair<int, kCompareType> user_auths;
    std::pair<int, kCompareType> disknum;

    int Compare(long inodes, double hr, int errors, int auths, int disknum) {
        int result = 0;

        if (::Compare(this->inodes.first, inodes, this->inodes.second) == false)
            result = 1;
        if (::Compare(HRtime.first, hr, this->HRtime.second) == false)
            result = 2;
        if (::Compare(system_errors.first, errors, this->system_errors.second) == false)
            result = 3;
        if (::Compare(user_auths.first, auths, this->user_auths.second) == false)
            result = 4;
        if (::Compare(this->disknum.first, disknum, this->disknum.second) == false)
            result = 5;

        return result;
    }
};

struct VMemoryConfig {
    std::string name;
    float update_time;
    std::pair<double, kCompareType> volume;
    std::pair<double, kCompareType> free;

    int Compare(double volume, double free) {
        int result = 0;

        if (::Compare(this->volume.first, volume, this->volume.second) == false)
            result = 1;
        if (::Compare(this->free.first, free, this->free.second) == false)
            result = 2;

        return result;
    }
};

class Config {
    public:
        // Return message about agents. If message empty it's mean no errors.
        
        std::string Update();

        void SetCurrentCPU(double cpu_loading, size_t process_count);
        void SetCurrentMemory(double total, double usage, double volume,
            size_t hardops, double throughput);
        void SetCurrentNetwork(double inet_throughput, bool is_site_up);
        void SetCurrentSpecialCPU(double idle, double user, double priveleged);
        void SetCurrentSwap(double swap, double used, double proc);
        void SetCurrentSystem(long inodes, double hr, int err, int auths, int disknum);
        void SetCurrentVMemory(double volume, double free);

        std::string GetSite() { return netw_.network_url; }

        std::string error_msg;

    private:

        CPUAgentConfig cpu_{};
        MemoryAgentConfig mem_{};
        NetworkAgentConfig netw_{};
        CPUSpecialAgentConfig cpuspec_{};
        SwapAgentConfig swap_{};
        SystemConfig system_{};
        VMemoryConfig vmem_{};

        bool IsExistDirectory();
        int CreateDirectory();

        int CheckFiles();
        int CreateDefaultFiles(const std::pair<std::string, int>& agents_name);

        void ParseConfFiles();

        // const std::string& GetAgentsInfo();

};

#endif  //  SRC_CONFIGS_CONFIG_PARSER_H_