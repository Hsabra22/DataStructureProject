#include <iostream>
#include <string>

using namespace std;
class TeacherManagementSystem {
public:
    struct Feedback {
        string message;
        Feedback*next;
        Feedback(string message): message(message),next(NULL) {};

    };
    struct Schedule {
        string timeSlot;
        string course;
        string day;
        Schedule*next;


        Schedule(string timeslot,string course,string day): timeSlot(timeslot),course(course),day(day),next(NULL) {};
    };
    struct Teacher {
        string name;
        int age;
        string teacherId;
        string dept;
        Teacher*next;
        Schedule* scheduleTop;
        Feedback*feedBackTop;
        Teacher(string name,int age,string dept,int index): name(name),age(age),dept(dept),next(NULL),feedBackTop(NULL),scheduleTop(NULL){
            teacherId = name + (index < 10 ? "000" : index < 100 ? "00" : index < 1000 ? "0" : "") + to_string(index);
        };
    };



private:
    Teacher*first;
    Teacher*last;
   int  teacherCount;
public:

    TeacherManagementSystem() {
        first=NULL;
        last=NULL;
        teacherCount=0;
    }
    void insertFirst(string name,int age,string dept) {
        Teacher*newNode=new Teacher(name,age,dept,teacherCount);
        if(first==NULL) {
            first=newNode;
            last=newNode;
        }
        else {
            newNode->next=first;
            first=newNode;
        }
        teacherCount++;
    }
    void insertTeacher(string name,int age,string dept) {
        Teacher*newNode=new Teacher(name,age,dept,teacherCount);
        if(first==NULL) {
            first=newNode;
            last=newNode;
            newNode->next=NULL;
            teacherCount++;
        }
        else {
           last->next=newNode;
            last=newNode;
           teacherCount++;
        }
        cout<<"_ Inserted Teacher :"<< name <<" with ID : " << newNode->teacherId << ", Age:" <<newNode->age<<", Department :"<<newNode->dept<< endl;

    }
    void removeFirst() {
        Teacher*temp=first;
        if(first==NULL) {
            cout<<"Empty List!";
        }
        else {
            first=first->next;
            delete temp;
            teacherCount--;
        }
    }
    void removeLast() {
        Teacher*cur,*prev;
        if(first==NULL) {
            cout<<"Empty List!";
        }
        else {
            cur=first;
            prev=NULL;
            while(cur->next!=NULL) {
                prev=cur;
                cur=cur->next;
            }
            prev->next=NULL;
            delete cur;
            last=prev;
            teacherCount--;
        }
    }
    void removeTeacherById(string id) {
        Teacher*cur=first;
        Teacher* prev=NULL;
        while(cur) {
            if(cur->teacherId==id) {
                if(prev==NULL) {
                    first=cur->next;

                }
                else
                     {
                        prev->next=cur->next;
                     }
                    if(cur==last) {
                        last=prev;
                        prev->next=NULL;
                    }
                delete cur;
                teacherCount--;
                cout << "_Teacher with ID " << id << " removed." << endl;

                return; //End of the function
            }
            cur=cur->next;

        }
        cout<<"_Teacher with ID " << id << " not found!" << endl;
    }

    void assingSchedule(string id,string timeSlot,string course,string day) {
        Teacher*cur=first;
        bool found=false;
        while(cur) {
            if(cur->teacherId==id) {
                found=true;
                Schedule*newSchedule=new Schedule(timeSlot,course,day);
                newSchedule->next=cur->scheduleTop;
                cur->scheduleTop=newSchedule;
                cout << "_Assigned schedule to " << cur->name << ": " << day << " at " << timeSlot << " for " << course << endl;
                return;
              }
           cur=cur->next;

        }

            cout<<"_Teacher not found!"<<endl;


    }



     void addFeedback(string id,string message) {
        Teacher*cur=first;
        bool found=false;
        while(cur) {
            if(cur->teacherId==id) {
                found=true;
                Feedback*newFeedBack=new Feedback(message);
                newFeedBack->next=cur->feedBackTop;
                cur->feedBackTop=newFeedBack;
                cout << "_Added feedback for " << cur->name << ": " << newFeedBack->message << endl;
                  return;

            }
            cur=cur->next;

        }

            cout<<"_Teacher not found!"<<endl;

    }

    void removeSchedule(string id,string day,string timeSlot) {
        Teacher*cur=first;
        while(cur) {
            if(cur->teacherId==id) {
                Schedule* curSchedule=cur->scheduleTop;
                Schedule* previousSchedule=NULL;
                while(curSchedule) {
                    if(curSchedule->day==day && curSchedule->timeSlot==timeSlot) {
                        if(previousSchedule==NULL) {
                            cur->scheduleTop = curSchedule->next;
                        }
                        else {
                            previousSchedule->next=curSchedule->next;
                        }

                        delete curSchedule;
                        cout<<"_Schedule deleted"<<endl;
                        return;
                    }
                    previousSchedule=curSchedule;
                    curSchedule=curSchedule->next;

                }
                cout << "_No matching schedule found for Teacher with ID " << id << endl;
               return;

            }
            cur=cur->next;
        }

            cout<<"Teacher not found!";

    }
    void removeFeedBack(string id,string message) {
        Teacher*cur=first;
        while(cur) {
            if(cur->teacherId==id) {
                Feedback*curFeedback=cur->feedBackTop;
                Feedback*prevFeedback=NULL;
                while(curFeedback) {
                    if(curFeedback->message==message) {
                        if(prevFeedback==NULL) {
                            cur->feedBackTop=curFeedback->next;

                        }
                        else {
                            prevFeedback->next=curFeedback->next;
                        }
                        delete curFeedback;
                        cout<<"_Feedback of "<<cur->name<<" is deleted!"<<endl;
                        return;

                    }
                    prevFeedback=curFeedback;
                    curFeedback=curFeedback->next;

                }
               cout << "_No matching feedback found for Teacher with ID " << id << endl;
                return;
            }
            cur=cur->next;
        } cout<<"Teacher not found"<<endl;

    }
    void updateTeacherInfo(string id,string newName,int newAge,string newDept ) {
        Teacher*cur=first;
        while(cur) {
            if(cur->teacherId==id) {
                cout<<"_Teacher "<< cur->name << " with updated info: ";
                cur->name=newName;
                cur->age=newAge;
                cur->dept=newDept;
                cur->teacherId=newName+(teacherCount<10? "000":teacherCount<100? "00":teacherCount<1000?"0":" ")+to_string(teacherCount);
                cout<< newName << " "<< newAge << " "<<newDept<< " "<<cur->teacherId<<endl;
                return;

            }
            cur=cur->next;
        }
        cout<<"_Teacher not found"<<endl;
    }

    void updateTeacherSchedule(string id,string timeSlot,string day,string course,string newTimeSlot,string newDay,string newCourse) {
        Teacher*cur=first;
        while(cur) {
            if(cur->teacherId==id) {
                Schedule* curSchedule=cur->scheduleTop;
                while(curSchedule) {
                    if(curSchedule->timeSlot==timeSlot && curSchedule->day==day && curSchedule->course==course) {
                        cout<<"_New Schedule for teacher "<<cur->name;
                        curSchedule->timeSlot=newTimeSlot;
                        curSchedule->day=newDay;
                        curSchedule->course=newCourse;
                        cout<< ": " << newDay << " at " << newTimeSlot << " for " << newCourse << endl;
                        return;
                    }
                    curSchedule=curSchedule->next;
                }
                cout<<"_This schedule not found for "<< cur->name<<endl;
                return;
            }
            cur=cur->next;
        }
        cout<<"_Teacher not found"<<endl;
    }

    void updateTeacherFeedback(string id,string message,string newMessage) {
        Teacher*cur=first;
        while(cur) {
            if(cur->teacherId==id) {
                Feedback* curFeedback=cur->feedBackTop;
                while(curFeedback) {
                    if(curFeedback->message==message ) {
                        cout<<"_New Feedback for teacher "<<cur->name;
                        curFeedback->message=newMessage;

                        cout<< ": " << newMessage  << endl;
                        return;
                    }
                    curFeedback=curFeedback->next;
                }
                cout<<"_This Feedback not found for "<< cur->name<<endl;
                return;
            }
            cur=cur->next;
        }
        cout<<"_Teacher not found"<<endl;
    }

    void displayTeacherSchedule(string id) {
        if(first==NULL) {
            cout<<"Empty List!";
        }
        else {

            Teacher*cur=first;

            while(cur) {

                if(cur->teacherId==id) {
                    if(cur->scheduleTop==NULL) {
                        cout<<"No Schedule found!";
                    }
                    else{
                        cout<<endl<<"Full Schedule of "<<cur->name<<": "<<endl;
                        Schedule*curSchedule=cur->scheduleTop;
                         while(curSchedule) {
                            cout<<"\t"<<"\t"<<"\t"<<"_"<<curSchedule->timeSlot<<" "<<curSchedule->day<<" "<<curSchedule->course<<endl;
                            curSchedule=curSchedule->next;
                        }
                    }
                    return;
                }
                cur=cur->next;
            }
        }
    }

    void displayTeacherFeedback(string id) {
        if(first==NULL) {
            cout<<"Empty List!";
        }
        else {
            Teacher*cur=first;
            while(cur) {
                if(cur->teacherId==id) {
                    if(cur->scheduleTop==NULL) {
                        cout<<"No Feedback found!";
                    }
                    else {
                        cout<<"Full Feedback of "<<cur->name<<": "<<endl;
                        Feedback* curFeedback=cur->feedBackTop;
                        while(curFeedback) {
                            cout<<"\t"<<"\t"<<"\t"<<"_"<<curFeedback->message<<" "<<endl;

                            curFeedback=curFeedback->next;
                        }
                    }
                    return;
                }
                cur=cur->next;
            }
        }
    }

    void getFirst() {
        if(first==NULL) {
            cout<<"Empty List!";
        }
        else {
            cout<<first->name<< " "<<first->age<<" "<< first->dept<<" "<<first->teacherId<<endl;
        }
    }

    void getLast() {
        if(first==NULL) {
            cout<<"Empty List!";
        }
        else {
            cout<<last->name<< " "<<last->age<<" "<< last->dept<<" "<<last->teacherId<<endl;
        }
    }

};

int main() {
    TeacherManagementSystem teacher;
    teacher.insertTeacher("Hassan",19,"Mathematics");
    teacher.insertTeacher("Ali",33,"Physics");
    teacher.insertTeacher("Joseph",40,"Chemistry");
    teacher.insertTeacher("Omar",25,"Biology");
    cout<<endl;
    teacher.assingSchedule("Hassan0000","10:00AM","Calculus","Friday");
    teacher.assingSchedule("Hassan0000","2:00AM","Linear Algebra","Wednsday");
    cout<<endl;
    teacher.assingSchedule("Ali0001","11:00AM","Mechanics","Tuesday");
    teacher.assingSchedule("Ali0001","1:00AM","Quantum Physics","Monday");
    cout<<endl;
    teacher.assingSchedule("Joseph0002","9:00AM","BioChemistry","Thursday");
    teacher.assingSchedule("Joseph0002","3:00AM","Organic Chemistry","Friday");
    cout<<endl;
    teacher.assingSchedule("Omar0003","11:00AM","BioChemistry","Tuesday");
    teacher.assingSchedule("Omar0003","1:00AM","SVT","Monday");
    cout<<endl;
    cout<<endl;
    teacher.addFeedback("Hassan0000","Great Job on the last lecture!");
    teacher.addFeedback("Hassan0000","Needs to improve in presentation clarity");
    cout<<endl;
    teacher.addFeedback("Ali0001","Very interactive session!");
    teacher.addFeedback("Ali0001","Excellent understanding of the subject");
    cout<<endl;
    teacher.addFeedback("Joseph0002","Makes litterature enjoyable!");
    teacher.addFeedback("Joseph0002","Covers topics thouroughtly");
    cout<<endl;
    teacher.addFeedback("Omar0003","Great Job on the last lecture!");
    teacher.addFeedback("Omar0003","Needs to improve in presentation clarity");
    cout<<endl;
    teacher.updateTeacherInfo("Hassan0000","Jamal",20,"Computer Science");
    cout<<endl;

    teacher.displayTeacherFeedback("Ali0001");
    teacher.displayTeacherSchedule("Ali0001");
    cout<<endl;
    teacher.displayTeacherFeedback("Joseph0002");
    teacher.displayTeacherSchedule("Joseph0002");
    cout<<endl;
    teacher.displayTeacherFeedback("Omar0003");
    teacher.displayTeacherSchedule("Omar0003");
    cout<<endl;
    teacher.displayTeacherFeedback("Jamal0004");
    teacher.displayTeacherSchedule("Jamal0004");





}
