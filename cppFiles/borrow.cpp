#ifndef BORROW_CPP
#define BORROW_CPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
using namespace std;

class userOperationBORROW
{
    private:
    string userID = "None";
    string borrowDate = " None";
    string dueDate = "None";
    string filepath = "Data/userData/";

    public:
    void getCurrentStatus(string userIDnow){
        time_t now = time(0);
        tm* localTime = localtime(&now);
        char dateStr[11];
        strftime(dateStr, sizeof(dateStr), "%d/%m/%Y", localTime);
        borrowDate = string(dateStr);
        userID=userIDnow;

    }

    void userDataWRITE(string userIDnow, string itemID){
        getCurrentStatus(userIDnow);
        string filename = filepath + userID +".csv";
        ifstream infile(filename);
        if(infile.is_open()){
            ofstream outfile(filename,ios::app);
            string NewLine = borrowDate+","+itemID;
            outfile << NewLine <<endl;
            outfile.close();
        } else {
            ofstream outfile(filename, ios::app);
            outfile << "Date,Component ID" << endl;
            string NewLine = borrowDate+","+itemID;
            outfile << NewLine <<endl;
            outfile.close();
        }
    }
};

#endif