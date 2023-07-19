#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>

#include "core/agent_core.h"

using namespace std::chrono;

int main() {
  auto t0 = high_resolution_clock::now();
  auto t1 = high_resolution_clock::now();
  s21::AgentCore agent_core;
  int i = 0;
  while (i < 3) {
    t0 = high_resolution_clock::now();

    agent_core.UpdateMetrics();

    t1 = high_resolution_clock::now();
    std::cout << "Time: " << duration_cast<milliseconds>(t1 - t0).count()
              << "msec\n";
    i++;
  }
  return 0;
}
