#ifndef TASKCLASS1_H
#define TASKCLASS1_H
#include <iostream>
#include <string>
#include <array>
#include <algorithm>


class TaskClass1
{
    public:
        TaskClass1(const std::string& taskNameIn, const std::array<int, 3>& dateIn);
        virtual ~TaskClass1();
        std::string getName();
        int getDay();
        int getMonth();
        int getYear();

    protected:

    private:
    std::string taskName;
    std::array<int, 3> date = {01, 01, 1970};

};

#endif // TASKCLASS1_H
