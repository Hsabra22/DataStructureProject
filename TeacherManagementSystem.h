#include <string>
#include<iostream>

using namespace std;
struct ActionResult
{
    string message;
    bool response;
    ActionResult(string message , bool response) : message(message), response(response) {};
};
class TeacherManagementSystem {
public:
    struct Feedback {
        string message;
        Feedback *next;
        Feedback(string msg) : message(msg), next(nullptr) {}
    };

    struct Schedule {
        string timeSlot;
        string course;
        string day;
        Schedule *next;
        Schedule(string ts, string crs, string dy) : timeSlot(ts), course(crs), day(dy), next(nullptr) {}
    };

    struct Teacher {
        string name;
        int age;
        string teacherId;
        string dept;
        Teacher *next;
        Schedule *scheduleTop;
        Feedback *feedBackTop;

        Teacher(string nm, int ag, string dp, string id) : name(nm), age(ag), dept(dp), teacherId(id), next(nullptr), scheduleTop(nullptr), feedBackTop(nullptr) {}
    };

    TeacherManagementSystem();
    void insertFirst(string name, int age, string dept);
    void insertTeacher(string name, int age, string dept);
    void removeFirst();
    void removeLast();
    void removeTeacherById(string id);
    void assignSchedule(string id, string timeSlot, string course, string day);
    void addFeedback(string id, string message);
    void removeSchedule(string id, string day, string timeSlot);
    void removeFeedback(string id, string message);
    void updateTeacherInfo(string id, string newName, int newAge, string newDept);
    void updateTeacherSchedule(string id, string timeSlot, string day, string course, string newTimeSlot, string newDay, string newCourse);
    void updateTeacherFeedback(string id, string message, string newMessage);
    void displayTeacherSchedule(string id);
    void displayTeacherFeedback(string id);
    void displayTeacher(string id);
    void displayAllTeachers();
    void displayTeacherName(string id);
    void displayAllTeachersNames();
    void getFirst();
    void getLast();
    bool checkIfIdExists(string Id);
    ActionResult checkIfTimeSlotIsTaken(string id , string timeSlot , string day);
    Teacher* findTeacherById(const string &id);
    Teacher* findTeacherByIndex(int index);
    Schedule* findScheduleByIndex(string teacherId, int index);
    int getTeacherScheduleSize(string teacherId);
    void saveTeachersToFile(const string &filename);
    void loadTeachersFromFile(const string &filename);
    int  size();

private:
    Teacher *first;
    Teacher *last;
    int teacherCount;

    string generateTeacherId(string name);
};


inline void LineBreaker() {
    std::cout << "\n====================TMS====================\n" << std::endl;
}

