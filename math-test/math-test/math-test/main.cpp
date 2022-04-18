//
//  main.cpp
//  MathTest
//
//  Created by Alexandra Tronyagina on 03.04.2022.
//

#include "math-test-header.hpp"

void readEaquations(vector<EQ>& tasks, FILE* fp) {
    double a, b, c;
    int check = 0;
    do {
        check = fscanf(fp, "%lf %lf %lf\n", &a, &b, &c);
        if (check == EOF)
            break;
        tasks.push_back(EQ(a, b, c));
    } while (1);
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

void test(){
    vector<EQ> tasks;
    FILE* fp = fopen("task.txt", "r");
    readEaquations(tasks, fp);
    fclose(fp);
    Teacher teacher((int)tasks.size());
    queue<Answer> answersToCheck = answersQueue(teacher.numOfTasks, tasks);
    teacher.printResults(answersToCheck);
}

int main() {
    test();
    return 0;
}

