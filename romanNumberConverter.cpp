#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

/*
Function 			: getNumber(char c)
Description 		: this function will return the hindu arabic number to the corresponding character
Input parameters 	: c - character					   
Return 				: corresponding hindu arabic number
*/
int getNumber(char c)
{
	int n;
	if(c=='i' || c=='I')
		n=1;
	else if(c=='v' || c=='V')
		n=5;
	else if(c=='x' || c=='X')
		n=10;
	else if(c=='l' || c=='L')
		n=50;
	else if(c=='c' || c=='C')
		n=100;
		
	return n;
}

/*
Function 			: checkOtherCharacters(string str)
Description 		: this function will return false if the string contains characters other than i,I, v,V, x,X, l,L or c,C
Input parameters 	: str - string				   
Return 				: true or false
*/
bool checkOtherCharacters(string str)
{
	//cout<<str.size();
	int count=0;
	for(int i=0;i<str.size();i++)
	{
		if(str[i]=='i' || str[i]=='I' || str[i]=='v' || str[i]=='V' || str[i]=='x' || str[i]=='X' || str[i]=='l' || str[i]=='L' || str[i]=='c' || str[i]=='C')
		{
			count++;
		}	
	}
	if(count==str.size()) //if count is equal to the string size, there are no other characters 
		return true;
	else
	{
		//cout<<"other characters";
		return false;
	}
	
}

/*
Function 			: checkRepeatingErrors(string str)
Description 		: this function will return false if the string contains i or x repeat more than 3 times or if v,l repeat more than 1 time
Input parameters 	: str - string				   
Return 				: true or false
*/
bool checkRepeatingErrors(string str)
{
	int count=0;
	int d=str.size();
	
	for(int i=0;i<d-1;i++)
	{
		if(str[i]=='v' || str[i]=='V') //check whether v repeat more than one time
		{
			if(str[i+1]=='v' || str[i+1]=='V')
			{
				//cout<<"v repeat error";
				return false;
			}		
		}
		
		else if(str[i]=='l' || str[i]=='L') //check whether l repeat more than one time
		{
			if(str[i+1]=='l' || str[i+1]=='L')
			{
				//cout<<"l repeat error";
				return false;
			}		
		}
	}
	
	for(int i=0;i<d;i++)
	{
		int x=i;
		while(str[x]=='i' || str[x]=='I') //check whether i repeat more than three time
		{
			count++;
			if(str[x+1]!='i' && str[x+1]!='I')
				break;
			else
				x=x+1;
		}
		if(count>3)
		{
			//cout<<" i repeat error";
			return false;
		}
		else
			count=0;
			
		x=i;
		while(str[x]=='x' || str[x]=='X') //check whether x repeat more than three time
		{
			count++;
			if(str[x+1]!='x' && str[x+1]!='X')
				break;
			else
				x=x+1;
		}
		if(count>3)
		{
			//cout<<"x repeat error";
			return false;
		}	
		else
			count=0;
	}
	
	return true;
}

/*
Function 			: checkFormatErrors(string str)
Description 		: this function will return true if the string has following conditions 
						1. there should not be l,L,c,C after i or I
						2. there should not be x,X,l,L,c,C after v or V - v cannot be substracted by any number
						3. there should not be c,C after l or L
Input parameters 	: str - string				   
Return 				: true or false
*/
bool checkFormatErrors(string str)
{
	for(int i=0;i<str.size();i++)
	{
		if(str[i]=='i' || str[i]=='I')
		{
			if(str[i+1]=='l' || str[i+1]=='L' ||str[i+1]=='c' ||str[i+1]=='C') //il or ic is not possible
			{
				//cout<<"i format error";
				return false;
			}
		}
		
		else if(str[i]=='v' || str[i]=='V')
		{
			if(str[i+1]=='x' || str[i+1]=='X' ||str[i+1]=='l' ||str[i+1]=='L' || str[i+1]=='c' || str[i+1]=='C') //vl,vx or vc is not possible
			{
				//cout<<"v format error";
				return false;
			}
		}
		
		else if(str[i]=='l' || str[i]=='L')
		{
			if(str[i+1]=='c' || str[i+1]=='C') //lc is not valid
			{
				//cout<<"l format error";
				return false;
			}
		}
	}
	return true;
}

/*
Function 			: check_iv_ix_errors(string str)
Description 		: this function will return true if the string has following conditions 
						1. there should not be any character after ix (ixi, ixc is not possible)
						2. there should not be any character after iv
Input parameters 	: str - string				   
Return 				: true or false
*/
bool check_iv_ix_errors(string str)
{
	int d=str.size(); //get the size of the string
	for(int i=0;i<d-1;i++)
	{
		if((str[i]=='i'|| str[i]=='I') && (str[i+1]=='x'|| str[i+1]=='X'))
		{
			if((i+1)!=d-1) //check if ix part comes at the end of the string by checking the position of (i+1)
			{
				//cout<<"ix error";
				return false;
			}
		}
		
		else if((str[i]=='i'|| str[i]=='I') && (str[i+1]=='v'|| str[i+1]=='V'))
		{
			if((i+1)!=d-1) //check if iv part comes at the end of the string by checking the position of (i+1)
			{
				//cout<<"iv error";
				return false;
			}
		}
	}
	
	return true;
}

/*
Function 			: checkAscendingErrors(string str)
Description 		: this function will return true if the string has following conditions 
						1. if there are 3 consecutive numbers have ascending order like iiv , it will returrn false. otherwise true
Input parameters 	: str - string				   
Return 				: true or false
*/
bool checkAscendingErrors(string str)
{
	int d=str.size();
	for(int i=0;i<d-2;i++)
	{
		int n1=getNumber(str[i]); //first number
		int n2=getNumber(str[i+1]); //second
		int n3=getNumber(str[i+2]); //third
		
		if(n1<=n2 && n2<n3) //if has ascending order return false
		{
			//cout<<"asending errror";
			return false;
		}
	}
	return true;
}

int main()
{
	vector<string> a; //vector to store strings in the text file
	ifstream file("numbers.txt"); //open the text file
	string str;
	if(file.is_open()) //check whether the file is open
	{
		while(!file.eof())
		{
			file>>str;
			a.push_back(str); //store the strings to the vector line by line
		}
	}
	else
		cout<<"error.. file is not open"<<endl;
		
	for(int i=0;i<a.size();i++)
	{
		string s=a.at(i); //elemnt of string array
		int size=s.size();
		
		if(checkRepeatingErrors(s) && checkOtherCharacters(s) && checkFormatErrors(s) && check_iv_ix_errors(s) && checkAscendingErrors(s))
		{
			int number=0;
			int n;
			for(int i=0;i<size-1;i++)
			{
				int A=getNumber(s[i]);
				int B=getNumber(s[i+1]);
				if(A>=B) //if the first number is less than second it should be added otherwise it should substract
					number=number+A;
				else
					number=number-A;
			}
			int c=getNumber(s[size-1]); 
			number=number+c; //add the last character in the string
			if(number>100)
				cout<<s<<" = error"<<endl; //print error if the number exceeds 100
			else
				cout<<s<<" = "<<number<<endl; //print the result
		}
		
		else
		{
			cout<<s<<" = error"<<endl; //if conditions are not true then print error
		}
	}
	
	return 0;
}

