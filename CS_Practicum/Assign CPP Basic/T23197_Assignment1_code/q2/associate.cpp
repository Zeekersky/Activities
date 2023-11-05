#include<iostream>
#include<vector>

using namespace std;

class associate {

public:
	int id;
	string technology;
	int experienceInYears;

	associate(){
		id = 0;
		experienceInYears = 0;
	}
};

class solution {

public:
	static const int max = 5;
	associate associates[max];
	int n_associate = 0;
	associate* add_associate(int id, const string& technology, int experienceInYears){
	if(n_associate < max) 
		associates[n_associate++] = associate(id, technology, experienceInYears);
	else{
		cout << "Max No. Associates Reached";
		return associates;
	}
	}

	void associatesForGivenTechnology(associate& associate, const string& searchtechnology) {
		cout<<"Matching Associate IDs:" << endl;
		for(int i = 0; i<max; i++)
		{
			associate = associates[i];
			if(caseinsensitive(associate.technology, searchtechnology) && (associate.experienceInYears % 5 == 0))
				cout<< associate.id << endl;
		}

	static bool caseinsensitive(const string& st1, const string& st2){
		if(st1.length() != st.length())
			return false;
		for(int i = 0; i<st.length(); i++)
		{
			if(tolower(st1[i]) != tolower(st2[i])
				return false;
		}
	}
	return true;
	
}

};

int main()
{
	solution sol;

	for(int i = 1; i<= 5; i++)
	{
		int id, experienceInYears;
		string technology;
		cout<<"Enter Associate "<<i<<" details:"<<endl;
		cout<<"ID: ";
		cin>> id;
		cout<<"Technology: ";
		cin.ignore();
		getline(cin, technology);
		cout<<"Experience in years";
		cin>>experienceInYears;

		sol.add_associate(id, technology, experienceInYears);
	}
	string searchtechnology;
	cout<<"Enter the search technology: ";
	cin.ignore();
	getline(cin, searchtechnology);
	sol.associatesForGivenTechnology(sol.associates, searchtechnology);
	return 0;

}
