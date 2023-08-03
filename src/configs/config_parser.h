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
    kEqualGreater,
    kEqualLess,
    kGreater,
    kLess,
    kNone
};

enum kAgentError {
    kOk,
    kFail
};

template <typename T>
bool Compare(T val1, T val2, kCompareType& statement);

struct CPUAgentConfig {
    std::string name;
    float update_time;
    std::pair<double, kCompareType> load;
    std::pair<size_t, kCompareType> proc_num;

    std::pair<kAgentError, std::string> Compare(double load, size_t procnum) {
        std::pair<kAgentError, std::string> error{};

        if (!::Compare(this->load.first, load, this->load.second))
            error = {kFail, std::string("CPU Load fail! " + std::to_string(load))};

        else if (!::Compare(proc_num.first, procnum, proc_num.second))
            error = {kFail, std::string("CPU process fail! " + std::to_string(procnum))};

        return error;
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

    std::pair<kAgentError, std::string> Compare(double ram, double usage, double volume, size_t ops, double throughput) {
        std::pair<kAgentError, std::string> error{};

        if (!::Compare(this->ram.first, ram, this->ram.second)) 
            error = {kFail, std::string("Memory ram total fail! " + std::to_string(ram))};
        if (!::Compare(this->usage.first, usage, this->usage.second)) 
            error = {kFail, std::string("Memory usage fail! " + std::to_string(usage))};
        if (!::Compare(this->volume.first, volume, this->volume.second)) 
            error = {kFail, std::string("Memory volume fail! " + std::to_string(volume))};
        if (!::Compare(this->hardops.first, ops, this->hardops.second)) 
            error = {kFail, std::string("Memory hardops fail! " + std::to_string(ops))};
        if (::Compare(this->throughput.first, throughput, this->throughput.second)) 
            error = {kFail, std::string("Memory ram fail! " + std::to_string(throughput))};


        return error;
    }
};

struct NetworkAgentConfig {
    std::string name;
    float update_time{};

    std::string network_url;
    bool is_site_up{true};
    std::pair<size_t, kCompareType> inet_throughput;

    std::pair<kAgentError, std::string> Compare(size_t inet_throughput, bool site_access) {
        std::pair<kAgentError, std::string> error{};

        if (!::Compare(this->inet_throughput.first, inet_throughput, this->inet_throughput.second)) 
            error = {kFail, std::string("Network throughput fail! " + std::to_string(inet_throughput))};
        if (!is_site_up)
            error = {kFail, std::string("Network fail! Site is down!")};

        return error;
    }
};

struct CPUSpecialAgentConfig {
    std::string name;
    float update_time{};

    std::pair<double, kCompareType> idle;
    std::pair<double, kCompareType> user;
    std::pair<double, kCompareType> priveleged;

    std::pair<kAgentError, std::string> Compare(double idle, double user, double priveleged) {
        std::pair<kAgentError, std::string> error{};

        if (!::Compare(this->idle.first, idle, this->idle.second))
            error = {kFail, std::string("Special idle fail!! " + std::to_string(idle))};
        if (!::Compare(this->user.first, user, this->user.second))
            error = {kFail, std::string("Special user fail!" + std::to_string(user))};
        if (!::Compare(this->priveleged.first, priveleged, this->priveleged.second))
            error = {kFail, std::string("Special priveleged fail!" + std::to_string(priveleged))};

        return error;
    }
};

struct SwapAgentConfig {
    std::string name;
    float update_time{};

    std::pair<double, kCompareType> total_swap;
    std::pair<double, kCompareType> used_swap;
    std::pair<size_t, kCompareType> proc_queue;

    std::pair<kAgentError, std::string> Compare(double total, double used, size_t proc_queue) {
        std::pair<kAgentError, std::string> error{};

        if (!::Compare(this->total_swap.first, total, this->total_swap.second))
            error = {kFail, std::string("Special idle fail!! " + std::to_string(total))};
        if (!::Compare(this->used_swap.first, used, this->used_swap.second))
            error = {kFail, std::string("Special user fail!" + std::to_string(used))};
        if (!::Compare(this->proc_queue.first, proc_queue, this->proc_queue.second))
            error = {kFail, std::string("Special priveleged fail!" + std::to_string(proc_queue))};

        return error;
    }
};

struct SystemAgentConfig {
    std::string name;
    float update_time{};

    std::pair<long, kCompareType> inodes;
    std::pair<double, kCompareType> hard_read_time;
    std::pair<size_t, kCompareType> system_errors;
    std::pair<size_t, kCompareType> user_auths;
    std::pair<size_t, kCompareType> disknum;

    std::pair<kAgentError, std::string> Compare(long inodes, double hardread, 
        size_t errors, size_t auths, size_t disknum) {
        std::pair<kAgentError, std::string> error{};

        if (!::Compare(this->inodes.first, inodes, this->inodes.second))
            error = {kFail, std::string("System inodes fail! " + std::to_string(inodes))};
        if (!::Compare(hard_read_time.first, hardread, hard_read_time.second))
            error = {kFail, std::string("System hardread fail! " + std::to_string(hardread))};
        if (!::Compare(system_errors.first, errors, system_errors.second))
            error = {kFail, std::string("System syserrors fail! " + std::to_string(errors))};
        if (!::Compare(user_auths.first, auths, user_auths.second))
            error = {kFail, std::string("System auths fail! " + std::to_string(auths))};
        if (!::Compare(this->disknum.first, disknum, this->disknum.second))
            error = {kFail, std::string("System disknum fail! " + std::to_string(disknum))};

        return error;
    }
};

struct VMemoryAgentConfig {
    std::string name;
    float update_time{};

    std::pair<double, kCompareType> vmem_volume;
    std::pair<double, kCompareType> vmem_free;

    std::pair<kAgentError, std::string> Compare(double vmem_volume, double vmem_free) {
        std::pair<kAgentError, std::string> error{};

        if (!::Compare(this->vmem_volume.first, vmem_volume, this->vmem_volume.second))
            error = {kFail, std::string("VMemory volume fail! " + std::to_string(vmem_volume))};
        if (!::Compare(this->vmem_free.first, vmem_free, this->vmem_free.second))
            error = {kFail, std::string("VMemory free fail! " + std::to_string(vmem_free))};

        return error;
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
        void SetCurrentSwap(double swap, double usedswap, size_t proc_queue);
        void SetCurrentSystem(long inodes, double hardreadtime, int errors, int auths, int disknum);
        void SetCurrentVMemory(double volume, double free);

        std::string GetSite() { return netw_.network_url; }

        std::string error_msg;

    private:

        CPUAgentConfig cpu_{};
        MemoryAgentConfig mem_{};
        NetworkAgentConfig netw_{};
        CPUSpecialAgentConfig cpuspec_{};
        SwapAgentConfig swap_{};
        SystemAgentConfig system_{};
        VMemoryAgentConfig vmem_{};

        bool IsExistDirectory();
        int CreateDirectory();

        int CheckFiles();
        int CreateDefaultFiles(const std::pair<std::string, int>& agents_name);

        void ParseConfFiles();

        // const std::string& GetAgentsInfo();

};




#endif  //  SRC_CONFIGS_CONFIG_PARSER_H_