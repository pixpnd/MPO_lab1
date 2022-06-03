// MPO_lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*Приложение для тайм-менеджмента
1. Матрица Эйзенхауэра
2. Список для хранения во внутренней памяти
3. Структура:
    ID - случайный (уникальный) - 4 значный
    Название задачи
    Дата окончания
    Срочно/Не срочно
    Важно/Не важно

 4. Функции:
    Сохранение всех файлов в бд
    Загрузка всех файлов из бд
    Вывод в виде матрицы с названиями и ID
    Вывод отдельной задачи по ID
    Вывод просроченных задач
    Добавление задачи +
    Удаление задачи по ID
    Удаление просроченных задач
    Сортировка по сроку
    Сортировка по алфавиту

*/
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <regex>
#include <ctime>
#include <Windows.h>
#include <fstream>
#include "date.h"
#include "Task.h"

using namespace std;


bool isNumberValid(string str) {
    int number;
    try
    {
        number = stoi(str);
    }
    catch (const std::invalid_argument&)
    {
        return false;
    }
    catch (const std::out_of_range&) {
        return false;
    }
    if (number < 0) return false;
    return true;

};

bool isDateValid(string date) {
    static const regex r(R"((^(((0[1-9]|1[0-9]|2[0-8])[\/](0[1-9]|1[012]))|((29|30|31)[\/](0[13578]|1[02]))|((29|30)[\/](0[4,6,9]|11)))[\/](19|[2-9][0-9])\d\d$)|(^29[\/]02[\/](19|[2-9][0-9])(00|04|08|12|16|20|24|28|32|36|40|44|48|52|56|60|64|68|72|76|80|84|88|92|96)$))", regex::collate);
    return regex_match(date.data(), r);
}

void UIWait() {
    cout << "Для возврата в предыдущее меню, нажмите Enter" << endl;
    cin.ignore(32767, '\n');
    getchar();
}
void printHeader(string header) {
    cout << "------------------------------" << endl;
    cout << header << endl;
    cout << "------------------------------" << endl;
}
Task* findTaskByID(int id, std::vector<shared_ptr<Task>>& tasks) {
    if (id >= 0) {
        for (auto iter = tasks.begin(); iter != tasks.end(); ++iter) {
            if (id = (*iter)->getID())
                return (*iter).get();
        }
    }
    return nullptr;
}
bool deleteTaskByID(int id, std::vector<shared_ptr<Task>>& tasks) {
    if (id >= 0) {
        for (auto iter = tasks.begin(); iter != tasks.end(); ++iter) {
            if (id == (*iter)->getID()) {
                iter = tasks.erase(iter);
                return true;
            }
        }
    }
    return false;
}

Task* UICreateNewTask() {
    string name, buffer;
    bool urgent, important;
  
    cin.ignore(32767, '\n');
    cout << "Введите название задачи: ";
    getline(cin, buffer);
    name = buffer;
    cout << "Укажите срочная ли задача: (0 - несрочная, 1 - срочная): ";
    getline(cin, buffer);
    if (!isNumberValid(buffer)) {
        cout << "Некорректное значение срочности задачи. " << endl;
        return nullptr;
    }
    urgent = stoi(buffer);
    cout << "Укажите важная ли задача: (0 - не важная, 1 - важная): ";
    getline(cin, buffer);
    if (!isNumberValid(buffer)) {
        cout << "Некорректное значение важности задачи. " << endl;
        return nullptr;
    }
    important = stoi(buffer);
    cout << "Введите крайний срок выполнения задачи в формате DD/MM/YYYY: ";
    getline(cin, buffer);
    if (!isDateValid(buffer)) {
        cout << "Некорректное значение срока выполнения. " << endl;
        return nullptr;
    }
    Date* due = new Date(stoi(buffer.substr(0, 2)), stoi(buffer.substr(3, 2)), stoi(buffer.substr(6, 4)));
    return new Task(name, urgent, important, due);
}

void printTask(Task* task) {
    if (task) {
        cout << task->getID() << " " << task->getName() << endl;
        cout << "Важная: ";
        if (task->getImportant())
            cout << "+ ";
        else
            cout << "- ";
        cout << "Срочная: ";
        if (task->getUrgent())
            cout << "+ ";
        else
            cout << "- ";
        cout << endl;
        cout << "Срок: " << (task->getDateString()) << endl;
    }
    else {
        cout << "Задача не существует. " << endl;
    }
}

std::vector<shared_ptr<Task>> loadFile() {
    std::vector<shared_ptr<Task>> tasks;
    ifstream in;
    string name, buffer;
    bool important, urgent;
    Date* date;
    Task* task;
    in.open("tasks.txt");
    if (in.is_open())
    {
        long file_size;
        in.seekg(0, ios::end);
        file_size = in.tellg();
        if (file_size == 0) {
            in.close();
            return tasks;
        }
        while (!in.eof()) {
            getline(in, name, '\t');
            getline(in, buffer, '\t');
            important = stoi(buffer);
            getline(in, buffer, '\t');
            urgent = stoi(buffer);
            getline(in, buffer, '\n');
            date = new Date(stoi(buffer.substr(0, 2)), stoi(buffer.substr(3, 2)), stoi(buffer.substr(6, 4)));
            task = new Task(name, urgent, important, date);
            task->setID(tasks.size());
            tasks.emplace_back(task);
        }
    }
    cout << "Загружено " << tasks.size() << " задач. ";
    in.close();
    return tasks;
}

void updateFile(std::vector<shared_ptr<Task>>& tasks) {
    ofstream out;
    out.open("tasks.txt", ios::trunc);
    for (auto iter = tasks.begin(); iter != tasks.end(); ++iter) {
        out << (*iter)->getName() << '\t' << (*iter)->getImportant() << '\t' << (*iter)->getUrgent() << '\t' << (*iter)->getDateString();
        if (next(iter) != tasks.end())
            out << endl;
    }
    out.close();
}

void savetoFile(Task* task) {
    ofstream out;
    out.open("tasks.txt", ios::app);
    out << endl << task->getName() << '\t' << task->getImportant() << '\t' << task->getUrgent() << '\t' << task->getDateString();
    out.close();
}
void clearFile() {
    ofstream out;
    out.open("tasks.txt", ios::trunc);
    out.close();
}
int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    std::vector<shared_ptr<Task>> tasks = loadFile();
    Task* task;
    Date* dateNow;
    bool result;
    int i;
    string buffer;
    struct tm newtime;
    __time64_t now;
    _time64(&now);
    localtime_s(&newtime, &now);
    dateNow = new Date(newtime.tm_mday, 1 + newtime.tm_mon, newtime.tm_year + 1900);
    Date* date;
    int selMenu = -1;
    while (selMenu != 0) {
        system("cls");
        printHeader("Менеджер задач");
        cout << "1. Добавить задачу" << endl; //+
        cout << "2. Показать все задачи" << endl; //+
        cout << "3. Сортировка задач по алфавиту" << endl; //+
        cout << "4. Сортировка задач по алфавиту в обратном порядке" << endl; //+
        cout << "5. Показать просроченные задачи" << endl;
        cout << "6. Показать непросроченные задачи" << endl;
        cout << "7. Удалить задачу по ID" << endl;
        cout << "8. Удалить просроченные задачи" << endl;
        cout << "9. Очистить файл" << endl;
        cout << "0. Выход" << endl;
        cin >> selMenu;
        system("cls");
        switch (selMenu)
        {
        case 1:
            printHeader("Добавление задачи");
            task = UICreateNewTask();
            if (task) {
                task->setID(tasks.size());
                savetoFile(task);
                tasks.emplace_back(task);
                cout << "Задача успешно добавлена" << endl;
            }
            break;
        case 2:
            if (!tasks.empty()) {
                cout << "Список задач: " << endl;
                for (auto iter = tasks.begin(); iter != tasks.end(); ++iter) {
                    printTask((*iter).get());
                }
            }
            else {
                cout << "Список задач пуст. ";
            }
            break;
        case 3:
            sort(tasks.begin(), tasks.end(), [](const shared_ptr<Task> a, const shared_ptr<Task> b) -> bool
                {
                    string name1 = a->getName();
                    string name2 = b->getName();
                    return (name1.compare(name2) < 0);
                });
            updateFile(tasks);
            cout << "Сортировка по имени по возрастанию выполнена. " << endl;
            break;
        case 4:
            sort(tasks.begin(), tasks.end(), [](const shared_ptr<Task> a, const shared_ptr<Task> b) -> bool
                {
                    string name1 = a->getName();
                    string name2 = b->getName();
                    return (name1.compare(name2) > 0);
                });
            cout << "Сортировка по имени по убыванию выполена. " << endl;
            updateFile(tasks);
            break;
        case 5:
            for (auto iter = tasks.begin(); iter != tasks.end(); ++iter) {
                if (*(*iter)->getDate() < *dateNow) {
                    printTask((*iter).get());
                }
            }
            break;
        case 6:
            for (auto iter = tasks.begin(); iter != tasks.end(); ++iter) {
                if (*(*iter)->getDate() > *dateNow) {
                    printTask((*iter).get());
                }
            }
            break;
        case 7:
            cout << "Введите ID задачи: ";
            cin.ignore(32767, '\n');
            getline(cin, buffer);
            if (isNumberValid(buffer)) {
                result = deleteTaskByID(stoi(buffer), tasks);
                if (result) {
                    i = 0;
                    cout << "Задача удалена. " << endl;
                    for (auto iter = tasks.begin(); iter != tasks.end(); ++iter) {
                        (*iter)->setID(i);
                        i++;
                    }
                }
                else {
                    cout << "Задача не найдена. " << endl;
                }
            }
            else {
                cout << "Неверно введен ID. ";
            }
            updateFile(tasks);
            break;
        case 8:
            for (auto iter = tasks.begin(); iter != tasks.end();) {
                task = (*iter).get();
                if (*(*iter)->getDate() < *dateNow) {
                    iter = tasks.erase(iter);
                }
                else ++iter;
            }
            i = 0;
            for (auto iter = tasks.begin(); iter != tasks.end(); ++iter) {
                (*iter)->setID(i);
                i++;
            }
            cout << "Просроченные задачи удалены. " << endl;
            updateFile(tasks);
            break;
        case 9:
            clearFile();
            tasks.clear();
            cout << "Файл очищен" << endl;
            break;
        case 0:

            break;
        default:
            selMenu = -1;
            break;
        }
        if (selMenu != 0)
        UIWait();
    }
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
