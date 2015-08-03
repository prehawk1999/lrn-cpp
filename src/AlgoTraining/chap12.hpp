/*
 * chap12.hpp
 *
 *  Created on: Mar 22, 2014
 *      Author: prehawk
 */

#ifndef CHAP12_HPP_
#define CHAP12_HPP_

#include "../algo_test.h"

#include <set>
#include <random>
#include <cstdlib>
#include <algorithm>
#include <cmath>

mt19937 generator(time(NULL));

vi getsorted(int num);





void gensets1(unsigned m, unsigned n){
	boost::timer::auto_cpu_timer t;

	set<unsigned> S;
	uniform_int_distribution<unsigned> dis( 0, n - 1);
	while( S.size() < m ){
		S.insert( dis(generator) );
	}

//	set<int>::iterator it;
//	for(it = S.begin(); it != S.end(); ++it){
//		cout << *it << endl;
//	}
}

void gensets2(int m, int n){
	boost::timer::auto_cpu_timer t;

	vector<int> test;
	for(int i=0; i<n; ++i) test.push_back(i);
	srand( unsigned ( time(0) ) );
	random_shuffle(test.begin(), test.end());

	vector<int> ret(test.begin(), test.begin()+m);
	sort(ret.begin(), ret.end());

}

void assertsorted(vi sorted ){

	int i = 0;
	for(vi::iterator it=sorted.begin(); it!=sorted.end(); ++it){
		assert(i <= *it);
		i = *it;
	}
}

vi getsorted(int num){

	vector<int> test;
	for(int i=0; i<=num; ++i){
		test.push_back(i);
	}
	return test;
}

void test1( ){
	cout << "******Testing version 1 ******" << endl;

	cout << 0 << " sorted random numbers:" << endl;
	gensets1(0, 0);
	gensets2(0, 0);
	cout << endl;

	for(int i=0, arg=1; i<7; ++i, arg*=10){
		cout << arg << " sorted random numbers:" << endl;

		gensets1(arg, arg * 200);
		gensets2(arg, arg * 200);
		cout << endl;
	}
}

void test2(){
	cout << "******Testing version 1 ******" << endl;

	cout << 0 << " sorted random numbers:" << endl;
	gensets2(0, 0);
	cout << endl;

	for(int i=0, arg=1; i<6; ++i, arg*=10){
		cout << arg << " sorted random numbers:" << endl;
 		gensets2(arg, arg * 200);
		cout << endl;
	}
}


void test_main(){
	//gensets2(20000, 4000000);
	test1();
	test2();
}

#endif /* CHAP12_HPP_ */
