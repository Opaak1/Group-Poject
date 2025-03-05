#include <iostream>
#include <fstream>
using namespace std;

string calculateLetterGrade(double quizAverageScore){
    string letterGrade = "This student has a grade of ";
    if(quizAverageScore >= 90){
        return letterGrade + "A";
    }
    else if(quizAverageScore >= 80){
        return letterGrade + "B";
    }
    else if(quizAverageScore >= 75){
        return letterGrade + "C+";
    }
    else if(quizAverageScore >= 70){
        return letterGrade + "C";
    }
    else if(quizAverageScore >= 60){
        return letterGrade + "D";
    }
    return letterGrade + "F";
}
double findMinQuiz(double q1, double q2, double q3, double q4){
    double min = q1;
    if(min > q2){
        min = q2;
    }
    if(min > q3){
        min = q3;
    }
    if(min > q4){ //else if is not needed here so I didn't bother and just used if as it achieves the same results
        min = q4;
    }
    return min;
}
double findAverageQuizScore(double q1, double q2, double q3, double q4){
    return ((q1 + q2 + q3 + q4) - findMinQuiz(q1, q2, q3, q4))/3; //findMinQuiz is used here as the lowest quiz score is dropped
}
double findAverageHWScore(double hw1, double hw2, double hw3, double hw4){
    return (hw1 + hw2 + hw3 + hw4)/4;
}
double findAverageLabScore(double l1, double l2, double l3, double l4, double l5, double l6, double l7, double l8){
    return (l1 + l2 + l3 + l4 + l5 + l6 + l7 + l8)/8;
}

int main(){





    return 0;
}