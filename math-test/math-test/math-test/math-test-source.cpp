//
//  math-test-source.cpp
//  MathTest
//
//  Created by Alexandra Tronyagina on 18.04.2022.
//

#include "math-test-header.hpp"

Solution EQ::correctSolution(){
    double d = b * b - 4 * a * c;
    Solution s;
    if (d < 0)
        s.numOfRoots = 0;
    else if (d == 0) {
        s.numOfRoots = 1;
        s.firstRoot = s.secondRoot = -b / (2 * a);
    }
    else{
        s.numOfRoots = 2;
        s.firstRoot = (-b + sqrt(d))/(2 * a);
        s.secondRoot = (-b - sqrt(d))/(2 * a);
    }
    return s;
}

void GoodStudent::solveEQ(vector<EQ>& task, queue<Answer>& studentAnswer){
    Solution s;
    for (int i = 0; i < task.size(); i++) {
        s = task[i].correctSolution();
        studentAnswer.push(Answer(task[i], name, s));
    }
}

void BadStudent::solveEQ(vector<EQ>& task, queue<Answer>& studentAnswer){
    Solution s;
    for (int i = 0; i < task.size(); i++)
        studentAnswer.push(Answer(task[i], name, s));
}

void NormalStudent::solveEQ(vector<EQ>& task, queue<Answer>& studentAnswer){
    Solution s;
    int r;
    for (int i = 0; i < task.size(); i++){
        r = rand() % 100;
        if (r < 50)
            s = task[i].correctSolution();
        else{
            s.firstRoot = s.secondRoot = 0;
            s.numOfRoots = 0;
        }
        studentAnswer.push(Answer(task[i], name, s));
    }
}

vector<Result> Teacher::taskCheck(queue<Answer>& answers){
    vector<Result> results;
    Answer studentAns;
    do {
        studentAns = answers.front();
        Result studentRes(studentAns.name);
        for (int i = 0; i < numOfTasks; i++){
            studentAns = answers.front();
            if (studentAns.studentSolution == studentAns.task.correctSolution())
                studentRes.correctAnswerCount++;
            double proc = studentRes.correctAnswerCount * 100 / numOfTasks;
            if (proc > 85)
                studentRes.grade = 5;
            else if (proc > 65)
                studentRes.grade = 4;
            else if (proc > 45)
                studentRes.grade = 3;
            else
                studentRes.grade = 2;
            answers.pop();
        }
        results.push_back(studentRes);
    } while(!answers.empty());
    return results;
}

void Teacher::printResults(queue<Answer>& answers){
    vector<Result> studentsResult = taskCheck(answers);
    cout<<"Студенты:\t\t Баллы:\t\t Оценка:\n";
    for (int i = 0 ; i < studentsResult.size(); i++)
        cout<< studentsResult[i].studentName << "\t\t\t" <<studentsResult[i].correctAnswerCount << "\t\t\t" << studentsResult[i].grade << "\n";
}

void Teacher::printResultsInFile(queue<Answer>& answers){
    vector<Result> studentsResult = taskCheck(answers);
    std::ofstream fout("FileToPublish.txt");
    fout<<"Студенты:\t\t Баллы:\t\t Оценка:\t\t Всего заданий: "<< numOfTasks << endl;
    for (int i = 0 ; i < studentsResult.size(); i++)
        fout<< studentsResult[i].studentName << "\t\t\t" <<studentsResult[i].correctAnswerCount << "\t\t" << studentsResult[i].grade << "\n";
    fout.close();
}

void readEaquations(vector<EQ>& tasks) {
    std::ifstream fin;
    fin.open("Tasks.txt");
    int a, b, c;
    while (!fin.eof()) {
        fin>>a>>b>>c;
        tasks.push_back(EQ(a, b, c));
    }
    fin.close();
}

queue<Answer> answersQueue(int numOfTasks, vector<EQ> tasks){
    vector<string> students = {
        "Тронягина ",
        "Уразалин  ",
        "Глушак    ",
        "Петрошенко",
        "Шамбергер ",
        "Ващенко   ",
        "Рубанова  ",
        "Шабанов   ",
        "Павлин    "
    };
    queue<Answer> answersToCheck;
    for (int i = 0; i < students.size(); i++) {
        string name = students[i];
        switch (rand() % 3) {
            case 0: {
                GoodStudent student(name);
                student.solveEQ(tasks, answersToCheck);
                break;
            }
            case 1: {
                NormalStudent student(name);
                student.solveEQ(tasks, answersToCheck);
                break;
            }
            case 2: {
                BadStudent student(name);
                student.solveEQ(tasks, answersToCheck);
                break;
            }
        }
    }
    return answersToCheck;
}

