#include "trie.h"
#include <fstream>
#include <stack>

node * node::search(char l)
{
	std::list<node*>::iterator it = children.begin();
	while (it != children.end() && (*it)->letter < l) {
		it++;
	}

	if (it == children.end()) {
		return NULL;
	} else if ((*it)->letter == l) {
		return (*it);
	}
}

trie::trie(std::string file_name)
{
	root = new node();
	word_file_name = file_name;
}

trie::~trie()
{
	delete root;
}

bool trie::initialize()
{
	if (word_file_name == "") {
		std::cerr << "File name not set, please set file name." << std::endl;
		return false;
	} else {

		std::ifstream infile;
		infile.open(word_file_name);

		if (!infile.is_open()) {
			std::cerr << "Not able to open file" << std::endl;
			return false;
		}
		std::string curr;
		
		while (std::getline(infile,curr)) {
				insert_word(curr);		
		}
		return true;
	}
}

bool trie::insert_word(std::string word)
{
	node * curr_node = root;
	//std::cout << "Inserting " << word << std::endl;
	for (int i = 0; i < word.size(); i++)
	{
		//std::cout << word[i] << std::endl;
		curr_node = curr_node->insert_child(word[i]);
		if (curr_node == NULL) {
			return false;
		}
	}
	curr_node->complete = true;
	//std::cout << std::endl;
	return true;
}

void trie::print()
{

}

std::vector<std::string> * trie::get_results(std::string partial)
{
	std::vector<std::string> * to_return = new std::vector<std::string>();

	node * curr = root;
	int i = 0;
	while (i < partial.size() && curr != NULL) {
		curr = curr->search(partial[i]);
		i++;
	}
	// found
	if (i == partial.size() && curr != NULL && curr->letter == partial[partial.size() - 1]) {
		for (auto it = curr->children.begin(); it != curr->children.end(); it++) {
			(*it)->get_sub(*to_return,partial);
		}
		return to_return;
	} else {
		return to_return;
	}
	
}

void node::get_sub(std::vector<std::string>& v, std::string curr_word) 
{
	curr_word += letter;
	if (complete) {
		v.push_back(curr_word);
	}
	for (auto it = children.begin(); it != children.end(); it++) {
		(*it)->get_sub(v,curr_word);
	}
}

