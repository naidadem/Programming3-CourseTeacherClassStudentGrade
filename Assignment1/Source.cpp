#include <iostream>
#include <regex>
#include <vector>
#include <string>

using namespace std;

bool VerifyTheValidityOfThePhoneNumber(string phoneNumber) {//global function

															// phone number needs to be in this format: +387(61)-222-333

	string rule = "(\\+)?(\\d{3})([-.])?(\\()?(\\d{2})(\\))?([-.])?(\\d{3})([-.]?)(\\d{3})";

	return regex_match(phoneNumber, regex(rule));

}

enum Courses { Maths, History, Geography, Chemistry, Biology, English, Music, German };
enum Classes { I1, I2, I3, II1, II2, II3, III1, III2, III3, IV1, IV2, IV3 };
char * printCourses[] = { "Maths", "History", "Geography", "Chemistry", "Biology", "English", "Music", "German" };
char * printClasses[] = { "I1", "I2", "I3", "II1", "II2", "II3", "III1", "III2", "III3", "IV1", "IV2", "IV3" };

ostream & operator << (ostream & C, Courses course) {

	C << "Course: " << printCourses[(int)course];

	return C;

}

ostream & operator << (ostream & C, Classes _class) {

	C << "Class: " << printClasses[(int)_class];

	return C;

}

char * crt = "\n------------\n\n";

template<Class T1, Class T2>
Class Collection{
	T1 * _elements1;
T2 * _elements2;
int _currently;
public:
	Collection()
	{
		_elements1 = nullptr;
		_elements2 = nullptr;
		_currently = 0;
	}
	~Collection()
	{
		delete[]_elements1;
		delete[]_elements2;
	}

	Collection(Collection & obj) {

		_elements1 = new T1[obj._currently];
		_elements2 = new T2[obj._currently];

		_currently = obj._currently;

		for (int i = 0; i < obj._currently; i++) {

			_elements1[i] = obj._elements1[i];
			_elements2[i] = obj._elements2[i];

		}

	}

	bool AddElement(T1 element1, T2 element2) {

		T1 * temp1 = new T1[_currently + 1];
		T2 * temp2 = new T2[_currently + 1];

		for (int i = 0; i < _currently; i++) {

			temp1[i] = _elements1[i];
			temp2[i] = _elements2[i];

		}

		if (_currently != 0) {
			delete[] _elements1;
			delete[] _elements2;
		}

		_elements1 = temp1;
		_elements2 = temp2;

		_elements1[_currently] = element1;
		_elements2[_currently] = element2;

		_currently++;

		return true;

	}

	bool RemoveElement(int location) {

		if (_currently == 0)
			return false;

		T1 * temp1 = new T1[_currently];
		T2 * temp2 = new T2[_currently];

		for (int i = 0, g = 0; i < _currently; i++, g++) {

			if (i == location)
				g++;

			temp1[i] = _elements1[g];
			temp2[i] = _elements2[g];

		}

		delete[] _elements1;
		delete[] _elements2;

		_elements1 = temp1;
		_elements2 = temp2;

		_currently--;

		return true;

	}

	T1 GetElement1(int location) { return _elements1[location]; }
	T2 GetElement2(int location) { return _elements2[location]; }

	void operator = (Collection & obj) {

		if (_currently != 0) {

			delete[] _elements1;
			delete[] _elements2;

		}

		for (int i = 0; i < obj._currently; i++) {

			AddElement(obj.GetElement1(i), obj.GetElement2(i));

		}

	}

	int GetCurrently() { return _currently; }

	friend ostream & operator << <> (ostream & C, Collection<T1, T2> & obj);

};

template<Class T1, Class T2>
ostream & operator << <> (ostream & C, Collection<T1, T2> & obj) {

	C << "Currently: " << obj._currently << endl;

	for (int i = 0; i < obj._currently; i++) {

		C << "Element1, location: " << i << " is ";
		C << obj._elements1[i];
		C << endl;
		C << "Element2, location " << i << " is ";
		C << obj._elements2[i];
		C << endl;

	}

	return C;

}

Class _Date{
	int *_day, *_month, *_year;
public:
	_Date(int day = 1, int month = 1, int year = 2000) {
		_day = new int(day);
		_month = new int(month);
		_year = new int(year);
	}

	_Date(const _Date&obj) {
		_day = new int(*obj._day);
		_month = new int(*obj._month);
		_year = new int(*obj._year);
	}

	~_Date() {
		delete _day; _day = nullptr;
		delete _month; _month = nullptr;
		delete _year; _year = nullptr;
	}

	_Date & operator = (_Date & obj) {

		*_day = *obj._day;
		*_month = *obj._month;
		*_year = *obj._year;

		return *this;

	}


	friend ostream& operator<< (ostream &COUT, const _Date &obj) {
		COUT << *obj._day << " " << *obj._month << " " << *obj._year;
		return COUT;
	}
};
Class Person{
protected:
	char * _nameSurname;
	_Date * _DateOfBirth;
	string _phoneNumber;
public:
	Person(char * nameSurname, _Date date) {
		_nameSurname = new char[strlen(nameSurname) + 1];
		strcpy_s(_nameSurname, strlen(nameSurname) + 1, nameSurname);
		_DateOfBirth = new _Date(date);
		_phoneNumber = "";

	}
	Person(const Person & obj) :_phoneNumber(obj._phoneNumber) {
		_nameSurname = new char[strlen(obj._nameSurname) + 1];
		strcpy_s(_nameSurname, strlen(obj._nameSurname) + 1, obj._nameSurname);
		_DateOfBirth = new _Date(*obj._DateOfBirth);
	}
	virtual ~Person() { delete[]_nameSurname; delete _DateOfBirth; }

	bool setPhoneNumber(string phoneNumber) {
		if (VerifyTheValidityOfThePhoneNumber(phoneNumber)) {
			_phoneNumber = phoneNumber;
			return true;
		}
		return false;
	}

};

Class Teacher : public Person{
	Collection<Courses, Classes> * _CoursesClasses;

public:

	Teacher(char * nameSurname, _Date dat) : Person(nameSurname, dat) {

		_CoursesClasses = new Collection < Courses, Classes >;

	}

	virtual ~Teacher() { delete _CoursesClasses; _CoursesClasses = nullptr; }

	Teacher(Teacher & obj) : Person(obj) {

		_CoursesClasses = new Collection < Courses, Classes >(*obj._CoursesClasses);

	}

	bool AddcourseClass(Courses course, Classes _class) {

		_CoursesClasses->AddElement(course, _class);

		return true;

	}

	bool RemoveCourseClass(Courses course) {

		bool isRemoved = 0;

		for (int i = 0; i < _CoursesClasses->GetCurrently(); i++) {

			if (_CoursesClasses->GetElement1(i) == course) {
				_CoursesClasses->RemoveElement(i);
				isRemoved = true;
			}

		}

		return isRemoved;

	}

	Teacher & operator = (Teacher & obj) {

		_phoneNumber = obj._phoneNumber;
		_nameSurname = new char[strlen(obj._nameSurname) + 1];
		strcpy_s(_nameSurname, strlen(obj._nameSurname) + 1, obj._nameSurname);
		__DateOfBirth = new _Date(*obj.__DateOfBirth);

		delete _CoursesClasses;

		_CoursesClasses = new Collection<Courses, Classes>(*obj._CoursesClasses);

		return *this;

	}

	bool operator == (Teacher & obj) {

		if (strcmp(_nameSurname, obj._nameSurname) == 0)
			return true;

		return false;

	}

	bool ifClassExists(Classes Class) {

		for (int i = 0; i < _CoursesClasses->GetCurrently(); i++) {

			if (_CoursesClasses->GetElement2(i) == Class)
				return true;

		}

		return false;

	}

	bool ifCourseExists(Courses course) {

		for (int i = 0; i < _CoursesClasses->GetCurrently(); i++) {

			if (_CoursesClasses->GetElement1(i) == course)
				return true;

		}

		return false;

	}

	Collection<Courses, Classes> & getCoursesClasses() { return *_CoursesClasses; }

	friend ostream & operator << (ostream & C, Teacher & obj) {

		C << "Teacher's name and surname: " << obj._nameSurname << endl;
		C << "Date of birth: " << *obj.__DateOfBirth << endl;
		C << "Phone number: " << obj._phoneNumber << endl;

		C << "Courses and classes teacher is teaching: " << endl;

		C << *obj._CoursesClasses << endl;

		return C;

	}

};

Class Student : public Person{
	int _studentID;
Classes _Class;
vector<Teacher *> _teachers;
Collection<Courses, int> _CoursesGrades;

public:

	Student(char * nameSurname, _Date dat, int studentID, Classes _class) : Person(nameSurname, dat), _Class(_class) {

		_studentID = studentID;

	}

	//Student(Student & obj) : Person(obj) {}

	Student & operator = (Student & obj) {

		_phoneNumber = obj._phoneNumber;
		_nameSurname = new char[strlen(obj._nameSurname) + 1];
		strcpy_s(_nameSurname, strlen(obj._nameSurname) + 1, obj._nameSurname);
		__DateOfBirth = new _Date(*obj.__DateOfBirth);

		_studentID = obj._studentID;
		_Class = obj._Class;

		_teachers = obj._teachers;

		_CoursesGrades = obj._CoursesGrades;

		return *this;

	}

	bool AddTeacher(Teacher & obj) {

		for (int i = 0; i < _teachers.size(); i++) {

			if (*_teachers[i] == obj)
				return false;

		}

		if (!obj.ifClassExists(_Class)) { return false; }



		_teachers.push_back(&obj);

		return true;

	}

	bool AddCourseGrade(Courses course, int grade) {

		for (int i = 0; i < _teachers.size(); i++) {

			if (_teachers[i]->ifCourseExists(course)) {

				_CoursesGrades.AddElement(course, grade);

				return true;

			}

		}

		return false;


	}

	vector<Teacher *> & getTeachers() { return _teachers; }

	Collection<Courses, int> & getCourseGrades() { return _CoursesGrades; }

	float GetAverageByTeacher(char * nameSurname) {

		float average = 0;
		int numberOfGrades = 0;
		bool isFound = false;

		_Date tempdat(10, 11, 12);

		Teacher temp(nameSurname, tempdat);

		for (int i = 0; i < _teachers.size(); i++) {

			if (temp == *_teachers[i]) {

				isFound = true;

				temp = *_teachers[i];

			}

		}

		if (!isFound)
			return average;

		for (int i = 0; i < _CoursesGrades.GetCurrently(); i++) {

			for (int j = 0; j < temp.getCoursesClasses().GetCurrently(); j++) {

				if (_CoursesGrades.GetElement1(i) == temp.getCoursesClasses().GetElement1(j)) {
					average += _CoursesGrades.GetElement2(i);
					numberOfGrades++;
				}

			}

		}

		if (numberOfGrades == 0)
			return average;

		return average / numberOfGrades;

	}

	friend ostream & operator << (ostream & C, Student & obj) {

		C << crt;
		C << "Student's name and surname: " << obj._nameSurname << endl;
		C << "Date of birth: " << *obj.__DateOfBirth << endl;
		C << "Phone number: " << obj._phoneNumber << endl;
		C << "Student ID: " << obj._studentID << endl;

		C << obj._Class << endl;

		C << "\n***Teachers that are teaching this student: \n" << endl;

		for (int i = 0; i < obj._teachers.size(); i++) {

			C << *obj._teachers[i];

		}

		C << "***Courses that this student is listening: " << endl;

		for (int i = 0; i < obj._CoursesGrades.GetCurrently(); i++) {

			C << obj._CoursesGrades.GetElement1(i) << endl;

		}

		return C;


	}

};



void main() {
	//Date testing
	_Date today(26, 11, 2015);
	_Date tomorrow(today);
	_Date dayAfterTomorrow;
	dayAfterTomorrow = today;
	cout << today << endl << tomorrow << endl << dayAfterTomorrow << crt;

	//Collection testing
	Collection<int, int> Collection1;
	int numberOfElements = 15;
	for (size_t i = 0; i < numberOfElements; i++)
		Collection1.AddElement(i, i);
	Collection1.RemoveElement(0);//removes element by its location
	cout << Collection1.GetElement1(0) << " " << Collection1.GetElement2(0) << endl;
	cout << Collection1 << endl;
	Collection<int, int> Collection2;
	Collection2 = Collection1;
	cout << Collection2 << crt;
	if (Collection1.GetCurrently() == Collection2.GetCurrently())
		cout << "SAME NUMBER OF ELEMENTS" << endl;
	Collection<int, int> Collection3(Collection2);
	cout << Collection3 << crt;

	//Teacher testing
	Teacher jasmin("Jasmin Azemovic", _Date(15, 2, 1980));
	Teacher adel("Adel Handzic", _Date(15, 10, 1981));
	//Teacher can teach same course, but it has to be in different classes and maximum two classes (two different years)
	if (jasmin.AddcourseClass(Maths, I1))
		cout << "Course added" << endl;
	if (jasmin.AddcourseClass(History, I1))
		cout << "Course added" << endl;

	if (jasmin.AddcourseClass(Geography, I1))
		cout << "Course added" << endl;

	if (jasmin.AddcourseClass(Geography, I2))
		cout << "Course added" << endl;

	if (adel.AddcourseClass(History, III1))
		cout << "Course added" << endl;

	if (adel.RemovecourseClass(History))
		cout << "Course removed!" << endl;

	Teacher goran(adel);
	if (goran == adel)
		cout << "Teachers are identical" << endl;
	goran = jasmin;
	if (goran == jasmin)
		cout << "Teachers are identical" << endl;

	Collection<Courses, Classes> & CoursesClasses = jasmin.getCoursesClasses();

	if (!jasmin.setBrojphoneNumbera("+38761111222"))
		cout << "Phone number hasn't been added!" << endl;
	if (!jasmin.setBrojphoneNumbera("+387-61-111-222"))
		cout << "Phone number hasn't been added!" << endl;
	if (jasmin.setBrojphoneNumbera("+387(61)-111-222"))
		cout << "Phone number has been added!" << endl;


	//Student testing
	Student denis("Denis Music", _Date(8, 10, 1990), 3, III1);
	Student elmin("Elmin Sudic", _Date(15, 6, 1993), 1, I1);
	Student adil("Adil Joldic", _Date(13, 8, 1992), 2, II1);
	//take care of that references are added to teachers so that all students would share same information about teachers in case that some course is added to teacher
	//for successful adding, teaches has to have (teach) at least one course in that class
	if (denis.AddTeacher(jasmin))
		cout << "Teacher has been added!" << endl;
	//disable adding identical teachers; identical means the same values of all atributes
	if (denis.AddTeacher(adel))
		cout << "Teacher has been added!" << endl;
	//to be able to add a grade for some course, student has to have teacher that is teaching that course
	if (denis.AddCourseGrade(Maths, 3))
		cout << "Grade has been added!" << endl;
	if (denis.AddCourseGrade(History, 4))
		cout << "Grade has been added!" << endl;

	vector<Teacher*> & nastavnici = denis.getTeachers();
	cout << "Student Denis has " << nastavnici.size() << " teachers" << endl;

	Collection<Courses, int> & score = denis.getCourseGrades();
	cout << "Denis has " << score.GetCurrently() << " passed courses" << endl;
	cout << "Average grade for Jasmin Azemovic is " << denis.GetAverageByTeacher("Jasmin Azemovic") << endl;

	Student denis2(denis);
	cout << denis2 << endl;


	system("pause>0");

}