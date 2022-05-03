#ifndef STATS_EXTRACTOR_H
#define STATS_EXTRACTOR_H

#include <string>
#include <vector>

#include "entities.hpp"

enum courseTypes {
	CIS1115, CIS3115, CIS3130, OTHER
};

int findInstructor(std::string target, std::vector <Instructor> &instructors);

int findCourse(std::vector <Report> &reports, std::string courseID, std::string termID, std::string sectionID);

// TODO: change return type to double 
void findPassAndWithdrawRate(std::vector <Instructor> &instructors);
void findCoursePassAndWithdrawRate(std::vector <Instructor> &instructors);
void findFallAndSpringPassAndWithdrawRate(std::vector <Instructor> &instructors);

#endif