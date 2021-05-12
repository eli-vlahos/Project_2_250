/**

*/



#include <iostream>
#include <math.h>
#include <cmath>
using namespace std;

#include "Node.h"

/**


*/

Node::Node(std::string const &city_name, double const &x, double const &y, int const &population, double const &cost_of_living, double const &net_salary) {

	//to initialize a node I just import the data needed to initialize it
	//Nodes began as nullptr

	this->city_name = city_name;
	this->x = x;
	this->y = y;
	this->population = population;
	this->cost_of_living = cost_of_living;
	this->net_salary = net_salary;

	this->NE = nullptr;
	this->SE = nullptr;
	this->NW = nullptr;
	this->SW = nullptr;


 }


Node::~Node(){

}

//function to get nodes
Node* Node::get_NE(){
	return this->NE;
}
Node* Node::get_NW(){
	return this->NW;
}
Node* Node::get_SW(){
	return this->SW;
}
Node* Node::get_SE(){
	return this->SE;
}

//calling a function to change the node
void Node::set_NE(Node* node){
	this->NE = node;
}
void Node::set_NW(Node* node){
	this->NW = node;
}
void Node::set_SW(Node* node){
	this->SW = node;
}
void Node::set_SE(Node* node){
	this->SE = node;
}


//other get functions
double Node::get_x(){
	return this->x;
}

double Node::get_y(){
	return this->y;
}
std::string Node::get_city(){
	return this->city_name;
}
double Node::get_population(){
	return this->population;
}
double Node::get_cost_of_living(){
	return this->cost_of_living;
}
double Node::get_net_salary(){
	return this->net_salary;
}



