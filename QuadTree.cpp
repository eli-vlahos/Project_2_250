/*
 * QuadTree.cpp
 *
 *  Created on: Oct. 28, 2020
 *      Author: elicv
 */


//include necessary libraries
#include "QuadTree.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <regex>
#include <math.h>
#include <cmath>
#include <iomanip>


//class is initially empty when initialized
Quad_Tree::Quad_Tree() {
	this->root = nullptr;
	this->count = 0;

}

//clear function already exists, just call it
Quad_Tree::~Quad_Tree() {

	this->clear(this->root);

}


//function that directs string input
void Quad_Tree::direct(std::vector<std::string> line) {

	std::cout<<std::fixed; //setting output to fixed early

	// for insert, clean input and then pass
	if(line[0] == "i") {
		line = vector_cleaner(line);

		this->insert(line);

	}
	else if(line[0] == "s"){
		//for search, get coordinates, check to see if something is there
		//if there is, return it

		line = vector_cleaner(line);

		double x = stod(line[0]);
		double y = stod(line[1]);

		Node* node = search_recursive(root, x, y);

		if (node != nullptr){
			std::cout<<"found " << node->get_city() <<std::endl;
		}
		else{
			std::cout<<"not found"<<std::endl;
		}

	}
	else if (line[0] == "print"){

		// uses a counter to track status
		//The counter is passed because the print is recursive
		int c = this->print(this->root, 0);

		//If the counter was larger than 0, then an end of line will be printed
		if (c > 0){
			std::cout<<std::endl;
		}
	}
	else if (line[0] == "clear"){
		//clear is called
		//clear is always a success, so success is always called

		this->clear(this->root);
		this->root = nullptr;
		std::cout<<"success"<<std::endl;
	}
	else if (line[0] == "size"){

		//just checks current size

		std::cout<<"tree size "<< this->count<<std::endl;

	}
	else if (line[0] == "q_max"){

		//all the q functions work in the same way. Input is parsed, passed to a function that then calls a recursive function

		line = vector_cleaner(line);

		q_max(line);

	}
	else if (line[0] == "q_min"){

		line = vector_cleaner(line);

		q_min(line);

	}
	else if (line[0] == "q_total"){

		line = vector_cleaner(line);

		q_total(line);

	}


}

std::vector<std::string> Quad_Tree::vector_cleaner(std::vector<std::string> line) {

	//cleans the input seperating by semi colons, white spaces are already eliminated

	line.erase(line.begin());
	std::regex comma(";");

	std::vector<std::string> line_update {
		std::sregex_token_iterator(line[0].begin(), line[0].end(), comma, -1), {}
	};

	return line_update;
}

void Quad_Tree::insert(std::vector<std::string> const &line){

		//initialize all variables for node, then create one with said variables

		std::string city_name = line[0];
		double x = stod(line[1]);
		double y = stod(line[2]);
		int population = stoi(line[3]);
		double cost_of_living = roundf(stod(line[4])*100)/100;
		double net_salary = roundf(stod(line[5])*100)/100;


		//making sure the node is not already in the tree
		if (search_recursive(this->root, x, y) != nullptr){
				std::cout<<"failure"<<std::endl;
		}
		else if (this->root == nullptr){

			//if root is null insert

			Node *node = new Node(city_name, x, y, population, cost_of_living, net_salary);
			this->root = node;
			std::cout<<"success"<<std::endl;
			this->count ++;
		}
		else {
			//call recursive insert

			Node *node = new Node(city_name, x, y, population, cost_of_living, net_salary);
			this->insert_recursive(this->root, node);
		}


}

void Quad_Tree::insert_recursive(Node *root_node, Node *new_node){

	//recursive insert, uses a "root" input and the node to be inserted

	double x = root_node->get_x();
	double x1 = new_node->get_x();
	double y = root_node->get_y();
	double y1 = new_node->get_y();


	//based on coordinates will insert in a certain location
	if (x1 >= x && y1 > y){

		//will check to see if there is a next node. If not, insert
		//same formula everywhere
		//uses a set next function to initialize
		if (root_node->get_NE() != nullptr){
			insert_recursive(root_node->get_NE(), new_node);
		}
		else{
			root_node->set_NE(new_node);
			std::cout<<"success"<<std::endl;
			this->count ++;
		}

	}
	if (x1 < x && y1 >= y){

		if (root_node->get_NW() != nullptr){
			insert_recursive(root_node->get_NW(), new_node);
		}
		else{
			root_node->set_NW(new_node);
			std::cout<<"success"<<std::endl;
			this->count ++;
		}

	}
	if (x1 <= x && y1 < y){

		if (root_node->get_SW() != nullptr){
			insert_recursive(root_node->get_SW(), new_node);
		}
		else{
			root_node->set_SW(new_node);
			std::cout<<"success"<<std::endl;
			this->count ++;
		}

	}
	if (x1 > x && y1 <= y){

		if (root_node->get_SE() != nullptr){
			insert_recursive(root_node->get_SE(), new_node);
		}
		else{
			root_node->set_SE(new_node);
			std::cout<<"success"<<std::endl;
			this->count ++;
		}

	}

}

void Quad_Tree::q_max(std::vector<std::string> const &line){

	//first finds the node to start at. Initializes all other values
	double q_max = 0.0; //just initializing q_max so no errors occur later
	double x = stod(line[0]);
	double y = stod(line[1]);
	std::string direction = line[2];
	std::string attribute = line[3];
	Node* node = search_recursive(this->root,x,y);
	Node* next_node = nullptr;


	//checks to make sure node exists, then initializes next node
	if (node != nullptr){
		if (direction == "NW"){
			next_node = node->get_NW();
		}
		else if (direction == "NE"){
			next_node = node->get_NE();
		}
		else if (direction == "SW"){
			next_node = node->get_SW();
		}
		else if (direction == "SE"){
			next_node = node->get_SE();
		}
	}

	//if either value is null, then the q function fails
	if (node != nullptr && next_node != nullptr){

		//don't need to check to see if input is right, can assume proper
		if (attribute == "p"){
			q_max = next_node->get_population();
		}
		else if (attribute == "r"){
			q_max = next_node->get_cost_of_living();
		}
		else if (attribute == "s"){
			q_max = next_node->get_net_salary();
		}

		//find max
		q_max = q_max_recursive(next_node, attribute, q_max);

		//set precision based on what type the output should be
		if (attribute == "p")
		{
		std::cout.precision(0);
		}
		else{
		std::cout.precision(2);
		}

		std::cout<< "max "<< q_max <<std::endl;

	}
	else {
		std::cout<<"failure"<<std::endl;
	}

}

double Quad_Tree::q_max_recursive(Node* node, std::string attribute, double q_max){


	//gets the value if not null
	//checks to see which is bigger then calls again
	if (node != nullptr){

		double q = 0.0; //initializing to make sure no errors


		if (attribute == "p"){
			q = node->get_population();
		}
		else if (attribute == "r"){
			q = node->get_cost_of_living();
		}
		else if (attribute == "s"){
			q = node->get_net_salary();
		}

		if (q > q_max){
			q_max = q;
		}


		q_max = q_max_recursive(node->get_NE(), attribute, q_max);
		q_max = q_max_recursive(node->get_NW(), attribute, q_max);
		q_max = q_max_recursive(node->get_SW(), attribute, q_max);
		q_max = q_max_recursive(node->get_SE(), attribute, q_max);
	}



	return q_max;
}

void Quad_Tree::q_min(std::vector<std::string> const &line){

	//first finds the node to start at. Initializes all other values
	double q_min = 0.0; //just initializing q_min so no errors occur later
	double x = stod(line[0]);
	double y = stod(line[1]);
	std::string direction = line[2];
	std::string attribute = line[3];
	Node* node = search_recursive(this->root,x,y);
	Node* next_node = nullptr;

	//checks to make sure node exists, then initializes next node
	if (node != nullptr){
		if (direction == "NW"){
			next_node = node->get_NW();
		}
		else if (direction == "NE"){
			next_node = node->get_NE();
		}
		else if (direction == "SW"){
			next_node = node->get_SW();
		}
		else if (direction == "SE"){
			next_node = node->get_SE();
		}
	}

	//if either value is null, then the q function fails
	if (node != nullptr && next_node != nullptr){

		//don't need to check to see if input is right, can assume proper
		if (attribute == "p"){
			q_min = next_node->get_population();
		}
		else if (attribute == "r"){
			q_min = next_node->get_cost_of_living();
		}
		else if (attribute == "s"){
			q_min = next_node->get_net_salary();
		}

		//find min
		q_min = q_min_recursive(next_node, attribute, q_min);

		//set precision based on what type the output should be
		if (attribute == "p")
		{
		std::cout.precision(0);
		}
		else{
		std::cout.precision(2);
		}
		std::cout<< "min "<<q_min <<std::endl;

	}
	else {
		std::cout<<"failure"<<std::endl;
	}

}

double Quad_Tree::q_min_recursive(Node* node, std::string attribute, double q_min){

	//gets the value if not null
	//checks to see which is smaller then calls again
	if (node != nullptr){

		double q = 0.0; //initializing to make sure no errors


		if (attribute == "p"){
			q = node->get_population();
		}
		else if (attribute == "r"){
			q = node->get_cost_of_living();
		}
		else if (attribute == "s"){
			q = node->get_net_salary();
		}

		if (q < q_min){
			q_min = q;
		}


		q_min = q_min_recursive(node->get_NE(), attribute, q_min);
		q_min = q_min_recursive(node->get_NW(), attribute, q_min);
		q_min = q_min_recursive(node->get_SW(), attribute, q_min);
		q_min = q_min_recursive(node->get_SE(), attribute, q_min);
	}



	return q_min;
}

void Quad_Tree::q_total(std::vector<std::string> const &line){

	//first finds the node to start at. Initializes all other values
	double q_total = 0.0; //just initializing q_total so no errors occur later
	double x = stod(line[0]);
	double y = stod(line[1]);
	std::string direction = line[2];
	std::string attribute = line[3];
	Node* node = search_recursive(this->root,x,y);
	Node* next_node = nullptr;

	//checks to make sure node exists, then initializes next node
	if (node != nullptr){
		if (direction == "NW"){
			next_node = node->get_NW();
		}
		else if (direction == "NE"){
			next_node = node->get_NE();
		}
		else if (direction == "SW"){
			next_node = node->get_SW();
		}
		else if (direction == "SE"){
			next_node = node->get_SE();
		}
	}

	//if either value is null, then the q function fails
	if (node != nullptr && next_node != nullptr){

		//return total, no need to check for type of input
		q_total = q_total_recursive(next_node, attribute, q_total);

		//set precision based on what type the output should be
		if (attribute == "p")
		{
		std::cout.precision(0);
		}
		else{
		std::cout.precision(2);
		}
		std::cout<< "total "<<q_total <<std::endl;

	}
	else {
		std::cout<<"failure"<<std::endl;
	}

}

double Quad_Tree::q_total_recursive(Node* node, std::string attribute, double q_total){

	//gets the value if not null
	//makes a total then calls again
	if (node != nullptr){

		double q = 0.0; //initializing to make sure no errors


		if (attribute == "p"){
			q = node->get_population();
		}
		else if (attribute == "r"){
			q = node->get_cost_of_living();
		}
		else if (attribute == "s"){
			q = node->get_net_salary();
		}

		q_total += q;


		q_total = q_total_recursive(node->get_NE(), attribute, q_total);
		q_total = q_total_recursive(node->get_NW(), attribute, q_total);
		q_total = q_total_recursive(node->get_SW(), attribute, q_total);
		q_total = q_total_recursive(node->get_SE(), attribute, q_total);
	}



	return q_total;
}

Node* Quad_Tree::search_recursive(Node *root_node, double x1, double y1){

	//checks to see if root is null
	if (root_node == nullptr){
		return nullptr;
	}
	else {

	double x = root_node->get_x();
	double y = root_node->get_y();

	Node* node = nullptr;

	//if equal, already there
	//else, checks to see where it should call next
	//will return nullptr if there is a failure
	if (x1 == x && y1 == y){
		node = root_node;
	}
	else if (x1 >= x && y1 > y){

		if (root_node->get_NE() != nullptr){
			node = search_recursive(root_node->get_NE(), x1, y1);
		}


	}
	else if (x1 < x && y1 >= y){

		if (root_node->get_NW() != nullptr){
			node = search_recursive(root_node->get_NW(), x1, y1);
		}

	}
	else if (x1 <= x && y1 < y){

		if (root_node->get_SW() != nullptr){
			node = search_recursive(root_node->get_SW(), x1, y1);
		}

	}
	else if (x1 > x && y1 <= y){

		if (root_node->get_SE() != nullptr){
			node = search_recursive(root_node->get_SE(), x1, y1);
		}

	}

	return node;

	}

}

int Quad_Tree::print(Node* root, int counter){


	//prints recursively inorder. This means that the print is done between the four recursive calls
	if (root != nullptr){

		counter = print(root->get_NE(), counter);
		counter = print(root->get_NW(), counter);
		std::cout<<root->get_city();
		counter++;
		if (counter != this->count){
			std::cout<< " ";
		}
		counter = print(root->get_SW(), counter);
		counter = print(root->get_SE(), counter);
	}

	return counter;

}

void Quad_Tree::clear(Node* root){

	//recursive clear function, if not empty calls the next point and erases the current

	if (root != nullptr){
		clear(root->get_NE());
		clear(root->get_NW());
		clear(root->get_SW());
		clear(root->get_SE());

		Node* temp = root;
		delete temp;
		this->count --;
	}

}

