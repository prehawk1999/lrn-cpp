/*
 * chap2.hpp
 *
 *  Created on: Mar 23, 2014
 *      Author: prehawk
 */

#ifndef CHAP2_HPP_
#define CHAP2_HPP_

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


char word[2000000];




/* P13
 * pre. left rotate i elements
 * note. my function is in low efficience. about o(nlogn)
 * */
void rotate1(int rot){

	char t, t2;
	bool newloop = true;
	int pre, n = sizeof word;

	rot %= n;
	if(rot < 0){
		rot = n + rot;
	}

	if(rot == 0 || rot == n - 1){// -1 to skip the null char
		return;
	}

	// -1 to skip the null char.
	for(int i=n-1-1; i>=0; i-=rot){// start from the end, with a pace in rot.


		pre = i - rot; // previous pivot
		if(pre >= 0){

			// keep rolling forward, keep the first int in a vec.
			if(newloop){
				t = word[pre];
				word[pre] = word[i];
				set(i);
			}
			else{
				t2 = word[pre];
				word[pre] = t;
				t = t2;
			}
			newloop = false;
		}
		else{
			pre = n - 1 - rot + i;// adjust the pre. -1 to skip the null char.

			t2 = word[pre];
			word[pre] = t;
			t = t2;

			if(!test(pre)){
				// +rot to negetive i-=rot after the loop, actually it sets the next i to be pre;
				i = pre + rot;
			}
			else{// old loop, but not end
				for(int e=n-rot; e<n; ++e){
					if(!test(e)){
						i = e;// pick a new loop
						newloop = true;
					}
				}
				break;// outer loop
			}

		}
	}

}




void reverse(int l, int r){

	char t;
	while(l < r){
		t = word[l];
		word[l] = word[r];
		word[r] = t;
		++l;
		--r;
	}
}


/* P14
 * pre. left rotate i elements,close to O(n) where n is the size of the array.
 * */
void rotate2(int i){

	//boost::timer::auto_cpu_timer t;
	int n = sizeof word;
	i %= n;
	if(i < 0){
		i = n + i;
	}
	reverse(0, i-1);
	reverse(i, n-2);// skip the null char at the end, thus n-2 not n-1
	reverse(0, n-2);
}


void vision_test1(){

	boost::timer::auto_cpu_timer t;
	for(int i=0; i<100; ++i){
		rotate1(i);
	}
}



void vision_test2(){

	boost::timer::auto_cpu_timer t;
	for(int i=0; i<100; ++i){
		rotate2(i);
	}
}

void efficient_test(){

	cout << "******Testing efficient compare of two version******" << endl;
	cout << "******Testing version 1******" << endl;
	vision_test1();

	cout << "******Testing version 2******" << endl;
	vision_test2();



}

/* P18. Section 2.8
 * Pre. echo all 3 transforms words with the dic.txt.
 * Using std::map
 * @return void
 * */
void echogramlist(){

	boost::timer::auto_cpu_timer t;
	fstream infile("./dic.txt", ios_base::in);
	if(!infile || infile.eof()){
		cout << "You should create a file in this dir named as dic.txt" << endl;
		return;
	}


	map<string, string> dic;
	map<string, string>::iterator dic_it;
	string raw, echo;
	bool isword = true;

	while(infile >> echo){
		if(isword){
			raw = echo;									// raw is raw
			sort(echo.begin(), echo.end());				// echo is the signature of the word
			dic_it = dic.find(echo);
			if( dic_it == dic.end() ){					// the word is new to the dic, then insert it
				dic.insert( make_pair( echo, raw) );
			}
			else if(raw != dic_it->second){				// concate the same sign words
				dic_it->second += "\t" + raw;
			}
			isword = false;
		}
		if(infile.peek() == '\r') isword = true;
	}

	// display words that have 3 transformations of his own.
	for(dic_it = dic.begin(); dic_it != dic.end(); ++dic_it){
		echo = dic_it->second;
		if(count(echo.begin(), echo.end(), '\t') > 1)
			cout << echo << endl;
	}

}


void test_main(){
	echogramlist();
}

#endif /* CHAP2_HPP_ */
