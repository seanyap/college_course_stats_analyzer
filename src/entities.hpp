#ifndef ENTITIES_H
#define ENTITIES_H

#include <string>
#include <vector>
#include <map>

struct Course {
	std::string id;
	std::string term;
	std::string section;
	Course() {}
	Course(std::string id, std::string term, std::string section) : id(id), term(term), section(section) {}
};

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

#endif