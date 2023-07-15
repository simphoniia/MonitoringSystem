#include "config_parser.h"

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
    
    if (error) {
        error_message = "Could not to create a /agents_config/ directory";
        return error_message;
    }

    
    error = CheckFiles();

    if (error) {
        error_message = "Could not to create a config file.";
        return error_message;
    }




    return error_message;
}

bool Config::IsExistDirectory() {
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
        "global_config.conf",
        "cpu_agent.conf",
        "memory_agent.conf",
        "network_agent.conf",
        "special_agent.conf"
    };

    std::ifstream config_file;
    for (size_t i = 0; i < agents_config.size(); i++) {
        config_file.open("agents_configs/" + agents_config[i]);
        if (!config_file.is_open())
            error += CreateDefaultFiles(agents_config[i]);
        else
            config_file.close();
    }

    return error;
}

bool CreateDefaultGlobal(const std::string& name);
bool CreateDefaultCPU(const std::string& name);


int Config::CreateDefaultFiles(const std::string& path) {
    int error = 0;

    static std::set<std::pair<std::string, bool(*)(const std::string&)>> functions = {
        {"global_config.conf", CreateDefaultGlobal},
        {"cpu_agent.conf", CreateDefaultCPU}
    };

    for (auto& var : functions) {
        if (var.first == path) 
            var.second(path);
    }

    return error;
}

void FillFile(std::ofstream& obj, const std::vector<std::string>& data) {
    for (auto& line : data) {
        obj << line;
    }
}

bool CreateDefaultGlobal(const std::string& name) {
    static std::vector<std::string> default_file = {
        "#   If TOTAL_UPDATE_TIME not null\n",
        "#   data will refresh by this counter;\n",
        "#   Otherwise each metric has personal update time;\n",
        "#   Mininum time for update is 10 seconds.\n",
        "\n",
        "TOTAL_UPDATE_TIME=10s\n",
        "\n",
        "CPU_AGENT=ON\n",
        "MEMORY_AGENT=ON\n",
        "NETWORK_AGENT=ON\n"
    };

    std::string full_path = "touch agents_config/" + name;
    SubFunctions::ExecCommand(full_path.c_str());

    std::ofstream file;
    file.open("agents_config/" + name);

    FillFile(file, default_file);

    file.close();
    return true;
}

bool CreateDefaultCPU(const std::string& name) {
    static std::vector<std::string> default_file = {
        "#   If TOTAL_UPDATE_TIME not null\n",
        "#   data will refresh by this counter;\n",
        "#   Otherwise each metric has personal update time;\n",
        "#   Mininum time for update is 10 seconds.\n",
        "\n",
        "TOTAL_UPDATE_TIME=10s\n",
        "\n",
        "CPU_AGENT=ON\n",
        "MEMORY_AGENT=ON\n",
        "NETWORK_AGENT=ON\n"
    };

    std::string full_path = "touch agents_config/" + name;
    SubFunctions::ExecCommand(full_path.c_str());

    std::ofstream file;
    file.open("agents_config/" + name);

    FillFile(file, default_file);

    file.close();
    return true;
}