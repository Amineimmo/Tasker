#include <fstream>
#include <string>
#include <iostream>
#include <limits>
#include "include/json.hpp"
using json = nlohmann::json;
using namespace std;





std::ifstream f("data.json");
json previous = json::parse(f, nullptr, false);
std::fstream out("data.json");

struct task {
    json data;
    int UID;
    std::string description;
    bool completed;
    task(){}
    task(int ID,std::string ds,bool st){
        UID=ID;
        description=ds;
        completed=st;
        data["UID"] = UID;
        data["description"] = description;
        data["completed"] = completed;
        previous.push_back(data);
        out.clear();
        out.seekp(0, std::ios::beg);
        out << previous.dump(4);
    }
    void setComp(bool statue){
        completed = statue;
        for(auto& dt : previous){
            if(dt["UID"] == UID){
                dt["completed"] = completed;
            }
        }
    }
    void setDesc(std::string desc){
        description = desc;
        for(auto& dt : previous){
            if(dt["UID"] == UID){
                dt["description"] = description;
            }
        }
    }
};


bool see_alltasks(){
    if(f.is_open()){
        for(auto& d : previous){
            cout << d["UID"] << " | " << d["description"] <<  " | " << d["completed"] << endl;
        }
        return true;
    } else {
        return false;
    }
}

void changestatue(int id){
    bool input;
    cout << "Type 0 (false) or 1 (true) : ";
    cin >> input;
    if(cin.fail()){
        while (cin.fail())
        {
            cout << "Invalid input, try again : ";
            cin >> input;
        }
        
    }
    if(f.is_open()){
        for(auto& d : previous){
            if(d["UID"] == id){
                d["completed"] = input;
            }
        }
        std::ofstream save("data.json", std::ios::trunc);
        if (save.is_open()) {
            save << previous.dump(4);
        } else {
            cerr << "Unable to open data.json for writing";
        }
    }
    else {
        cerr << "outle not open";
    }
}
void changedesc(int id){
    std::string desc;
    cout << "Type your description : ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(cin, desc);
    if(f.is_open()){
        for(auto& d : previous){
            if(d["UID"] == id){
                d["description"] = desc;
            }
        }
        std::ofstream save("data.json", std::ios::trunc);
        if (save.is_open()) {
            save << previous.dump(4);
        } else {
            cerr << "Unable to open data.json for writing";
        }
    }
    else {
        cerr << "outle not open";
    }
}

bool check_id(int i){
    if(f.is_open()){
        for(auto& d : previous){
            if(d["UID"] == i){
                return true;
            }
        }
    }
    return false;
}
int UID_giver(){
    int n = 0;
    if(f.is_open()){
        for(auto& d : previous){
            n++;
        }
        return n+1;
    }
    return 0;
}
string get_des(){
    std::string d;
    cout <<"Type a description for your new task : ";
    cin >> d;
    return d;
}
bool get_sta(){
    bool st;
    cout <<"Type the statue for your new task (0 not yet or 1 completed): ";
    cin >> st;
    if(cin.fail()){
        while(cin.fail()){
            cout << "Please type in a valid boolean (0 not yet or 1 completed) : ";
            cin >>st;
        }
    }
    return st;
}
bool createTask(){
    string dis = get_des();
    bool stat = get_sta();
    task t1(UID_giver(),dis,stat);
    return true;
}

int main(){
    std::ifstream f("data.json");

    if (previous.is_discarded()) {
        previous = json::array();
    }
    const char* banner = R"(████████╗ █████╗ ███████╗██╗  ██╗███████╗██████╗
╚══██╔══╝██╔══██╗██╔════╝██║ ██╔╝██╔════╝██╔══██╗
   ██║   ███████║███████╗█████╔╝ █████╗  ██████╔╝
   ██║   ██╔══██║╚════██║██╔═██╗ ██╔══╝  ██╔══██╗
   ██║   ██║  ██║███████║██║  ██╗███████╗██║  ██║
   ╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝)";
    cout << banner;
    cout <<endl;
    cout <<endl;
    cout <<endl;
    cout <<endl;
    cout << "Welcome to tasker! a task manager that will help you decide less and work more  || choose a number (0-3)" << endl;
    int i ;
    bool ongoing = true;
    while (ongoing)
    {    
        cout << "1-View your tasks " <<endl;
        cout << "2-Add a task" << endl;
        cout << "3-Delete a task"<<endl;
        cout <<"0-Exit"<<endl;
        cout << "choice : " ;
        cin >> i ;
        if(i < 0 || i>3 ){
            while(i < 0 || i>3){
                cout << "Invalid choice! choose an option (0,3) : ";
                cin >> i;
            }
        }
        cout << "\033[2J\033[1;1H";
        switch (i)
        {
        case 0:
            cout<<"Au revoir!" << endl;
            out.clear();
             out.seekp(0, std::ios::beg);
             out.close();
             f.close();
            return 0;
            break;
        case 1:
            if(see_alltasks()){
                cout << endl;
                cout << "1-Edit an existing task" << endl;
                cout << "2-Return to main menu" << endl;
                int choice;
                cout <<"choice : ";
                cin >> choice;
                if(choice < 1 || choice > 2 ){
                    while(choice < 1 || choice > 2){
                        cout << "Invalid choice! choose an option (1,2) : ";
                        cin >> choice;
                     }
                }
                switch (choice)
                {
                case 1:
                    int choice_x;
                    cout << "1-Change description" << endl;
                    cout << "2-Change statue " << endl;
                    cout << "0-Return main menu " << endl;
                    cout << endl;
                    cin >> choice_x;
                    if(choice_x <0 || choice_x >2){
                        cout << "Invalid input! choose an option (1,2)";
                        cin >> choice_x;
                    }
                    switch (choice_x)
                    {
                    case 1:
                        int id;
                        cout << "Choose a task with the UID : ";
                        cin >> id;
                        if(check_id(id)){
                            changedesc(id);
                        }else {
                            while(!check_id(id)){
                                cout << "Invalid UID, please type a valid one : ";
                                cin >>id;
                            }
                        }
                        break;
                    case 2:
                        cout << "Choose a task with the UID : ";
                        cin >> id;
                        if(check_id(id)){
                            changestatue(id);
                        }else {
                            while(!check_id(id)){
                                cout << "Invalid UID, please type a valid one : ";
                                cin >>id;
                            }
                        }
                        break;
                    case 0:
                        break;
                    }
                    break;
                case 2:
                    break;
                }
            }
            cout << "\033[2J\033[1;1H";
            break;
        case 2: //add a task
            createTask();
            cout << "\033[2J\033[1;1H";
            break;
        case 3: 
            cout <<"Will be available later !";
            cout << "\033[2J\033[1;1H";
            break;
        }
    }
}