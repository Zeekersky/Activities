#include<iostream>


using namespace std;

class bankaccount {
private:
	string name;
	string accnumber;
	string acctype;
	float bal;

public:
bankaccount() {
	name = "";
	accnumber = "";
	acctype = "";
	bal = 0.0;	
}

void createaccount(string iname, string iaccnumber, string iacctype){
	name = iname;
	accnumber = iaccnumber;
	acctype = iacctype;
}

void deposit(float amount){
	bal = bal + amount;
	cout<<"The Final Amount: "<<bal;
}

void withdraw(float amount){
	if(bal-amount < 0)
		cout<< "Insufficient Balance";
	else
	{
		bal = bal-amount;
		cout<< "Balance After Withdrawn: "<< bal;
	}
}

void display(){
	cout<< "Account Holder Name: " << name;
	cout<< "\nAccount Number: " << accnumber;
	cout<< "\nAccount Type: " << acctype;
	cout<< "\nBalance: " << bal<<"\n";
}

};

int main()
{

bankaccount b;
int ch;
string accname, accnumber, acctype; 

while(true)
{

cout<<"Enter yout choice: ";
cout<< "\n1. Create an Account ";
cout<<"\n2. Deposit Some Ammount ";
cout<<"\n3. Withdraw some amount ";
cout<<"\n4. Display Account Details ";
cout<<"\n5. Exit\n";
cin>> ch;


switch(ch)
{
case 1:{ 
	cout<< "\nEnter Account Details ";
	cout<<"\nEnter Account Holder Name: ";
	cin.ignore();
	getline(cin, accname);
	cout<<"\nEnter Account Number: ";
	getline(cin, accnumber);
	cout<<"\nEnter Account Type: ";
	getline(cin, acctype);
	
	b.createaccount(accname, accnumber, acctype);
	break;
}

case 2:{
	int amount;
	cout<<"Enter the amount: ";
	cin>> amount;
	b.deposit(amount);
	break;
}

case 3:{
	int amount;
	cout<<"Enter the amount: ";
	cin>>amount;
	b.withdraw(amount);
	break;
}

case 4:{
	b.display();
	break;
}
default: {
	printf("Invalid Choice\n");
	break;
	
}

case 5:{
	printf("Exit...");
	return 0;
}
}

}

}
