#include "test.h"
#include <iostream>
#include <vector>
#include "kdtree.hpp"

#include <stdlib.h> 
#include <time.h>  

void testKDtree() {
	pointVec points;
	point_t pt;


	pt = { 0.0, 0.0 ,0.5};
	points.push_back(pt);
	pt = { 1.0, 0.0 ,1.0};
	points.push_back(pt);
	pt = { 0.0, 1.0 ,2.0};
	points.push_back(pt);
	pt = { 1.0, 1.0 ,2.5};
	points.push_back(pt);
	pt = { 0.5, 0.5 ,3.4};
	points.push_back(pt);

	clock_t startTime, endTime;
	startTime = clock();

	srand((unsigned)time(NULL));
	for (int i = 0; i < 100000; i++) {
		double x = 5*rand() / double(RAND_MAX);
		double y = 5*rand() / double(RAND_MAX);
		double z = 5*rand() / double(RAND_MAX);
		points.push_back({x,y,z});
	}
	endTime = clock();

	std::cout << "time: generate rand number : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;

	startTime = clock();

	KDTree tree(points);

	endTime = clock();
	std::cout << "time: build tree : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;

	std::cout << "nearest test\n";

	
	pt = { 0.8, 0.2 ,0.1};

	startTime = clock();
	auto res = tree.nearest_point(pt);
	endTime = clock();
	std::cout << "time: search nearest : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;

	for (double b : res) {
		std::cout << b << " ,";
	}
	std::cout << '\n';

	/*
	std::cout << "going down the tree\n";
	for (auto b : point_t(*tree)) {
		std::cout << b << " ";
	}
	std::cout << '\n';
	for (auto b : point_t(*tree->left)) {
		std::cout << b << " ";
	}
	std::cout << '\n';
	for (auto b : point_t(*tree->right)) {
		std::cout << b << " ";
	}
	std::cout << '\n';
	for (auto b : point_t(*tree->left->left)) {
		std::cout << b << " ";
	}
	std::cout << '\n';
	for (auto b : point_t(*tree->right->left)) {
		std::cout << b << " ";
	}
	std::cout << '\n';
	std::cout << "printing nbh\n";
	pt = {.0, .5};
	*/

	startTime = clock();
	auto res2 = tree.neighborhood_points(pt, 0.1);
	endTime = clock();
	std::cout << "time: search neighborhood : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;

	for (point_t a : res2) {
		for (double b : a) {
			std::cout << b << " ,";
		}
		std::cout << '\n';
	}
}