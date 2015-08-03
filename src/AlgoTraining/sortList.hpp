/*
 * sortList.hpp
 *
 *  Created on: 2014年5月12日
 *      Author: admin
 */

#ifndef SORTLIST_HPP_
#define SORTLIST_HPP_

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


struct ListNode {
	int val;
	ListNode * next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode * sortList(ListNode * head) {
		if(head == NULL){
			return NULL;
		}

		bool toNext = true;
		ListNode * pNext, * ppNext, * pp, * p = head;
		ListNode tmp = ListNode(0);
		ListNode * root = &tmp;
		root->next = head;

		do{
			pNext = p->next;
			pp = root;
			do{
				ppNext = pp->next;

				if( pNext != NULL && (pNext->val < ppNext->val) ){
					p->next = pNext->next;
					pNext->next = ppNext;
					pp->next =pNext;
					toNext = false;
					break;
				}

			}while( (pp = pp->next) != p );

			if(toNext){
				p = p->next;
			}
			else{
				toNext = true;
			}

		}while( p->next != NULL);

		return root->next;
    }
};


void test_main(){
	Solution s  = Solution();
	 ListNode head	= ListNode(9);
	 ListNode a		= ListNode(3);
	 ListNode b		= ListNode(2);
	 ListNode c		= ListNode(4);
	 ListNode d		= ListNode(10);
	 head.next	= &a;
	 a.next		= &b;
	 b.next		= &c;
	 c.next		= &d;
	 ListNode * ret = s.sortList(&head);
	 //ListNode * ret = &head;
	 do{
		cout << ret->val << endl;
	 } while ( (ret = ret->next) != NULL ) ;
}




#endif /* SORTLIST_HPP_ */
