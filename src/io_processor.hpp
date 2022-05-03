#ifndef IO_PROCESSOR_H
#define IO_PROCESSOR_H

#include <string>
#include <vector>

#include "entities.hpp"

std::vector <std::string> split(std::string &str, char delimiter);

void readCSV(std::vector <Instructor> &instructors, std::string filepath);

#endif