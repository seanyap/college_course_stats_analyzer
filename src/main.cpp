#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

// for iterating map in old ways/ before c++11
// #include <iterator>
#include <map>


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
	std::string id;
	std::string term;
	std::string section;
	Course() {}
	Course(std::string id, std::string term, std::string section) : id(id), term(term), section(section) {}
};

// omit Student struct for now because we only has 1 field
// struct Student {
// 	std::string id;
// 	Student(std::string id) : id(id) {}
// };

// to represent the relationship between course and list of students and their grades
struct Report {
	Course course;
	// mapping each student to their grade
	std::map <std::string, std::string> studentGrades; 

	Report() {}
	Report(Course course) : course(course) {}
};

struct Instructor {
	std::string id;
	// each resport represents a course instructor taught 
	std::vector <Report> reports;
	
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

int findInstructor(std::string target, std::vector <Instructor> &instructors) {
	for (int i=0; i<instructors.size(); ++i) {
		if (instructors[i].id ==  target) return i;
	}
	return -1;
}

bool hasCourse(std::vector <Report> reports, std::string courseID) {
	for (auto const& report : reports) {
		if (report.course.id == courseID)
			return true;
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
		std::string studentID (cols.at(0));	
		std::string courseID (cols.at(1));
		std::string instructorID (cols.at(2));
		std::string termID (cols.at(3));
		std::string sectionID(cols.at(4));
		std::string studentGrade(cols.at(5));
		
		int instructorIdx = findInstructor(instructorID, instructors);

		// if current instructor don't exist 
		if (instructorIdx == -1) {
			// create instructor
			Instructor instructor (instructorID);

			// initialize student, course and report
			
			Course course (courseID, termID, sectionID);
			Report report (course);

			// add current student grade into report
				report.studentGrades.insert(std::pair<std::string,std::string>(studentID, studentGrade));
			// assign report to instructor
			instructor.reports.push_back(report);
			instructors.push_back(instructor);
		}
		// current instructor exist
		else {
			// get instructor from memory
			Instructor instructor = instructors.at(instructorIdx);
			
			// check if current student course exist in instructor
			if (hasCourse(instructor.reports, courseID)) {
				
			}
			// course doesn't exist, so has to create it
			else {
				
			}
		}


		

		
		// who's responsible to keep track of struct objects? main?
		// --> main keeps track of the list of instructors which
		//		will connect to all the other objects 
		
	}

	// iterate studentGrades map to test 
	for (auto const& instructor : instructors) {
		std::cout << "inside instructor" << '\n';
		for (auto const& report : instructor.reports) {
			std::cout << "inside report" << '\n';
			for (auto const& student : report.studentGrades) {
    std::cout << student.first << ':' 
              << student.second 
              << std::endl;
				}
		}
	}


}

