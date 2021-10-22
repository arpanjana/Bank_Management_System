/*
  Bank management system
  Author: Arpan Jana
  Date: 22 Oct ,2021

*/


#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;


class Account
{
    
    char holderName_[50], accountType_[50],homeAddress_[100];
    long accountNumber_;
    float balanceAmount_;
    
public:
    Account() {}
    void DepositAmount(ofstream & TransactionDb);
    void WithdrawAmount(ofstream &TransactionDb);
    void OpenAccount(ofstream &CustomerDb); // Here the address of the filepointer should be passed
    void ShowAccount(ifstream &readCustomerDb); // Here the address of the filepointer should be passed
    int SearchAccount(int);
    void ShowIndividualAccount();

    
};


void Account::OpenAccount(ofstream &CustomerDb)
{
  // CustomerDb is a textFile in which we will insert the records
    cout << "Enter Name: ";
    cin.get();
    cin.getline(holderName_, 50);
    CustomerDb<<holderName_<<"\t";
    cout<< "Enter your address  ";

    cin.getline(homeAddress_,99);
    CustomerDb<<homeAddress_<<"\t";
    cout << "Enter Account Type (Saving/current) :";
    cin.getline(accountType_,50);
    CustomerDb<<accountType_<<"\t";
    cout << "Enter Account Number: ";
    cin >> accountNumber_;
    CustomerDb<<accountNumber_<<"\t";
    cout << "Enter Balance: ";
    cin >> balanceAmount_;
    CustomerDb<<balanceAmount_<<"\t";
    CustomerDb<<"\n";

}


void Account::ShowAccount(ifstream &readCustomerDb)
{


   while(readCustomerDb)
    {
      readCustomerDb>>holderName_;
      readCustomerDb>>homeAddress_;
      readCustomerDb>>accountType_;
      readCustomerDb>>balanceAmount_;


      cout << "Name: " << holderName_ << endl;
      cout << "Account Type: " << accountType_ << endl;
      cout << "Balance: " << balanceAmount_ << endl;
      cout << "Address: "<<homeAddress_<<endl; 
    }

}
void Account::ShowIndividualAccount()
{
    cout << "Account Type: " << accountType_ << endl;
    cout << "Name: " << holderName_ << endl;
    cout << "Balance: " << balanceAmount_ << endl;
}

void Account::DepositAmount(ofstream & TransactionDb)
{

    float amt;
    cout << "Enter amount you want to deposit: ";
    cin >> amt;
    TransactionDb<<amt<<"\n";

    balanceAmount_ = balanceAmount_ + amt;
    cout << "\nAmount successfully deposited.\n";
}


void Account::WithdrawAmount(ofstream & TransactionDb)
{
    float amt;
    cout << "Enter Amount you want to withdraw: ";
    cin >> amt;
    TransactionDb<<amt<<"\n";

    if (amt <= balanceAmount_)
    {
        balanceAmount_ = balanceAmount_ - amt;
        cout << "\nAmount successfully withdrawn.\n";
    }
    else
    {
        cout << "\nERROR: Insufficient Balance!!\nYour balance is not sufficient for this request.\n";
        cout << "Please add money before proceeding." << endl;
    }
}


int Account::SearchAccount(int a)
{
    if (accountNumber_ == a)
        return 1;
    return 0;
}



int main()
{
  
    string CustomerFile = "customerFiles.txt";
    ofstream CustomerDb(CustomerFile);
    ifstream readCustomerDb(CustomerFile);

    int size=1;

    string TransactionFile = "transactionFiles.txt";
    ofstream TransactionDb(TransactionFile);


    Account b[100];

  
    
    int found = 0, choice, i;
    long accNo;

    do
    {
        cout << "\n\t\t\tWelcome to a generic Bank\n\nChoose  to perform:"<< endl;
        cout << "1:Open new account\n2:Deposit amount\n3:Withdraw amount\n4:Check Balance\n5:To View all the Bank account holders\n6:Last Account Added\n7:Exit" << endl;

        // user input
        cout << "\nPlease input your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            
                b[size++].OpenAccount(CustomerDb);
                cout << "\nAccount created successfully.\n";

                break;

            case 2:
                
                cout << "Please enter your VALID account number ";
                cin >> accNo;

                for (i = 0; i < size; i++)
                {
                    found = b[i].SearchAccount(accNo);
                    if (found)
                    {
                        TransactionDb<<"Account No. "<<accNo<<" deposited ";
                        b[i].DepositAmount(TransactionDb);
                        break;
                    }
                }
                if (!found)
                    cout << "ERROR: Account Not Found!!" << endl;

                break;

            case 3:
      
                cout << "Enter your account number: ";
                cin >> accNo;

                for (i = 0; i < size; i++)
                {
                    found = b[i].SearchAccount(accNo);
                    if (found)
                    { 
                        TransactionDb<<"Account No. "<<accNo<<" withdraws ";
                        b[i].WithdrawAmount(TransactionDb);
                        break;
                    }
                }
                if (!found)
                    cout << "ERROR: Account Not Found!!" << endl;

                break;

            case 4:
            
                cout << "Please enter your account number: ";
                cin >> accNo;

                for (i = 0; i < size; i++)
                {
                    found = b[i].SearchAccount(accNo);
                    if (found)
                    {
                        cout << endl;
                        b[i].ShowIndividualAccount();
                        break;
                    }
                }
                if (!found)
                    cout << "ERROR: Account Not Found!!" << endl;

                break;

            
            case 5:
                cout<<"\nThe list of bank account holders:\n";
                  for(int i=0;i < size; i++)
                  {
                    cout<<"\n";
                    b[i].ShowAccount(readCustomerDb);
                    cout<<"\n";
                  }
                  break;
            case 6:
                cout<<"\nLast Account Added:\n";
                b[size-1].ShowIndividualAccount();
                cout<<'\n';
                break;

            case 7:
                
                cout << "\nThank you for using Our bank service.\nHave a nice day!\n"
                    << endl;

                break;

            default:
                cout << "Please Enter a valid input" << endl;
        }
    } while (choice != 7);
  // closing the files
  TransactionDb.close();
  CustomerDb.close();

    return 0;
}
