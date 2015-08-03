/*
 * chap3.hpp
 *
 *  Created on: Mar 18, 2014
 *      Author: prehawk
 */

#ifndef CHAP3_HPP_
#define CHAP3_HPP_
#include "../algo_test.h"


const char * tails[] = {
		"etic", "alistic", "stic", "ptic", "lytic", "otic",
		"antic", "ntic", "ctic", "atic", "hnic", "nic", "mic",
		"llic", "blic", "clic", "lic", "hic", "fic", "dic", "bic",
		"aic", "mac", "iac"
};

const int tails_l = 24;




string getsuffix(string input){

	string tail;
	for(int i=0; i<24; ++i){
		tail = tails[i];
		if(1){
			cout << tail << endl;
		}
	}
	return input;
}

void test(){

	getsuffix("ethnic");

}

int foo(int i){
	int a = i;
	int b = -i;
	return a & b;
}

typedef int ElemType;

struct Node{ElemType data; struct Node * next;};

size_t lstLen(Node * lst){

	size_t len = 0;
	while(lst != NULL){
		lst = lst->next;
		++len;
	}
	return len;
}

void intersect(Node * a, Node * b){

	Node * pa = a;
	Node * pb = b;

	size_t dif = lstLen(a) - lstLen(b);
	if(dif < 0){
		pa = b;
		pb = a;
		dif = -dif;
	}



}

void test_main(){

	//test();



	int i;
	cin >> i;
}

#endif /* CHAP3_HPP_ */
