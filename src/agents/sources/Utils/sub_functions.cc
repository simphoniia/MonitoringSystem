#include "sub_functions.h"

// std::string SubFunctions::GetIostatParam(int position) {
//   static const std::string iostat{"iostat -d -c 2 | tail -1"};
//   static std::vector<std::string> buffer;
//   buffer.push_back(SubFunctions::ExecCommand(iostat.c_str()));

//   std::string new_string;
//   for (auto it = buffer.back().begin() + position; it != buffer.back().end();
//        ++it) {
//     new_string.push_back(*it);
//   }
//   std::cout << new_string << '\n';
//   return new_string;
// }

std::string SubFunctions::ExecCommand(const char* cmd) {
  std::array<char, 128> buffer;
  std::string result;

  FILE* fterminal = popen(cmd, "r");
  if (!fterminal) std::runtime_error("Terminal is not opened.");

  while (fgets(buffer.data(), buffer.size(), fterminal) != nullptr)
    result += buffer.data();

  pclose(fterminal);
  return result;
}

std::string SubFunctions::GetOnlyDigits(std::string& output) {
  std::string new_string;
  new_string.reserve(output.size());

  std::copy_if(output.begin(), output.end(), std::back_inserter(new_string),
               [](const char symbol) -> bool {
                 if (std::isdigit(symbol) || symbol == '.') return true;
                 return false;
               });

  return new_string;
}