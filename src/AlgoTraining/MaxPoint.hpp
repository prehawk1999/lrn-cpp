/*
 * MaxPoint.hpp
 *
 *  Created on: 2014Äê5ÔÂ12ÈÕ
 *      Author: admin
 */

#ifndef MAXPOINT_HPP_
#define MAXPOINT_HPP_

#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include <set>

using std::vector;
using std::string;
using std::stack;
using std::cout;
using std::endl;
using std::multiset;

 struct Point {
	int x;
	int y;
	Point() : x(0), y(0) {}
	Point(int a, int b) : x(a), y(b) {}
};

 struct Line {
	 int 		px;
	 int 		py;
	 bool  		hasK;
	 double   	k;
	 int		count;
	 Line(int a, int b, bool c, double d, int e):
		 px(a), py(b), hasK(c), k(d), count(e){}
 };


class Solution {
public:
    int maxPoints(vector<Point> & points) {

    	int count, max = 0;
    	vector<Line> lines;
    	vector<Point> tmpA(points), tmpB(points);
    	vector<Point>::iterator iterA, iterB;
    	vector<Line>::iterator linIter;
    	for(iterA = tmpA.begin(); iterA != tmpA.end(); ++iterA){
    		ptrdiff_t offset = iterA - tmpA.begin();
    		for(iterB = tmpB.begin() + offset; iterB != tmpB.end(); ++iterB){

    			double k;
    			Line l = Line( (*iterA).x, (*iterA).y, getK(*iterA, *iterB, k), k);
    			for(linIter = lines.begin(); linIter != lines.end(); ++linIter){

    			}
    			lines.push_back(l);
    		}
    	}


    	return max;

    }

    bool getK(Point pA, Point pB, double & k){
    	if(pA.x == pB.x)
    		return false;
    	k = (pB.y - pA.y) / (pB.x - pA.x);
    	return true;
    }

    bool inLine(Point pointA, Point pointB, Point point){

    	if(pointA.x != pointB.x){
    		if(pointA.x == point.x ){
    			return false;
    		}
    		else if( pointA.y == point.y){ // same point
    			return true;
    		}
    		else{
    			int k1 = ((pointB.y - pointA.y)/(pointB.x - pointA.x));
    			int k2 = ((point.y - pointA.y)/(point.x - pointA.x));
    			return k1 == k2;
    		}
    	}
    	else{
    		return pointA.x == point.x;
    	}
    }



};




void test_main(){
	Solution s  = Solution();
	vector<Point> vecPoint;
	vecPoint.push_back( Point() );
	vecPoint.push_back( Point(1, 1) );
	vecPoint.push_back( Point(2, 2) );
	vecPoint.push_back( Point(3, 3) );
	vecPoint.push_back( Point(1, 0) );
	vecPoint.push_back( Point(2, 0) );
	vecPoint.push_back( Point(2, 1) );
	vecPoint.push_back( Point(3, 1) );
	vecPoint.push_back( Point(3, 2) );
	cout << s.maxPoints(vecPoint) << endl;
}




#endif /* MAXPOINT_HPP_ */
