#ifndef ADMIN_CPP
#define ADMIN_CPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
#include <regex>
#include <thread>
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define BOLD    "\033[1m"
#define RESET   "\033[0m"
#define MOVE_CURSOR(row, col) "\033[" #row ";" #col "H"
#define CLEAR_SCREEN "\033[2J"
#define CLEAR_TO_END "\033[0J"
using namespace std;

class admin{
    private:
    string date;
    string adminID;

    public:
    int lineCalculator(string filename) {
        int lineCount = 0;
        ifstream infile(filename);
        if (infile.is_open()) {
            string line;
            while (getline(infile, line)) {
                lineCount++;
            }
            infile.close();
        } else {
            cerr << "Error: Unable to open file!" << endl;
        }
        return lineCount;
    }
    
    void displayPenaltyList(){
        string userID;
        string userName;
        string amount;
        string filename = "Data/overDueList/overDueList.csv";
        const int column_1_width = 8;
        const int column_2_width = 15;
        const int column_3_width = 20;
        int lineCount = lineCalculator(filename);
        string tableList[lineCount][3];
        int row = 0; 
        ifstream infile(filename);
        if (infile.is_open()) {
            string line;
            while (getline(infile, line)) {
                stringstream ss(line);
                string cell;
                int column = 0;
                while (getline(ss, cell, ',')) {
                    if (column < 3 && row < lineCount) {
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
            cerr << "Error: Unable to open file!" << endl;
        }
        if(lineCount>1){
            for (int row = 0; row < lineCount; row++) {
            if(row>0){
                cout << left << setw(column_1_width) << row;
            }else{
                cout << left << setw(column_1_width) << "No.";
            }
            for (int column = 0; column < 3; column++) {
                if(row==0){
                    if(column ==0){
                        cout << left << setw(column_2_width) << tableList[row][column];
                    } else {
                        cout << left << setw(column_3_width) << tableList[row][column];
                    }
                } else {
                    if(column ==0){
                        cout << left << setw(column_2_width) << tableList[row][column];
                    } else if(column==1){
                        cout << left << setw(column_3_width) << tableList[row][column];
                    } else if(column==2){
                        cout << left << setw(column_3_width) << fixed << setprecision(2) << stod(tableList[row][column]);
                    }
                }
            }
            cout << endl;
        }
        } else {
            cout<<"All the Borrowed Item had been Successfully Returned!"<<endl;
        }
    }

    void getCurrentStatus(string adminIDfromConsole){
        time_t now = time(0);
        tm* localTime = localtime(&now);
        char dateStr[11];
        strftime(dateStr, sizeof(dateStr), "%d/%m/%Y", localTime);
        date = string(dateStr);
        adminID = adminIDfromConsole;
    }

    void purchaseRequest(string adminIDfromConsole){
        getCurrentStatus(adminIDfromConsole);
        string filename = "Data/purchaseRequest/puchaseRequest.csv";
        ifstream infile(filename);
        string ComponentsName,Quantity,Specifications;
        regex nameRegex("^[A-Za-z ]+$");
        regex quantityRegex("^[0-9]+$");
        regex specRegex("^[A-Za-z0-9, ]+$");

        while (true) {
            cout<<"Enter The Name of Components You Wanted to Buy > ";
            cin.ignore();
            getline(cin,ComponentsName);
            if (regex_match(ComponentsName, nameRegex)) {
                break;
            } else {
                cout << RED << BOLD << "Invalid component name. Please enter alphabetic characters and spaces only." << RESET << endl;
                this_thread::sleep_for(chrono::duration<double>(1));
                cout << MOVE_CURSOR(14,0) << CLEAR_TO_END;
            }
        }
        while (true) {
            cout << "Enter The Quantity of Components > ";
            getline(cin, Quantity);
            if (regex_match(Quantity, quantityRegex)) {
                break;
            } else {
                cout << RED << BOLD << "Invalid quantity. Please enter a number only." << RESET << endl;
                this_thread::sleep_for(chrono::duration<double>(1));
                cout << MOVE_CURSOR(15,0) << CLEAR_TO_END;
            }
        }
        
        while (true) {
            cout << "Enter The Specification You wish to add on > ";
            getline(cin, Specifications);
            if (regex_match(Specifications, specRegex)) {
                break;
            } else {
                cout << RED << BOLD << "Invalid specification. Please enter alphabetic characters, numbers, spaces and commas only." << RESET << endl;
                this_thread::sleep_for(chrono::duration<double>(1));
                cout << MOVE_CURSOR(16,0) << CLEAR_TO_END;
            }
        }

        cout<<BLUE<<BOLD<<"\nThe Request Entered is:"<<RESET<<endl;
        cout<<BLUE<<BOLD<<setw(16)<<left<<"Components"<<": "<<ComponentsName<<RESET<<endl;
        cout<<BLUE<<BOLD<<setw(16)<<left<<"Quantity"<<": "<<Quantity<<RESET<<endl;
        cout<<BLUE<<BOLD<<setw(16)<<left<<"Specifications"<<": "<<Specifications<<RESET<<endl;

        cout<<"\nAre You Sure You Want To Make This Request? (Y for YES and N for NO) \nEnter (Y/N) > ";
        char Confirmation;
        cin>>Confirmation;
        if(Confirmation=='Y'||Confirmation=='y'){
            cout<<GREEN<<BOLD<<"The request is marked SUCCESSFULLY!"<<RESET<<endl;
            if(infile.is_open()){
                ofstream outfile(filename,ios::app);
                string NewLine = adminID+","+date+","+ComponentsName+","+Quantity+","+Specifications;
                outfile<< NewLine <<endl;
                outfile.close();
            } else {
                ofstream outfile(filename, ios::app);
                outfile << "AdminID,Date,Components Name,Quantity,Specifications" << endl;
                string NewLine = adminID+","+date+","+ComponentsName+","+Quantity+","+Specifications;
                outfile << NewLine <<endl;
                outfile.close();
            }
        } else {
            cout<<RED<<BOLD<<"Request is recalled."<<RESET<<endl;
        }
    }
};

#endif
