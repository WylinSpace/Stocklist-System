#ifndef ITEM_CPP
#define ITEM_CPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define BOLD    "\033[1m"
#define RESET   "\033[0m"

using namespace std;

class itemData{
    private:
    string itemID;
    string itemName;
    string itemNumber;
    string filename = "Data/ItemID/item.csv";

    public:
    int lineCalculator() {
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

    void itemList() {
        const int column_1_width = 10;
        const int column_2_width = 20;
        const int column_3_width = 15;
        int lineCount = lineCalculator();
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
        for (int row = 0; row < lineCount; row++) {
            for (int column = 0; column < 3; column++) {
                if(column ==0){
                    cout << left << setw(column_1_width) << tableList[row][column];
                } else if (column==1) {
                    cout << left << setw(column_2_width) << tableList[row][column];
                } else if (column==2) {
                    cout << left << setw(column_3_width) << tableList[row][column];
                }
            }
            cout << endl;
    }
}

    bool itemFind(string requiredItem){
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
                        itemID = cell;
                    }
                    if(column==1){
                        itemName = cell;
                    }
                    if(column==2){
                        itemNumber = cell;
                    }
                    column++;
                }
                if(requiredItem==itemID){
                    itemFound = true;
                    if (borrow()) {
                        updatedContent << itemID << "," << itemName << "," << itemNumber << endl;
                    } else {
                        return false;
                    }
                } else {
                    updatedContent << itemID << "," << itemName << "," << itemNumber << endl;
                }
            }
            infile.close();
        }

            if (itemFound) {
                ofstream outfile(filename);
                if (outfile.is_open()) {
                    outfile << updatedContent.str();
                    outfile.close();
                    cout << BOLD << GREEN << "Item borrowed and quantity updated successfully!\nPlease return it in 14 day(s) EFFECTIVE FROM TODAY!\nYou can borrow the next item by input the next item code." << RESET << endl;
                    return true;
                } else {
                    cerr << BOLD << RED << "Error: Unable to open file for writing!" << RESET << endl;
                    return false;
                }
            return false;
        } else {
            cerr << BOLD << RED << "Error, Item not found!"<< RESET << endl;
            return false;
        }
        cerr << BOLD << RED << "Error, Item not found!" << RESET;
        return false;
    }

    bool borrow(){
        int quantity = stoi(itemNumber);
        if (quantity > 0) {
            quantity -= 1;
            itemNumber = to_string(quantity);
            return true;   
        } else {
            cerr << "Error: Item quantity is already 0!" << endl;
            return false;
        }    
    }
};

#endif