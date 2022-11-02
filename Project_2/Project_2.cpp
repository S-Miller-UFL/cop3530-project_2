
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
	adj.pagerank(power_iterations);
}

