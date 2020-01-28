// GPRO-FW-Launcher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<stdio.h>
#include <iomanip>
#include <iostream>
#include "StaticLib1/Foo.h"

using namespace std;

int main()
{
	int test = foo(9000);
	int age, ageGuess;

	srand(time(0));

	age = rand() % 120;

	cout << "Guess my age!";
	
	cin >> ageGuess;

	while (age != ageGuess)
	{
		cout << "Guess my age!";

		cin >> ageGuess;
	}
	if (age == ageGuess)
	{
		cout << "Congrats! You win!";
	}
}
