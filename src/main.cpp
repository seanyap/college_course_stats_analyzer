#include <string>
#include <vector>

#include <iostream>
#include <cstdio> // for printf

#include "entities.hpp"
#include "io_processor.hpp"
#include "stats_extractor.hpp"


int main() {
	std::vector <Instructor> instructors;

	// read 3 CSV files and instantiate structs in memory
	readCSV(instructors, "./data/1115.csv");
	readCSV(instructors, "./data/3115.csv");
	readCSV(instructors, "./data/3130.csv");

	// Task 1 & 3
	std::printf("|----------------------------------------|\n");
	std::printf("| Instructor | Pass Rate | Withdraw Rate |\n");
	std::printf("|----------------------------------------|\n");
	findPassAndWithdrawRate(instructors);
	std::printf("|----------------------------------------|\n");
	
	// Task 2 & 4
	std::printf("|------------------------------------|\n");
	std::printf("| Course | Pass Rate | Withdraw Rate |\n");
	std::printf("|------------------------------------|\n");
	findCoursePassAndWithdrawRate(instructors);
	std::printf("|------------------------------------|\n");

	// Task 5
	std::printf("|----------------------------------------------|\n");
	std::printf("| Course | Fall P / W Rate | Spring P / W Rate |\n");
	std::printf("|----------------------------------------------|\n");
	findFallAndSpringPassAndWithdrawRate(instructors);
	std::printf("|----------------------------------------------|\n");

	return 0;
}

