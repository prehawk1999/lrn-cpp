/*
 * chap11.hpp
 *
 *  Created on: Mar 20, 2014
 *      Author: prehawk
 *
 *
 *
 *      usage: change the mysort func. with different _innerQsort method and test it
 */

#ifndef CHAP11_HPP_
#define CHAP11_HPP_

#include "../algo_test.h"

#include <random>
#include <cstdlib>


mt19937 generator(time(NULL));

/*
 * pre. quicksort
 * $1: begin iter, $2: end iter that point over the end of vector
 * @return void
 * */
template<typename Type>
void _innerQsort1(typename Type::iterator l, typename Type::iterator u){

	if(l >= u) return;

	vi::iterator m = l ;
	for(vi::iterator it = m+1; it != u; ++it){
		if( (*it) < (*l) ){
			swap( *++m, *it );
		}
	}
	swap( *l, *m );
	_innerQsort1< Type >(l, m);
	_innerQsort1< Type >(m+1, u);
}

/*
 * pre. quicksort version 2, scan from two directions, better perf. in sorting same elem.
 * $1: begin iter, $2: end iter that point over the end of vector
 * @return void
 * */
template<typename Type>
void _innerQsort2(typename Type::iterator l, typename Type::iterator u){

	if(l >= u) return;

	vi::iterator i(l);
	vi::iterator j(u);
	int t = *l;

	while(1){
		do i++; while( i <= u && *i < t);
		do j--; while( j == u || *j > t);
		if( i > j )
			break;
		swap(*i, *j);
	}
	swap(*l, *j);
	_innerQsort2< Type >(l, j);
	_innerQsort2< Type >(j+1, u);
}


/*
 * pre. quicksort version 3, scan from two directions, better perf. in sorting same elem.
 * with random characteristic, better perf. in sorting invert vectors.
 * $1: begin iter, $2: end iter that point over the end of vector
 * @return void
 * */
template<typename Type>
void _innerQsort3(typename Type::iterator l, typename Type::iterator u){

	if(l >= u) return;

	uniform_int_distribution<int> dis( 0, u - l - 1);
	swap(*l, *( l + dis(generator) ) );

	vi::iterator i(l);
	vi::iterator j(u);
	int t = *l;

	while(1){
		do i++; while( i <= u && *i < t);
		do j--; while( j == u || *j > t);
		if( i > j )
			break;
		swap(*i, *j);
	}
	swap(*l, *j);
	_innerQsort3< Type >(l, j);
	_innerQsort3< Type >(j+1, u);
}


/*
 * P112 example
 * pre. user define sort method
 * $1: input unsort array vector<int>
 * @return: no return
 * */
template<typename Type>
Type mysort(Type x, int version){

	boost::timer::auto_cpu_timer t;
	switch(version){
	case 1:
		_innerQsort1< Type >(x.begin(), x.end());
		break;
	case 2:
		_innerQsort2< Type >(x.begin(), x.end());
		break;
	case 3:
		_innerQsort3< Type >(x.begin(), x.end());
		break;
	case 4:
		sort(x.begin(), x.end());
	}
	return x;
}



vi getunsort(int num){

	vector<int> test;
	for(int i=0; i<num; ++i) test.push_back(i);
	srand ( unsigned ( time(0) ) );
	random_shuffle(test.begin(), test.end());

	return test;
}

vi getsame(int num){

	vector<int> test;
	for(int i=0; i<num; ++i) test.push_back(0);
	return test;
}

vi getsorted(int num){

	vector<int> test;
	for(int i=num; i>=0; --i){
		test.push_back(i);
	}
	return test;
}

void assertsorted(vi sorted ){

	int i = 0;
	for(vi::iterator it=sorted.begin(); it!=sorted.end(); ++it){
		assert(i <= *it);
		i = *it;
	}
}

void version_test(int version){

	cout << "******Testing non-value******" << endl;
	assertsorted( mysort< vi >( getunsort(0), version ));
	cout << endl << endl;

	cout << "******Testing unsorted array******" << endl;
	for(int i = 1; i<=10000000; i *= 10){

		assertsorted( mysort< vi >( getunsort(i), version ) );
		cout << i << "\telements sorted!" << endl << endl;
	}

	cout << "******Testing same elem array******" << endl;
	for(int i = 1; i<=10000000; i *= 10){

		assertsorted( mysort< vi >( getsame(i), version ) );
		cout << i << "\telements sorted!" << endl << endl;
	}

	cout << "******Testing descending elem array******" << endl;
	for(int i = 1; i<=10000000; i *= 10){

		assertsorted( mysort< vi >( getsorted(i), version ) );
		cout << i << "\telements sorted!" << endl << endl;
	}

	cout << "======All tests have been passed======" << endl;
}

void test_main(){

	// about 1 minute, version 1 and 2 for some reason can't pass the test
	version_test(3);
}

#endif /* CHAP11_HPP_ */
