//
//  math-test-header.hpp
//  MathTest
//
//  Created by Alexandra Tronyagina on 18.04.2022.
//

#ifndef math-test-header_hpp
#define math-test-header_hpp

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <time.h>

using std::string;
using std::vector;
using std::queue;
using std::cout;
using std::endl;

class Solution{
public:
    double firstRoot, secondRoot;
    int numOfRoots;
    Solution(int numOfRoots, double root1, double root2);
    Solution() : firstRoot(0), secondRoot(0), numOfRoots(0) {};
    friend bool operator == (const Solution& x, const Solution& y){
        return x.numOfRoots == y.numOfRoots && x.firstRoot == y.firstRoot && x.secondRoot == y.secondRoot ;
    }
};

class EQ{
public:
    double a, b, c;
    EQ(int a_, int b_, int c_) : a(a_), b(b_), c(c_) {};
    EQ() : a(0), b(0), c(0) {};
    Solution correctSolution();
};

class Answer{
public:
    EQ task;
    string name;
    Solution studentSolution;
    Answer() : task(), name("no name"), studentSolution() {};
    Answer(EQ task_, string name_, Solution solve_) : task(task_), name(name_), studentSolution(solve_) {};
};

class Student{
public:
    string name;
    Student(string name_): name(name_) {};
    virtual void solveEQ(vector<EQ>& task, queue<Answer>& studentAnswer);
};

class GoodStudent : Student{
public:
    GoodStudent(string name_) : Student(name_) {};
    void solveEQ(vector<EQ>& task, queue<Answer>& studentAnswer);
};

class BadStudent : Student{
public:
    BadStudent(string name_) : Student(name_) {};
    Solution studentSolve;
    void solveEQ(vector<EQ>& task, queue<Answer>& studentAnswer);
    
};

class NormalStudent : Student{
public:
    NormalStudent(string name_) : Student(name_) {};
    void solveEQ(vector<EQ>& task, queue<Answer>& studentAnswer);
};

class Result{
public:
    string studentName;
    int correctAnswerCount;
    int grade;
    Result(string name_) : studentName(name_), correctAnswerCount(0), grade(2) {};
};

class Teacher{
public:
    int numOfTasks;
    Teacher(int numOfTask) : numOfTasks(numOfTask) {};
    vector<Result> taskCheck(queue<Answer>& answers);
    void printResults(queue<Answer>& answers);
};

void readEaquations(vector<EQ>& tasks);
queue<Answer> answersQueue(int numOfTasks, vector<EQ> tasks);

#endif /* math-test-header_hpp */
