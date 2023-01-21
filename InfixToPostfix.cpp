
#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

int priority(char c) {
	if (c == '*' || c == '/')
		return 2;
	if (c == '+' || c == '-')
		return 1;
	return 0;
}

string infixToPostfix(string infix) {
	stack<char> operations;
	string postfix = "";
	for (int i = 0; i < infix.length(); i++)
	{
		char c = infix[i];
		if (isdigit(c))
			postfix += c;
		else if (c == '(')
			operations.push(c);
		else if (c == ')')
		{
			while (!operations.empty() && operations.top() != '(')
			{
				postfix += operations.top();
				operations.pop();
			}
			operations.pop();
		}
		else
		{
			while (!operations.empty() && priority(c) <= priority(operations.top()))
			{
				postfix += operations.top();
				operations.pop();
			}
			operations.push(c);
		}
	}
	while (!operations.empty())
	{
		postfix += operations.top();
		operations.pop();
	}
	cout << "Postfix zapis: " << postfix << endl;
	return postfix;
}

int postfixEvaluation(string postfix)
{
	stack<int> num;
	for (int i = 0; i < postfix.length(); i++)
	{
		if (isdigit(postfix[i]))
		{
			num.push(postfix[i] - '0');
		}
		else
		{
			int op2 = num.top();
			num.pop();
			int op1 = num.top();
			num.pop();
			switch (postfix[i])
			{
			case '+':
				num.push(op1 + op2);
				break;
			case '-':
				num.push(op1 - op2);
				break;
			case '*':
				num.push(op1 * op2);
				break;
			case '/':
				num.push(op1 / op2);
				break;
			default:
				return num.top();
			}
		}
	}
	return num.top();
}

int main()
{
	string infix;
	cin >> infix;
	string postfix = infixToPostfix(infix);
	cout << postfixEvaluation(postfix);
	return 0;
}
