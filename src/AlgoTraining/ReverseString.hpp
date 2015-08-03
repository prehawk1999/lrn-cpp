#include <string>
#include <algorithm>
#include <iostream>
 
using std::string; 
using std::cout;
using std::endl;

class Solution {
public:
    void reverseWords(string & s) { 
		string temp;
		string::reverse_iterator iterA, iterB;
		int phase = 0; 
		for(string::reverse_iterator riter = s.rbegin();riter != s.rend(); ++riter){ 
			if(*riter == 0x20){
				if(phase == 1){
					iterB = riter;
					reverse_copy(iterA, iterB, back_inserter(temp));
					temp.push_back(0x20);
					phase = 0;				
				}			
			}
			else{
				if(phase == 0){
					iterA = riter;
					phase = 1;
				}
			} 
		} 
		if(phase == 1){
			iterB = s.rend();
			reverse_copy(iterA, iterB, back_inserter(temp)); 
		}
		while(temp.back() == 0x20){
			temp.pop_back();
		}
		s = temp;

	}
};


void test_main(){
	Solution s = Solution();
	string str(" the     sky     is    blue ");
	s.reverseWords(str);
	cout << str << "||" << endl;
}
