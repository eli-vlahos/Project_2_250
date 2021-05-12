/**

*/

#ifndef NODE_H
#define NODE_H

#include <iostream>

class Node {


    // class variables
	private:

		double x; // logitude
		double y; // latitude
		std::string city_name;
		int population;
		double cost_of_living;
		double net_salary;
		Node *NE;
		Node *NW;
		Node *SW;
		Node *SE;


    // class functions
    public:
		Node (std::string const &city_name, double const &x, double const &y, int const &population, double const &cost_of_living, double const &net_salary);
		~Node();

		Node* get_NE();
		Node* get_NW();
		Node* get_SW();
		Node* get_SE();

		void set_NE(Node* node);
		void set_NW(Node* node);
		void set_SW(Node* node);
		void set_SE(Node* node);


		double get_x();
		double get_y();
		std::string get_city();
		double get_population();
		double get_cost_of_living();
		double get_net_salary();



};

#endif
