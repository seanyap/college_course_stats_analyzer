#include <fstream>
#include <sstream>

#include <string>
#include <vector>

#include "entities.hpp"
#include "io_processor.hpp"
#include "stats_extractor.hpp"

std::vector <std::string> split(std::string &str, char delimiter) {
	std::vector <std::string> tokens;
	
	std::stringstream sstream(str);
	std::string token;
	while (std::getline(sstream, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
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