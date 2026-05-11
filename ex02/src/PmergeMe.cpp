/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 13:01:25 by mcaro-ro          #+#    #+#             */
/*   Updated: 2026/05/11 14:12:38 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <climits>
#include <sys/time.h>

/* ============================================================================== */
/*                                   Canonical Form                               */
/* ============================================================================== */

PmergeMe::PmergeMe(void) : _vectorSortTime(0), _dequeSortTime(0) {}

PmergeMe::PmergeMe(const PmergeMe& other) { *this = other; }

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		this->_vector = other._vector;
		this->_deque = other._deque;
		this->_vectorSortTime = other._vectorSortTime;
		this->_dequeSortTime = other._dequeSortTime;
	}
	return (*this);
}

PmergeMe::~PmergeMe(void) {}

/* ============================================================================== */
/*                                   Input Parsing                                */
/* ============================================================================== */

void PmergeMe::parseInput(int argc, char **argv)
{
	if (argc < 2)
		throw std::runtime_error("Error");

	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];

		for (size_t j = 0; j < arg.size(); j++)
		{
			if (!std::isdigit(arg[j]))
				throw std::runtime_error("Error");
		}

		long value = std::atol(arg.c_str());
		if (value < 0 || value > INT_MAX)
			throw std::runtime_error("Error");

		_vector.push_back(static_cast<int>(value));
		_deque.push_back(static_cast<int>(value));
	}
}

/* ============================================================================== */
/*                                   Printing                                     */
/* ============================================================================== */

void PmergeMe::printBeforeSort(void) const
{
	std::cout << "Before: ";
	printContainer(_vector);
}

void PmergeMe::printAfterSort(void) const
{
	std::cout << "After: ";
	printContainer(_vector);
}

template <typename Container>
void PmergeMe::printContainer(const Container& container) const
{
	for (typename Container::const_iterator it = container.begin(); it != container.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

/* ============================================================================== */
/*                                   Sorting                                      */
/* ============================================================================== */

void PmergeMe::sortVector(void)
{
	double start = getTimeUs();
	mergeInsertSort(_vector);
	double end = getTimeUs();

	_vectorSortTime = end - start;
}

void PmergeMe::sortDeque(void)
{
	double start = getTimeUs();
	mergeInsertSort(_deque);
	double end = getTimeUs();

	_dequeSortTime = end - start;
}

/* ============================================================================== */
/*                                   Getters                                      */
/* ============================================================================== */

double PmergeMe::getVectorSortTime(void) const
{
	return (_vectorSortTime);
}

double PmergeMe::getDequeSortTime(void) const
{
	return (_dequeSortTime);
}

double PmergeMe::getTimeUs(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1e6 + tv.tv_usec);
}

/* ============================================================================== */
/*                                   Explicit Template Instantiations             */
/* ============================================================================== */

template void PmergeMe::mergeInsertSort(std::vector<int>& container);
template void PmergeMe::mergeInsertSort(std::deque<int>& container);

template void PmergeMe::makePairs(const std::vector<int>& container, std::vector<std::pair<int, int> >& pairs, bool& hasOdd, int& oddValue);
template void PmergeMe::makePairs(const std::deque<int>& container, std::vector<std::pair<int, int> >& pairs, bool& hasOdd, int& oddValue);

template void PmergeMe::insertMinElements(const std::vector<std::pair<int, int> >& pairs, std::vector<int>& sortedContainer);
template void PmergeMe::insertMinElements(const std::vector<std::pair<int, int> >& pairs, std::deque<int>& sortedContainer);

/* ============================================================================== */
/*                                   Sorting Algorithm                            */
/* ============================================================================== */

template <typename Container>
void PmergeMe::mergeInsertSort(Container& container)
{
	if (container.size() <= 1)
		return ;

	std::vector<std::pair<int, int> > pairs;
	bool hasOdd = false;
	int oddValue = 0;

	makePairs(container, pairs, hasOdd, oddValue);

	std::vector<int> maxElements;
	extractMaxPairs(pairs, maxElements);

	mergeInsertSort(maxElements);

	Container sortedContainer;
	sortedContainer.insert(sortedContainer.end(), maxElements.begin(), maxElements.end());

	insertMinElements(pairs, sortedContainer);

	if (hasOdd)
	{
		typename Container::iterator pos = std::lower_bound(sortedContainer.begin(), sortedContainer.end(), oddValue);
		sortedContainer.insert(pos, oddValue);
	}

	container = sortedContainer;
}

template <typename Container>
void PmergeMe::makePairs(const Container& container, std::vector<std::pair<int, int> >& pairs, bool& hasOdd, int& oddValue)
{
	pairs.clear();
	hasOdd = false;

	size_t n = container.size();

	for (size_t i = 0; i + 1 < n; i += 2)
	{
		int first = container[i];
		int second = container[i + 1];

		if (first < second)
			pairs.push_back(std::make_pair(first, second));
		else
			pairs.push_back(std::make_pair(second, first));
	}

	if (n % 2 != 0)
	{
		hasOdd = true;
		oddValue = container[n - 1];
	}
}

void PmergeMe::extractMaxPairs(const std::vector<std::pair<int, int> >& pairs, std::vector<int>& maxElements)
{
	maxElements.clear();

	for (size_t i = 0; i < pairs.size(); i++)
	{
		maxElements.push_back(pairs[i].second);
	}
}

template <typename Container>
void PmergeMe::insertMinElements(const std::vector<std::pair<int, int> >& pairs, Container& sortedContainer)
{
	if (pairs.empty())
		return ;
	
	std::vector<size_t> jacobsthalIndeces = generateJacobsthalIndices(pairs.size());

	for (size_t i = 0; i < jacobsthalIndeces.size(); i++)
	{
		size_t index = jacobsthalIndeces[i];
		if (index >= pairs.size())
			continue ;

		int minElement = pairs[index].first;
		int maxElement = pairs[index].second;

		typename Container::iterator upper = std::upper_bound(sortedContainer.begin(), sortedContainer.end(), maxElement);
		typename Container::iterator pos = std::lower_bound(sortedContainer.begin(), upper, minElement);

		sortedContainer.insert(pos, minElement);
	}
}

std::vector<size_t> PmergeMe::generateJacobsthalIndices(size_t n) const
{
	std::vector<size_t> result;
	if (n == 0)
		return result;

	std::vector<size_t> raw;
	raw.push_back(0);
	raw.push_back(1);

	while (true)
	{
		size_t next = raw[raw.size() - 1] + 2 * raw[raw.size() - 2];
		if (next >= n)
			break;
		raw.push_back(next);
	}

	for (size_t i = 1; i < raw.size(); i++)
	{
		if (std::find(result.begin(), result.end(), raw[i]) == result.end())
			result.push_back(raw[i]);
	}

	for (size_t i = 0; i < n; i++)
	{
		if (std::find(result.begin(), result.end(), i) == result.end())
			result.push_back(i);
	}

	return (result);
}
