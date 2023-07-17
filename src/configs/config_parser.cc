#include "config_parser.h"

bool CreateFileWithData(const std::string& file_name, const std::string& folder_name, const std::vector<std::string>& data);

bool Compare(double val1, double val2, kCompareType& statement) {
    bool result = false;

    if (statement == kCompareType::kEqual) 
        result = (val1 == val2);
    else if (statement == kCompareType::kEqualGreater)
        result = (val1 >= val2);
    else if (statement == kCompareType::kEqualLess)
        result = (val1 <= val2);
    else if (statement == kCompareType::kGreater)
        result = (val1 > val2);
    else
        result = (val1 < val2);

    return result;
}

std::string Config::Update() {
    int error{};
    std::string error_message;


    if (!IsExistDirectory()) 
        error = CreateDirectory();
    
    if (error) 
        error_message = "Could not to create a /agents_config/ directory";

    error = CheckFiles();

    if (error) 
        error_message = "Could not to create a config file.";

    return error_message;
}

inline bool Config::IsExistDirectory() {
    return std::filesystem::is_directory("./agents_config/");
}

int Config::CreateDirectory() {
    SubFunctions::ExecCommand("mkdir agents_config");

    int error = 0;
    error = !(IsExistDirectory());
    return error;
}

int Config::CheckFiles() {
    int error = 0;

    static std::vector<std::string> agents_config = {  
        "cpu_agent.conf",
        "memory_agent.conf",
        "network_agent.conf"
        //"special_agent.conf"
    };

    for (size_t i = 0; i < agents_config.size() && !error; i++) {
        std::string path = "./agents_config/" + agents_config[i];
        
        if (!std::filesystem::exists(path))
            error = CreateDefaultFiles(std::pair<std::string, int>(agents_config[i], i));
    }

    return error;
}

inline int CreateFile(const std::string& file_name, const std::string& folder) {
    SubFunctions::ExecCommand(std::string("touch " + folder + "/" + file_name).c_str());
    return !std::filesystem::exists(folder + "/" + file_name);
} 

int Config::CreateDefaultFiles(const std::pair<std::string, int>& agents_name) {
    int error = 0;

    static std::string folder_name = "agents_config";
    static std::vector<std::vector<std::string>> default_file_data = {
        {
            "agent_name=CPU_AGENT\n",
            "agent_type=cpu_agent\n\n",
            "load_metric=\">= 50\"\n",
            "load_update=4s\n\n",
            "processes_metric=\">= 1000\"\n",
            "processes_update=4s\n"
        }, 
        {
            "agent_name=MEMORY_AGENT\n",
            "agent_type=memory_agent\n\n",
            "total_metric=\"\"\n",
            "total_update=4s\n\n",
            "usage_metric=\">= 80\"\n",
            "usage_update=4s\n\n",
            "volume_metric=\"<= 1.0\"\n",
            "volume_update=4s\n\n",
            "hardops_metric=\"== 0\"\n",
            "hardops_update=4s\n\n",
            "hardthroughput_metric=\"== 0\"\n",
            "hardthroughput_update=4s\n"
        },
        {
            "agent_name=NETWORK_AGENT\n",
            "agent_type=network_agent\n\n",
            "url=\"2ip.ru\"\n",
            "url_update=5s\n\n",
            "inet_throughput_metric=\"> 0\"\n",
            "inet_throughput_update=5s\n"
        }
    };

    error = CreateFileWithData(agents_name.first, folder_name, default_file_data[agents_name.second]);

    return error;
}

inline void FillFile(std::ofstream& stream, const std::vector<std::string>& data) {
    for (auto& line : data) stream << line;
}

bool CreateFileWithData(const std::string& file_name, const std::string& folder_name, const std::vector<std::string>& data) {
    bool is_created_file = !CreateFile(file_name, folder_name);
    if (is_created_file) {
        std::ofstream file;
        file.open(folder_name + "/" + file_name);
        FillFile(file, data);
        file.close();
    }

    return !is_created_file;
}
