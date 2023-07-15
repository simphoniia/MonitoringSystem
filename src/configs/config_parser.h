#ifndef SRC_CONFIGS_CONFIG_PARSER_H_
#define SRC_CONFIGS_CONFIG_PARSER_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <set>

#include "../agents/sources/Utils/sub_functions.h"

enum kCompareType {
    kEqual,
    kEqualGreater,
    kEqualLess,
    kGreater,
    kLess
};

bool Compare(double val1, double val2, kCompareType& statement);

class Config {
    public:
        // Return message about agents. If message empty it's mean no errors.
        std::string Update();

    private:
        bool IsExistDirectory();
        int CreateDirectory();

        int CheckFiles();
        int CreateDefaultFiles(const std::string& path);
        // void FillConfigFiles();
        // void ParseConfigFiles();
        // const std::string& GetAgentsInfo();

};



class CpuAgentConfig {
    public:
        void SetCPULoadConfig(std::pair<int, kCompareType>& cpu_load) { cpu_load_ = cpu_load; }
        void SetProcNumber(std::pair<int, kCompareType>& proc_num) { process_number_ = proc_num; }
        
        bool IsCorrectCPULoad(int current_load) {
            return Compare(current_load, cpu_load_.first, cpu_load_.second);
        }

        bool IsCorrectProccessNumber(int proc_count) {
            return Compare(proc_count, process_number_.first, process_number_.second);
        }

    private:
        std::pair<int, kCompareType> cpu_load_;
        std::pair<int, kCompareType> process_number_;
};



#endif  //  SRC_CONFIGS_CONFIG_PARSER_H_