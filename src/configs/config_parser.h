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

struct CPUAgentConfig {
        void SetName(const std::string& name) { agent_name_ = name; }

        void SetCPULoadConfig(std::pair<double, kCompareType> cpu_load) { cpu_load_ = cpu_load; }
        void SetProcNumber(std::pair<int, kCompareType> proc_num) { process_number_ = proc_num; }
        void SetUpdateTime(int time) { 
            if (time > 0) update_time_ = time; 
        }

        bool IsCorrectCPULoad(int current_load) { 
            return Compare(current_load, cpu_load_.first, cpu_load_.second); }

        bool IsCorrectProccessNumber(int proc_count) {
            return Compare(proc_count, process_number_.first, process_number_.second); }
    
    private:
        std::pair<double, kCompareType> cpu_load_;
        std::pair<int, kCompareType> process_number_;
        std::string agent_name_;
        int update_time_ = 10;
};


class Config {
    public:
        // Return message about agents. If message empty it's mean no errors.
        
        std::string Update(std::ifstream& log_file);

    private:
        CPUAgentConfig cpu_;
        
        bool IsExistDirectory();
        int CreateDirectory();

        int CheckFiles();
        int CreateDefaultFiles(const std::pair<std::string, int>& agents_name);

        void ParseConfFiles();
        
        std::string ParseLog(std::ifstream& log_file);

        // const std::string& GetAgentsInfo();

};




#endif  //  SRC_CONFIGS_CONFIG_PARSER_H_