#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Student {
    string first;
    string last;
    double attendance;         
    double quiz[4];         
    double lab[8];          
    double hw[4];   //reminder: 2 are graded out of 10, other 2 out of 20
    double groupWork;       
    double midterm;         
    double finalExam;       
    double courseAverage;   
    string letterGrade;     
};


double findMinQuiz(Student s){
    double min = s.quiz[0];
    for(int i = 0; i < 4; i++){
        if(s.quiz[i] < min){
            min = s.quiz[i];
        }
    }
    return min;
}
double findAverageQuizScore(Student s){
    double sum = 0;
    for (int i = 0; i < 4; i++) {
        sum += s.quiz[i];
    }
    return (sum - findMinQuiz(s)) / 3.0; //drop lowest
}
double findAverageHWScore(Student s){
    double homework[4];
    homework[0] = s.hw[0]; 
    homework[1] = s.hw[1]; 
    homework[2] = (s.hw[2] / 20.0) * 10.0;
    homework[3] = (s.hw[3] / 20.0) * 10.0;

    double sum = 0;
    for (int i = 0; i < 4; i++) {
        sum += homework[i];
    }
    return sum / 4.0;
}
double findAverageLabScore(Student s){
    double sum = 0;
    for (int i = 0; i < 8; i++) {
        sum += s.lab[i];
    }
    return sum / 8.0;
}

double calculateCourseAverage(Student s) {
    double labAvg = findAverageLabScore(s);            
    double hwAvg = findAverageHWScore(s);         
    double quizAvg = findAverageQuizScore(s);         
    double attendanceScore = s.attendance;
    double group = s.groupWork;                 

    double courseAverage =
        (attendanceScore / 10.0) * 10 +
        (labAvg / 10.0) * 15 + 
        (hwAvg / 10.0) * 15 +
        (quizAvg / 100.0) * 15 +
        (group / 10.0) * 5 +
        (s.midterm / 100.0) * 20 +
        (s.finalExam / 100.0) * 20;

    return courseAverage;
}

string calculateLetterGrade(Student s){
    string letterGrade = "Letter Grade: ";
    if(s.courseAverage >= 90)
        return letterGrade + "A";
    else if(s.courseAverage >= 80)
        return letterGrade + "B";
    else if(s.courseAverage >= 75)
        return letterGrade + "C+";
    else if(s.courseAverage >= 70)
        return letterGrade + "C";
    else if(s.courseAverage >= 60)
        return letterGrade + "D";
    return letterGrade + "F";
}

int main() {
    ifstream fin("/Users/yannis/Documents/projectFiles/gradesIn.txt");
    if (!fin) {
        cerr << "gradeIn file failed to open" << endl; //if this fails to open change filepath or check your file name
        return 1;
    }

    Student students[35]; 
    int studentCount = 0;  
    while (fin >> students[studentCount].first >> students[studentCount].last) {
        fin >> students[studentCount].attendance;

        for (int i = 0; i < 8; i++)
        fin >> students[studentCount].lab[i];
        for (int i = 0; i < 4; i++)
        fin >> students[studentCount].hw[i];
        for (int i = 0; i < 4; i++)
        fin >> students[studentCount].quiz[i];

        fin >> students[studentCount].groupWork;
        fin >> students[studentCount].midterm;
        fin >> students[studentCount].finalExam;

        students[studentCount].courseAverage = calculateCourseAverage(students[studentCount]);
        students[studentCount].letterGrade = calculateLetterGrade(students[studentCount]);

        studentCount++;    //to know how many students there are as 35 is the maximun # of students, doesn't mean it will be max
    } //store the information in the file to the struct

    fin.close();

    ofstream fout("/Users/yannis/Documents/projectFiles/gradesOut1.txt");
    fout << fixed << setprecision(2);  //2 decimal places
    for (int i = 0; i < studentCount; i++) {
        fout << students[i].first << " " << students[i].last << endl;
        fout << "Attendance: " << students[i].attendance << endl;
        fout << "Group Work: " << students[i].groupWork << endl;
        fout << "Quiz Average: " << findAverageQuizScore(students[i]) << endl;
        fout << "Lab Average: " << findAverageLabScore(students[i]) << endl;
        fout << "Homework Average: " << findAverageHWScore(students[i]) << endl;
        fout << "Final Exam: " << students[i].finalExam << endl;
        fout << "Course Average: " << students[i].courseAverage << endl;
        fout << "--------------------" << endl;
    }
    fout.close();

    ofstream fout2("/Users/yannis/Documents/projectFiles/gradesOut2.txt");
    fout2 << fixed << setprecision(2);  
    double totalCourseAvg = 0;
    for (int i = 0; i < studentCount; i++) {
        fout2 << students[i].first << " " << students[i].last << endl;
        fout2 << "Course Average: " << students[i].courseAverage << endl;
        fout2 << students[i].letterGrade << endl;
        fout2 << "--------------------" << endl;
        totalCourseAvg += students[i].courseAverage;
    }

    fout2 << "Total number of students: " << studentCount << endl;
    fout2 << "Total course average: " << (totalCourseAvg / studentCount) << endl;

    fout2.close();

    return 0;
}