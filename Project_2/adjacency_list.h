#pragma once
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
//got help from sara osmanovic on 10/31/2022
//got help from angela on 11/1/2022
class adj_list
{
public:
	struct node
	{
		double pagerank = 0.0f;
		std::string name;
		std::vector<int> out_indexes;
		std::vector<int> in_indexes;
		std::vector<node*> out;
		std::vector<node*> in;
	};
	void add_node(std::string, std::string);
	int get_map_size();
	std::string get_name(node*);
	//void print_list();
	//void print_list_helper(node*);
	node* find_node(std::string);
	void pagerank(int);
	bool check_if_edge(std::string, std::string);
	int get_index(node*);
	~adj_list();
	std::vector<node*> get_incoming_nodes(std::string);
	std::vector<node*> get_outgoing_nodes(std::string);

private:
	std::map<std::string,node*> node_map;
	int map_size = 0;
};

//use strings for index and not ints
//this is O(N) i believe
void adj_list::add_node(std::string from, std::string to)
{
	node* node_from = find_node(from);
	node* node_to = find_node(to);
	//if both of our nodes exist
	if (node_from != nullptr && node_to != nullptr && !check_if_edge(from,to))
	{
		//link the nodes together
		node_from->out.push_back(node_to); //add the node at our "to" to the out vector at our "from" node
		node_to->in.push_back(node_from); //add the node at our "from" to the in vector at our "to" node
		node_from->out_indexes.push_back(get_index(node_to));
		node_to->in_indexes.push_back(get_index(node_from));
	}
	//if the "from" node doesnt exist
	else if (node_from == nullptr && node_to != nullptr)
	{
		//create "from" node
		node_from = new node;
		node_from->name = from;
		//add our "from" node to the node map
		node_map.emplace(from,node_from);
		//link them together
		node_to->in.push_back(node_from);
		node_from->out.push_back(node_to);
		node_from->out_indexes.push_back(get_index(node_to));
		node_to->in_indexes.push_back(get_index(node_from));
		map_size++;
	}
	//if our "to" doesnt exist
	else if (node_from != nullptr && node_to == nullptr)
	{
		//create "to" node
		node_to = new node;
		node_to->name = to;
		//add our "to" node to the node map
		node_map.emplace(to, node_to);
		//link them together
		node_from->out.push_back(node_to);
		node_to->in.push_back(node_from);
		node_from->out_indexes.push_back(get_index(node_to));
		node_to->in_indexes.push_back(get_index(node_from));
		map_size++;
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
		node_map.emplace(from, node_from);
		node_map.emplace(to, node_to);
		//link them together
		node_from->out.push_back(node_to);
		node_to->in.push_back(node_from);
		node_from->out_indexes.push_back(get_index(node_to));
		node_to->in_indexes.push_back(get_index(node_from));
		map_size++;
		map_size++;
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

//this was really for debugging purposes, i dont think i need this anymore.
/*
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
		//std::cout << "at node " << n->name << std::endl;
		//std::cout << "in nodes: ";
		for (int i = 0; i < n->in.size(); i++)
		{
			std::cout << n->in.at(i)->name << std::endl;
		}
		//std::cout << "out nodes: ";
		for (int i = 0; i < n->out.size(); i++)
		{
			std::cout << n->out.at(i)->name << std::endl;
		}
	}
}
*/

//this function is O(N)
adj_list::node* adj_list::find_node(std::string name)
{
	auto it = node_map.begin();
	while (it != node_map.end())
	{
		if (it->first == name)
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

//this is O(N^2)
void adj_list::pagerank(int iterations)
{

	auto it = node_map.begin();
	//we need a vector of our page ranks so we can work on them
	std::vector<node*> node_list;
	std::vector<node*> incoming;
	for (int i = 0; i < map_size; i++)
	{
		it->second->pagerank = (1.0f / double(map_size));
		node_list.push_back(it->second);

		it++;
	}
	//calculate our page rank
	/*
	* get our incoming nodes for our respective node
	* get their page ranks
	* divide their page ranks by the number of their outgoing nodes
	* add those numbers to our respective node pagerank
	*/
	it = node_map.begin();
	double rank = 0.0f;
	std::vector<double> page_ranks;
	for (int i = 0; i < node_list.size(); i++)
	{
		page_ranks.push_back(1.0f/map_size);
	}
	while (iterations > 1)
	{
		for (int i = 0; i < node_list.size(); i++)
		{
			incoming = node_list.at(i)->in; //incoming nodes
			
			//this looks at every incoming node at our current vertex, gets it pagerank, divides it, then adds it to our rank
			for (int l = 0; l < incoming.size(); l++)
			{
				rank += (incoming.at(l)->pagerank / incoming.at(l)->out.size());
			}
			page_ranks.at(i) = (rank);
			incoming.clear();
			rank = 0.0f;
		}
		for (int i = 0; i < node_list.size(); i++)
		{
			node_list.at(i)->pagerank = page_ranks.at(i);
		}
		iterations--;
	}
	for (int i = 0; i < page_ranks.size(); i++)
	{
		node_list.at(i)->pagerank = page_ranks.at(i);
	}
	it = node_map.begin();
	for (int i = 0; i < map_size; i++)
	{
		std::cout << it->first << " " << std::fixed << std::setprecision(2) << it->second->pagerank << std::endl;
		it++;
	}
	
}

//this is O(N)
bool adj_list::check_if_edge(std::string from, std::string to)
{
	auto it = node_map.find(from);
	auto it_ = node_map.find(to);
	
	for (int i =0; i < it->second->out.size(); i++)
	{
		if (it->second->out.at(i)->name == to)
		{
			return true;
		}
	}
	return false;
}

//this is O(N)
int adj_list::get_index(node* n)
{
	auto it = node_map.begin();
	while (it != node_map.end())
	{
		if (it->second == n)
		{
			return 0;
		}
		else
		{
			it++;
		}
	}
	return -1;
}


adj_list::~adj_list()
{
	//std::cout << "clearing memory..." << std::endl;
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

std::vector<adj_list::node*> adj_list::get_incoming_nodes(std::string name)
{
	node* n = find_node(name);
	return n->in;
}


std::vector<adj_list::node*> adj_list::get_outgoing_nodes(std::string name)
{
	node* n = find_node(name);
	return n->out;
}
