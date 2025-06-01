#include <iostream>
#include <list>
#include<map>
#include<set>
#include<queue>
class nfa_node
{
public:
	nfa_node();
	~nfa_node();
	std::map<char, std::list<nfa_node*>> none_landa_connections;	
	std::list<nfa_node*> landa_nonnections;
private:

};
class dfa_node
{
public:
	dfa_node();
	~dfa_node();
	std::map<char,dfa_node*> none_landa_connections;
	
private:

};
dfa_node::dfa_node()
{
}

dfa_node::~dfa_node()
{
}

nfa_node::nfa_node()
{
}

nfa_node::~nfa_node()
{
}
class dfa_machine
{
public:
	dfa_machine();
	~dfa_machine();
	std::list<dfa_node*> final_nodes;
	dfa_node* starting_node;
	std::list<char> alphabet;
	std::list<dfa_node*> all_nodes;
private:

};

dfa_machine::dfa_machine()
{
}

dfa_machine::~dfa_machine()
{
}
class nfa_machine
{
public:
	nfa_machine();
	~nfa_machine();
	std::list<nfa_node*> final_nodes;
	nfa_node* starting_node;
	std::list<char> alphabet;
	std::list<nfa_node*> all_nodes;
	dfa_machine* to_dfa() {
		std::map<nfa_node*, std::map<char, std::set<nfa_node*>>*> table;
		for (auto node_item : all_nodes)
		{
			table[node_item] = new std::map<char, std::set<nfa_node*>>;
			for (auto symbol : alphabet)
			{
				//first landa
				std::set<nfa_node*> starting_landa_connected_nodes;
				starting_landa_connected_nodes.insert(node_item);
				std::queue<nfa_node*> landa_unvisited_nodes;
				for (auto landa_connection_node : node_item->landa_nonnections)
				{
					if (starting_landa_connected_nodes.find(landa_connection_node)== starting_landa_connected_nodes.end())
					{
						starting_landa_connected_nodes.insert(landa_connection_node);
						landa_unvisited_nodes.push(landa_connection_node);
					}					
				}
				while (!landa_unvisited_nodes.empty())
				{
					auto selected_landa_node = landa_unvisited_nodes.front();
					landa_unvisited_nodes.pop();
					for (auto landa_connection_node : selected_landa_node->landa_nonnections)
					{
						if (starting_landa_connected_nodes.find(landa_connection_node) == starting_landa_connected_nodes.end())
						{
							starting_landa_connected_nodes.insert(landa_connection_node);
							landa_unvisited_nodes.push(landa_connection_node);
						}
					}
				}
				//symbol_connoction_node					 		
				for (auto landa_connection_node : starting_landa_connected_nodes)
				{
					for (auto symbol_connoction_node : landa_connection_node->none_landa_connections[symbol])
					{
						if ((*table[node_item])[symbol].find(symbol_connoction_node) == (*table[node_item])[symbol].end())
						{
							(*table[node_item])[symbol].insert(symbol_connoction_node);
							landa_unvisited_nodes.push(symbol_connoction_node);
						}					
						
					}
				}
				while (!landa_unvisited_nodes.empty())
				{
					auto selected_landa_node = landa_unvisited_nodes.front();
					landa_unvisited_nodes.pop();
					for (auto connoction_node : selected_landa_node->landa_nonnections)
					{
						if ((*table[node_item])[symbol].find(connoction_node) == (*table[node_item])[symbol].end())
						{
							(*table[node_item])[symbol].insert(connoction_node);
							landa_unvisited_nodes.push(connoction_node);
						}
					}
				}
				
					
					
					
			}
		}
		//starting node
		dfa_machine* return_dfa_machin = new dfa_machine();
		return_dfa_machin->starting_node = new dfa_node();
		return_dfa_machin->all_nodes.push_back(return_dfa_machin->starting_node);
		std::set< std::set<nfa_node*>> nodes_node_sets;
		std::map< std::set<nfa_node*>, dfa_node*> dfa_node_map;
		dfa_node_map[{this->starting_node}] = return_dfa_machin->starting_node;
		nodes_node_sets.insert({ this->starting_node });		
		std::set<nfa_node*> node_set;		
		std::queue< std::set<nfa_node*>> unvisited_dfa_nodes;		
		for (auto symble : alphabet)
		{
			node_set.clear();
			auto other_set = (*table[this->starting_node])[symble];
			node_set.insert(other_set.begin(), other_set.end());
			if (nodes_node_sets.find(node_set)!= nodes_node_sets.end())
			{
				nodes_node_sets.insert(node_set);
				dfa_node_map[node_set] = new dfa_node();				
				return_dfa_machin->all_nodes.push_back(dfa_node_map[node_set]);
				unvisited_dfa_nodes.push(node_set);
				for (auto* nfa_final_node : this->final_nodes)
				{
					bool found = false;
					for (auto* posible_final_node : node_set)
					{
						if (nfa_final_node == posible_final_node)
						{
							return_dfa_machin->final_nodes.push_back(dfa_node_map[node_set]);
							found = true;
							break;
						}
					}
					if (found)
					{
						break;
					}
				}
			}
			return_dfa_machin->starting_node->none_landa_connections[symble] = dfa_node_map[node_set];			
					
		}
		//other nodes
		while (!unvisited_dfa_nodes.empty())
		{
			auto front_dfa_node_item = unvisited_dfa_nodes.front();
			unvisited_dfa_nodes.pop();
			
			for (auto symble : alphabet)
			{
				node_set.clear();
				for (auto* item: front_dfa_node_item)
				{
					auto other_set = (*table[item])[symble];
					node_set.insert(other_set.begin(), other_set.end());
				}
				if (nodes_node_sets.find(node_set) != nodes_node_sets.end())
				{
					nodes_node_sets.insert(node_set);
					dfa_node_map[node_set] = new dfa_node();
					return_dfa_machin->all_nodes.push_back(dfa_node_map[node_set]);
					unvisited_dfa_nodes.push(node_set);
					for (auto* nfa_final_node : this->final_nodes)					
					{
						bool found = false;
						for (auto* posible_final_node : node_set)
						{							
							if (nfa_final_node== posible_final_node)
							{
								return_dfa_machin->final_nodes.push_back(dfa_node_map[node_set]);								
								found = true;
								break;
							}
						}
						if (found)
						{
							break;
						}
					}
				}
				dfa_node_map[front_dfa_node_item]->none_landa_connections[symble] = dfa_node_map[node_set];
			}
		}
		
		for (auto item:this->alphabet)
		{
			return_dfa_machin->alphabet.push_back(item);
		}	
		
		//deleting table
		for (auto item : all_nodes)
		{
			delete table[item];
		}
		return return_dfa_machin;
	}
private:

};

nfa_machine::nfa_machine()
{
}

nfa_machine::~nfa_machine()
{
}

int main()
{
   
}