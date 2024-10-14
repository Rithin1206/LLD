// Implement a meeting scheduler application that allows users to schedule and manage meetings. The application should do this:
// * Users can create, update, and delete meetings.
// * Each meeting has a start time, end time, and attendees.
// * The application should prevent users from scheduling overlapping meetings
// * Users can view a calendar of scheduled meetings.
// * The application should be easy to maintain and easy to extend with additional features in the future./

// Entities:
//  meeting scheduler, meeting, time slot, users
// if one person is not free donot schedule the meeting

class TimeStamp{
    public:
    int hour;
    int min;
    int date;
    int month;
    int year;
    
    TimeStamp(int year, int month, int date, int hour, int min){
        this->year= year;
        this->month= month;
        this->date = date;
        this->hour = hour;
        this->min = min;
    }
    
    int compare(TimeStamp* t1){
        // this < t1: -1 || > : 1 || == 0
        if(this->year < t1->year)
            return -1;
        else if(this->year > t1->year)
            return 1;
        
        if(this->month < t1->month)
            return -1;
        else if(this->month > t1->month)
            return 1;
        
        if(this->date < t1->date)
            return -1;
        else if(this->date > t1->date)
            return 1;
        
        if(this->hour < t1->hour)
            return -1;
        else if(this->hour > t1->hour)
            return 1;
        
        if(this->min < t1->min)
            return -1;
        else if(this->min > t1->min)
            return 1;
        
        return 0;
    }
};

class TimeSlot{
    public:
    TimeStamp* start;
    TimeStamp* end;
     
    TimeSlot(TimeStamp* _start, TimeStamp* _end){
        this->start= _start;
        this->end = _end;
    }
     bool overlaps(TimeSlot* t1){
        // cs, ce, ns, ne 
        // cs ns ce
        // ns cs ne
        TimeStamp* cs= this-> start;
        TimeStamp* ce= this->end;
        TimeStamp* ns= t1-> start;
        TimeStamp* ne =  t1->end;

         if((cs->compare(ns)!=1 and ns->compare(ce)==-1 ) or 
            (ns->compare(cs)!=1 and cs->compare(ne)==-1 )){
             return true;
         }
         return false;
    }
};

class User; 

class Meeting{
    public:
    int id;
    TimeSlot* timeSlot;
    vector<User*> attendees;
    
    Meeting(int id, TimeSlot* ts,  vector<User*> _attendees){
        this->id= id;
        this->timeSlot = ts;
        this->attendees = _attendees;
    }
};


class User{
    public:
    string name;
    int id;
    set<Meeting* > calander;
    User(string name, int id){
        this->name = name;
        this->id= id;
    }
    
    void addMeeting(Meeting* meeting){
        this->calander.insert(meeting);
    }
    
    void removeMeeting(Meeting* meeting){
        for(auto& m: calander){
            if(m->id == meeting->id){
                calander.erase(m);
                return;
            }
        }
    }
    
    void printCal(){
        cout<<"meetings of user "<<this->name<<" ";
        for(auto &m: calander){
            cout<<m->id<<" ";
        }
        cout<<endl;
    }
};



// singleton class
class MeetingScheduler{
    public:
    
    static bool createMeeting(Meeting* meeting){
        if(!isPossible(meeting)){
            return false;
        }
        
        for(auto att: meeting->attendees){
            att->addMeeting(meeting);
        }
        return true;
    }
    
    static void deleteMeeting(Meeting* meeting){
        for(auto att: meeting->attendees){
            att->removeMeeting(meeting);
        }
    }
    
    static bool updateMeeting(Meeting* oldMeeting, Meeting* newMeeting){
        // if possible update the meeting -> else no update and keep it as is?
       for(auto user: newMeeting->attendees){
            for(auto&m : user->calander){
                if( m->id != oldMeeting->id and newMeeting->timeSlot->overlaps(m->timeSlot)){
                    return false;
                }
            }
        }
        
        // it is possible -> delete the old ones and create the new one
        deleteMeeting(oldMeeting);
        createMeeting(newMeeting);
        return true;
    }
    
    private:
    static bool isPossible(Meeting* meeting){
        for(auto user: meeting->attendees){
            for(auto&m : user->calander){
                if( m->id != meeting->id and meeting->timeSlot->overlaps(m->timeSlot)){
                    return false;
                }
            }
        }
        return true;
    }
    
};


int main() {
    User* u1= new User("hulk", 5);
    User* u2= new User("thor", 10);
    User* u3= new User("vision", 15);
    
    TimeSlot* ts = new TimeSlot(new TimeStamp(2024, 10, 20, 12, 30), new TimeStamp(2024, 10, 20, 14, 30));
    Meeting* m = new Meeting(1, ts, {u1, u2, u3});
    
    cout<<MeetingScheduler::createMeeting(m)<<endl;
    u1->printCal();
    u2->printCal();
    u3->printCal();
        
    TimeSlot* t2 = new TimeSlot(new TimeStamp(2024, 10, 20, 13, 30), new TimeStamp(2024, 10, 20, 14, 30));
    Meeting* m2 =  new Meeting(2, t2, {u1, u2});
    cout<<MeetingScheduler::updateMeeting(m, m2)<<endl;
    u1->printCal();
    u2->printCal();
    u3->printCal();
    
}