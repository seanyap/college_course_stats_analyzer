#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include <iterator>

// for iterating map in old ways/ before c++11
// #include <iterator>
#include <map>

#include <cstdio> // for printf


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

int findCourse(std::vector <Report> &reports, std::string courseID, std::string termID, std::string sectionID) {
	for (int i=0; i<reports.size(); ++i) {
		if (reports[i].course.id == courseID && reports[i].course.term == termID && reports[i].course.section == sectionID) return i;
	}
	return -1;
}

void readCSV(std::vector <Instructor> &instructors, std::string filepath) {
	std::ifstream data (filepath);
	
	// ignore heading 
	data.ignore(1000, '\n') ;
	while (data.good()) {
		std::string row;
		std::getline(data, row); // get one row
		
		// split record into respective cols 
		std::vector <std::string> cols (split(row, ','));
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

			// instantiate course and report
			Course course (courseID, termID, sectionID);
			Report report (course);

			// add current student grade into report
			report.studentGrades.insert({studentID, studentGrade});
			// assign report to instructor
			instructor.reports.push_back(report);
			instructors.push_back(instructor);
		}
		// current instructor exist
		else {
			// get instructor from memory (make sure its referenced to the same object)
			Instructor &instructor = instructors.at(instructorIdx);
			
			// check if current student course exist in instructor
			int reportIdx = findCourse(instructor.reports, courseID, termID, sectionID);
			// instructor doesn't have current course read in
			if (reportIdx == -1) {
				
				// create a report & course
				Course course (courseID, termID, sectionID);
				Report report (course);

				// add current student to report 
				report.studentGrades.insert({studentID, studentGrade});
				instructor.reports.push_back(report);
			}
			// course exist, so just add student grade 
			else {			instructor.reports[reportIdx].studentGrades.insert({studentID, studentGrade});
			}
		}
	}
}

int main() {
	std::vector <Instructor> instructors;

	// read 3 CSV files and instantiate structs in memory
	readCSV(instructors, "./data/1115.csv");
	readCSV(instructors, "./data/3115.csv");
	readCSV(instructors, "./data/3135.csv");

	// process data in memory to complete assignment tasks
	//	Task 1 - pass rate per instructor 
	//	Steps: iterate over all instructors, for each instructor, 
	//		find the count of students who pass divided by the total 
	//		number of students current instructor taught
	//	Task 3 - W rate per instructor 
	//	Steps: Similar to task 1. for each instructor, 
	//		find the count of students who got a W divided by
	//		the total number of students current instructor taught
	std::printf("|----------------------------------------|\n");
	std::printf("| Instructor | Pass Rate | Withdraw Rate |\n");
	std::printf("|----------------------------------------|\n");
	for (int i=0; i<instructors.size(); ++i) {
		int passedStudentCount = 0;
		int withdrawStudentCount = 0;
		int totalStudentCount = 0;
		for (int j=0; j<instructors[i].reports.size(); ++j) {
			for (std::pair<std::string, std::string> student : instructors[i].reports[j].studentGrades) {
		        // accessing current student grade from map
		        std::string grade = student.second;
				if (grade == "A+" || grade == "A" || grade == "A-" ||
					grade == "B+" || grade == "B" || grade == "B-" ||
					grade == "C+" || grade == "C" || grade == "C-") 
					passedStudentCount++;
				else if (grade == "W") 
					withdrawStudentCount++;
				totalStudentCount++;
			}
		}	
		// calculate metrics for pass and withdraw rate for current instructor
		double passRate = (double)passedStudentCount / (double)totalStudentCount; 
		double withdrawRate = (double)withdrawStudentCount / (double)totalStudentCount;

		std::printf("|    %s     ", instructors[i].id.c_str());
		std::printf("|   %.3f   ", passRate);
		std::printf("|     %.3f     |\n", withdrawRate);
	}
	std::printf("|----------------------------------------|\n");
	
	
	//	Task 2 - pass rate per course number
	//	Steps: find the count of students who pass divided by the 
	//		total number of students (all instructors combined)
	// 	Task 4 - W rate per course number
	//	Steps: Similar to task 2, but find the count of students who
	//		got a W instead of who pass
	std::printf("|------------------------------------|\n");
	std::printf("| Course | Pass Rate | Withdraw Rate |\n");
	std::printf("|------------------------------------|\n");
	
	int passedStudentCount = 0;
	int withdrawStudentCount = 0;
	int totalStudentCount = 0;
	for (int i=0; i<instructors.size(); ++i) {
		for (int j=0; j<instructors[i].reports.size(); ++j) {
			for (std::pair<std::string, std::string> student : instructors[i].reports[j].studentGrades) {
		        // accessing current student grade from map
		        std::string grade = student.second;
				if (grade == "A+" || grade == "A" || grade == "A-" ||
					grade == "B+" || grade == "B" || grade == "B-" ||
					grade == "C+" || grade == "C" || grade == "C-") 
					passedStudentCount++;
				else if (grade == "W") 
					withdrawStudentCount++;
				totalStudentCount++;
			}
		}	
	}
	// calculate metrics for pass and withdraw rate for current course
	double passRate = (double)passedStudentCount / (double)totalStudentCount; 
	double withdrawRate = (double)withdrawStudentCount / (double)totalStudentCount;

	// insert 1115 for now, will have to change later when adding 3115 & 3130
	std::printf("|  %s  ", "1115"); 
	std::printf("|   %.3f   ", passRate);
	std::printf("|     %.3f     |\n", withdrawRate);
	std::printf("|------------------------------------|\n");
	

	//	Task 5 - Fall vs Spring pass rate for each course 
	//	Steps: create 4 variables: 2 variables for the count of students
	//		in the Fall & Spring who passed and 2 variables for the count
	//		of total students in the Fall & Spring. Then, divide the 
	//		respective semester count of students who pass by the total
	//		number of students in that semester
	std::printf("|----------------------------------------------|\n");
	std::printf("| Course | Fall P / W Rate | Spring P / W Rate |\n");
	std::printf("|----------------------------------------------|\n");

	int passedStudentCountFall = 0;
	int withdrawStudentCountFall = 0;
	int totalStudentCountFall = 0;
	
	int passedStudentCountSpring = 0;
	int withdrawStudentCountSpring = 0;
	int totalStudentCountSpring = 0;
	
	for (int i=0; i<instructors.size(); ++i) {
		for (int j=0; j<instructors[i].reports.size(); ++j) {
			bool isFallCourse = false;
			std::string term = instructors[i].reports[j].course.term;
			// check if current report is for Spring or Fall 
			if (term == "T04" || term == "T08" || term == "T12" ||
				term == "T16" || term == "T20" || term == "T23")
				isFallCourse = true;
			
			for (std::pair<std::string, std::string> student : instructors[i].reports[j].studentGrades) {
		        // accessing current student grade from map
		        std::string grade = student.second;
				if (grade == "A+" || grade == "A" || grade == "A-" ||
					grade == "B+" || grade == "B" || grade == "B-" ||
					grade == "C+" || grade == "C" || grade == "C-") {
					if (isFallCourse) 
						passedStudentCountFall++;
					else
						passedStudentCountSpring++;
				}
				else if (grade == "W") {
					if (isFallCourse)
						withdrawStudentCountFall++;
					else 
						withdrawStudentCountSpring++;
				}
				if (isFallCourse) 
					totalStudentCountFall++;
				else 
					totalStudentCountSpring++;
			}
		}	
	}
	// calculate metrics for pass and withdraw rate for fall vs spring course
	double passRateFall = (double)passedStudentCountFall / (double)totalStudentCountFall; 
	double withdrawRateFall = (double)withdrawStudentCountFall / (double)totalStudentCountFall;

	double passRateSpring = (double)passedStudentCountSpring / (double)totalStudentCountSpring; 
	double withdrawRateSpring = (double)withdrawStudentCountSpring / (double)totalStudentCountSpring;

	// insert 1115 for now, will have to change later when adding 3115 & 3130
	std::printf("|  %s  ", "1115"); 
	std::printf("|  %.3f ", passRateFall);
	std::printf("/ %.3f  ", withdrawRateFall);
	std::printf("|   %.3f ", passRateSpring);
	std::printf("/ %.3f   |\n", withdrawRateSpring);
	std::printf("|----------------------------------------------|\n");
	

	// iterate studentGrades map to test 
		// for (auto const& instructor : instructors) 	
	// input csv file is ordered by TermID
	// int count = 0;
	// for (int i=0; i<instructors.size(); ++i) {
	// 	std::cout << "instructor: " << instructors[i].id << '\n';
	// 	std::cout << "report size: " << instructors[i].reports.size() << '\n';
	// 	for (int j=0; j<instructors[i].reports.size(); ++j) {
	// 		std::map<std::string, std::string>::iterator it = instructors[i].reports[j].studentGrades.begin();
	// 		for (std::pair<std::string, std::string> element : instructors[i].reports[j].studentGrades) {
	// 	        // Accessing KEY from element
	// 	        std::string student = element.first;
	// 	        // Accessing VALUE from element.
	// 	        std::string grade = element.second;
	// 	        std::cout << student << " :: " << grade << std::endl;
	// 			count++;
	// 		}
	// 	}
	// }
	// std::cout << count << '\n';
}

