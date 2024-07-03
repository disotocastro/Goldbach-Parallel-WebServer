#ifndef REPORT_HPP
#define REPORT_HPP

#include <cstdio>
#include <ctime>
#include <load_data.hpp>
#include <matrix.hpp>
#include <simulation.hpp>
#include <string>

void Report(Simulation* sim);
static std::string format_time(const time_t seconds);

#endif  // REPORT_HPP