#include "TeacherManagementSystem.h"
#include <iostream>
#include <string>

using namespace std;

const int DEP_SIZE = 5;
const int DAYS = 5;
const int TS_SIZE = 3;

const char *departments[DEP_SIZE] = {"Engineering", "Medical", "Business", "Art", "Sports"};
const char *days[DAYS] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
const char *time_slots[TS_SIZE] = {"8:30 AM - 11:15 AM", "11:30 AM - 2:15 PM", "3:30 PM - 6:15 PM"};

// menus
void OpenGuestMenu(TeacherManagementSystem &tms);
void OpenTeacherSelectMenu(TeacherManagementSystem &tms);
void OpenSelectedTeacherMenu(TeacherManagementSystem &tms, int choice);

void OpenAdminMenu(TeacherManagementSystem &tms);
void CreateTeacherForm(TeacherManagementSystem &tms);
void DeleteTeacherForm(TeacherManagementSystem &tms);
void UpdateTeacherForm(TeacherManagementSystem &tms);
void ViewTeacherForm(TeacherManagementSystem &tms);
void OpenUpdateScheduleForm(TeacherManagementSystem &tms, TeacherManagementSystem::Teacher *teacher);
string UpdateDepartmentForm();
void ShowDepartments();

// program start

void start();
void login(int &attempts);

// main

int main()
{
    TeacherManagementSystem tms;
    start();

    return 0;
}

void start()
{
    TeacherManagementSystem tms;
    tms.loadTeachersFromFile("teachers.txt");

    int choice;

    cout << "Welcome to the Teacher Management System" << endl;
    LineBreaker();
    do
    {
        do
        {
            cout << "1 - Login as admin\n2 - Continue as guest\n3 - Exit\nEnter your choice ( 1 - 3 ): ";
            cin >> choice;
            if (choice == 3)
            {
                tms.saveTeachersToFile("teachers.txt");
                return;
            }
            if (choice != 1 && choice != 2)
            {
                cout << "Invalid Choice" << endl;
            }
            LineBreaker();

        } while (choice != 1 && choice != 2 && choice != 3);

        if (choice == 1)
        {
            int attempts = 4;
            login(attempts);

            if (attempts == 0)
            {
                cout << "No more attempts left. Closing the application." << endl;
                return;
            }
            cout << "Logged in successfully. Loading Admin menu..." << endl;
            LineBreaker();

            OpenAdminMenu(tms);
        }
        else if (choice == 2)
        {
            cout << "Continuing as guest..." << endl;
            LineBreaker();
            OpenGuestMenu(tms);
        }
        else
        {
            tms.saveTeachersToFile("teachers.txt");
            return; // unreachable , returns in the inner do while. this is just here for fun
        }

    } while (choice != 3);
}

void login(int &attempts)
{
    cout << "Log in as Admin " << endl;
    const string admin_username = "admin";
    const string admin_password = "password";

    string username, password;

    while (attempts > 0)
    {
        cout << "Enter your username: ";
        cin >> username;
        LineBreaker();
        cout << "Enter your password: ";
        cin >> password;

        if (username == admin_username && password == admin_password)
        {
            cout << "Login successful." << endl;
            return; // Exit on successful login
        }
        else
        {
            attempts--;
            cout << "Wrong credentials, " << attempts << " attempts left." << endl;
            LineBreaker();
        }
    }
}

void OpenGuestMenu(TeacherManagementSystem &tms)
{
    cout << "Welcome guest ! Please pick one of the options below !" << endl;
    LineBreaker();

    int choice;
    do
    {
        cout << "1-Display all teachers\n2-Select a teacher\n3-go back" << endl;
        do
        {
            cout << "Enter your choice ( 1 to 3 ) : " << endl;
            cin >> choice;

            if (choice > 3 && choice < 1)
                cout << "Invalid Choice. Try again" << endl;

            LineBreaker();

        } while (choice > 3 && choice < 1);

        if (choice == 1)
        {
            tms.displayAllTeachers();
        }
        else if (choice == 2)
        {
            OpenTeacherSelectMenu(tms);
        }
        else
        {
            return;
        }
    } while (choice != 3);
}

void OpenTeacherSelectMenu(TeacherManagementSystem &tms)
{
    tms.displayAllTeachersNames();
    int size = tms.size();
    int choice;
    cout << size + 1 << " - Go Back" << endl;
    do
    {
        cout << "Enter your choice ( 1 - " << size << " ) : " << endl;
        cin >> choice;
        if (choice == size + 1)
            return;
        if (choice > size || choice < 1)
        {
            cout << "Invalid Choice ! try again";
        }
        LineBreaker();
    } while (choice > size || choice < 1);
    OpenSelectedTeacherMenu(tms, choice);
}

void OpenSelectedTeacherMenu(TeacherManagementSystem &tms, int choice)
{
    int inner_choice;
    do
    {
        TeacherManagementSystem::Teacher *selectedTeacher = tms.findTeacherByIndex(choice - 1);
        cout << "the selected teacher is " << selectedTeacher->name << endl;
        cout << "\n1-View Information\n2-View Schedule\n3-View Feedbacks\n4-Add Feedback\n5-Go Back" << endl;

        do
        {
            cout << "Enter your choice ( 1 - 4 ) : " << endl;
            cin >> inner_choice;
            if (inner_choice == 5)
                return;
            if (inner_choice > 5 || inner_choice < 1)
                cout << "Invalid Choice ! try again";
            /* code */
        } while (inner_choice > 5 || inner_choice < 1);

        if (inner_choice == 1)
        {
            tms.displayTeacher(selectedTeacher->teacherId);
            LineBreaker();
        }
        else if (inner_choice == 2)
        {
            tms.displayTeacherSchedule(selectedTeacher->teacherId);
            LineBreaker();
        }

        else if (inner_choice == 3)
        {
            tms.displayTeacherFeedback(selectedTeacher->teacherId);
            LineBreaker();
        }
        else if (inner_choice == 4)
        {
            string feedback;
            do
            {
                cout << "Enter your feedback: " << endl;
                cin.ignore();           // Clear the newline character from the input buffer
                getline(cin, feedback); // Use getline to allow multi-word input
                if (feedback.empty())
                    cout << "Invalid feedback" << endl;
            } while (feedback.empty());
            LineBreaker();
            tms.addFeedback(selectedTeacher->teacherId, feedback);
        }

    } while (inner_choice != 5);
}

void OpenAdminMenu(TeacherManagementSystem &tms)
{
    int choice;
    cout << "Welcome to the Admin Menu" << endl;
    LineBreaker();

    do
    {
        cout << "1-Create teacher\n2-Delete Teacher\n3-Update Teacher\n4-View Teacher\n5-Go Back" << endl;

        do
        {
            cout << "Enter your choice ( 1 - 5 ) : " << endl;
            cin >> choice;
            if (choice < 1 || choice > 5)
            {
                cout << "Invalid Choice." << endl;
            }
            LineBreaker();
        } while (choice < 1 || choice > 5);

        switch (choice)
        {
        case 1:
            CreateTeacherForm(tms);
            break;
        case 2:
            DeleteTeacherForm(tms);
            break;
        case 3:
            UpdateTeacherForm(tms);
            break;
        case 4:
            ViewTeacherForm(tms);
            break;
        case 5:
            return;
            break;
        default:
            return;
            break;
        }

        /* code */
    } while (choice != 5);
}

void CreateTeacherForm(TeacherManagementSystem &tms)
{
    cout << "Create a new teacher :\n";
    LineBreaker();

    string name, dept;
    int age;

    do
    {
        cout << "Enter teacher name : " << endl;
        cin >> name;

        if (name == "")
            cout << "Invalid name" << endl;
    } while (name == "");

    LineBreaker();
    do
    {
        cout << "Enter teacher age : " << endl;
        cin >> age;

        if (age <= 0)
            cout << "Invalid age" << endl;
    } while (age <= 0);

    LineBreaker();

    int department_choice;
    do
    {
        cout << "Select department : " << endl;
        ShowDepartments();
        cout << "Enter your choice ( 1 - " << DEP_SIZE << " ) : " << endl;
        cin >> department_choice;
        if (department_choice < 0 || department_choice > DEP_SIZE)
        {
            cout << "Invalid choice." << endl;
        }

    } while (department_choice < 0 || department_choice > DEP_SIZE);
    dept = departments[department_choice - 1];
    LineBreaker();
    tms.insertTeacher(name, age, dept);
}

void ShowDepartments()
{
    for (int i = 0; i < DEP_SIZE; i++)
    {
        cout << i + 1 << " - " << departments[i] << endl;
    }
}

void DeleteTeacherForm(TeacherManagementSystem &tms)
{
    cout << "Select a teacher to delete : " << endl;
    int choice;
    do
    {
        tms.displayAllTeachersNames();
        cout << "Enter your choice ( 1 - " << tms.size() << " ) : " << endl;
        cin >> choice;

        if (choice <= 0 && choice > tms.size())
            cout << "Invalid Choice" << endl;
    } while (choice <= 0 && choice > tms.size());
    TeacherManagementSystem::Teacher *teacher_to_delete = tms.findTeacherByIndex(choice - 1);
    tms.removeTeacherById(teacher_to_delete->teacherId);
    LineBreaker();
}

void UpdateTeacherForm(TeacherManagementSystem &tms)
{
    cout << "Select a teacher to update : " << endl;
    int choice;
    do
    {
        tms.displayAllTeachersNames();
        cout << "Enter your choice ( 1 - " << tms.size() << " ) : " << endl;
        cin >> choice;

        if (choice <= 0 || choice > tms.size())
            cout << "Invalid Choice" << endl;
    } while (choice <= 0 || choice > tms.size());
    TeacherManagementSystem::Teacher *teacher_to_update = tms.findTeacherByIndex(choice - 1);

    // Initialize variables with current teacher info
    string name = teacher_to_update->name;
    string department = teacher_to_update->dept;
    int age = teacher_to_update->age;

    cout << "You are updating the teacher: " << teacher_to_update->name << " with ID: " << teacher_to_update->teacherId << endl;
    LineBreaker();
    int inner_choice;

    do
    {
        cout << "Select what you want to update or press 4 to go back: " << endl;
        cout << "1 - Update name (" << teacher_to_update->name << ")\n"
             << "2 - Update age (" << teacher_to_update->age << ")\n"
             << "3 - Update Department (" << teacher_to_update->dept << ")\n"
             << "4 - Update Schedule\n"
             << "5 - Save and Go Back" << endl;

        do
        {
            cout << "Enter your choice (1 - 5): " << endl;
            cin >> inner_choice;

            if (inner_choice > 4 || inner_choice < 1)
                cout << "Invalid Choice." << endl;
        } while (inner_choice < 1 || inner_choice > 5);

        LineBreaker();

        if (inner_choice == 1)
        {
            string new_name;
            do
            {
                cout << "Enter new teacher name: " << endl;
                cin >> new_name;

                if (new_name == "")
                    cout << "Invalid name" << endl;
            } while (new_name == "");
            name = new_name;
            tms.updateTeacherInfo(teacher_to_update->teacherId, name, age, department);
        }
        else if (inner_choice == 2)
        {
            int new_age;
            do
            {
                cout << "Enter new teacher age: " << endl;
                cin >> new_age;

                if (new_age <= 0)
                    cout << "Invalid age" << endl;
            } while (new_age <= 0);
            age = new_age;
            tms.updateTeacherInfo(teacher_to_update->teacherId, name, age, department);
        }
        else if (inner_choice == 3)
        {
            string new_department = UpdateDepartmentForm();
            if (new_department != "")
                department = new_department;
            tms.updateTeacherInfo(teacher_to_update->teacherId, name, age, department);
        }
        else if (inner_choice == 4)
        {
            OpenUpdateScheduleForm(tms, teacher_to_update);
        }
        else
        {
            // Save and exit (this will ensure that any accumulated changes are saved)
            tms.updateTeacherInfo(teacher_to_update->teacherId, name, age, department);
            return;
        }

    } while (inner_choice != 4);
}

string UpdateDepartmentForm()
{
    string new_department;
    for (int i = 0; i < DEP_SIZE; i++)
    {
        cout << i + 1 << " - " << departments[i] << endl;
    }
    cout << DEP_SIZE + 1 << " - Cancel" << endl;
    int choice;
    do
    {
        cout << "Enter your choice ( 1 - " << DEP_SIZE + 1 << " ) : " << endl;
        cin >> choice;
        if (choice == DEP_SIZE + 1)
            return "";

        if (choice < 1 || choice > DEP_SIZE + 1)
            cout << "Invalid Choice." << endl;
    } while (choice < 1 || choice > DEP_SIZE + 1);
    LineBreaker();
    return departments[choice - 1];
}

void OpenUpdateScheduleForm(TeacherManagementSystem &tms, TeacherManagementSystem::Teacher *teacher)
{
    if (teacher->scheduleTop == nullptr)
    {
        cout << "No Current Schedule" << endl;
        return;
    }
    else
    {
        tms.displayTeacherSchedule(teacher->teacherId);
    }

    int size = tms.getTeacherScheduleSize(teacher->teacherId);
    int choice;
    do
    {
        cout << "Enter which schedule you want to update (1 - " << size << "): ";
        cin >> choice;
    } while (choice < 1 || choice > size);
    LineBreaker();

    TeacherManagementSystem::Schedule *scheduleToUpdate = tms.findScheduleByIndex(teacher->teacherId, choice - 1);
    string newTimeSlot = scheduleToUpdate->timeSlot;
    string newDay = scheduleToUpdate->day;
    string newCourse = scheduleToUpdate->course;

    int inner_choice;
    do
    {
        cout << "Select what you want to update:\n"
             << "1 - Time slot (" << scheduleToUpdate->timeSlot << ")\n"
             << "2 - Day (" << scheduleToUpdate->day << ")\n"
             << "3 - Course (" << scheduleToUpdate->course << ")\n"
             << "4 - Save and go back" << endl;

        do
        {
            cout << "Enter your choice (1 - 4): ";
            cin >> inner_choice;
        } while (inner_choice < 1 || inner_choice > 4);

        LineBreaker();

        if (inner_choice == 1)
        {
            int timeSlotChoice;
            cout << "Select new time slot: " << endl;
            for (int i = 0; i < TS_SIZE; i++)
            {
                cout << i + 1 << " - " << time_slots[i] << endl;
            }
            do
            {
                cout << "Enter your choice (1 - " << TS_SIZE << "): ";
                cin >> timeSlotChoice;
            } while (timeSlotChoice < 1 || timeSlotChoice > TS_SIZE);
            newTimeSlot = time_slots[timeSlotChoice - 1];
            tms.updateTeacherSchedule(teacher->teacherId, scheduleToUpdate->timeSlot, scheduleToUpdate->day, scheduleToUpdate->course, newTimeSlot, newDay, newCourse);
        }
        else if (inner_choice == 2)
        {
            int dayChoice;
            cout << "Select new day: " << endl;
            for (int i = 0; i < DAYS; i++)
            {
                cout << i + 1 << " - " << days[i] << endl;
            }
            do
            {
                cout << "Enter your choice (1 - " << DAYS << "): ";
                cin >> dayChoice;
            } while (dayChoice < 1 || dayChoice > DAYS);
            newDay = days[dayChoice - 1];
            tms.updateTeacherSchedule(teacher->teacherId, scheduleToUpdate->timeSlot, scheduleToUpdate->day, scheduleToUpdate->course, newTimeSlot, newDay, newCourse);
        }
        else if (inner_choice == 3)
        {
            cout << "Enter new course: ";
            cin.ignore();
            getline(cin, newCourse);
            tms.updateTeacherSchedule(teacher->teacherId, scheduleToUpdate->timeSlot, scheduleToUpdate->day, scheduleToUpdate->course, newTimeSlot, newDay, newCourse);
        }

    } while (inner_choice != 4);
}

void ViewTeacherForm(TeacherManagementSystem &tms)
{
    cout << "Select a teacher to view : " << endl;
    int view_choice;
    do
    {
        tms.displayAllTeachersNames();
        cout << "Enter your choice ( 1 - " << tms.size() << " ) : " << endl;
        cin >> view_choice;

        if (view_choice <= 0 || view_choice > tms.size())
            cout << "Invalid Choice" << endl;
    } while (view_choice <= 0 || view_choice > tms.size());
    TeacherManagementSystem::Teacher *teacher_to_view = tms.findTeacherByIndex(view_choice - 1);
    tms.displayTeacher(teacher_to_view->teacherId);
    LineBreaker();
}