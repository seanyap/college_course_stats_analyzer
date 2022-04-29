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
	Course() {}
	Course(std::string term, std::string section) : term(term), section(section) {}
};

struct Student {
	std::string id;
	Student(std::string id) : id(id) {}
};

// to represent the relationship between course and list of students and their grades
struct Roster {
	Course course;
	// std::vector <std::vector <Student, std::string> > studentsWithGrades;

	Roster() {}
	Roster(Course course) : course(course) {}
};

struct Instructor {
	std::string id;
	// each roster represents a course instructor taught 
	std::vector <Roster> rosters;
	
	Instructor() {}
	Instructor(std::string id) : id(id) {}
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

bool hasInstructor(std::string target, std::vector <Instructor> &instructors) {
	for (int i=0; i<instructors.size(); ++i) {
		if (instructors[i].id ==  target) return true;
	}
	return false;
}

int main() {
	std::ifstream data_1115 ("../data/1115.csv");

	std::vector <Instructor> instructors;

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

		// if current instructor don't exist 
		if (!hasInstructor(cols.at(2), instructors)) {
			// create instructor
			Instructor instructor (cols.at(2));
			instructors.push_back(instructor);
			std::cout << "instructor created: " << cols.at(2) << '\n';
			// todo create roster
		}
		// current instructor exist
		else {
			std::cout << "instructor exists: " << cols.at(2) << '\n';
		}

		Student student (cols.at(0));
		Course course (cols.at(3), cols.at(4));

		// create rosters & instructors

		// temp test
		//std::cout << course.term << '\n';

		
		// call functions to create objects in memory through instantiating struct
		// who's responsible to keep track of these objects? main?

		// 
		
	}
}

