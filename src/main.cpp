#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

// 1. Pass rate per instructor (and per course number)
// 2. W rate per instructor (and per course number)

// - what data structure should i use? instructor-focus

// instructor
// - each instructor teaches a number of course
// - each course is offered in multiple terms and sections
//		(we need to specify which term and section the instructor taught)
// - each course also has a list of students

// student
// - each student has their emplid, course, grade  

// Process Flow
// 1. read in data from file into memory 
//		a. transform each data line into struct format 
//		- create instructor if it doesnt exist
//		- create student if it doesnt exist & add to
//			array of students struct to run processing 
//			(which struct should i store this list?) 
//			either instructor or course? they don't work
//			because of too much inter-dependency
//			(decided to go with a new separated entity called Roster)
// 2. perform the required insights
// 3. write the insights into an output file
//		a. use printf to format and output nicely

// Questions:
// why is string, vector, ifstream all in std namespace?

struct Course {
	std::string term;
	std::string section;
};

struct Student {
	std::string id;
};

// to represent the relationship between course and list of students and their grades
struct Roster {
	Course course;
	std::vector <std::vector <Student, std::string>> studentsWithGrades;
};

struct Instructor {
	std::string id;
	// each roster represents a course instructor taught 
	std::vector <Roster> rosters;
};

std::vector <std::string> split(std::string &str, char delimiter) {
	std::vector <std::string> tokens;
	
	std::stringstream sstream(str);
	std::string token;
	while (std::getline(sstream, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

int main() {
	std::ifstream data_1115 ("../data/1115.csv");

	// place below code into a reader wrapper
	while (data_1115.good()) {
		// get one record
		std::string record;
		std::getline(data_1115, record); 
		
		// split record into respective cols 
		std::vector <std::string> cols (split(record, ','));
		// check if cols are parsed correctly
		// for (const auto &str : cols) {
		// 	std::cout << str << '\n';
		// }

		
		// call functions to create objects in memory through instantiating struct
		// who's responsible to keep track of these objects? main?

		// 
		
	}
}

