/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 12:12:42 by mcaro-ro          #+#    #+#             */
/*   Updated: 2026/05/11 12:31:59 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>
#include <cstdlib>

/* ============================================================================== */
/*                                   Canonical Form                               */
/* ============================================================================== */

RPN::RPN(void) {}

RPN::RPN(const RPN& other) { *this = other; }

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
		this->_stack = other._stack;
	return (*this);
}

RPN::~RPN(void) {}

/* ============================================================================== */
/*                                 Validation                                     */
/* ============================================================================== */

bool RPN::isOperator(char c) const
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool RPN::isDigitToken(const std::string& token) const
{
	return (token.length() == 1 && std::isdigit(token[0]));
}

/* ============================================================================== */
/*                                 Processing                                     */
/* ============================================================================== */

void RPN::processDigit(char c)
{
	int value = c - '0';
	this->_stack.push(value);
}

void RPN::processOperator(char op)
{
	if (this->_stack.size() < 2)
		throw std::runtime_error("");

	int b = this->_stack.top();
	this->_stack.pop();

	int a = this->_stack.top();
	this->_stack.pop();

	int result = applyOperator(a, b, op);
	this->_stack.push(result);
}

/* ============================================================================== */
/*                                 Helpers										  */
/* ============================================================================== */

int RPN::applyOperator(int a, int b, char op) const
{
	switch (op)
	{
		case '+':
			return (a + b);
		case '-':
			return (a - b);
		case '*':
			return (a * b);
		case '/':
			if (b == 0)
				throw std::runtime_error("");
			return (a / b);
		default:
			throw std::runtime_error("");
	}
}

/* ============================================================================== */
/*                                 Public Interface                               */
/* ============================================================================== */

int RPN::evaluate(const std::string& expression)
{
	std::istringstream iss(expression);
	std::string token;

	while (iss >> token)
	{
		if (isDigitToken(token))
			processDigit(token[0]);
		else if (token.length() == 1 && isOperator(token[0]))
			processOperator(token[0]);
		else
			throw std::runtime_error("");
	}

	if (this->_stack.size() != 1)
		throw std::runtime_error("");
	
	return (this->_stack.top());
}
