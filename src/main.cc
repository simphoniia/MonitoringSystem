#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>

#include "core/agent_core.h"
#include "configs/config_parser.h"

using namespace std::chrono;

int main() {
  auto t0 = high_resolution_clock::now();
  auto t1 = high_resolution_clock::now();
  s21::AgentCore agent_core;
  std::unique_ptr<Config> config_(new Config);

  int i = 0;
  std::string error;
  while (true) {
    t0 = high_resolution_clock::now();
    agent_core.SetConfigFile(config_.get());
    agent_core.UpdateMetrics();
    error = config_->Update();
    t1 = high_resolution_clock::now();
    std::cout << "Time: " << duration_cast<milliseconds>(t1 - t0).count()
              << "msec\n";
    if (!error.empty()) std::cout << "ERROR! Type of error is: " << error << "\n";
    i++;
  }

  return 0;
}
