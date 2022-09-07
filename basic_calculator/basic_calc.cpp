// Given a string s which represents an expression, evaluate this expression and return its value. 
// The integer division should truncate toward zero.
// You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].
// Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

#include <iostream>
#include <sstream>
#include <string>
#include <stack>
using namespace std;

bool isOperator(const char ch) {
    return (ch=='+' || ch=='-' || ch=='*' || ch=='/');
}


int Priority(const char c) {
    if (c == '*' || c == '/') {
        return 2;
    } else if (c== '+' || c == '-') {
        return 1;
    } else {
        return 0;
    }
}

long long calculate_exp(long long x, long long y, char op) {
    switch(op) {
        case '+': return x + y;
        case '-': return x - y;
        case '*': return x * y;
        case '/': return x / y;
    }
    return -1;
}


//Two Stacks solution
int calculate_two_stacks(string& s) {

    s += "+0";
    stack<long long> num_stack; //give the number
    stack<char> op_stack; //give the operations

    #define CALCULATE_IT { \
        long long y = num_stack.top(); num_stack.pop(); \
        long long x = num_stack.top(); num_stack.pop(); \
        char op = op_stack.top(); op_stack.pop(); \
        num_stack.push(calculate_exp(x, y, op));\
    }

    for(int i = 0; i < s.size(); i++){
        char ch = s[i];
        if (isspace(ch)) continue;
        if (isdigit(ch)) {
            string num;
            num += s[i];
            while(isdigit(s[i+1])){
                num += s[i+1];
                i++;
            }
            num_stack.push(stoll(num));
            continue;
        }
        if (isOperator(ch)) {
            while (!op_stack.empty() && Priority(op_stack.top()) >= Priority(ch) ) {
                CALCULATE_IT;
            }

            op_stack.push(ch);
        }

    }

    while(!op_stack.empty()){
        CALCULATE_IT;
    }
    
    return num_stack.top();
}


int calculate(string s) {
    return calculate_two_stacks(s);
}

int main(int argc, char**argv) 
{
    string exp = " 1+15 / 2 ";
    if (argc>1) {
        exp = argv[1];
    }

    cout << "\"" << exp << "\" = " << calculate(exp) << endl;

}