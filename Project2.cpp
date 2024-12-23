#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>


using namespace std;

struct Course {
    string courseID;
    string courseName;
    vector<string> prerequisites;
};

void loadDataStructure(const string& filename, unordered_map<string, Course>& courses);
void printCourseList(const unordered_map<string, Course>& courses);
void printCourse(const unordered_map<string, Course>& courses, const string& courseID);
void displayMenu();

int main() {
    unordered_map<string, Course> courses;
    string userInput;

    cout << "Welcome to the course planner." << endl;

    while (true) {
        displayMenu();
        cout << "What would you like to do? ";
        cin >> userInput;

        if (userInput == "1") {
            string filename;
            cout << "Enter the file name: ";
            cin >> filename;
            loadDataStructure(filename, courses);
        } else if (userInput == "2") {
            printCourseList(courses);
        } else if (userInput == "3") {
            string courseID;
            cout << "What course do you want to know about? ";
            cin >> courseID;
            printCourse(courses, courseID);
        } else if (userInput == "9") {
            cout << "Thank you for using the course planner!" << endl;
            break;
        } else {
            cout << userInput << " is not a valid option." << endl;
        }
    }

    return 0;
}

void displayMenu() {
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
}

void loadDataStructure(const string& filename, unordered_map<string, Course>& courses) {
    ifstream file(filename);
    if (!file) {
        cout << "Error: Cannot open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseID, courseName, prereq;
        
        // Using ',' as the delimiter instead of '\t'
        getline(ss, courseID, ',');
        getline(ss, courseName, ',');

        Course course;
        course.courseID = courseID;
        course.courseName = courseName;

        // Collecting prerequisites if they exist (could be empty)
        while (getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }

        courses[courseID] = course;
    }

    file.close();
    cout << "Data loaded successfully." << endl;
}


void printCourseList(const unordered_map<string, Course>& courses) {
    if (courses.empty()) {
        cout << "No courses available. Please load data first." << endl;
        return;
    }

    vector<string> sortedCourseIDs;
    for (const auto& pair : courses) {
        sortedCourseIDs.push_back(pair.first);
    }

    sort(sortedCourseIDs.begin(), sortedCourseIDs.end());

    cout << "Here is a sample schedule:" << endl;
    for (const string& courseID : sortedCourseIDs) {
        const Course& course = courses.at(courseID);
        cout << course.courseID << ", " << course.courseName << endl;
    }
}

void printCourse(const unordered_map<string, Course>& courses, const string& courseID) {
    auto it = courses.find(courseID);
    if (it == courses.end()) {
        cout << "Error: Course not found." << endl;
        return;
    }

    const Course& course = it->second;
    cout << course.courseID << ", " << course.courseName << endl;

    if (course.prerequisites.empty()) {
        cout << "This course has no prerequisites." << endl;
    } else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

