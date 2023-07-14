#include "../includes/system_agent.h"

#include "Utils/sub_functions.h"

double GetDiskReadTime(std::string command, int position);
double ReadTimeCalculation(const std::string &command);

void s21::SystemAgent::RefreshData() {
  static const std::string get_inodes{
      "df -i | sed -n '2p' | awk '{print $7}'"};  // ???
  static const std::string get_number_of_disks{
      "diskutil list | grep \"/dev/disk\" | grep -v \"synthesized\" | wc -l"};
  static const std::string get_disk_read_time{
      "iostat -d -c 2 | tail -1 | awk '{print $"};
  static const std::string get_number_of_errors{
      "cat /var/log/fusioninventory.log | grep error | wc -l | awk '$1=$1'"};
  static const std::string get_number_of_auths{
      "cat /var/log/storage-login.log | wc -l | awk '$1=$1'"};

  std::string number_of_disks =
      SubFunctions::ExecCommand(get_number_of_disks.c_str());

  std::string inodes = SubFunctions::ExecCommand(get_inodes.c_str());
  std::string system_errors =
      SubFunctions::ExecCommand(get_number_of_errors.c_str());
  std::string user_auths =
      SubFunctions::ExecCommand(get_number_of_auths.c_str());

  try {
    inodes_ = std::stol(inodes);
    system_errors_ = std::stoi(system_errors);
    user_auths_ = std::stoi(user_auths);
    hard_read_time_ = ReadTimeCalculation(get_disk_read_time);
  } catch (...) {
    std::cerr << "convertaion error!";
  }
}

double GetDiskReadTime(std::string command, int position) {
  static std::string end_of_command{"}'"};
  command += std::to_string(position) + end_of_command;
  std::string result = SubFunctions::ExecCommand(command.c_str());
  return stod(result);
}

double ReadTimeCalculation(const std::string &command) {
  std::vector<double> read_time_vector(10);
  int number_of_disks{};
  double result{};

  read_time_vector.push_back(GetDiskReadTime(command, 3));
  ++number_of_disks;
  result += read_time_vector.back();
  for (int i = 6; i / 3 < number_of_disks; i += 3) {
    read_time_vector.push_back(GetDiskReadTime(command, i));
    ++number_of_disks;
    result += read_time_vector.back();
  }
  return result / (number_of_disks);
}