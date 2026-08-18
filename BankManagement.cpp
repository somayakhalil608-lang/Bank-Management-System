#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <iomanip>
using namespace std;


const string fileName = "Koko.txt";

void ShowMainMenue();
void TransactionList();
 
struct stLineInfo {
    string name;
    string accountNum;
    string pinCode;
    string phone;
    double accountBalance;

};


vector <string> spliteString(string line, string delim) {

    int pos;
    string subW = " ";
    vector <string> VSubWords;

    while (line.find(delim) != std::string::npos) {

        pos = line.find(delim);

        subW = line.substr(0, pos);

        if (subW != "") {
            VSubWords.push_back(subW);
        }

        line.erase(0, pos + delim.length());

    }

    if (line != "") {
        VSubWords.push_back(line);
    }

    return VSubWords;

}


stLineInfo understandVec(vector<string> line) {

    stLineInfo i;

    i.name = line[0];
    i.accountNum = line[1];
    i.pinCode = line[2];
    i.phone = line[3];
    i.accountBalance = stod(line[4]);

    return i;

}


string readAccountNum() {

    string accountNum;

    cout << "Enter Account Num \n";
    cin >> accountNum;
    return accountNum;
}



string structToRecord(stLineInfo i, string delim = "###") {

    string s = "";
    s += i.name + delim;
    s += i.accountNum + delim;
    s += i.pinCode + delim;
    s += i.phone + delim;
    s += to_string(i.accountBalance);
    return s;
}



vector <stLineInfo> readMode() {


    fstream myFile;
    string lineFromFile;
    vector <stLineInfo>BigVector;


    myFile.open(fileName, ios::in);
    if (myFile.is_open()) {

        while (getline(myFile, lineFromFile)) {
            vector <string> Vecline = spliteString(lineFromFile, "###");

            stLineInfo i = understandVec(Vecline);
            BigVector.push_back(i);

        }
        myFile.close();
    }

    return BigVector;

}



void writeMode(vector <stLineInfo> vClients) {


    fstream MyFile;
    MyFile.open(fileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (stLineInfo C : vClients)
        {


            //we only write records that are not marked for delete.  
            DataLine = structToRecord(C);
            MyFile << DataLine << endl;

        }

        MyFile.close();
    }
}


void printStruct(stLineInfo s) {


    cout << left << setw(10) << s.name << "|";
    cout << left << setw(18) << s.accountNum << "|";
    cout << left << setw(10) << s.pinCode << "|";
    cout << left << setw(15) << s.phone << "|";
    cout << left << setw(18) << s.accountBalance << "|" << endl;


}


void printAllInfo() {


    vector <stLineInfo> i = readMode();

    if (i.size() == 0) {
        cout << "\t\t\t\tNo Clients Available In the System!";
    }
    else {
        cout << "Clients (" << i.size() << ")" << "Information: \n";


        cout << "------------------------------------------------------------------------------------------\n";

        cout << left << setw(10) << "Name"
            << "|" << left << setw(18) << "Account Number"
            << "|" << left << setw(10) << "PIN code"
            << "|" << left << setw(15) << "Phone"
            << "|" << left << setw(18) << "Account Balance"
            << "|" << endl;
        cout << "------------------------------------------------------------------------------------------\n";

        for (stLineInfo& s : i) {

            printStruct(s);
        }

        cout << "------------------------------------------------------------------------------------------\n";

    }
}


bool exitAccountNum(string accountNum) {


    fstream myFile;
    string line;
    myFile.open(fileName, ios::in);

    if (myFile.is_open()) {

        while (getline(myFile, line)) {

            stLineInfo s = understandVec(spliteString(line, "###"));
            if (s.accountNum == accountNum) {

                myFile.close();
                return true;
            }


        }

        myFile.close();

    }

    return false;


}


bool FoundAccountNum(vector <stLineInfo> &s, string accountNum, stLineInfo& G) {



    for (stLineInfo& i : s) {

        if (accountNum == i.accountNum) {
            G = i;
            return true;
        }
    }

    return false;

}


stLineInfo ReadNewClient() {

    stLineInfo i;


    cout << "Enter Account Number \n";
    getline(cin >> ws, i.accountNum);


    while (exitAccountNum(i.accountNum)) {
        cout << "Account Num " << i.accountNum << "Already exists ,Enter another \n";
        getline(cin >> ws, i.accountNum);
    }

    cout << "Enter Name \n";
    getline(cin >> ws, i.name);



    cout << "Enter PIN code \n";
    getline(cin, i.pinCode);


    cout << "Enter Phone \n";
    getline(cin, i.phone);


    cout << "Enter Account Balance \n";
    cin >> i.accountBalance;


    return i;

}


stLineInfo stUpdateClient(string accountNum) {

    stLineInfo i;

    cout << "Enter Name \n";
    getline(cin >> ws, i.name);

    i.accountNum = accountNum;


    cout << "Enter PIN code \n";
    getline(cin, i.pinCode);


    cout << "Enter Phone \n";
    getline(cin, i.phone);


    cout << "Enter Account Balance \n";
    cin >> i.accountBalance;


    return i;

}


void AddClientInFile(string Line) {



    fstream myFile;
    myFile.open(fileName, ios::out | ios::app);




    if (myFile.is_open()) {

        myFile << Line << endl;

    }

}


void AddClient() {
     
    stLineInfo clientInfo = ReadNewClient();

    string Line = structToRecord(clientInfo, "###");

    AddClientInFile(Line);

}


void addClients() {

    char add = 'y';


    while (add == 'y' || add == 'Y') {

        AddClient();
        cout << "Do you want to add again Clients ? \n";
        cin >> add;



    }


}



vector <stLineInfo> updateRecord(vector <stLineInfo> originalV, string accountNum) {


    for (stLineInfo& u : originalV) {

        if (u.accountNum == accountNum) {
            u = stUpdateClient(accountNum);
        }
    }
    return originalV;

}


vector <stLineInfo> deleteRecord(vector <stLineInfo> originalV, string accountNum) {


    vector <stLineInfo> NewVec;
    // vector <stLineInfo> originalV=
   //  vector <stLineInfo> originalVec = readMode();

      // if (exitAccountNum(originalV, accountNum, G)) {
    for (stLineInfo& B : originalV) {

        if (B.accountNum != accountNum) {
            NewVec.push_back(B);

        }
    }
    //   }


    return NewVec;
}


void saveDelete(vector <stLineInfo> originalV) {



    vector <stLineInfo> newVec = originalV;

    stLineInfo G;

    char delet;

    char deletAgain = 'y';


    while (deletAgain == 'Y' || deletAgain == 'y') {

        string accountNum = readAccountNum();

        if (FoundAccountNum(newVec, accountNum, G)) {
            cout << "Client Information: \n";

            cout << "-----------------------------------------------------------------\n";
          
            printStruct(G);
            cout << "------------------------------------------------------------------\n";
            cout << "Are you sure Do you want to delete This Record \n";
            cin >> delet;




            if (delet == 'y' || delet == 'Y') {

                newVec = deleteRecord(newVec, accountNum);


                writeMode(newVec);
                cout << "Deleted is Successfly!\n";


            }


        }

        else {
            cout << "Client is not Found \n";
        }

        cout << "Do you want to Delete more clients ? \n";
        cin >> deletAgain;

    }

}


void DeleteScreen() {

    cout << "-------------------------------------\n";
    cout << "         Delete Screen \n";
    cout << "-------------------------------------\n";

    saveDelete(readMode());
}


void saveUpdate(vector <stLineInfo> originalV) {


    vector <stLineInfo>newVec;
    newVec = originalV;
    stLineInfo G;


    char update;

    char updateAgain = 'y';


    while (updateAgain == 'Y' || updateAgain == 'y') {



        string accountNum = readAccountNum();

        if (FoundAccountNum(newVec, accountNum, G)) {
            cout << "Client Information" << endl;

            cout << "---------------------------------------------------------------------------------\n";
      
            printStruct(G);

            cout << "----------------------------------------------------------------------------------\n";

            cout << "Are you sure Do you want to Update This Record \n";
            cin >> update;

            if (update == 'y' || update == 'Y') {


                newVec = updateRecord(newVec, accountNum);


                writeMode(newVec);
                cout << "Updated is Successfly!\n";


                //   deleteRecord(G);

            }


        }

        else {
            cout << "Client is not Found \n";
        }

        cout << "Do you want to Update more clients ? \n";
        cin >> updateAgain;
    }

}


void UpdateScreen() {

    cout << "--------------------------------------\n";
    cout << "          Update Screen \n";
    cout << "---------------------------------------\n";

    saveUpdate(readMode());
}


void findClient() {


    vector <stLineInfo>i = readMode();

    stLineInfo G;
    string  accountNum = readAccountNum();

    if (FoundAccountNum(i, accountNum, G)) {

        cout << "Client is Foound \n";
        cout << "---------------------------------------------------------------------------------------\n";
        printStruct(G);
        cout << "---------------------------------------------------------------------------------------\n";
    }
    else {

        cout << "Client is not Found\n";

    }


}


enum enbankChoise { Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5,Transaction=6, Exit = 7 };


short clientChoise1to7() {

    short  c;

    do {
        cout << "Choose what do you want to do? [1 to 7]\n";
        cin >> c;

    } while (c < 1 || c > 7);

 
    return c;

}


void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();

}


void GoBackToMainMenueT()
{
    cout << "\n\nPress any key to go back to Transaction Menue...";
    system("pause>0");
    TransactionList();
}

enum enTransAction{Deposite=1,Withdraw=2,TotalBalances=3,mainMenue=4};

char Sure() {

    char sure;
    cout << "Are you sure you want perform this transaction? \n";
    cin >> sure;
    return sure;
}


double Deposite1(vector<stLineInfo> &Vec) {

    stLineInfo d;
    double deposite;

   string accountNum = readAccountNum();
    while(!FoundAccountNum(Vec, accountNum, d)) {


        cout << "Client with [" << accountNum << "] does not exist \n";
        accountNum = readAccountNum();
    }
    
    cout << "The Following Are The Client Details: \n";
    cout << "-------------------------------------------------------------------------------\n";
    printStruct(d);
    cout << "-------------------------------------------------------------------------------\n";

    cout << "Please Enter Deposite Amount \n";
    cin >> deposite;
 

    if (toupper(Sure())=='Y') {
        for (stLineInfo& i : Vec) {
            if (i.accountNum == accountNum) {
                i.accountBalance += deposite;
                writeMode(Vec);
                return i.accountBalance;
            }
        }
    }
   
        return d.accountBalance;
    
}


void DepositeScreen() {

    vector<stLineInfo> Vec = readMode();

    cout << "----------------------------------\n";
    cout << "\t\tDeposite Screen\t\t \n";
    cout << "----------------------------------\n";

   double i= Deposite1(Vec);
   //áÇÒã ÈÑÖæ ÇÚÏá Ýí ÇáãáÝ ãÔ ÇáÝíßÊæÑ ÈÓ

   cout << "Current Balance =" << i << endl;
}


double WithDraw(vector<stLineInfo>& Vec) {

    stLineInfo d;
    double withdraw;

    string accountNum = readAccountNum();
    while (!FoundAccountNum(Vec, accountNum, d)) {


        cout << "Client with [" << accountNum << "] does not exist \n";
        accountNum = readAccountNum();
    }

    cout << "The Following Are The Client Details: \n";
    cout << "-------------------------------------------------------------------------------\n";
    printStruct(d);
    cout << "-------------------------------------------------------------------------------\n";

    cout << "Please Enter Withdraw Amount \n";
    cin >> withdraw;

    while (withdraw > d.accountBalance) {

        cout << "Amount Exceeds the balance , you can not with draw up to : " << d.accountBalance << endl;
        cout << "Please Enter another amount \n";
        cin >> withdraw;

    }
     if (toupper(Sure()) == 'Y') {
            for (stLineInfo& i : Vec) {
                if (i.accountNum == accountNum) {
                    i.accountBalance -= withdraw;
                    writeMode(Vec);
                    return i.accountBalance;
                }
            }
        }
    

    return d.accountBalance;

}


void withdrawScreen() {

    vector<stLineInfo> Vec = readMode();

    cout << "----------------------------------\n";
    cout << "\t\tWithdraw Screen\t\t \n";
    cout << "----------------------------------\n";

    double i =  WithDraw(Vec);
  //áÇÒã ÈÑÖæ ÇÚÏá Ýí ÇáãáÝ ãÔ ÇáÝíßÊæÑ ÈÓ

    cout << "Current Balance =" << i << endl;


}


void printBalances(stLineInfo i){


    cout<<"| "<< left << setw(20) << i.accountNum;
    cout<<"| " << left << setw(20) << i.name;
    cout << "| " << left << setw(20) <<i.accountBalance<<endl;

}


double totalBalances(vector<stLineInfo> Vec) {


    double totalBalances=0;

    for (stLineInfo& i : Vec) {

        totalBalances += i.accountBalance;
    }

    return totalBalances;
}


void BalancesScreen() {

    vector<stLineInfo> Vec = readMode();

    cout << "-------------------------------------------------------------\n";
    cout << "| " << left << setw(20) << "Account Number ";
    cout << "| " << left << setw(20) << "Client Nmae";
    cout << "| " << left << setw(10) << "Balance" << endl;
    cout << "-------------------------------------------------------------\n";

    for (stLineInfo& i : Vec) {

        printBalances(i);
    }
    cout<< "-------------------------------------------------------------\n";
   cout<<"Total Balances = " <<totalBalances(Vec)<<endl;


}


short transactionChoise() {

    short c;

    do {
        cout << "Choose what do you want to do? [1 to 4]\n";
        cin >> c;

    } while (c < 1 || c > 4);

 
    return c;

}


void ShowMainMenueTransAction() {

    enTransAction i = ((enTransAction)transactionChoise());

    switch (i)
    {
    case Deposite:
        DepositeScreen();
        GoBackToMainMenueT();
        break;
    case Withdraw:
        withdrawScreen();
        GoBackToMainMenueT();
        break;
    case TotalBalances:
        BalancesScreen();
        GoBackToMainMenueT();
        break;
    case mainMenue:
        ShowMainMenue();
        break;
    /*default:
        break;*/
    }



}


void TransactionList(){

    system("cls");
    cout << "===========================================\n";
    cout << "\t\Transaction Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposite.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Shaw All Balaces.\n";
    cout << "\t[4] Go Back to main menue.\n";

    cout << "===========================================\n";
    ShowMainMenueTransAction();

}


void MenueList()
{


    enbankChoise C = enbankChoise(clientChoise1to7());

    switch (C)
    {
    case Show:
        system("cls");
        printAllInfo();
        GoBackToMainMenue();
        break;


    case Add:
        system("cls");
        addClients();
        GoBackToMainMenue();
        break;

    case Delete:
        system("cls");
        DeleteScreen();
        GoBackToMainMenue();
        break;

    case Update:
        system("cls");
        UpdateScreen();
        GoBackToMainMenue();
        break;

    case Find:
        system("cls");
        findClient();
        GoBackToMainMenue();
        break;

    case Transaction:
        TransactionList();
        break;

    case Exit:
        system("cls");
        printAllInfo();
        GoBackToMainMenue();
       
    }

}


void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transaction.\n";
    cout << "\t[7] Exit.\n";
   
    cout << "===========================================\n";
    MenueList();
}



int main()
{
    ShowMainMenue();
    system("pause>0");



    // writeMode();


}