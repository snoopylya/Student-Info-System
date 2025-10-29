#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_STUDENTS = 10;
const int MAX_SUBJECTS = 5;

struct Subject {
    string name;
    int credit;
    double mark;
    char grade;
};

struct Student {
    string name;
    int age;
    Subject subjects[MAX_SUBJECTS];
    int subjectCount;
    double cpa;
};

Student students[MAX_STUDENTS];
int studentCount = 0;

void addStudent();
void displayStudents();
char calculateGrade(double mark);
double calculateCPA(const Student &s);

int main() {
    int choice;
    do {
        cout << "\n------ STUDENT INFORMATION SYSTEM ------\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 3);
    return 0;
}

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "Maximum number of students reached.\n";
        return;
    }

    Student s;
    cout << "\nEnter student name: ";
    cin >> ws;
    getline(cin, s.name);
    cout << "Enter age: ";
    cin >> s.age;

    cout << "Enter number of subjects (max 5): ";
    cin >> s.subjectCount;
    if (s.subjectCount > MAX_SUBJECTS) s.subjectCount = MAX_SUBJECTS;

    for (int i = 0; i < s.subjectCount; i++) {
        cout << "\nSubject #" << (i + 1) << endl;
        cout << "Subject name: ";
        cin >> ws;
        getline(cin, s.subjects[i].name);
        cout << "Credit hour: ";
        cin >> s.subjects[i].credit;

        do {
            cout << "Mark (0-100): ";
            cin >> s.subjects[i].mark;
            if (s.subjects[i].mark < 0 || s.subjects[i].mark > 100)
                cout << "Invalid mark! Please enter between 0 and 100.\n";
        } while (s.subjects[i].mark < 0 || s.subjects[i].mark > 100);

        s.subjects[i].grade = calculateGrade(s.subjects[i].mark);
    }

    s.cpa = calculateCPA(s);
    students[studentCount++] = s;
    cout << "Student added successfully!\n";
}

char calculateGrade(double mark) {
    if (mark >= 80) return 'A';
    else if (mark >= 70) return 'B';
    else if (mark >= 60) return 'C';
    else if (mark >= 50) return 'D';
    else return 'F';
}

double calculateCPA(const Student &s) {
    double totalPoints = 0, totalCredits = 0;
    for (int i = 0; i < s.subjectCount; i++) {
        double gradePoint;
        switch (s.subjects[i].grade) {
            case 'A': gradePoint = 4.0; break;
            case 'B': gradePoint = 3.0; break;
            case 'C': gradePoint = 2.0; break;
            case 'D': gradePoint = 1.0; break;
            default: gradePoint = 0.0; break;
        }
        totalPoints += gradePoint * s.subjects[i].credit;
        totalCredits += s.subjects[i].credit;
    }
    return (totalCredits == 0) ? 0 : (totalPoints / totalCredits);
}

void displayStudents() {
    if (studentCount == 0) {
        cout << "No students found.\n";
        return;
    }

    cout << "\n------ STUDENT LIST ------\n";
    for (int i = 0; i < studentCount; i++) {
        cout << "\nStudent #" << i + 1 << ": " << students[i].name << endl;
        cout << "Age: " << students[i].age << endl;
        cout << "CPA: " << fixed << setprecision(2) << students[i].cpa << endl;

        cout << left << setw(20) << "Subject"
             << setw(10) << "Credit"
             << setw(10) << "Mark"
             << setw(10) << "Grade" << endl;

        for (int j = 0; j < students[i].subjectCount; j++) {
            cout << left << setw(20) << students[i].subjects[j].name
                 << setw(10) << students[i].subjects[j].credit
                 << setw(10) << students[i].subjects[j].mark
                 << setw(10) << students[i].subjects[j].grade << endl;
        }
    }
}