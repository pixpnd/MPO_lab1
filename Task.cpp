#include "Task.h"
Task::Task() {
	this->name = "";
	this->due = new Date;
	this->urgent = false;
	this->important = false;
	this->id = 0;
}

Task::Task(std::string name, bool urgent, bool important, Date* due) {
	this->name = name;
	this->urgent = urgent;
	this->important = important;
	this->due = due;
	this->id = 0;
}
std::string Task::getName() {
	return this->name;
};
bool Task::getUrgent() {
	return this->urgent;
};
bool Task::getImportant() {
	return this->important;
}
Date* Task::getDate() {
	return this->due;
};
std::string Task::getDateString() {
	return this->due->getDate();
};
int Task::getID() {
	return this->id;
}
void Task::setID(int id) {
	this->id = id;
}