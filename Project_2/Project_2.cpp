// Project_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "adjacency_list.h"

int main()
{
	int no_of_lines, power_iterations;
	std::string from, to;
	std::cin >> no_of_lines;
	std::cin >> power_iterations;
	adj_list adj;
	for (int i = 0; i < no_of_lines; i++)
	{
		std::cin >> from;
		std::cin >> to;
		adj.add_node(from, to);
	}
	//Create a graph object
	adj.print_list();
	adj.pagerank(power_iterations);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
