#include<iostream>

using namespace std;

class area {
public:
int length;
int breadth;

int getarea(int length, int breadth)
{
	return (length * breadth);
}

};

class circle: public area {
public:
	int radius;
	int getarea(int radius)
	{
		return (3.141 * radius * radius);
	}
};

class triangle: public area {
public:
	int baselength;
	int height;
	float getarea(int baselength, int height)
	{
		return (0.5 * baselength * height);
	}
};

class solution {
public:
	area a1;
	circle c1;
	triangle t1;
};

int main()
{
	solution s1;
	int ch;
	cout<<"Select which area you want"<<endl;
	cout<<"1. Rectangle"<<endl;
	cout<<"2. Circle"<<endl;
	cout<<"3. Triangle"<<endl;
	cout<<"Enter Choice: ";
	cin>>ch;
	switch(ch)
	{
	case 1:{
		int length, breadth;
		cout<<"Enter Length: ";
		cin>>length;
		cout<<"Enter Breadth: ";
		cin>>breadth;
		cout<<"Area: "<<s1.a1.getarea(length, breadth);
		break;
	}

	case 2:{
		int radius;
		cout<<"Enter Radius: ";
		cin>>radius;
		cout<<"Area: "<<s1.c1.getarea(radius);	
		break;
	}

	case 3:{
		int baselength, height;
		cout<<"Enter Base Length: ";
                cin>>baselength;
                cout<<"Enter height: ";
                cin>>height;
		cout<<"Area: "<<s1.t1.getarea(baselength, height);
		break;
	}

	default:{
		cout<<"Invalid Choice"<<endl;;
	}
}

}
