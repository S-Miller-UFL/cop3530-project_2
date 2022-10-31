#pragma once
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
class adj_list
{
public:
	struct node
	{
		float weight = 0.0f;
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
	bool check_if_edge(int, int);
	void create_adjacency_matrix();
	int get_index(node*);
	void create_map_matrix();
	void dot_product();
	~adj_list();

private:
	std::map<int,node*> node_map;
	int map_size = 0;
	std::vector<std::vector<float>> adjacency_matrix;
	//std::vector<int> columns;
	std::vector<float> map_matrix;
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
		node_map.emplace(map_size++,node_from);
		//link them together
		node_to->in.push_back(node_from);
		node_from->out.push_back(node_to);
		node_from->out_indexes.push_back(get_index(node_to));
		node_to->in_indexes.push_back(get_index(node_from));
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
		node_from->out_indexes.push_back(get_index(node_to));
		node_to->in_indexes.push_back(get_index(node_from));

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
		node_from->out_indexes.push_back(get_index(node_to));
		node_to->in_indexes.push_back(get_index(node_from));
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
	create_adjacency_matrix(); //populate adjacency matrix
	create_map_matrix();//populate map matrix
	for (int i = 1; i < iterations; i++)
	{
		dot_product();
	}
	auto it = node_map.begin();
	std::pair<std::string, float> p;
	std::vector<std::pair <std::string, float>> v;
	for (int i = 0; i < map_size; i++)
	{
		/*
		it->second->weight = map_matrix.at(i);
		
		std::cout << it->second->name << " " << map_matrix.at(i) << std::endl;
		*/
		p.first = it->second->name;
		p.second = map_matrix.at(i);
		v.push_back(p);
		it++;
	}
	std::sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); i++)
	{
		std::cout << v.at(i).first << " " << std::fixed<< std::setprecision(2)<< v.at(i).second << std::endl;
	}
}

bool adj_list::check_if_edge(int from, int to)
{
	auto it = node_map.at(from);
	auto it_ = node_map.at(to);
	
	for (int i =0; i < it->out_indexes.size(); i++)
	{
		if (it->out_indexes.at(i) == to)
		{
			return true;
		}
	}
	return false;
}

void adj_list::create_adjacency_matrix()
{
	auto it = node_map.begin();
	for (int i = 0; i < map_size; i++)
	{
		std::vector<float> c;
		for (int j = 0; j < map_size; j++)
		{
			c.push_back(0);
			//columns.push_back(j + 1);
		}
		this->adjacency_matrix.push_back(c);
	}
	for (int i = 0; i < map_size; i++)
	{
		for (int j = 0; j < map_size; j++)
		{
			if (check_if_edge(j, i))
			{
				this->adjacency_matrix.at(i).at(j) = (1 / float((it->second->out.size())));
			}
		}
	}
}

int adj_list::get_index(node* n)
{
	auto it = node_map.begin();
	while (it != node_map.end())
	{
		if (it->second == n)
		{
			return it->first;
		}
		else
		{
			it++;
		}
	}
	return -1;
}

void adj_list::create_map_matrix()
{
	for (int i = 0; i < map_size; i++)
	{
		this->map_matrix.push_back (1/(float)map_size);
	}
}

void adj_list::dot_product()
{
	for (int i = 0; i < map_size; i++)
	{
		for (int j = 0; j < map_size; j++)
		{
			//multiply matrices
			this->adjacency_matrix.at(i).at(j) = (this->adjacency_matrix.at(i).at(j))*this->map_matrix.at(j);
		}
	}
	//initialize map matrix
	for (int j = 0; j < map_size; j++)
	{
		this->map_matrix.at(j) = 0;
	}
	//create dot product
	for (int i = 0; i < map_size; i++)
	{
		for (int j = 0; j < map_size; j++)
		{
			this->map_matrix.at(i) += this->adjacency_matrix.at(i).at(j);
		}
		//std::cout << std::truncf(this->map_matrix.at(i)) << std::endl;
	}
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