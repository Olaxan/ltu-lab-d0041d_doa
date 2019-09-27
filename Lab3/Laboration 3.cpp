#include "pch.h"
#include <iostream>
#include <chrono>
#include <random>

namespace {
	using std::cout;
	using std::endl;
	using std::chrono::high_resolution_clock;
	using std::chrono::duration;
}


// Recursive function which takes an array, index of left- and rightmost element, and two references to integer variables
void maximized_indices(int arr[], int left_bound, int right_bound, int &min, int &max)
{
	// Base condition, method will call itself recursively if array contains more than 1 element
	if (right_bound - left_bound > 0)
	{
		// Middle index
		int mid = (right_bound + left_bound) / 2;
		// Call method on left array
		maximized_indices(arr, left_bound, mid, min, max);
		// Call methid on right array
		maximized_indices(arr, mid + 1, right_bound, min, max);
	}

	// Comparison if the value is smaller than the current smallest element, if so -> swap
	min = min < arr[left_bound] ? min : arr[left_bound];
	// Comparison if the value is larger than the current largest element, if so -> swap
	max = max > arr[left_bound] ? max : arr[left_bound];
}

// Class to measure average operation time
class Counter
{
private:
	double sum = 0;
	double num = 0;
public:
	void add(double d)
	{
		sum += d;
		num++;
	}
	double get_average_ms()
	{
		return sum / num;
	}
};

int main()
{
	// Test variables
	const unsigned int num_elements_array_one = 1000;
	const unsigned int num_elements_array_two = 10000;
	const unsigned int num_elements_array_three = 100000;

	int indices_one[num_elements_array_one] = {};
	int indices_two[num_elements_array_two] = {};
	int indices_three[num_elements_array_three] = {};

	std::random_device rand;

	high_resolution_clock::time_point t1;
	high_resolution_clock::time_point t2;

	Counter c1;
	Counter c2;
	Counter c3;

	for (int i = 0; i < 100; i++)
	{

		for (int i = 0; i < num_elements_array_one; i++)
		{
			int num = (rand() % 5000) + 1;
			indices_one[i] = num;
		}

		for (int i = 0; i < num_elements_array_two; i++)
		{
			int num = (rand() % 5000) + 1;
			indices_two[i] = num;
		}

		for (int i = 0; i < num_elements_array_three; i++)
		{
			int num = (rand() % 5000) + 1;
			indices_three[i] = num;
		}

		int min = 5001;
		int max = 0;

		t1 = high_resolution_clock::now();
		maximized_indices(indices_one, 0, num_elements_array_one - 1, min, max);
		t2 = high_resolution_clock::now();
		c1.add(std::chrono::duration_cast<duration<double>>(t2 - t1).count());

		min = 5001;
		max = 0;

		t1 = high_resolution_clock::now();
		maximized_indices(indices_two, 0, num_elements_array_two - 1, min, max);
		t2 = high_resolution_clock::now();
		c2.add(std::chrono::duration_cast<duration<double>>(t2 - t1).count());

		min = 5001;
		max = 0;

		t1 = high_resolution_clock::now();
		maximized_indices(indices_three, 0, num_elements_array_three - 1, min, max);
		t2 = high_resolution_clock::now();
		c3.add(std::chrono::duration_cast<duration<double>>(t2 - t1).count());
	}
	
	cout << "1 000 elements in array, average microseconds: " << c1.get_average_ms() << "\n";
	cout << "10 000 elements in array, average microseconds: " << c2.get_average_ms() << "\n";
	cout << "100 000 elements in array, average microseconds: " << c3.get_average_ms() << "\n";
}