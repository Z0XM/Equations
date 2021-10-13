#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <algorithm>
#include "Operands.hpp"

std::stringstream& getInput(std::stringstream& ss);
void format(std::stringstream& eq);
double solveInfix(std::stringstream& ss);

int main()
{
	while (true) {
		std::stringstream eq;
		getInput(eq);

		if (eq.str() == "end")break;

		format(eq);

		double result = solveInfix(eq);

		std::cout << result << '\n' << '\n';
	}
	return 0;
}

std::stringstream& getInput(std::stringstream& eq)
{
	std::string input;
	std::getline(std::cin, input);

	eq << input;

	return eq;
}

void format(std::stringstream& eq)
{
	/*std::string eq_str(eq.str());
	eq.str("");

	std::string str;
	str += eq_str[0];

	bool isNum = false;
	if (str[0] >= '0' && str[0] <= '9')isNum = true;

	for (int i = 1; i < eq_str.size(); i++) {
		if (!isNum) {
			if (str.size() == 1 && str[0] >= '0' && str[0] <= '9') {
				isNum = true;
			}
			else if (std::find_if(Operands.begin(), Operands.end(), [&str](Operand& o) { return str == std::string(o.sym); }) != Operands.end()) {

			}
		}
		else if (eq_str[i] < '0' || eq_str[i] > '9' && eq_str[i] != '.') {
			isNum = false;
			eq << str << " ";
		}

		str += eq_str[i];
	}

	ss << str;*/
}

double solveInfix(std::stringstream& postfix)
{
	std::stringstream eq;
	postfix.swap(eq);

	std::stack<double> values;
	std::stack<OperandType> stack;

	std::string str;
	while (eq >> str) {
		OperandType op = getOp(str.c_str());
		if (op == NONE) {
			values.push(std::stod(str));
		}
		else if (op == OPEN) {
			stack.push(op);
		}
		else if (op == CLOSE) {
			double b = values.top(); values.pop();
			double a = values.top(); values.pop();

			values.push(operate(a, b, stack.top()));

			stack.pop();
			stack.pop();
		}
		else {
			while (!stack.empty()) {
				if (Operands[op].lvl > Operands[stack.top()].lvl) break;

				if (Operands[op].lvl < Operands[stack.top()].lvl || Operands[stack.top()].aso == LEFT_TO_RIGHT) {
					double b = values.top(); values.pop();
					double a = values.top(); values.pop();

					values.push(operate(a, b, stack.top()));

					stack.pop();
				}
			}
			stack.push(op);
		}
	}

	while (!stack.empty()) {
		double b = values.top(); values.pop();
		double a = values.top(); values.pop();

		values.push(operate(a, b, stack.top()));

		stack.pop();
	}

	return values.top();
}

