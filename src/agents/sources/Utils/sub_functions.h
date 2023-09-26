#ifndef SRC_AGENTS_SOURCES_UTILS_SUB_FUNCTIONS_H_
#define SRC_AGENTS_SOURCES_UTILS_SUB_FUNCTIONS_H_

#include <algorithm>
#include <array>
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace SubFunctions {
std::string ExecCommand(const char* cmd);
std::string GetOnlyDigits(const std::string& output);
//std::string GetIostatParam(int position);
}  // namespace SubFunctions

#endif  //  SRC_AGENTS_SOURCES_UTILS_SUB_FUNCTIONS_H_