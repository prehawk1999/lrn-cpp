#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>

using namespace std;

class EvaluateExpression{
public:
	enum exp_t {FORWARD_EXP, BACKWARD_EXP, MIDWARD_EXP};

	EvaluateExpression(string exp, exp_t type){
		m_exp = exp;
		m_type = type;
		m_tmp[2] = 0;

		initTable();
	}

	int getvalue(){
		string tmp;
		switch (m_type)
		{
		case EvaluateExpression::FORWARD_EXP:
			m_result = calcForward(m_exp);
			break;
		case EvaluateExpression::MIDWARD_EXP:
			m_repr = m_exp;
			tmp = convert2forward(m_exp);
			m_result = calcForward( tmp );
			break;
		case EvaluateExpression::BACKWARD_EXP:
			m_result = calcBackward(m_exp);
			break;
		default:
			break;
		}
		return m_result;
	};

private:

	void initTable(){

		m_table.insert( make_pair("++", 1) );
		m_table.insert( make_pair("+-", 1) );
		m_table.insert( make_pair("+*", -1) );
		m_table.insert( make_pair("+/", -1) );
		m_table.insert( make_pair("+(", -1) );
		m_table.insert( make_pair("+)", 1) );
		m_table.insert( make_pair("+#", 1) );

		m_table.insert( make_pair("-+", 1) );
		m_table.insert( make_pair("--", 1) );
		m_table.insert( make_pair("-*", -1) );
		m_table.insert( make_pair("-/", -1) );
		m_table.insert( make_pair("-(", -1) );
		m_table.insert( make_pair("-)", 1) );
		m_table.insert( make_pair("-#", 1) );

		m_table.insert( make_pair("*+", 1) );
		m_table.insert( make_pair("*-", 1) );
		m_table.insert( make_pair("**", 1) );
		m_table.insert( make_pair("*/", 1) );
		m_table.insert( make_pair("*(", -1) );
		m_table.insert( make_pair("*)", 1) );
		m_table.insert( make_pair("*#", 1) );

		m_table.insert( make_pair("/+", 1) );
		m_table.insert( make_pair("/-", 1) );
		m_table.insert( make_pair("/*", 1) );
		m_table.insert( make_pair("//", 1) );
		m_table.insert( make_pair("/(", -1) );
		m_table.insert( make_pair("/)", 1) );
		m_table.insert( make_pair("/#", 1) );

		m_table.insert( make_pair("(+", -1) );
		m_table.insert( make_pair("(-", -1) );
		m_table.insert( make_pair("(*", -1) );
		m_table.insert( make_pair("(/", -1) );
		m_table.insert( make_pair("((", -1) );
		m_table.insert( make_pair("()", 0) );
		m_table.insert( make_pair("(#", -2) );

		m_table.insert( make_pair(")+", 1) );
		m_table.insert( make_pair(")-", 1) );
		m_table.insert( make_pair(")*", 1) );
		m_table.insert( make_pair(")/", 1) );
		m_table.insert( make_pair(")(", -2) );
		m_table.insert( make_pair("))", 1) );
		m_table.insert( make_pair(")#", 1) );

		m_table.insert( make_pair("#+", -1) );
		m_table.insert( make_pair("#-", -1) );
		m_table.insert( make_pair("#*", -1) );
		m_table.insert( make_pair("#/", -1) );
		m_table.insert( make_pair("#(", -1) );
		m_table.insert( make_pair("#)", -2) );
		m_table.insert( make_pair("##", 0) );
	}

	int precedeOpt(char a, char b){
		m_tmp[0] = a;
		m_tmp[1] = b;
		return m_table[m_tmp];
	}

	string convert2forward(string exp){

		char c;
		stack<char> s1, s2;
		s1.push('#');
		for (string::reverse_iterator i = exp.rbegin(); i != exp.rend(); ++i){
			c = *i;

			if ( isalnum(c) )
				s2.push(c);
			else{
				switch (c)
				{
				case '+':
				case '-':
				case '*':
				case '/':
					percolate(s1, s2, c);
					break;
				case ')':
					s1.push(c);
					break;
				case '(':
					transmitt(s1, s2);
					break;
				default:
					break;
				}
			}
		}
		transmitt(s1, s2);

		string ret;
		while( !s2.empty() ){
			ret.push_back(s2.top());
			s2.pop();
		}
		return ret;
	}


	//push new optrand into s1 only if optrand is higher than s1.top(), other cases pop s1 into s2 do it again.
	void percolate(stack<char> & s1, stack<char> & s2, char c){
		if( precedeOpt(c, s1.top()) == 1 )		// c is higher than s1.top()
			s1.push(c);
		else{
			s2.push( s1.top() );
			s1.pop();
			percolate(s1, s2, c);
		}
	}

	//transmitt all optrnd from s1 to s2 except '('
	void transmitt(stack<char> & s1, stack<char> & s2){
		if( s1.top() == ')' || s1.top() == '#'){
			s1.pop();
		}
		else{
			s2.push( s1.top() );
			s1.pop();
			transmitt(s1, s2);
		}
	}

	int calcForward(string exp){ // must be midward
		char c;
		int opA, opB;
		stack<int> oprnd;
		for (string::reverse_iterator i = exp.rbegin(); i != exp.rend(); ++i)
		{
			c = *i;
			switch (c)
			{
			case '+':
				opA = oprnd.top(); oprnd.pop();
				opB = oprnd.top(); oprnd.pop();
				oprnd.push(opA + opB);
				break;
			case '-':
				opA = oprnd.top(); oprnd.pop();
				opB = oprnd.top(); oprnd.pop();
				oprnd.push(opA - opB);
				break;
			case '*':
				opA = oprnd.top(); oprnd.pop();
				opB = oprnd.top(); oprnd.pop();
				oprnd.push(opA * opB);
				break;
			case '/':
				opA = oprnd.top(); oprnd.pop();
				opB = oprnd.top(); oprnd.pop();
				oprnd.push(opA / opB);
				break;
			default:
				unsigned t =  boost::lexical_cast<unsigned>(c);
				oprnd.push( t );
				break;
			}
		}
		return oprnd.top();
	}

	int calcBackward(string exp){

		char c;
		int opA, opB;
		stack<int> oprnd;
		for (string::iterator i = exp.begin(); i != exp.end(); ++i)
		{
			c = *i;
			switch (c)
			{
			case '+':
				opA = oprnd.top(); oprnd.pop();
				opB = oprnd.top(); oprnd.pop();
				oprnd.push(opA + opB);
				break;
			case '-':
				opA = oprnd.top(); oprnd.pop();
				opB = oprnd.top(); oprnd.pop();
				oprnd.push(opA - opB);
				break;
			case '*':
				opA = oprnd.top(); oprnd.pop();
				opB = oprnd.top(); oprnd.pop();
				oprnd.push(opA * opB);
				break;
			case '/':
				opA = oprnd.top(); oprnd.pop();
				opB = oprnd.top(); oprnd.pop();
				oprnd.push(opA / opB);
				break;
			default:
				unsigned t =  boost::lexical_cast<unsigned>(c);
				oprnd.push( t );
				break;
			}
		}
		return oprnd.top();
	}

private:
	char					 m_tmp[3];
	map<string, int>  m_table;
	int					m_result;
	exp_t				 m_type;
	string				 m_exp;
	string				 m_repr;			//midward expression for human reading.
};