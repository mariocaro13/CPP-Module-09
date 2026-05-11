/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 11:51:06 by mcaro-ro          #+#    #+#             */
/*   Updated: 2026/05/11 12:32:59 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}

	try 
	{
		RPN calculator;
		int result = calculator.evaluate(argv[1]);
		std::cout << result << std::endl;

	} catch (const std::exception& e) 
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}

	return (0);
}
