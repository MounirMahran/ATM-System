#include <iostream>
#include<iomanip>
#include"ReadInputsLib.h";
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#pragma warning(disable:4996)
using namespace std;

void ATMSystem();

void Login();

const string ClientsFileName = "Clients.txt";

struct stBankClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance = 0;
	bool ToDelete = false;
	bool ToUpdate = false;
};

stBankClient CurrentClient;

enum enATMMenu {
	QckWithdraw = 1, NrmlWithdraw = 2, Depst = 3, ChkBalance = 4, LogOut = 5
};

enum enQuickWithdrawAmounts {
	Twenty = 1, Fifty = 2, OneHundred = 3, TwoHundred = 4, FourHundred = 5, SixHundred = 6, EightHundred = 7,
	OneThousand = 8
};

void AddDataLineToFile(string FileName, string DataLine) {
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open()) {
		MyFile << DataLine << endl;
		MyFile.close();
	}
}

string ConvertRecordToLine(stBankClient Client1, string Del = "#//#") {
	string Record = "";

	Record += Client1.AccountNumber;
	Record += Del;
	Record += Client1.PinCode;
	Record += Del;
	Record += Client1.Name;
	Record += Del;
	Record += Client1.Phone;
	Record += Del;
	Record += to_string(Client1.AccountBalance);

	return Record;


}

stBankClient ConvertLineToRecord(string S1, string Del = "#//#") {
	short Pos = S1.find(Del);
	stBankClient Client1;
	string sWord;


	sWord = S1.substr(0, Pos);
	S1.erase(0, Pos + Del.length());
	Client1.AccountNumber = sWord;
	Pos = S1.find(Del);


	sWord = S1.substr(0, Pos);
	S1.erase(0, Pos + Del.length());
	Client1.PinCode = sWord;
	Pos = S1.find(Del);

	sWord = S1.substr(0, Pos);
	S1.erase(0, Pos + Del.length());
	Client1.Name = sWord;
	Pos = S1.find(Del);

	sWord = S1.substr(0, Pos);
	S1.erase(0, Pos + Del.length());
	Client1.Phone = sWord;

	Client1.AccountBalance = stod(S1);


	return Client1;
}

vector <stBankClient> ReadClientsFromFile(string FileName) {
	vector <stBankClient> vClients;

	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {
		string Line;
		stBankClient Client;
		while (getline(MyFile, Line)) {
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}

		MyFile.close();

	}

	return vClients;
}

vector <stBankClient> vClients = ReadClientsFromFile(ClientsFileName);

bool IsAccount(string AccountNumber, string PinCode, stBankClient& Client, vector <stBankClient> vClients) {

	for (stBankClient& C : vClients) {
		if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

void SaveVectorToFile(string FileName, vector <stBankClient> vClients) {
	fstream MyFile;
	string Line;

	MyFile.open(FileName, ios::out);
	if (MyFile.is_open()) {
		for (stBankClient& Client : vClients) {
			Line = ConvertRecordToLine(Client);
			MyFile << Line << endl;
		}

		MyFile.close();
	}
}

void ATMMainMenuScreen() {
	system("cls");
	cout << "===============================================" << endl;
	cout << "                Main Menu Screen               " << endl;
	cout << "===============================================" << endl;

	cout << "\t[1] Quick Withdraw." << endl;
	cout << "\t[2] Normal Withdraw." << endl;
	cout << "\t[3] Deposit." << endl;
	cout << "\t[4] Check Balance." << endl;
	cout << "\t[5] Logout." << endl;

	cout << "===============================================" << endl;
}

void Withdraw() {
	double Amount;
	system("cls");

	cout << "===============================================" << endl;
	cout << "             Normal Withdraw Screen            " << endl;
	cout << "===============================================" << endl;

	do {
		cout << "Please enter amount you want to withdraw, only multiple of 5's" << endl;
		cin >> Amount;
	} while ((int)Amount % 5 != 0);

	char Dep = 'N';
	cout << "Are you sure you want to withdraw: $" << Amount << " from " << CurrentClient.AccountNumber << endl;
	cin >> Dep;
	if (toupper(Dep) == 'Y') {
		for (stBankClient& Client : vClients) {
			if (Client.AccountNumber == CurrentClient.AccountNumber) {
				if (Client.AccountBalance >= Amount) {
					Client.AccountBalance -= Amount;
					SaveVectorToFile(ClientsFileName, vClients);
					CurrentClient.AccountBalance -= Amount;
					cout << "Amount of: $" << Amount << " has been withdrawed from " << Client.Name << " Successfully" << endl;
					cout << "You balance is: " << CurrentClient.AccountBalance << endl;

				}
				else {
					cout << "Failed, Please pick an amount below: " << Client.AccountBalance << endl;
				}
			}
		}
	}
	else return;
}

short TranslateAmountQuickWithdraw(short Choice) {
	switch (Choice)
	{
	case enQuickWithdrawAmounts::Twenty:
		return 20;
	case enQuickWithdrawAmounts::Fifty:
		return 50;
	case enQuickWithdrawAmounts::OneHundred:
		return 100;
	case enQuickWithdrawAmounts::TwoHundred:
		return 200;
	case enQuickWithdrawAmounts::FourHundred:
		return 400;
	case enQuickWithdrawAmounts::SixHundred:
		return 600;
	case enQuickWithdrawAmounts::EightHundred:
		return 800;
	case enQuickWithdrawAmounts::OneThousand:
		return 1000;
	}
}

void PerformQuickWithdraw(short Amount) {
	char Dep = 'N';
	cout << "Are you sure you want to withdraw: $" << Amount << " from " << CurrentClient.AccountNumber << endl;
	cin >> Dep;
	if (toupper(Dep) == 'Y') {
		for (stBankClient& Client : vClients) {
			if (Client.AccountNumber == CurrentClient.AccountNumber) {
				if (Client.AccountBalance >= Amount) {
					Client.AccountBalance -= Amount;
					SaveVectorToFile(ClientsFileName, vClients);
					CurrentClient.AccountBalance -= Amount;
					cout << "Amount of: $" << Amount << " has been withdrawed from " << Client.Name << " Successfully" << endl;
				}
				else {
					cout << "Failed, Please pick an amount below: " << Client.AccountBalance << endl;
				}
			}
		}
	}
}

void QuickWithdrawScreen() {
	system("cls");
	cout << "===============================================" << endl;
	cout << "             Quick Withdraw Screen             " << endl;
	cout << "===============================================" << endl;

	cout << "\t[1] 20 \t\t\t[2]50" << endl;
	cout << "\t[3] 100 \t\t[4]200" << endl;
	cout << "\t[5] 400 \t\t[6]600" << endl;
	cout << "\t[7] 800 \t\t[8]1000" << endl;
	cout << "\t[9] Exit" << endl;

	cout << "You balance is: " << CurrentClient.AccountBalance << endl;

	short Choice = ReadInput::ReadNumInRange(1, 9, "Please choose the amount [1] -> [8] or [9] to get back to main menu");

	if (Choice == 9) ATMSystem();
	else PerformQuickWithdraw(TranslateAmountQuickWithdraw(Choice));

}

void Deposit() {
	system("cls");
	cout << "===============================================" << endl;
	cout << "                 Deposit Screen                " << endl;
	cout << "===============================================" << endl;
	double Amount;
	cout << "Please enter amount you want to deposit" << endl;
	cin >> Amount;
	char Dep = 'N';
	cout << "Are you sure you want to deposit: $" << Amount << " to " << CurrentClient.AccountNumber << endl;
	cin >> Dep;
	if (toupper(Dep) == 'Y') {
		for (stBankClient& Client : vClients) {
			if (Client.AccountNumber == CurrentClient.AccountNumber) {
				Client.AccountBalance += Amount;
				SaveVectorToFile(ClientsFileName, vClients);
				CurrentClient.AccountBalance += Amount;
				cout << "Amount of: $" << Amount << " has been deposited to " << Client.Name << " Successfully" << endl;
				cout << "You balance is: " << CurrentClient.AccountBalance << endl;
			}
		}
	}
	else return;

}

void CheckBalance() {
	system("cls");
	cout << "===============================================" << endl;
	cout << "             Check Balance Screen              " << endl;
	cout << "===============================================" << endl << endl;

	cout << "Your Balance is: " << CurrentClient.AccountBalance << endl;
}

void PerformChoice(short Choice) {
	switch (Choice)
	{
	case enATMMenu::QckWithdraw:
		QuickWithdrawScreen();
		system("pause");
		ATMSystem();
	case enATMMenu::NrmlWithdraw:
		Withdraw();
		system("pause");
		ATMSystem();
	case enATMMenu::Depst:
		Deposit();
		system("pause");
		ATMSystem();
	case enATMMenu::ChkBalance:
		CheckBalance();
		system("pause");
		ATMSystem();
	case enATMMenu::LogOut:
		Login();
	}
}

void ATMSystem() {
	ATMMainMenuScreen();

	short Choice = ReadInput::ReadNumInRange(1, 5, "Please Choose what to do [1] -> [5]");
	PerformChoice(Choice);
}

void Login() {
	system("cls");
	cout << "===============================================" << endl;
	cout << "                ATM Login Screen               " << endl;
	cout << "===============================================" << endl;
	cout << endl;
	string AccountNum = ReadInput::ReadString("Please enter the account number");
	string PinCode = ReadInput::ReadString("Please enter the pin code");

	if (IsAccount(AccountNum, PinCode, CurrentClient, vClients)) {
		ATMSystem();
	}
	else {
		cout << "Sorry, Account Can't be found" << endl;
		cout << "Enter any key to re-enter your account number and pincode" << endl;
		system("pause");
		Login();
	}
}

int main() {

	Login();



	system("pause");
	return 0;
}