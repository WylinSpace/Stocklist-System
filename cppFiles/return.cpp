#ifndef RETURN_CPP
#define RETURN_CPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define BOLD    "\033[1m"
#define RESET   "\033[0m"
using namespace std;

class userOperationRETURN
{
    private:
    string userID = "None";
    string userName = "None";
    string borrowDate = "None";
    string dueDate = "None";
    string itemID = "None";
    string filepath = "Data/userData/";
    double finePerDay = 0.5;
    string ParsedItemID = "None";
    string ParsedItemName = "None";
    string ParsedItemNumber = "None";

    public:
    void displayItemBorrowed(string userIDfromConsole,string userNamefromConsole){
        userID = userIDfromConsole;
        userName = userNamefromConsole;
        string filename = filepath + userID +".csv";
        const int column_1_width = 8;
        const int column_2_width = 15;
        const int column_3_width = 20;
        int lineCount = lineCalculator();
        string tableList[lineCount][2];
        int row = 0; 
        ifstream infile(filename);
        if (infile.is_open()) {
            string line;
            while (getline(infile, line)) {
                stringstream ss(line);
                string cell;
                int column = 0;
                while (getline(ss, cell, ',')) {
                    if (column < 2 && row < lineCount) {
                        tableList[row][column] = cell;
                    }
                    column++;
                }
                if (row < lineCount) {
                    row++;
                }
            }
            infile.close();
        } else {
            cerr << RED << BOLD << "User do not have an existing Borrow Record!" << RESET << endl;
        }
        if(lineCount>1){
            for (int row = 0; row < lineCount; row++) {
            if(row>0){
                cout << left << setw(column_2_width) << row;
            }else{
                cout << left << setw(column_2_width) << "Item No.";
            }
            for (int column = 0; column < 2; column++) {
                if(row==0){
                    if(column ==0){
                        cout << left << setw(column_2_width) << tableList[row][column];
                    } else {
                        cout << left << setw(column_3_width) << tableList[row][column];
                    }
                } else {
                    if(column ==0){
                        cout << left << setw(column_2_width) << tableList[row][column];
                    } else {
                        cout << left << setw(column_3_width) << itemIDtoName(tableList[row][column]);
                    }
                }
            }
            cout << endl;
        }
        } else {
            cout<<BOLD<<GREEN<<"All the Borrowed Item had been Successfully Returned!"<<RESET<<endl;
        }
    }

    bool NothingToReturn(){
        int lineCount = lineCalculator();
        if(lineCount>1){
            return false;
        } else {
            return true;
        }
    }

    int lineCalculator() {
        string filename = filepath + userID +".csv";
        int lineCount = 0;
        ifstream infile(filename);
        if (infile.is_open()) {
            string line;
            while (getline(infile, line)) {
                lineCount++;
            }
                infile.close();
        }
        return lineCount;
    }

    string itemIDtoName(string itemIDinStr){
        int itemIDinInt;
        itemIDinInt = stoi(itemIDinStr);
        switch(itemIDinInt){
            case 1000:
            return "Wires";
            break;
            case 2000:
            return "Resistor";
            break;
            case 3000:
            return "Capacitor";
            break;
            case 4000:
            return "Diode";
            break;
            case 5000:
            return "Breadboard";
            break;
            case 6000:
            return "Soldering Tools";
            break;
            case 7000:
            return "Multimeter";
            break;
            case 8000:
            return "Brush Motor";
            break;
            case 9000:
            return "Brushless Motor";
            default:
            return "Others...";
            break;
        }
    }

    void deleteReturnItem(int lineToDelete){
        lineToDelete++;
        getItemBorrowDate(lineToDelete);
        returnTheItemToSystem(itemID);
        string filename = filepath + userID +".csv";
        ifstream infile(filename);
        stringstream updatedContent;
        int currentLine = 0;
        bool itemDeleted = false;
        if(infile.is_open()){
            string line;
            while(getline(infile,line)){
                currentLine++;
                if(currentLine == lineToDelete){
                    itemDeleted = true;
                    continue;
                }
                updatedContent << line << endl;
            }
            if (!itemDeleted) {
                cerr << RED << BOLD << "Selected number: " << (lineToDelete-- -1) << " does not exist in the record." << RESET << endl;
                this_thread::sleep_for(chrono::duration<double>(2));
            }
        } else {
            cerr << RED << BOLD << "User do not have an existing Borrow Record!" << RESET << endl;
            this_thread::sleep_for(chrono::duration<double>(2));
            infile.close();
        }
        ofstream outfile(filename);
        if (outfile.is_open()) {
            calculateDateDifference(itemDeleted);
            outfile << updatedContent.str();
            outfile.close();
        } else {
            cerr << RED << BOLD << "User do not have an existing Borrow Record!" << RESET << endl;
            this_thread::sleep_for(chrono::duration<double>(2));
            outfile.close();
        }
    }

    void getItemBorrowDate(int lineToDelete){
        string filename = filepath + userID +".csv";
        ifstream infile(filename);
        int currentLine = 0;
        bool lineFound = false;
        if(infile.is_open()){
            string line;
            while (std::getline(infile, line)){
            currentLine++;
            if (currentLine == lineToDelete) {
                lineFound = true;
                stringstream ss(line);
                string cell;
                int column = 0;
                while(getline(ss,cell,',')){
                    if(column==0){
                        borrowDate = cell;
                    }
                    if(column==1){
                        itemID = cell;
                    }
                    column++;
                }
                break;
            }
        }
        infile.close();
        }
    }

    void calculateDateDifference(bool itemDeleted) {
        string format = "%d/%m/%Y";
        tm tm1 = {};
        istringstream ss1(borrowDate);
        ss1 >> get_time(&tm1, format.c_str());

        string currentDate;
        time_t now = time(0);
        tm* localTime = localtime(&now);
        char dateStr[11];
        strftime(dateStr, sizeof(dateStr), "%d/%m/%Y", localTime);
        currentDate = string(dateStr);

        tm tm2 = {};
        istringstream ss2(currentDate);
        ss2 >> get_time(&tm2, format.c_str());

        std::time_t time1 = std::mktime(&tm1);
        std::time_t time2 = std::mktime(&tm2);

        double differenceInSeconds = std::difftime(time2, time1);

        int daysDifference = std::abs(differenceInSeconds) / (60 * 60 * 24);

        if(daysDifference>=14 && itemDeleted){
            cout<<RED<<BOLD<<"The Borrowed Item is overdue."<<RESET<<endl;
            int amount = daysDifference*finePerDay;
            reportToAdmin(amount);
            cout<<RED<<BOLD<<"Please pay RM " << amount << " for this component at Office."<<RESET<<endl;
            this_thread::sleep_for(chrono::duration<double>(1));
        } else if(daysDifference<14 && itemDeleted){
            cout<<BOLD<<GREEN<<"Item Returned Successfully!"<<RESET<<endl;
            this_thread::sleep_for(chrono::duration<double>(1));
        }
    }

    void reportToAdmin(int amount){
        string filename = "Data/overDueList/overDueList.csv";
        ifstream infile(filename);
        if(infile.is_open()){
            ofstream outfile(filename,ios::app);
            string NewLine = userID+","+userName+","+to_string(amount);
            outfile << NewLine <<endl;
            outfile.close();
        } else {
            ofstream outfile(filename, ios::app);
            outfile << "userID,Name,Amount To Pay (In RM)" << endl;
            string NewLine = userID+","+userName+","+to_string(amount);
            outfile << NewLine <<endl;
            outfile.close();
        }
    }

    void returnTheItemToSystem(string requiredItem){
        string filename = "Data/ItemID/item.csv";
        ifstream infile(filename);
        stringstream updatedContent;
        bool itemFound = false;
        if(infile.is_open()){
            string line;
            while(getline(infile,line)){
                stringstream ss(line);
                string cell;
                int column = 0;
                while(getline(ss,cell,',')){
                    if(column==0){
                        ParsedItemID = cell;
                    }
                    if(column==1){
                        ParsedItemName = cell;
                    }
                    if(column==2){
                        ParsedItemNumber = cell;
                    }
                    column++;
                }
                if(requiredItem==ParsedItemID){
                    itemFound = true;
                    int itemNumber = stoi(ParsedItemNumber);
                    ParsedItemNumber = to_string(++itemNumber);
                    updatedContent << ParsedItemID << "," << ParsedItemName << "," << ParsedItemNumber << endl;
                } else {
                    updatedContent << line << endl;
                }
            }
            infile.close();
            if (itemFound) {
                ofstream outfile(filename);
                if (outfile.is_open()) {
                    outfile << updatedContent.str();
                    outfile.close();
                }
            }
        }
    }
};

#endif