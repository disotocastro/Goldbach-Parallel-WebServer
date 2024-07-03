#ifndef REPORT_HPP
#define REPORT_HPP

#include <cstdio>
#include <ctime>
#include <load_data.hpp>
#include <matrix.hpp>
#include <simulation.hpp>
#include <string>

void Report(std::vector<Simulation*> simulations);
static std::string format_time(const time_t seconds);
void save_matrix_to_file(const Matrix* matrix,
                         const std::string& original_plate_name, int64_t k);
std::string RegexPlatename(const std::string& original_plate_name, int64_t k);
std::string RegexTabName(const std::string& file_name);

#endif  // REPORT_HPP