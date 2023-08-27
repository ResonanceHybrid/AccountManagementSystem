#include <iostream>
#include <fstream>
#include <string>

// AccountManagementSystem 
//Sohan Mehta

using namespace std;

class Account {
public:
    int accountNumber;
    string lastName;
    string firstName;
    double totalBalance;

    Account() : accountNumber(0), lastName(""), firstName(""), totalBalance(0.0) {}
    Account(int accNum, const string& lName, const string& fName, double balance)
        : accountNumber(accNum), lastName(lName), firstName(fName), totalBalance(balance) {}
};

void writeAccountToFile(const Account& account, int recordNumber) {
    ofstream outFile("accounts.dat", ios::binary | ios::in | ios::out);

    if (!outFile) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    outFile.seekp(recordNumber * sizeof(Account));
    outFile.write(reinterpret_cast<const char*>(&account), sizeof(Account));
}

void readAccountFromFile(Account& account, int recordNumber) {
    ifstream inFile("accounts.dat", ios::binary);

    if (!inFile) {
        cout << "Error opening file for reading!" << endl;
        return;
    }

    inFile.seekg(recordNumber * sizeof(Account));
    inFile.read(reinterpret_cast<char*>(&account), sizeof(Account));
}

void displayAccount(const Account& account) {
    cout << "Account Number: " << account.accountNumber << endl;
    cout << "Last Name: " << account.lastName << endl;
    cout << "First Name: " << account.firstName << endl;
    cout << "Total Balance: " << account.totalBalance << endl;
    cout << "----------------------------------" << endl;
}

int main() {
    int choice;
    int accountNumber;
    Account account;

    do {
        cout << "1. Add Account" << endl;
        cout << "2. Update Account" << endl;
        cout << "3. Delete Account" << endl;
        cout << "4. Display Account" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter Account Number: ";
                cin >> account.accountNumber;
                cout << "Enter Last Name: ";
                cin >> account.lastName;
                cout << "Enter First Name: ";
                cin >> account.firstName;
                cout << "Enter Total Balance: ";
                cin >> account.totalBalance;

                writeAccountToFile(account, account.accountNumber);
                break;
            }
            case 2: {
                cout << "Enter Account Number to Update: ";
                cin >> accountNumber;

                readAccountFromFile(account, accountNumber);
                if (account.accountNumber != 0) {
                    cout << "Enter New Total Balance: ";
                    cin >> account.totalBalance;

                    writeAccountToFile(account, accountNumber);
                } else {
                    cout << "Account not found!" << endl;
                }
                break;
            }
            case 3: {
                cout << "Enter Account Number to Delete: ";
                cin >> accountNumber;

                Account emptyAccount;
                writeAccountToFile(emptyAccount, accountNumber);
                cout << "Account deleted." << endl;
                break;
            }
            case 4: {
                cout << "Enter Account Number to Display: ";
                cin >> accountNumber;

                readAccountFromFile(account, accountNumber);
                if (account.accountNumber != 0) {
                    displayAccount(account);
                } else {
                    cout << "Account not found!" << endl;
                }
                break;
            }
            case 5:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
