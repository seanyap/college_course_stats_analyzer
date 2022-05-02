# college_course_stats_analyzer

College Course Stats Analyzer is a C++ program to process CSV data files to extract insights from college courses and the instructors who taught those courses.

#### Insights extracted include:

- Pass rate for each instructor & course
- Withdraw rate for each instructor & course
- Fall vs Spring Pass & Withdraw rate for each course

#### Process Flow

1. read in data from file into memory
   * parse each record into cols
   * extract respective cols to instantiate structs in memory
2. perform the required insights
   * utilize the data stored and structured by structs to process analysis
3. write the insights into an output file
   * use printf to format and output nicely

#### Data structure motivation

Structs data structure is designed with instructor-centric in mind. It begins with the Instructor entity, which is then connected to other entities, such as Report and Course.

- Instructor entity contains an ID and a list of reports, which represents all the courses that this specific instructor taught
- Report entity contains a Course entity, which tells us the course that this report relates to, and a map data structure of the students who took this course and their respective grades. This Report entity represents the one to many relationship of a single course to many students that took it and their grades.
- Course entity contains an ID (1115, 3115, 3130), the term it was offered, and the section ID

Since I designed the data structure with a focus on instructor, the only data that I needed to track students is the their student ID, hence I omitted from creating a Student struct. A Student struct might be useful in the future if I had other things I needed to keep track that relates to a student.
