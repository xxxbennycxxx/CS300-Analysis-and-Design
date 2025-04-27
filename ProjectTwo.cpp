#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Course structure
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

// Load course data from CS 300 ABCU_Advising_Program_Input.csv (manually added)
void loadCourses(unordered_map<string, Course>& courseTable) {
    courseTable["MATH201"] = { "MATH201", "Discrete Mathematics", {} };
    courseTable["CSCI100"] = { "CSCI100", "Introduction to Computer Science", {} };
    courseTable["CSCI101"] = { "CSCI101", "Introduction to Programming in C++", {"CSCI100"} };
    courseTable["CSCI200"] = { "CSCI200", "Data Structures", {"CSCI101"} };
    courseTable["CSCI300"] = { "CSCI300", "Introduction to Algorithms", {"CSCI200", "MATH201"} };
    courseTable["CSCI301"] = { "CSCI301", "Advanced Programming in C++", {"CSCI101"} };
    courseTable["CSCI350"] = { "CSCI350", "Operating Systems", {"CSCI300"} };
    courseTable["CSCI400"] = { "CSCI400", "Large Software Development", {"CSCI301", "CSCI350"} };

    cout << "Courses loaded successfully. Total courses: " << courseTable.size() << endl;
}

// Function to print all courses sorted
void printAllCourses(const unordered_map<string, Course>& courseTable) {
    if (courseTable.empty()) {
        cout << "No courses loaded. Please load the data first." << endl;
        return;
    }

    vector<Course> courseList;
    for (const auto& pair : courseTable) {
        courseList.push_back(pair.second);
    }

    sort(courseList.begin(), courseList.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
        });

    for (const auto& course : courseList) {
        cout << course.courseNumber << ": " << course.courseName << endl;
    }
}

// Function to search for a course and show details
void searchCourse(const unordered_map<string, Course>& courseTable, const string& courseNumber) {
    auto it = courseTable.find(courseNumber);
    if (it == courseTable.end()) {
        cout << "Course not found" << endl;
        return;
    }

    const Course& course = it->second;
    cout << course.courseNumber << ": " << course.courseName << endl;

    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    }
    else {
        cout << "Prerequisites:" << endl;
        for (const string& prereqNumber : course.prerequisites) {
            auto preIt = courseTable.find(prereqNumber);
            if (preIt != courseTable.end()) {
                cout << "- " << preIt->second.courseNumber << ": " << preIt->second.courseName << endl;
            }
            else {
                cout << "- " << prereqNumber << ": Not found" << endl;
            }
        }
    }
}

// Display menu
void displayMenu() {
    unordered_map<string, Course> courseTable;
    int choice = 0;

    while (choice != 9) {
        cout << "\nMenu:" << endl;
        cout << "  1. Load Data Structure" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline

        switch (choice) {
        case 1:
            loadCourses(courseTable);
            break;
        case 2:
            printAllCourses(courseTable);
            break;
        case 3:
            cout << "Enter course number: ";
            {
                string courseNumber;
                getline(cin, courseNumber);
                searchCourse(courseTable, courseNumber);
            }
            break;
        case 9:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid option. Please choose 1, 2, 3, or 9." << endl;
        }
    }
}

int main() {
    displayMenu();
    return 0;
}
