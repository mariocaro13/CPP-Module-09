/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 12:52:21 by mcaro-ro          #+#    #+#             */
/*   Updated: 2026/05/11 14:02:36 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <string>
# include <stdexcept>
# include <ctime>
# include <iostream>

class PmergeMe
{
	public:
		PmergeMe(void);
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe(void);

		void parseInput(int argc, char **argv);

		void sortVector(void);
		void sortDeque(void);

		void printBeforeSort(void) const;
		void printAfterSort(void) const;

		double getVectorSortTime(void) const;
		double getDequeSortTime(void) const;
		double getTimeUs(void);

	private:
		std::vector<int> _vector;
		std::deque<int> _deque;

		double _vectorSortTime;
		double _dequeSortTime;

		template <typename Container>
		void mergeInsertSort(Container& container);

		template <typename Container>
		void makePairs(const Container& container, std::vector<std::pair<int, int> >& pairs, bool& hasOdd, int& oddValue);

		void extractMaxPairs(const std::vector<std::pair<int, int> >& pairs, std::vector<int>& maxElements);

		template <typename Container>
		void insertMinElements(const std::vector<std::pair<int, int> >& pairs, Container& sortedContainer);

		std::vector<size_t> generateJacobsthalIndices(size_t n) const;

		template <typename Container>
		void printContainer(const Container& container) const;

};

#endif
