// Lab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <queue>
#include <chrono>
#include <thread>

using namespace std::chrono;

std::string MakeGoodString(std::string str)
{
	///Makes a string suitable for palindrome testing by clearing whitespace and punctuation.
	std::stringstream ss;
	for (char& a : str)
	{
		if (isalnum(a))
			ss << char(toupper(a));
	}
	return ss.str();
}

bool IsPalindromeStack(std::string word)
{
	///Tests an imput string for palindromeness using just a stack.
	word = MakeGoodString(word);

	int len = word.length();
	std::stack<char> testStack;

	for (int i = 0; i < len; i++)
	{
		if (i < len / 2)						//First half of the string:
			testStack.push(word[i]);			//Add all chars to stack.
		else if (i >= (len + 1) / 2)			//Second half of the string (excluding the middle for uneven length strings):
		{
			if (word[i] != testStack.top())		//Match the stack from top-down against the rest of the string.
				return false;
			else
				testStack.pop();
		}
	}

	return true;
}

bool IsPalindromeQueue(std::string word)
{
	///Tests an imput string for palindromeness using a stack and a queue.
	word = MakeGoodString(word);

	int len = word.length();
	std::queue<char> testQueue;
	std::stack<char> testStack;

	//Add the chars of the string to both data structures.
	for (char& a : word)
	{
		testQueue.push(a);
		testStack.push(a);
	}

	for (int i = 0; i < len / 2; i++)				//Loop through half the string.
	{
		if (testQueue.front() != testStack.top())	//Match the front of the queue with the top of the stack.
			return false;
		else
		{
			testQueue.pop();
			testStack.pop();
		}
	}

	return true;
}


int main()
{
	bool isPalindrome;
	std::string input;
	high_resolution_clock::time_point t1, t2;
	microseconds m1, m2;

	std::cout << " === FREDRIK MICROSYSTEMS INCORPORATED === "
		<< "\n\nPatent Palindrome Tester Version 2.99C"
		<< "\nCertified for Big Data Testing"
		<< "\n\nTesting extended memory...\n\n";

	for (int i = 0; i < 1024 * 4; i++)
	{
		std::cout << "\r" << i << "/" << 1024 * 4 << "MiB";
	}

	std::cout << "\nOK" << "\n\nTesting secure data regions...\n\n";

	for (int i = 0; i < 4; i++)
	{
		std::cout << "_MSEC" << i << "\n";
		for (int j = 0; j < 32; j++)
		{
			std::this_thread::sleep_for(milliseconds(std::rand() % 128));
			std::cout << ".";
		}
		std::cout << " [OK] \n";
	}

	std::cout << "\n -- FAN0 [OK]\n";
	std::this_thread::sleep_for(milliseconds(256));

	std::cout << "\n -- FAN1 [OK]\n";
	std::this_thread::sleep_for(milliseconds(128));

	std::cout << "\n -- CPU [OK]\n";
	std::this_thread::sleep_for(milliseconds(256));

	std::cout << "\n -- GPU [OK]\n";
	std::this_thread::sleep_for(milliseconds(512));

	std::cout << "\n -- PSU0 [OK]\n";
	std::this_thread::sleep_for(milliseconds(256));

	std::cout << "\n -- PSU1 [OK]\n";
	std::this_thread::sleep_for(milliseconds(256));

	std::cout << "\n\nSystems check complete with [0] errors."
		<< "\nPlease wait for virtual machine...\n";

	std::this_thread::sleep_for(milliseconds(1000));

	std::cout << "\nSYSTEM READY\n";

	while (true)
	{
		std::cout << "\n> ";
		std::getline(std::cin, input);

		if (input == "exit")
			break;

		t1 = high_resolution_clock::now();
		isPalindrome = IsPalindromeQueue(input);
		t2 = high_resolution_clock::now();
		m1 = duration_cast<microseconds>(t2 - t1);

		t1 = high_resolution_clock::now();
		isPalindrome = IsPalindromeStack(input) && isPalindrome;
		t2 = high_resolution_clock::now();
		m2 = duration_cast<microseconds>(t2 - t1);


		std::cout << "\n'" << input << "' is " << (isPalindrome ? "indeed" : "not") << " a palindrome.\n";
		std::cout << "Took " << m1.count() << "/" << m2.count() << " microseconds (queue/stack).\n";
	}
}