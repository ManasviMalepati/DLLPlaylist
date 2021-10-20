/*
 * DNode.cpp
 *
 *  Created on: Oct 16, 2021
 *      Partner: Daniel Xu
 */
#include "DNode.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;
	DNode::DNode(){
		//create node with song constructor (default)
		song = new Song();
		prev = NULL;
		next = NULL;
	}
	DNode::DNode(string s, string a, int lenmin, int lensec){
		//create node with song constructor (with input)
		song = new Song(s,a,lenmin,lensec);
		prev = NULL;
		next = NULL;
	}




