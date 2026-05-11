/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 11:51:06 by mcaro-ro          #+#    #+#             */
/*   Updated: 2026/05/11 14:11:57 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <iomanip>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}

	try 
	{
		PmergeMe pmergeMe;

		pmergeMe.parseInput(argc, argv);

		pmergeMe.printBeforeSort();

		pmergeMe.sortVector();
		pmergeMe.sortDeque();

		pmergeMe.printAfterSort();

		int count = argc - 1;
		std::cout << std::fixed << std::setprecision(5);
		std::cout << "Time to process a range of " << count << " elements with std::vector : " << pmergeMe.getVectorSortTime() << " us" << std::endl;
		std::cout << "Time to process a range of " << count << " elements with std::deque : " << pmergeMe.getDequeSortTime() << " us" << std::endl;

	} catch (const std::exception& e) 
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}

	return (0);
}
