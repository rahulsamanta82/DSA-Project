#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <limits>
#include <thread>
#include <chrono>


using namespace std;
void showWelcomeScreen()
{
    system("cls");

    string welcome = "WELCOME TO STUDENT MANAGEMENT SYSTEM";
    cout << "\n\n\n";
    cout << "\t\t";
    for (char c : welcome)
    {
        cout << c;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(30));
    }

    cout << "\n\n\t\t";
    cout << "\033[33m";
    for (int i = 0; i < 3; i++)
    {
        cout << "Loading";
        for (int j = 0; j < 3; j++)
        {
            this_thread::sleep_for(chrono::milliseconds(90));
            cout << ".";
            cout.flush();
        }

        if (i < 2)
        {
            cout << "\r\t\t         ";
            cout << "\r\t\t";
            cout.flush();
        }
    }
    cout << "\033[0m";

    cout << "\n\n\t\t";
    cout << "\033[32m[";
    for (int i = 0; i < 30; i++)
    {
        cout << "=";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(30));
    }
    cout << "] 100%\033[0m";

    this_thread::sleep_for(chrono::milliseconds(500));
    system("cls");
}

void showendingScreen()
{
    system("cls");

   
    cout << "\n\n\t\t";
    cout << "\033[33m";
    for (int i = 0; i < 3; i++)
    {
        cout << "Shutdown";
        for (int j = 0; j < 3; j++)
        {
            this_thread::sleep_for(chrono::milliseconds(90));
            cout << ".";
            cout.flush();
        }

        if (i < 2)
        {
            cout << "\r\t\t         ";
            cout << "\r\t\t";
            cout.flush();
        }
    }

    system("cls");
}

class Student
{
public:
    int id;
    string name;
    int semester;
    float cgpa;
    Student *next;

    Student(int id, string name, int semseter, float cgpa)
    {
        this->id = id;
        this->name = name;
        this->semester = semseter;
        this->cgpa = cgpa;
        next = nullptr;
    }
};

class Studentlist
{
public:
    Student *head;
    int count;
    Studentlist()
    {
        head = nullptr;
        count = 1;
    }
    void showLoading()
    {
        cout << "\n\033[33mSearching";
        for (int i = 0; i < 3; i++)
        {
            this_thread::sleep_for(chrono::milliseconds(300));
            cout << ".";
            cout.flush();
        }
        cout << "\033[0m" << endl;
        this_thread::sleep_for(chrono::milliseconds(200));
    }

    void add_student(int id, string name, int semseter, float cgpa)
    {
        Student *new_student = new Student(id, name, semseter, cgpa);
        if (head == nullptr)
        {
            head = new_student;
        }
        else
        {
            Student *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = new_student;
            cout << "\033[32mStudent Recode Add Successfully!\033[0m" << endl;
            count++;
        }
    }

    void display_all_student()
    {
        system("cls");
        if (head == nullptr)
        {
            cout << "\033[31mNo Recode Found!\033[0m" << endl;
            return;
        }
        cout << "\n+-------------------------------------------+\n";
        cout << "|            Total Student: " << count << "                    |\n";
        cout << "+-------------------------------------------+\n";
        cout << endl;

        Student *temp = head;
        cout << "\n+-------------------------------------------+\n";
        cout << "|            STUDENT Details            |\n";
        cout << "+-------------------------------------------+\n";
        while (temp != nullptr)
        {

            cout << "  ID       : " << temp->id << endl;
            cout << "  Name     : " << temp->name << endl;
            cout << "  Semester : " << temp->semester << endl;
            cout << "  CGPA     : " << temp->cgpa << endl;
            temp = temp->next;
            cout << endl
                 << endl;
        }
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
        system("cls");
    }

    void search_student(int id)
    {

        if (head == nullptr)
        {
            cout << "\033[31mNo Recode Found!\033[0m" << endl;
            cout << "\033[31mNo Record Found!\033[0m" << endl;
            cout << "\nPress Enter to continue...";
            cin.get();
            system("cls");
            return;
        }
        Student *temp = head;
        system("cls");
        showLoading();
        system("cls");
        bool found = false;
        while (temp != nullptr)
        {
            if (temp->id == id)
            {
                cout << "\n+-------------------------------------------+\n";
                cout << "|            STUDENT FOUND                  |\n";
                cout << "+-------------------------------------------+\n";
                cout << "  ID       : " << temp->id << endl;
                cout << "  Name     : " << temp->name << endl;
                cout << "  Semester : " << temp->semester << endl;
                cout << "  CGPA     : " << temp->cgpa << endl;
                found = true;
                cout << "\nPress Enter to continue...";
                cin.get();
                system("cls");
                return;
            }
            temp = temp->next;
        }

        if (!found)
        {
            cout << "\033[31mStudent not found!\033[0m" << endl;
            cout << "\nPress Enter to continue...";
            cin.get();
            system("cls");
        }
    }

    void delete_recode(int id)
    {
        system("cls");
        if (head == nullptr)
        {
            cout << "\033[31mNo Recode Found!\033[0m" << endl;
            cout << "\033[31mNo Record Found!\033[0m" << endl;
            cout << "\nPress Enter to continue...";
            cin.get();
            system("cls");
            return;
            return;
        }
        Student *temp = head;
        Student *prev = NULL;
        if (temp != NULL && temp->id == id)
        {
            head = temp->next;
            delete temp;

            cout << "\033[32mStudent record deleted successfully!\033[0m" << endl;
            count--;
            return;
        }
        while (temp != NULL && temp->id != id)
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
        {
            cout << "\033[31mStudent Recode not found!\033[0m" << endl;
            return;
        }

        prev->next = temp->next;
        delete temp;
        cout << "\033[32mStudent record deleted successfully\033[0m" << endl;

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
        system("cls");
    }

    void showMenu()
    {

        cout << "\n+===========================================+\n";
        cout << "|   STUDENT RECORD MANAGEMENT SYSTEM        |\n";
        cout << "+===========================================+\n";
        cout << "|  1. Add New Student                       |\n";
        cout << "|  2. Display All Students                  |\n";
        cout << "|  3. Search Student by ID                  |\n";
        cout << "|  4. Delete Student Record                 |\n";
        cout << "|  5. Exit                                  |\n";
        cout << "+===========================================+\n";
        cout << "Enter your choice: ";
    }
};

class Main
{
public:
    Studentlist list;
    void start()
    {
        int choice;
        do
        {
            list.showMenu();
            cin >> choice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\033[31mInvalid input! Please enter a number.\033[0m\n\n";
                continue;
            }
            switch (choice)
            {
            case 1:
            {
                string *name = new string;
                int *id = new int;
                int *semester = new int;
                float *cgpa = new float;
                char choice;
                system("cls");
                do
                {

                    cout << "\n+-------------------------------------------+\n";
                    cout << "|           ADD NEW STUDENT RECORD           |\n";
                    cout << "+-------------------------------------------+\n";
                    cout << "Enter student id: ";
                    cin >> *id;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Enter student name: ";
                    getline(cin, *name);

                    cout << "Enter Student Semester: ";
                    cin >> *semester;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Enter student CGPA: ";
                    cin >> *cgpa;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    list.add_student(*id, *name, *semester, *cgpa);
                    cout << "\n Press q/Q to exit(other wise Press Y to enter data): ";
                    cin >> choice;

                } while (choice != 'q' && choice != 'Q');
                system("cls");

                delete id;
                delete name;
                delete semester;
                delete cgpa;
                break;
            }

            case 2:
            {
                list.display_all_student();
                break;
            }
            case 3:
            {
                system("cls");
                int *id = new int;
                cout << "\n+-------------------------------------------+\n";
                cout << "|              SEARCH STUDENT BY ID           |\n";
                cout << "+-------------------------------------------+\n";
                cout << "Enter student id: ";
                cin >> *id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                list.search_student(*id);
                delete id;
                break;
            }
            case 4:
            {
                system("cls");
                int *id = new int;
                cout << "\n+-----------------------------------------------+\n";
                cout << "|           Delete STUDENT Recode BY ID           |\n";
                cout << "+-------------------------------------------------+\n";
                cout << "Enter student id: ";
                cin >> *id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                list.delete_recode(*id);
                delete id;
                break;
            }
            case 5:
            {
                showendingScreen();
                break;
            }
            }

        } while (choice != 5);
    }
};

int main()
{
    showWelcomeScreen();
    Main app;
    app.start();
}