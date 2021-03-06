// Lab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <queue>
#include <chrono>

using namespace std::chrono;

std::string MakeGoodString(std::string str)
{
	///Makes a string suitable for palindrome testing by clearing whitespace and punctuation.
	std::stringstream ss;

	for (char& a : str)
	{
		if (isalnum(a))						//Only use alphanumerals
			ss << char(toupper(a));			//Make all entered characters uppercase
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

void LargeScaleTest()
{
	int tests = 50;
	int length;
	high_resolution_clock::time_point t1, t2;
	microseconds m1 = microseconds(0);
	microseconds m2 = microseconds(0);;

	for (int j = 0; j < 5; j++)
	{
		length = 3 * std::pow(10, j);

		for (int i = 0; i < tests; i++)
		{
			t1 = high_resolution_clock::now();
			IsPalindromeQueue(std::string(length, 'a'));
			t2 = high_resolution_clock::now();
			m1 += duration_cast<microseconds>(t2 - t1);

			t1 = high_resolution_clock::now();
			IsPalindromeStack(std::string(length, 'a'));
			t2 = high_resolution_clock::now();
			m2 += duration_cast<microseconds>(t2 - t1);
		}

		std::cout << "Avg. time with " << length << " characters: (" << m1.count() / tests << "/" << m2.count() / tests << " MS)\n";
	}
}


int main()
{
	bool isPalindrome;
	std::string input;
	high_resolution_clock::time_point t1, t2;
	microseconds m1, m2;

	std::cout << " === FREDRIK MICROSYSTEMS INCORPORATED === "
		<< "\n\nPatent Palindrome Tester Version 2.99C"
		<< "\nEnter a sequence to test, or 'exit' to terminate.\n";

	while (true)
	{
		std::cout << "\n> ";
		std::getline(std::cin, input);

		if (input == "exit")
			break;

		if (input == "test")
		{
			LargeScaleTest();
			continue;
		}

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