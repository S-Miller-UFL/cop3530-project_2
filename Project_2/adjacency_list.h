#pragma once
#include <map>
#include <string>
#include <vector>
#include "mtrx.h"
class adj_list
{
	//nevermind, we need an edge to determine if theres a connection between two nodes
public:
	struct node
	{
		std::string name;
		std::vector<node*> out;
		std::vector<node*> in;
	};
	void add_node(std::string, std::string);
	int get_map_size();
	std::string get_name(node*);
	void print_list();
	void print_list_helper(node*);
	node* find_node(std::string);
	void pagerank(int);
	bool check_if_edge(int, int);
	void create_matrix();
	~adj_list();

private:
	std::map<int,node*> node_map;
	int map_size = 0;
	std::vector<std::vector<int>> rows;
	std::vector<int> columns;
	//mtrx* matrix;
};

//this is O(N) i believe
void adj_list::add_node(std::string from, std::string to)
{
	node* node_from = find_node(from);
	node* node_to = find_node(to);
	//if both of our nodes exist
	if (node_from != nullptr && node_to != nullptr)
	{
		//link the nodes together
		node_from->out.push_back(node_to); //add the node at our "to" to the out vector at our "from" node
		node_to->in.push_back(node_from); //add the node at our "from" to the in vector at our "to" node
	}
	//if the "from" node doesnt exist
	else if (node_from == nullptr && node_to != nullptr)
	{
		//create "from" node
		node_from = new node;
		node_from->name = from;
		//add our "from" node to the node map
		node_map.emplace(map_size++,node_from);
		//link them together
		node_to->in.push_back(node_from);
		node_from->out.push_back(node_to);
	}
	//if our "to" doesnt exist
	else if (node_from != nullptr && node_to == nullptr)
	{
		//create "to" node
		node_to = new node;
		node_to->name = to;
		//add our "to" node to the node map
		node_map.emplace(map_size++, node_to);
		//link them together
		node_from->out.push_back(node_to);
		node_to->in.push_back(node_from);

	}
	//if neither exist
	else if (node_from == nullptr && node_to == nullptr)
	{
		//create "from" node
		node_from = new node;
		node_from->name = from;
		//create "to" node
		node_to= new node;
		node_to->name = to;
		//add them to the node map
		node_map.emplace(map_size++, node_from);
		node_map.emplace(map_size++, node_to);
		//link them together
		node_from->out.push_back(node_to);
		node_to->in.push_back(node_from);
	}
}

//this is O(1)
int adj_list::get_map_size()
{
	return this->map_size;
}

//this is O(1)
std::string adj_list::get_name(node* node)
{
	return node->name;
}

//this is O(N^2)
void adj_list::print_list()
{
	for (int i =0; i< node_map.size(); i++)
	{
		print_list_helper(node_map.at(i));
	}
}

//this is O(N)
void adj_list::print_list_helper(node* n)
{
	if (n == nullptr)
	{
		return;
	}
	else
	{
		std::cout << "at node " << n->name << std::endl;
		std::cout << "in nodes: ";
		for (int i = 0; i < n->in.size(); i++)
		{
			std::cout << n->in.at(i)->name << std::endl;
		}
		std::cout << "out nodes: ";
		for (int i = 0; i < n->out.size(); i++)
		{
			std::cout << n->out.at(i)->name << std::endl;
		}
	}
}

//this function is O(N)
adj_list::node* adj_list::find_node(std::string name)
{
	auto it = node_map.begin();
	while (it != node_map.end())
	{
		if (it->second->name == name)
		{
			return it->second;
		}
		else
		{
			it++;
		}
	}
	return nullptr;
}

void adj_list::pagerank(int iterations)
{
	auto it = node_map.begin();

	for(int i =0; i < map_size; i++)
	{
		for (int j = 0; j < map_size; j++)
		{
			if (check_if_edge(i,j))
			{
				rows.at(i).at(j) = (1 / (it->second->out.size()));
				
			}
		}
		columns.at(i) = (1 / (it->second->out.size()));
	}

	for (int i = 0; i < map_size; i++)
	{
		//map_matrix->insert_at_index(i, 0,it->first);
		it++;
	}

}

bool adj_list::check_if_edge(int from, int to)
{
	auto it = node_map.at(from);
	auto it_ = node_map.at(to);
	
	for (int i =0; i < it->out.size(); i++)
	{
		if (it->out.at(i)->name == it_->name)
		{
			return true;
		}
	}
	return false;
}

void adj_list::create_matrix()
{
	for (int i = 0; i < map_size; i++)
	{
		std::vector<int> c;
		for (int j = 0; j < map_size; j++)
		{
			c.push_back(0);
			columns.push_back(j + 1);
		}
		this->rows.push_back(c);
	}
}

adj_list::~adj_list()
{
	std::cout << "clearing memory..." << std::endl;
	auto it = node_map.end();
	it--;
	while (it != node_map.begin())
	{
		delete it->second;
		it--;
	}
	delete it->second;
	node_map.clear();
}