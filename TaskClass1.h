#ifndef TASKCLASS1_H
#define TASKCLASS1_H
#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <list>
#include <map>


class TaskClass1
{
    public:
        TaskClass1(const std::string& taskNameIn, const std::array<int, 3>& dateIn);
        virtual ~TaskClass1();
        std::string getName() const;
        int getDay() const;
        int getMonth() const;
        int getYear() const;

    protected:

    private:
    std::string taskName;
    std::array<int, 3> date = {01, 01, 1970};

};

extern std::list<TaskClass1> taskObjects;
extern std::array<int, 3> tempDateTemplate;
extern std::map<std::string, std::list<TaskClass1>::iterator> taskMap;
#endif // TASKCLASS1_H

