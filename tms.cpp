#include "TeacherManagementSystem.h"

#include <sstream>
#include <fstream>

// class definition

TeacherManagementSystem::TeacherManagementSystem() : first(nullptr), last(nullptr), teacherCount(0) {}

string TeacherManagementSystem::generateTeacherId(string name)
{
    return name + (teacherCount < 10 ? "000" : teacherCount < 100 ? "00"
                                           : teacherCount < 1000  ? "0"
                                                                  : "") +
           to_string(teacherCount);
}

void TeacherManagementSystem::insertFirst(string name, int age, string dept)
{
    Teacher *newNode = new Teacher(name, age, dept, generateTeacherId(name));
    if (!first)
    {
        first = last = newNode;
    }
    else
    {
        newNode->next = first;
        first = newNode;
    }
    teacherCount++;
}

void TeacherManagementSystem::insertTeacher(string name, int age, string dept)
{
    Teacher *newNode = new Teacher(name, age, dept, generateTeacherId(name));
    if (!first)
    {
        first = last = newNode;
    }
    else
    {
        last->next = newNode;
        last = newNode;
    }
    teacherCount++;
    cout << "Inserted Teacher: " << name << " with ID: " << newNode->teacherId << ", Age: " << newNode->age << ", Department: " << newNode->dept << endl;
}

void TeacherManagementSystem::removeFirst()
{
    if (!first)
    {
        cout << "Empty List!" << endl;
        return;
    }
    Teacher *temp = first;
    first = first->next;
    delete temp;
    teacherCount--;
}

void TeacherManagementSystem::removeLast()
{
    if (!first)
    {
        cout << "Empty List!" << endl;
        return;
    }
    if (first == last)
    {
        delete first;
        first = last = nullptr;
    }
    else
    {
        Teacher *prev = nullptr;
        Teacher *cur = first;
        while (cur->next)
        {
            prev = cur;
            cur = cur->next;
        }
        prev->next = nullptr;
        last = prev;
        delete cur;
    }
    teacherCount--;
}

void TeacherManagementSystem::removeTeacherById(string id)
{
    Teacher *cur = first, *prev = nullptr;
    while (cur)
    {
        if (cur->teacherId == id)
        {
            if (!prev)
                first = cur->next;
            else
                prev->next = cur->next;

            if (cur == last)
                last = prev;

            delete cur;
            teacherCount--;
            cout << "Teacher with ID " << id << " removed." << endl;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    cout << "Teacher with ID " << id << " not found!" << endl;
}

void TeacherManagementSystem::assignSchedule(string id, string timeSlot, string course, string day)
{
    Teacher *cur = first;
    while (cur)
    {
        if (cur->teacherId == id)
        {
            Schedule *newSchedule = new Schedule(timeSlot, course, day);
            newSchedule->next = cur->scheduleTop;
            cur->scheduleTop = newSchedule;
            cout << "Assigned schedule to " << cur->name << ": " << day << " at " << timeSlot << " for " << course << endl;
            return;
        }
        cur = cur->next;
    }
    cout << "Teacher not found!" << endl;
}

void TeacherManagementSystem::addFeedback(string id, string message)
{
    Teacher *cur = first;
    while (cur)
    {
        if (cur->teacherId == id)
        {
            Feedback *newFeedback = new Feedback(message);
            newFeedback->next = cur->feedBackTop;
            cur->feedBackTop = newFeedback;
            cout << "Added feedback for " << cur->name << ": " << message << endl;
            return;
        }
        cur = cur->next;
    }
    cout << "Teacher not found!" << endl;
}

void TeacherManagementSystem::removeSchedule(string id, string day, string timeSlot)
{
    Teacher *cur = first;
    while (cur)
    {
        if (cur->teacherId == id)
        {
            Schedule *curSchedule = cur->scheduleTop, *prev = nullptr;
            while (curSchedule)
            {
                if (curSchedule->day == day && curSchedule->timeSlot == timeSlot)
                {
                    if (!prev)
                        cur->scheduleTop = curSchedule->next;
                    else
                        prev->next = curSchedule->next;

                    delete curSchedule;
                    cout << "Schedule deleted" << endl;
                    return;
                }
                prev = curSchedule;
                curSchedule = curSchedule->next;
            }
            cout << "No matching schedule found for Teacher with ID " << id << endl;
            return;
        }
        cur = cur->next;
    }
    cout << "Teacher not found!" << endl;
}

void TeacherManagementSystem::removeFeedback(string id, string message)
{
    Teacher *cur = first;
    while (cur)
    {
        if (cur->teacherId == id)
        {
            Feedback *curFeedback = cur->feedBackTop, *prev = nullptr;
            while (curFeedback)
            {
                if (curFeedback->message == message)
                {
                    if (!prev)
                        cur->feedBackTop = curFeedback->next;
                    else
                        prev->next = curFeedback->next;

                    delete curFeedback;
                    cout << "Feedback deleted" << endl;
                    return;
                }
                prev = curFeedback;
                curFeedback = curFeedback->next;
            }
            cout << "No matching feedback found for Teacher with ID " << id << endl;
            return;
        }
        cur = cur->next;
    }
    cout << "Teacher not found!" << endl;
}

void TeacherManagementSystem::updateTeacherInfo(string id, string newName, int newAge, string newDept)
{
    Teacher *cur = first;
    while (cur)
    {
        if (cur->teacherId == id)
        {
            cout << "_Teacher " << cur->name << " with updated info: ";
            cur->name = newName;
            cur->age = newAge;
            cur->dept = newDept;
            cur->teacherId = newName + (teacherCount < 10 ? "000" : teacherCount < 100 ? "00"
                                                                : teacherCount < 1000  ? "0"
                                                                                       : " ") +
                             to_string(teacherCount);
            cout << newName << " " << newAge << " " << newDept << " " << cur->teacherId << endl;
            return;
        }
        cur = cur->next;
    }
    cout << "_Teacher not found" << endl;
}

void TeacherManagementSystem::updateTeacherSchedule(string id, string timeSlot, string day, string course, string newTimeSlot, string newDay, string newCourse)
{
    Teacher *cur = first;
    while (cur)
    {
        if (cur->teacherId == id)
        {
            // Check if the new time slot is already taken
            ActionResult ar = checkIfTimeSlotIsTaken(id, newTimeSlot, newDay);
            if (ar.message == "teacher_exists" && ar.response == true) // If the time slot is taken
            {
                cout << "_New time slot " << newTimeSlot << " on " << newDay << " is already occupied. Update failed!" << endl;
                return;
            }

            Schedule *curSchedule = cur->scheduleTop;
            while (curSchedule)
            {
                if (curSchedule->timeSlot == timeSlot && curSchedule->day == day && curSchedule->course == course)
                {
                    cout << "_New Schedule for teacher " << cur->name;
                    curSchedule->timeSlot = newTimeSlot;
                    curSchedule->day = newDay;
                    curSchedule->course = newCourse;
                    cout << ": " << newDay << " at " << newTimeSlot << " for " << newCourse << endl;
                    return;
                }
                curSchedule = curSchedule->next;
            }
            cout << "_This schedule not found for " << cur->name << endl;
            return;
        }
        cur = cur->next;
    }
    cout << "_Teacher not found" << endl;
}

void TeacherManagementSystem::updateTeacherFeedback(string id, string message, string newMessage)
{
    Teacher *cur = first;
    while (cur)
    {
        if (cur->teacherId == id)
        {
            Feedback *curFeedback = cur->feedBackTop;
            while (curFeedback)
            {
                if (curFeedback->message == message)
                {
                    cout << "_New Feedback for teacher " << cur->name;
                    curFeedback->message = newMessage;

                    cout << ": " << newMessage << endl;
                    return;
                }
                curFeedback = curFeedback->next;
            }
            cout << "_This Feedback not found for " << cur->name << endl;
            return;
        }
        cur = cur->next;
    }
    cout << "_Teacher not found" << endl;
}

void TeacherManagementSystem::displayTeacherSchedule(string id)
{
    if (first == NULL)
    {
        cout << "Empty List!";
    }
    else
    {

        Teacher *cur = first;

        while (cur)
        {

            if (cur->teacherId == id)
            {
                if (cur->scheduleTop == NULL)
                {
                    cout << "No Schedule found!";
                }
                else
                {
                    cout << "The schedule for teacher " << cur->name << " is : " << endl;
                    Schedule *curSchedule = cur->scheduleTop;
                    int counter = 0;
                    while (curSchedule)
                    {
                        cout << "\t" << "\t" << "\t" << counter + 1 << " - " << curSchedule->timeSlot << " " << curSchedule->day << " " << curSchedule->course << endl;
                        curSchedule = curSchedule->next;
                        counter++;
                    }
                }
                return;
            }
            cur = cur->next;
        }
    }
}

void TeacherManagementSystem::displayTeacherFeedback(string id)
{
    if (first == NULL)
    {
        cout << "Empty List!";
    }
    else
    {
        Teacher *cur = first;
        while (cur)
        {
            if (cur->teacherId == id)
            {
                if (cur->scheduleTop == NULL)
                {
                    cout << "No Feedback found!";
                }
                else
                {
                    cout << "Full Feedback of " << cur->name << ": " << endl;
                    Feedback *curFeedback = cur->feedBackTop;
                    while (curFeedback)
                    {
                        cout << "\t" << "\t" << "\t" << "_" << curFeedback->message << " " << endl;

                        curFeedback = curFeedback->next;
                    }
                }
                return;
            }
            cur = cur->next;
        }
    }
}

void TeacherManagementSystem::getFirst()
{
    if (first == NULL)
    {
        cout << "Empty List!";
    }
    else
    {
        cout << first->name << " " << first->age << " " << first->dept << " " << first->teacherId << endl;
    }
}

void TeacherManagementSystem::getLast()
{
    if (first == NULL)
    {
        cout << "Empty List!";
    }
    else
    {
        cout << last->name << " " << last->age << " " << last->dept << " " << last->teacherId << endl;
    }
}

TeacherManagementSystem::Teacher *TeacherManagementSystem::findTeacherById(const string &id)
{
    Teacher *cur = first;
    while (cur)
    {
        if (cur->teacherId == id)
        {
            return cur;
        }
        cur = cur->next;
    }
    return nullptr;
}

bool TeacherManagementSystem::checkIfIdExists(string id)
{
    Teacher *cur = first;
    while (cur)
    {
        if (cur->teacherId == id)
        {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

ActionResult TeacherManagementSystem::checkIfTimeSlotIsTaken(string id, string timeSlot, string day)
{
    Teacher *teacher = findTeacherById(id);
    if (teacher == nullptr)
    {
        ActionResult ar("!teacher_exists", false);
        return ar;
    }
    else
    {
        Schedule *cur = teacher->scheduleTop;
        while (cur)
        {
            if (cur->timeSlot == timeSlot && cur->day == day)
            {
                ActionResult ar("teacher_exists", true);
                return ar;
            }
            cur = cur->next;
        }
        ActionResult ar("teacher_exists", false);
        return ar;
    }
}
TeacherManagementSystem::Schedule *TeacherManagementSystem::findScheduleByIndex(string teacherId, int index)
{
    if (first == NULL)
    {
        cout << "Teacher list is empty!" << endl;
        return nullptr;
    }

    // Find the teacher by ID
    Teacher *curTeacher = first;
    while (curTeacher)
    {
        if (curTeacher->teacherId == teacherId)
        {
            // Check if the schedule list is empty
            if (curTeacher->scheduleTop == NULL)
            {
                cout << "No schedule found for this teacher!" << endl;
                return nullptr;
            }

            // Find the schedule at the given index
            Schedule *curSchedule = curTeacher->scheduleTop;
            int counter = 0;
            while (curSchedule)
            {
                if (counter == index)
                {
                    // Schedule found at the desired index
                    return curSchedule;
                }
                curSchedule = curSchedule->next;
                counter++;
            }

            // Index out of range
            cout << "Schedule index out of range!" << endl;
            return nullptr;
        }
        curTeacher = curTeacher->next;
    }

    // Teacher not found
    cout << "Teacher with ID " << teacherId << " not found!" << endl;
    return nullptr;
}
int TeacherManagementSystem::getTeacherScheduleSize(string teacherId)
{
    if (first == NULL)
    {
        cout << "Teacher list is empty!" << endl;
        return 0;
    }

    // Find the teacher by ID
    Teacher *curTeacher = first;
    while (curTeacher)
    {
        if (curTeacher->teacherId == teacherId)
        {
            // If the teacher has no schedule, return size as 0
            if (curTeacher->scheduleTop == NULL)
            {
                cout << "No schedule found for this teacher!" << endl;
                return 0;
            }

            // Count the number of schedule entries
            int size = 0;
            Schedule *curSchedule = curTeacher->scheduleTop;
            while (curSchedule)
            {
                size++;
                curSchedule = curSchedule->next;
            }
            return size;
        }
        curTeacher = curTeacher->next;
    }

    // Teacher not found
    cout << "Teacher with ID " << teacherId << " not found!" << endl;
    return 0;
}

void TeacherManagementSystem::saveTeachersToFile(const string &filename)
{
    ofstream outFile(filename);
    if (!outFile.is_open())
    {
        cout << "Failed to open file " << filename << endl;
        return;
    }

    Teacher *current = first;
    while (current != NULL)
    {
        outFile << current->teacherId << ";" << current->name << ";" << current->age << ";" << current->dept << ";";

        Feedback *feedback = current->feedBackTop;
        bool firstFeedback = true;
        while (feedback != NULL)
        {
            if (!firstFeedback)
                outFile << "|";
            outFile << feedback->message;
            feedback = feedback->next;
            firstFeedback = false;
        }
        outFile << ";";

        Schedule *schedule = current->scheduleTop;
        bool firstSchedule = true;
        while (schedule != NULL)
        {
            if (!firstSchedule)
                outFile << "|";
            outFile << schedule->timeSlot << "," << schedule->course << "," << schedule->day;
            schedule = schedule->next;
            firstSchedule = false;
        }
        outFile << endl;
        current = current->next;
    }
    outFile.close();
}

void TeacherManagementSystem::loadTeachersFromFile(const string &filename)
{
    ifstream inFile(filename);
    if (!inFile.is_open())
    {
        cout << "Failed to open file " << filename << endl;
        return;
    }

    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string id, name, age, dept, feedbacks, schedules;
        getline(ss, id, ';');
        getline(ss, name, ';');
        getline(ss, age, ';');
        getline(ss, dept, ';');
        getline(ss, feedbacks, ';');
        getline(ss, schedules);

        int ageInt = stoi(age);
        insertTeacher(name, ageInt, dept);

        stringstream ssFeedback(feedbacks);
        string feedback;
        while (getline(ssFeedback, feedback, '|'))
        {
            addFeedback(id, feedback);
        }

        stringstream ssSchedule(schedules);
        string schedule;
        while (getline(ssSchedule, schedule, '|'))
        {
            stringstream ssSchedDetails(schedule);
            string timeSlot, course, day;
            getline(ssSchedDetails, timeSlot, ',');
            getline(ssSchedDetails, course, ',');
            getline(ssSchedDetails, day, ',');
            assignSchedule(id, timeSlot, course, day);
        }
    }
    inFile.close();
}

void TeacherManagementSystem::displayTeacher(string id)
{
    if (first == NULL)
    {
        cout << "Empty List!";
    }
    else
    {
        Teacher *cur = first;
        while (cur)
        {
            if (cur->teacherId == id)
            {
                cout << cur->name << " : " << endl;
                cout << "name : " << cur->name << "\nage : " << cur->age << "\ndepartment : " << cur->dept << endl;
                cout << "Feedbacks : " << endl;
                TeacherManagementSystem::displayTeacherFeedback(cur->teacherId);
                cout << endl;
                cout << "Schedule : " << endl;
                TeacherManagementSystem::displayTeacherSchedule(cur->teacherId);
                return;
            }
            cur = cur->next;
        }
    }
}

void TeacherManagementSystem::displayAllTeachers()
{
    if (first == NULL)
    {
        cout << "Empty List!" << endl;
    }
    else
    {
        Teacher *cur = first;
        while (cur)
        {
            displayTeacher(cur->teacherId); // Call displayTeacher for each teacher
            LineBreaker();
            cur = cur->next; // Move to the next teacher in the list
        }
    }
};

void TeacherManagementSystem::displayTeacherName(string id)
{
    Teacher *teacher = findTeacherById(id);
    if (teacher == nullptr)
        cout << "Teacher not found" << endl;
    else
        cout << teacher->name << endl;
}

void TeacherManagementSystem::displayAllTeachersNames()
{
    if (first == NULL)
    {
        cout << "Empty List!" << endl;
    }
    else
    {
        Teacher *cur = first;
        int counter = 1;
        while (cur)
        {
            cout << counter << " - ";
            displayTeacherName(cur->teacherId); // Call displayTeacherName for each teacher
            cur = cur->next;
            counter++;
            // Move to the next teacher in the list
        }
    }
}

TeacherManagementSystem::Teacher *TeacherManagementSystem::findTeacherByIndex(int index)
{
    if (index < 0 || index >= teacherCount)
    {
        cout << "Index out of range!" << endl;
        return nullptr;
    }

    Teacher *cur = first;
    int currentIndex = 0;
    while (cur)
    {
        if (currentIndex == index)
        {
            return cur;
        }
        cur = cur->next;
        currentIndex++;
    }
    return nullptr; // In case something goes wrong (it shouldn't in this case)
}

int TeacherManagementSystem::size()
{
    return teacherCount;
}