#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Score {
	public:
	int math;
	int english;
	Score(int m, int e) : math(m), english(e) {}
};

class Student {
	public:
	int age;
	int birth_year;
	Score score;
	Student(int age, int year, Score score): age(age), birth_year(year), score(score) {}
};

/**
 * @brief Print the students' infomation.
 * 
 * @param s All students.
 */
void
printStudents(const vector<Student *> &s) {
	for(auto &one: s) {
		printf("Age: %d; Birth Year: %d; Math: %d; English: %d\n", 
			one->age, one->birth_year, one->score.math, one->score.english);
	}
	printf("----------\n");
}

int main() {
	Student *s1 = new Student(10, 2001, Score(100, 100));
	Student *s2 = new Student(10, 2002, Score(200, 200));
	vector<Student *> students;
	students.push_back(s1);
	students.push_back(s2);
	printStudents(students);
	s2->birth_year = 2012;
	s2->score.math = 200000;
	printStudents(students);
	return 0;
}