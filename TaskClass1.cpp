#include "TaskClass1.h"
#include <iostream>
#include <string>
#include <array>
#include <algorithm>

TaskClass1::TaskClass1(const std::string& taskNameIn, const std::array<int, 3>& dateIn) //constructor for class object with same name variable which replaces white space with underscore and adds array with date
{
    date = dateIn;
    taskName = taskNameIn;
    std::replace(taskName.begin(), taskName.end(), ' ', '_');

}

std::string TaskClass1::getName() const//return the underscore version of task name
{
    return taskName;
}

int TaskClass1::getDay() const//return day
{
    return date[0];
}

int TaskClass1::getMonth() const//return month
{
    return date[1];
}

int TaskClass1::getYear() const//return year
{
    return date[2];
}

TaskClass1::~TaskClass1()
{
    //destructor
}
std::vector<TaskClass1> taskObjects;
std::array<int, 3> tempDateTemplate;
