/*
 * chap4.hpp
 *
 *  Created on: Mar 18, 2014
 *      Author: prehawk
 */

#ifndef CHAP4_HPP_
#define CHAP4_HPP_

#include "../algo_test.h"





/* P42 11.
 * pre. the input array x must be sorted
 * $1 input array, $2 expect value
 * @return the num of array x
 *
 * */
template<typename DataType>
int binarysearch(DataType x[], int n){

	boost::timer::auto_cpu_timer t;
	int m, l = 0, u = 9;
	while(l <= u){
		m = (l + u)/2;
		if(n > x[m]){
			l = m + 1;
		}
		else if(n < x[m]){
			u = m - 1;
		}
		else{ // point_y == m
			return m;
		}
	}
	return l;
}


const double array_0[]	= {1.1, 2.3, 4.6, 4.8, 4.9, 5.7, 7.8, 8.1, 9.3, 9.9};
const double array_1[]	= {1.9, 3.2, 3.4, 4.3, 4.7, 5.8, 5.9, 6.2, 6.3, 7.1};

/*
 * P40 7.
 * pre. the line stack is 10 high 1 wide.
 * $1: point x, $2: point y
 * @return the num of line that is just below the point or is stepping on the point
 *
 * */
int showlevel(double point_x, double point_y){

	boost::timer::auto_cpu_timer t;
	double array_x[10] = {0};

	//create an array that contain the y coords.
	for(int i=0; i<10; ++i){
		array_x[i] = (array_1[i] - array_0[i]) * point_x + array_0[i];
	}

	int m, l = 0, u = 9;
	while(l <= u){
		m = (l + u)/2;
		if(point_y > array_x[m]){
			l = m + 1;
		}
		else if(point_y < array_x[m]){
			u = m - 1;
		}
		else{ // point_y == m
			return m;
		}
	}
	return l;
}

#endif /* CHAP4_HPP_ */
