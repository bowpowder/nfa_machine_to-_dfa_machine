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

nfa_node::nfa_node()
{
}

nfa_node::~nfa_node()
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
	void to_dfa() {
		std::map<nfa_node*, std::map<char, std::set<nfa_node*>>*> table;
		for (auto node_item : all_nodes)
		{
			table[node_item] = new std::map<char, std::set<nfa_node*>>;
			for (auto symbol : alphabet)
			{
				//first landa
				std::set<nfa_node*> starting_landa_connected_nodes;
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
		
		//deleting table
		for (auto item : all_nodes)
		{
			delete table[item];
		}
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