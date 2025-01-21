#include "main.hpp"

int main(){

//Software Upper Title
cout << MOVE_CURSOR(1, 0) << CLEAR_SCREEN;
cout << YELLOW << BOLD << UNDERLINE << "ELECTRONIC COMPONENT DATABSE FOR PPKEE STOCKLIST" << RESET << endl;
cout << ITALIC << "Press ctrl+C to Exit!"<< RESET << endl;
cout<<endl;

//Declaration of structure
    userData Data;
    userOperationBORROW Borrow;
    userOperationRETURN Return;
    itemData item;
    
//Boolean of Page
    bool ProgramMainPage = true;
    bool LogIn = false;
    bool InBorrow = false;
    bool InReturn = false;
    bool InAdmin = false;

//Porgram Start
    while(ProgramMainPage){

//Log in page
        int LogInTrialCount = 3;
        string Email,password;
        bool checkEmailPasswordValidity = false;
        bool checkIfAdmin = false;
        do {
            cout << MOVE_CURSOR(4, 0) << CLEAR_TO_END;
            cout << setw(19) << left << "Enter Your Email" << " > " << endl;
            cout << setw(19) << left << "Enter Your Password" << " > " << MOVE_CURSOR(4, 23);
            getline(cin, Email);
            cout << MOVE_CURSOR(5, 23);
            getline(cin, password);

            checkEmailPasswordValidity = Data.find_userEmail(Email, password);
            if (!checkEmailPasswordValidity){
                checkIfAdmin = Data.find_adminEmail(Email, password);
            }

            if (!checkEmailPasswordValidity && !checkIfAdmin) {
                LogInTrialCount--;
                cout << endl;
                cout << RED << BOLD << "Log In failed. Wrong Email or Password Entered. Please Try Again." << RESET << endl;
                cout << RED << BOLD << "You have " << LogInTrialCount << " chance(s) left." << RESET << endl;
                this_thread::sleep_for(chrono::duration<double>(1));
            }

            if (LogInTrialCount == 0) {
                cout << RED << BOLD << "The Log In Session has been terminated due to multiple failed trials." << RESET << endl;
                cout << RED << BOLD << "The software will now exit." << RESET << endl;
                return 0;
            }

        } while (!checkEmailPasswordValidity && !checkIfAdmin && LogInTrialCount > 0);

        if (checkEmailPasswordValidity || checkIfAdmin) {
            cout << GREEN << BOLD <<"\nLog In Successful!" << RESET << endl;
            LogIn = true;
            if (checkIfAdmin) {
                cout << "\nWelcome, " << Data.giveUserName() << "!" << endl;
                cout << BLUE <<BOLD << "Loading to admin pages" << RESET;
                for (int i = 0; i < 5; i++) {
                    this_thread::sleep_for(chrono::duration<double>(0.5));
                    cout << BLUE << BOLD << "." << RESET;
                }
            } else {
                cout << "\nWelcome, " << Data.giveUserName() << "!" << endl;
                cout << BLUE <<BOLD << "Loading to user pages" << RESET;
                for (int i = 0; i < 4; i++) {
                    this_thread::sleep_for(chrono::duration<double>(0.5));
                    cout << BLUE << BOLD << "." << RESET;
                }
            }
        }

        while(LogIn){
            cout << MOVE_CURSOR(4,0) << CLEAR_TO_END;
            Data.statusCheck();

//Transit To Borrow, Return and Admin Page (User)
            cout<< BOLD << YELLOW << "MAIN PAGE" << RESET << endl;
            cout << endl;       
            cout<<"Please choose the operation:"<<endl;
            cout<<"1 - Borrow Item"<<endl;
            cout<<"2 - Return Item"<<endl;
            if(checkIfAdmin){
                cout<< BLUE << BOLD <<"3 - Admin Page" << RESET <<endl;
            }
            cout<<"Input 0 to Log Out > ";
            int BorrowOrReturn;
            cin>>BorrowOrReturn;


//Borrow (Uses userData class & item Class)
            if(BorrowOrReturn==1){
                InBorrow = true;
                int itemChoosenInt;
                string itemChoosen;
                bool failedborrowLoop = false;
                do{
                    do{    
                        cout<<MOVE_CURSOR(9,0)<<CLEAR_TO_END;
                        cout<<endl;
                        cout<< BOLD << YELLOW << "BORROW ITEM" << RESET << endl;
                        cout<<endl;
                        item.itemList();
                        cout<<"(Enter 0 to Exit the Page)"<<endl;
                        cout<<"Enter The Item ID that you wish to borrow > ";
                        cin>>itemChoosenInt;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore();
                            cout << RED << BOLD << "Error, please enter a number." << RESET << endl;
                            this_thread::sleep_for(chrono::duration<double>(1));
                        continue;
                        }
                        itemChoosen = to_string(itemChoosenInt);
                        if(itemChoosen=="0") {
                            InBorrow = false;
                            break;
                        }
                        failedborrowLoop = item.itemFind(itemChoosen);
                        this_thread::sleep_for(chrono::duration<double>(1));
                    } while (!failedborrowLoop);
                    if(itemChoosen!="0"){
                        Borrow.userDataWRITE(Data.giveUserID(),itemChoosen);
                    } else {
                        InBorrow = false;
                        break;
                    }
                } while (InBorrow);
            } 

//Return (Uses userData Class & itemClass)
            else if(BorrowOrReturn==2){
                InReturn = true;
                bool NothingToReturn = false;
                do{
                    cout<<MOVE_CURSOR(9,0)<<CLEAR_TO_END;
                    cout<<endl;
                    cout<< BOLD << YELLOW << "RETURN ITEM" << RESET << endl;
                    cout << endl;
                    Return.displayItemBorrowed(Data.giveUserID(),Data.giveUserName());
                    NothingToReturn = Return.NothingToReturn();
                    int returnedItem;
                    if(!NothingToReturn){
                        cout<<"(Enter 0 to Exit the Page)"<<endl;
                        cout<<"Enter the item you wish to return according to the item number displayed at left > ";
                        cin>>returnedItem;
                    } else {
                        cout<<"Enter 0 to Exit the Page > ";
                        cin>>returnedItem;
                    }
                    
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore();
                        cout << RED << BOLD << "Error, please enter a number." << RESET << endl;
                        this_thread::sleep_for(chrono::duration<double>(1));
                    continue;
                    }
                    if(returnedItem==0) {
                            InReturn = false;
                            break;
                        }
                    Return.deleteReturnItem(returnedItem);
                }while (InReturn);
            }

//Admin
            else if(BorrowOrReturn==3 && checkIfAdmin){
                admin admin;
                InAdmin = true;
                bool CheckIfAdmin = false;
                bool PenaltyList = false;
                bool ItemList = false;
                bool PurchaseRequest = false;
                int ExitInput;
                do{
                    cout<<MOVE_CURSOR(9,0)<<CLEAR_TO_END;
                    cout<<endl;
                    cout<< BOLD << YELLOW << "ADMIN FUNCTION" << RESET << endl;
                    cout << endl;
                    cout<<"Please choose the operation:"<<endl;
                    cout<<"1 - View Penalty List"<<endl;
                    cout<<"2 - View Stock List"<<endl;
                    cout<<"3 - Make Purchase Request"<<endl;
                    cout<<"(Enter 0 to Exit the Page)"<<endl;
                    cout<<"Enter the Next Operation > "; 
                    int adminPageOperation;
                    cin>>adminPageOperation;
                    if(adminPageOperation==1){
                        PenaltyList=true;
                        do{
                            cout<<MOVE_CURSOR(12,0)<<CLEAR_TO_END;
                            cout<< BOLD << YELLOW << "Penalty List:" << RESET << endl;
                            cout << endl;
                            admin.displayPenaltyList();
                            cout<<"\nInput 0 to Exit > ";
                            cin>>ExitInput;
                            if(ExitInput==0){
                                PenaltyList = false;
                                break;
                            } else {
                                cout<<RED<<BOLD<<"Invalid Input. Please try again."<<RESET<<endl;
                                this_thread::sleep_for(chrono::duration<double>(1));
                            }
                        } while (PenaltyList);
                    } else if(adminPageOperation==2){
                        ItemList=true;
                        do{
                            cout<<MOVE_CURSOR(12,0)<<CLEAR_TO_END;
                            cout<< BOLD << YELLOW << "Available Item List:" << RESET << endl;
                            cout << endl;
                            item.itemList();
                            cout<<"\nInput 0 to Exit > ";
                            cin>>ExitInput;
                            if(ExitInput==0){
                                ItemList = false;
                                break;
                            } else {
                                cout<<RED<<BOLD<<"Invalid Input. Please try again."<<RESET<<endl;
                                this_thread::sleep_for(chrono::duration<double>(1));
                            }
                        } while (ItemList);
                    } else if(adminPageOperation==3){
                        PurchaseRequest=true;
                        do{
                            cout<<MOVE_CURSOR(12,0)<<CLEAR_TO_END;
                            cout<< BOLD << YELLOW << "Enter New Purchase Request:" << RESET << endl;
                            cout << endl;
                            admin.purchaseRequest(Data.giveUserID());
                            cout<<endl;
                            cout<<"Input the following number for next course of action > "<<endl;
                            cout<<"0 - To exit this page."<<endl;
                            cout<<"1 - To make a New Request."<<endl;
                            cout << MOVE_CURSOR(27,56);
                            cin>>ExitInput;
                            if(ExitInput==0){
                                ItemList = false;
                                break;
                            } else if(ExitInput==1){
                                cout<<MOVE_CURSOR(28,0)<<CLEAR_TO_END;
                                cout<<BLUE<<BOLD<<"Please Wait. Processing"<<RESET;
                                for(int i=0;i<4;i++){
                                    this_thread::sleep_for(chrono::duration<double>(0.5));
                                    cout<<BLUE<<BOLD<<"."<<RESET;
                                }
                            } else {
                                cout<<MOVE_CURSOR(28,0)<<CLEAR_TO_END;
                                cout<<RED<<BOLD<<"Invalid Input. Exiting The page by default."<<RESET<<endl;
                                this_thread::sleep_for(chrono::duration<double>(0.5));
                                break;
                            }
                        } while (PurchaseRequest);
                    } else if(adminPageOperation==0){
                        InAdmin = false;
                        break;
                    } else {
                        cout << RED << BOLD << "\nInvalid Input. Please Try Again." << RESET;
                        this_thread::sleep_for(chrono::duration<double>(1));
                    }
                } while (InAdmin);

//Log Out Function
            } else {
                cout<<MOVE_CURSOR(4,0) <<CLEAR_TO_END;
                cout<<BLUE<<BOLD<<"Loging Out"<<RESET;
                for(int i =0;i<4;i++){
                    cout<<BLUE<<BOLD<<"."<<RESET;
                    this_thread::sleep_for(chrono::duration<double>(0.5));
                }
                LogIn=false;
                cin.ignore(); 
                break;
            }        
        }
    }
}