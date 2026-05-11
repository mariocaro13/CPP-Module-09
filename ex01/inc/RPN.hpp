/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 11:53:19 by mcaro-ro          #+#    #+#             */
/*   Updated: 2026/05/11 12:26:56 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <string>
# include <stdexcept>

class RPN
{
	public:
		RPN(void);
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN(void);

		int evaluate(const std::string& expression);

	private:
		std::stack<int> _stack;

		bool isOperator(char c) const;
		bool isDigitToken(const std::string& token) const;

		void processDigit(char c);
		void processOperator(char op);

		int applyOperator(int a, int b, char op) const;
};

#endif
