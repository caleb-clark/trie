#include <string>
#include <iostream>
#include <vector>
#include <list>


#ifndef TRIE_H
#define TRIE_H

struct node
{
	char letter;
	bool complete;
	std::list<node*> children;
	node(char l = '\0') : letter(l), complete(false)
	{}
	node * insert_child(char l)
	{
		std::list<node*>::iterator it = children.begin();
		while (it != children.end() && (*it)->letter < l) {
			it++;
		}
		if (it == children.end() || (*it)->letter != l) {
			node * new_node = new node(l);
			children.insert(it, new_node);
			return new_node;
		} else {
			return (*it);
		}
	}
	node * search(char l);
	void get_sub(std::vector<std::string>& v, std::string curr_word);
};

class trie
{
	node * root;
	std::string word_file_name;
public:
	// constructor
	trie(std::string file_name = "");

	// destructor
	~trie();

	// get words from file and
	// construct data structure
	bool initialize();

	// insert a word into the trie
	// for looking up or validating
	bool insert_word(std::string word);

	// based on a partial word
	// get list of possible complete words
	std::vector<std::string> * get_results(std::string partial);

	void print();

	//std::vector<std::string> trie::get_sub(node * n) 
};

#endif