#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

typedef struct candidate{
	int ID;
	int value;
};



void vote()
{
	int n;
	cin >> n;
	candidate person[n];
	
	for(int i = 0; i < n; i++){
		person[i].ID = i+1;
		cin >> person[i].value;
	}
	
	candidate max; max.value=INT_MIN;
	int AllAdd = 0;
	bool is_same = false;
	for(int i = 0; i < n; i++){
		AllAdd += person[i].value;
		if(person[i].value > max.value){
			is_same = false;
			max = person[i];
			continue;
		} 
		if(person[i].value == max.value)
			is_same = true;
	}
	
	if(max.value > (AllAdd/2))
		cout << "majority winner " << max.ID << endl;
	else if(is_same == false)
		cout << "minority winner " << max.ID << endl;
	else if(is_same) 
		cout << "no winner" << endl;
}

int main(void)
{
	int TestCase;
	
	cin >> TestCase;
	
	for(int i = 0; i < TestCase; i++)
		vote();
}