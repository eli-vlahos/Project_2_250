/*
 * QuadTree.h
 *
 *  Created on: Oct. 28, 2020
 *      Author: elicv
 */

#ifndef QUADTREE_H_
#define QUADTREE_H_

#include <iostream>
#include <vector>
#include "Node.h"

class Quad_Tree {

private:
	Node *root; //root of the tree
	int count; //number of trees in

public:
	Quad_Tree();
	~Quad_Tree();

	void direct(std::vector<std::string> line);
	std::vector<std::string> vector_cleaner(std::vector<std::string>);
	void insert(std::vector<std::string> const &line);
	void insert_recursive(Node *root_node, Node *new_node);
	void q_max(std::vector<std::string> const &line);
	double q_max_recursive(Node* node, std::string attribute, double q_max);
	void q_min(std::vector<std::string> const &line);
	double q_min_recursive(Node* node, std::string attribute, double q_min);
	void q_total(std::vector<std::string> const &line);
	double q_total_recursive(Node* node, std::string attribute, double q_total);
	Node* search_recursive(Node *root_node, double x1, double y1);
	int print(Node* root, int counter);
	void clear(Node* root);


};

#endif /* QUADTREE_H_ */
