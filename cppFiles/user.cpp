#ifndef USER_CPP
#define USER_CPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
#define BOLD "\033[1m"
#define RESET "\033[0m"
using namespace std;

class userData
{
    private:
    string userID = "None";
    string userEmail = "None";
    string userPassword = "None";
    string userName = "None";
    string filename = "Data/userID/user.csv";
    string filenameAdmin = "Data/userID/admin.csv";
    string currentDate = "None";

    public:
    void getCurrentDate(){
        time_t now = time(0);
        tm* localTime = localtime(&now);
        char dateStr[11];
        strftime(dateStr, sizeof(dateStr), "%d/%m/%Y", localTime);
        currentDate = string(dateStr);
    }

    void statusCheck(){
        cout<<"┌";
        for(int i =0;i<56;i++) cout<<"─";
        cout<<"┐"<<endl;
        cout<<"│"<<BOLD<<setw(28)<<left<<"The current user NAME is"<<setw(28)<<left<<": "+userName<<RESET<<"│"<<endl;
        cout<<"│"<<BOLD<<setw(28)<<left<<"The current user EMAIL is"<<setw(28)<<left<<": "+userEmail<<RESET<<"│"<<endl;
        cout<<"│"<<BOLD<<setw(28)<<left<<"The current DATE is"<<setw(28)<<left<<": "+currentDate<<RESET<<"│"<<endl;
        cout<<"└";
        for(int i =0;i<56;i++) cout<<"─";
        cout<<"┘"<<endl;
        cout<<endl;
    }

    bool find_userEmail(string test_userEmail,string test_userPassword){
        ifstream infile(filename);
        if(infile.is_open()){
            string line;
            while(getline(infile,line)){
                stringstream ss(line);
                string cell;
                int column = 0;
                while(getline(ss,cell,',')){
                    if(column==0){
                        userEmail = cell;
                    }
                    if(column==1){
                        userPassword = cell;
                    }
                    if(column==2){
                        userID = cell;
                    }
                    if(column==3){
                        userName = cell;
                    }
                    getCurrentDate();
                    column++;
                }
                if(test_userEmail==userEmail&&test_userPassword==userPassword){
                    infile.close();
                    return true;
                }
            }
            infile.close();
            return false;
        } else {
            cerr << "Error: Unable to open file! \nPlease report this to Admin for further actions."<<endl;
            return false;
        }
    }

    bool find_adminEmail(string test_userEmail,string test_userPassword){
        ifstream infile(filenameAdmin);
        if(infile.is_open()){
            string line;
            while(getline(infile,line)){
                stringstream ss(line);
                string cell;
                int column = 0;
                while(getline(ss,cell,',')){
                    if(column==0){
                        userEmail = cell;
                    }
                    if(column==1){
                        userPassword = cell;
                    }
                    if(column==2){
                        userID = cell;
                    }
                    if(column==3){
                        userName = cell;
                    }
                    getCurrentDate();
                    column++;
                }
                if(test_userEmail==userEmail&&test_userPassword==userPassword){
                    infile.close();
                    return true;
                }
            }
            infile.close();
            return false;
        } else {
            cerr << "Error: Unable to open file! \nPlease report this to Admin for further actions."<<endl;
            return false;
        }
    }
    
    string giveUserID(){
        return userID;
    }

    string giveUserName(){
        return userName;
    }
};

#endif