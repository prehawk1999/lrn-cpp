#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <sstream>

using std::vector;
using std::string;
using std::stack;
using std::cout;
using std::endl;
using std::stringstream;


class Solution {
public:
    int evalRPN(vector<string> & tokens) {
		string optA, optB;
        stack<string> bag;
		string temp; 

		for(vector<string>::iterator iter = tokens.begin(); iter != tokens.end(); ++iter){ 
			stringstream ss;
			if(*iter == string("+")){
				getOpt(optA, optB, bag);  
				ss << (getVal(optA) + getVal(optB));
			}
			else if(*iter == string("-")){
				getOpt(optA, optB, bag); 
				ss << (getVal(optA) - getVal(optB));
			}
			else if(*iter == string("*")){
				getOpt(optA, optB, bag); 
				ss << getVal((optA) * getVal(optB));
			}
			else if(*iter == string("/")){
				getOpt(optA, optB, bag); 
				ss << (getVal(optB) / getVal(optA));
			}
			else{
				ss << *iter;
			} 
			temp = ss.str();
			bag.push( temp );
		} 
		return getVal(bag.top());
    }

	int getVal(string s){
		stringstream ss(s);
		int val;
		ss >> val;
		return val;
	}
	void getOpt(string & optA, string & optB, stack<string> & bag){
		optA = bag.top(); bag.pop();
		optB = bag.top(); bag.pop();
	}
};

void test_main(){
	Solution s = Solution();
	vector<string> token;
	token.push_back(string("2"));
	token.push_back(string("1"));
	token.push_back(string("+"));
	token.push_back(string("3"));
	token.push_back(string("*"));
	token.push_back(string("0"));
	token.push_back(string("/"));
	cout << s.evalRPN(token) << endl; 
}
