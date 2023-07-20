#ifndef SRC_CONFIGS_CONFIG_PARSER_H_
#define SRC_CONFIGS_CONFIG_PARSER_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <filesystem>
#include <set>
#include <map>

#include "../core/agent_core.h"
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

struct CPUAgentConfig {
        void SetName(const std::string& name) { agent_name_ = name; }

        void SetCPULoadConfig(std::pair<double, kCompareType> cpu_load) { cpu_load_ = cpu_load; }
        void SetProcNumber(std::pair<int, kCompareType> proc_num) { process_number_ = proc_num; }
        void SetUpdateTime(int time) { if (time > 0) update_time_ = time; }

        void SetCurrentLoad(double value) { current_cpu_load_ = value; }
        void SetCurrentProcNumber(size_t value) { current_process_count_ = value; }

        bool IsCorrectCPULoad() { return Compare(current_cpu_load_, cpu_load_.first, cpu_load_.second); }
        bool IsCorrectProcNumber() { return Compare(current_process_count_, process_number_.first, process_number_.second); }

    private:
        
        double current_cpu_load_{};
        size_t current_process_count_{};
        
        std::pair<double, kCompareType> cpu_load_;
        std::pair<int, kCompareType> process_number_;
        std::string agent_name_;
        int update_time_ = 10;
};


class Config {
    public:
        // Return message about agents. If message empty it's mean no errors.
        
        std::string Update();

        void SetCurrentCPU(double cpu_loading, size_t process_count) {
            cpu_.SetCurrentLoad(cpu_loading);
            cpu_.SetCurrentProcNumber(process_count);
        }

    private:

        size_t last_log_output_{};
        size_t total_line_{};
        std::map<std::string, std::pair<bool, std::shared_ptr<s21::BaseAgent>>> agents_;

        CPUAgentConfig cpu_;
        
        bool IsExistDirectory();
        int CreateDirectory();

        int CheckFiles();
        int CreateDefaultFiles(const std::pair<std::string, int>& agents_name);

        void ParseConfFiles();

        std::string CheckResults();

        // const std::string& GetAgentsInfo();

};




#endif  //  SRC_CONFIGS_CONFIG_PARSER_H_