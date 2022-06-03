#pragma once
#include "date.h"
class Task
{
public:
    Task();
    Task(std::string name, bool urgent, bool important, Date* due);
    std::string getName();
    bool getUrgent();
    bool getImportant();
    Date* getDate();
    int getID();
    void setID(int id);
    std::string getDateString();
private:
    std::string name;
    bool urgent;
    bool important;
    Date* due;
    int id;
};

