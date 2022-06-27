//
//  Header.h
//  dsa_midterm
//
//  Created by jason on 27/06/2022.
//

#ifndef Header_h
#define Header_h

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
#define FEMALE "Female"
#define MALE "Male"
#define MAX_NAME_LENGTH 50

struct Student
{
    string fullName;
    int age;
    string sex;
    unsigned short int point;
};

struct Node
{
    Student infor;
    Node* nextNode;
};

//Merge sort
struct Array
{
    Student* container;
    int size;

    Array()
    {
        container = nullptr;
        size = 0;
    }

    Array(int conSize)
    {
        size = conSize;
        container = new Student[size];
    }

    Student& operator[](const int& index)
    {
        return container[index];
    }
    ~Array()
    {
        if (container)
            delete[] container;
    }
};

#endif /* Header_h */
