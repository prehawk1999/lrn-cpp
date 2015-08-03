/*
 * chap1.hpp
 *
 *  Created on: Mar 23, 2014
 *      Author: prehawk
 */

#ifndef CHAP1_HPP_
#define CHAP1_HPP_

#include "../algo_test.h"

#define BITSPERWORD 32
#define SHIFT		5
#define N			10000000
#define LEN			1 + N/BITSPERWORD

int bitmap[LEN];


/* P7. execise 2
 * pre. prepare a vector of int that contain 10 000 000 bits, it's used to sort integer.
 * */
void set(int i){		bitmap[i>>SHIFT] |=  (1<<(i & 0x1F)); }// low five bits
void clr(int i){		bitmap[i>>SHIFT] &= ~(1<<(i & 0x1F)); }
int test(int i){ return bitmap[i>>SHIFT] &	(1<<(i & 0x1F)); }

int data[LEN];
int from[LEN];
int to[LEN];
int top = 0;


/* P8. execise 9
 * pre. You can access the data[i] without initialize the data[], when i is pointed to an uninitialize elem, return 0
 * */
int getdata(int i){

	if(from[i] < top && to[from[i]] == i){
		return data[i];
	}
	else{
		from[i] = top;
		to[top] = i;
		data[i] = 0;
		top ++;
		return 0;
	}
}

void bitsort(int unsort[], int n){
	boost::timer::auto_cpu_timer t;

	for(int i=0; i != n; ++i){
		set(unsort[i]);
	}

	vi sorted;
	sorted.reserve(n);
	for(int i=0; i!=LEN; ++i){
		if(test(i)){
			sorted.push_back(i);
		}
	}
}

int * getunsort(int num){

	vector<int> unsorted;
	for(int i=0; i!=num; ++i) unsorted.push_back(i);
	srand ( unsigned ( time(0) ) );
	random_shuffle(unsorted.begin(), unsorted.end());

	int i;
	int * ret = new int[num];
	vi::iterator it;
	for(i=0, it = unsorted.begin(); it != unsorted.end(); ++it, ++i){
		ret[i] = *it;
	}
	return ret;
}

void test1(){
	cout << "******Testing bitmap sorting******" << endl;
	cout << "******zero elem******" << endl;
	bitsort(getunsort(0), 0);
	cout << endl;

	int i=0,arg=1;
	for(;i!=8;++i, arg*=10){
		cout << "******tests with " << arg << " elems******" << endl;
		bitsort(getunsort(arg), arg);
		cout << endl;
	}
	cout << "======All tests have been passed======" << endl;
}

void test2(){
	cout << "******Testing constant time initialization******" << endl;
	cout << "******test with 10, 2314, 331******" << endl;
	assert(getdata(1) == 0);
	data[1] = 10, assert(getdata(1) == 10);
	assert(getdata(20) == 0);
	data[20] = 2314, assert(getdata(20) == 2314);
	assert(getdata(300) == 0);
	data[300] = 331, assert(getdata(300) == 331);
	cout << "======All tests have been pass======" << endl;

}


void test_main(){
	test2();
}


#endif /* CHAP1_HPP_ */
