#include <iostream>
#include "BinaryTree.h"
#include <stack>
#include <string>
#include <limits.h> 
#include <algorithm>

using namespace std;

string infixToPostfix(string s);
int solveTree(TreeNode* root);
int calculate(int l, int r, char op);
int precedence(char c);


//Function to return precedence of operators
int precedence(char c){
    switch(c){
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        case '^': return 3;
        default:  return 0; // precedence of an operand
    }
}

//infix exp to postfix exp
string infixToPostfix(string infix_str){
    stack<char> op_stack; //For stack operations
    string posfix_str;

    string::iterator end_pos = remove(infix_str.begin(), infix_str.end(), ' ');
    infix_str.erase(end_pos, infix_str.end());
 
    for(int i = 0; i < infix_str.length(); i++) {
        char c = infix_str[i];
 
        // operands are added to directly to posfix_str.
        if(c >= '0' && c <= '9'){
            posfix_str += c;
        }

        // If the scanned character is an
        // ‘(‘, push it to the stack.
        else if(c == '('){
            op_stack.push('(');
        }
 
        // If the scanned character is an ‘)’,
        // pop and to output string from the stack
        // until an ‘(‘ is encountered.
        else if(c == ')') {
            while(op_stack.top() != '(')
            {
                posfix_str += op_stack.top();
                op_stack.pop();
            }
            op_stack.pop();//popping '('
        }
 
        //If an operator is scanned
        else {
            while(!op_stack.empty() && precedence(c) <= precedence(op_stack.top())){
                posfix_str += op_stack.top();
                op_stack.pop(); 
            }
            op_stack.push(c);
        }
    }
 
    // concatenate the remaining elements in the stack
    while(!op_stack.empty()) {
        posfix_str += op_stack.top();
        op_stack.pop();
    }
    
    return posfix_str;
}

TreeNode* PostfixToExpTree(string pf){
    stack<TreeNode*> st;
    for(const char& c : pf){
        if('0' <= c && c <= '9'){
            TreeNode* new_operand = new TreeNode(c);
            st.push(new_operand);
        }
        else{
           TreeNode* first_operand = st.top();
           st.pop();
           TreeNode* second_operand = st.top();
            st.pop();
            TreeNode* op = new TreeNode(c, second_operand, first_operand);
            st.push(op);
        }
    }
    return st.top();
}


int solveTree(TreeNode* root){
    if(root == nullptr){
        return 0;
    }
    char c = root->val;
    
    if('0' <= c && c <= '9'){
        return (c-'0');
    }
        
    int l = solveTree(root->left);
    int r = solveTree(root->right);
    
    return calculate(l,r,root->val);
}


int calculate(int l, int r, char op){
    switch(op){
        case '+': return l+r;
        case '-': return l-r;
        case '*': return l*r;
        case '/': return l/r;
        case '^': return l^r;
    }
    return INT_MIN;
}


void printTree(TreeNode* root){
    if(root == nullptr){
        return;
    }

    printTree(root->left);
    cout<< root->val << " ";
    printTree(root->right);
}

int calculateInfix(string infix_exp){
    string postfix = infixToPostfix(infix_exp);
    TreeNode* tree_res = PostfixToExpTree(postfix);
    int res = solveTree(tree_res);
    return res;
}

int main() {
    string infix = "(7*3+ 2)*5 + 1 +(4 * 6*(1 +1))";
    // string postfix = infixToPostfix(infix);
    // cout<< "infix = "<<infix<<endl;
    // cout<< "postfix = "<<postfix<<endl;
    // cout << infix <<" = ";
    // TreeNode* tree_res = PostfixToExpTree(postfix);
    // // printTree(tree_res);
    // int int_res = solveTree(tree_res);
    int res = calculateInfix(infix);
    cout <<infix<<" = "<<res<< endl;
    return 0;
}