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

bool Compare(double val1, double val2, kCompareType& statement);
bool Compare(size_t val1, size_t val2, kCompareType& statement);

struct CPUAgentConfig {
    public:
        std::string& GetName() { return name_; }
        size_t& GetUpdateTime() { return update_time_; }

        void SetLoad(std::pair<double, kCompareType> load) { load_ = load; }
        void SetProc(std::pair<size_t, kCompareType> proc) { proc_num_ = proc; }

        void SetCurrentLoad(double val) { current_load_ = val; }
        void SetCurrentProc(size_t val) { current_proc_num_ = val; }

        bool IsCorrectLoad() { return Compare(load_.first, current_load_, load_.second); }
        bool IsCorrectProc() { return Compare(proc_num_.first, current_proc_num_, proc_num_.second); }

    private:
        std::string name_;
        size_t update_time_{};

        double current_load_{};
        size_t current_proc_num_{};
        std::pair<double, kCompareType> load_;
        std::pair<size_t, kCompareType> proc_num_;
};

struct MemoryAgentConfig {
    public:
        std::string& GetName() { return name_; }
        size_t& GetUpdateTime() { return update_time_; }

        void SetTotal(std::pair<double, kCompareType> ram) { ram_ = ram; }
        void SetUsage(std::pair<double, kCompareType> usage) { usage_ = usage; }
        void SetVolume(std::pair<double, kCompareType> volume) { volume_ = volume; }
        void SetHardOps(std::pair<size_t, kCompareType> hardops) { hardops_ = hardops; }
        void SetThroughput(std::pair<double, kCompareType> throughput) { throughput_ = throughput; }

        void SetCurrentRam(double ram) { current_ram_ = ram; }
        void SetCurrentUsage(double usage) { current_usage_ = usage; }
        void SetCurrentVolume(double volume) { current_volume_ = volume; }
        void SetCurrentHardops(size_t hardops) { current_hardops_ = hardops; }
        void SetCurrentThroughput(double throughtput) { current_throughput_ = throughtput; }

        bool IsCorrectTotal() { return Compare(ram_.first, current_ram_, ram_.second); }
        bool IsCorrectUsage() { return Compare(usage_.first, current_usage_, usage_.second); }
        bool IsCorrectVolume() { return Compare(volume_.first, current_volume_, volume_.second); }
        bool IsCorrectHardops() { return Compare(hardops_.first, current_hardops_, hardops_.second); }
        bool IsCorrectThroughput() { return Compare(throughput_.first, current_throughput_, throughput_.second); }


    private:
        std::string name_;
        size_t update_time_{};

        double current_ram_{};
        double current_usage_{};
        double current_volume_{};
        size_t current_hardops_{};
        double current_throughput_{};
        std::pair<double, kCompareType> ram_;
        std::pair<double, kCompareType> usage_;
        std::pair<double, kCompareType> volume_;
        std::pair<size_t, kCompareType> hardops_;
        std::pair<double, kCompareType> throughput_;
        
};



class Config {
    public:
        // Return message about agents. If message empty it's mean no errors.
        
        std::string Update();

        void SetCurrentCPU(double cpu_loading, size_t process_count);
        void SetCurrentMemory(double total, double usage, double volume,
            size_t hardops, double throughput);

    private:

        CPUAgentConfig cpu_{};
        MemoryAgentConfig mem_{};

        bool IsExistDirectory();
        int CreateDirectory();

        int CheckFiles();
        int CreateDefaultFiles(const std::pair<std::string, int>& agents_name);

        void ParseConfFiles();

        std::string CheckResults();

        // const std::string& GetAgentsInfo();

};




#endif  //  SRC_CONFIGS_CONFIG_PARSER_H_