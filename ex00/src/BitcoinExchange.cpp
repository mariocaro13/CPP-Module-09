/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:26:01 by mcaro-ro          #+#    #+#             */
/*   Updated: 2026/05/06 18:38:48 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

#include <iostream>
#include <sstream>
#include <cstdlib> 

/* ========================================================================== */
/*                               Canonical Form                               */
/* ========================================================================== */

BitcoinExchange::BitcoinExchange(void) {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _exchangeRates(other._exchangeRates) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_exchangeRates = other._exchangeRates;
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void) {}

/* ========================================================================== */
/*                               Validation                                   */
/* ========================================================================== */

bool BitcoinExchange::isValidDate(const std::string& date) const
{
	static const int MIN_YEAR = 2009;
	static const int MAX_YEAR = 2100;

	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return (false);

	for (size_t i = 0; i < date.size(); ++i)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(date[i]))
			return (false);
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (year < MIN_YEAR || year > MAX_YEAR)
		return (false);
	if (month < 1 || month > 12)
		return (false);
	if (day < 1 || day > 31)
		return (false);

	return (true);
}

bool BitcoinExchange::isValidNumber(const std::string& str) const
{
	if (str.empty())
		return (false);
	
	bool hasDecimalPoint = false;
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] == '.')
		{
			if (hasDecimalPoint)
				return (false);
			hasDecimalPoint = true;
		}
		else if (!std::isdigit(str[i]))
			return (false);
	}

	if (str == "." || str[0] == '.' || str[str.size() - 1] == '.')
		return (false);

	return (true);
}

bool BitcoinExchange::isValidValue(const std::string& value) const
{
	if (!isValidNumber(value))
		return (false);

	double number = std::atof(value.c_str());
	if (number < 0.0 || number > 1000.0)
		return (false);

	return (true);
}

bool BitcoinExchange::isValidInput(const std::string& date, const std::string& value) const
{
	if (!isValidDate(date))
	{
		std::cerr << "Error: Invalid date => " << date << std::endl;
		return (false);
	}
	if (!isValidValue(value))
	{
		std::cerr << "Error: Invalid value => " << value << std::endl;
		return (false);
	}
	return (true);
}

/* ========================================================================== */
/*                               Parsing                                      */
/* ========================================================================== */

bool BitcoinExchange::parseDatabaseLine(const std::string& line, std::string& date, std::string& value) const
{
	std::stringstream ss(line);
	if (!std::getline(ss, date, ','))
		return (false);
	if (!std::getline(ss, value))
		return (false);
	return (true);
}

bool BitcoinExchange::parseInputLine(const std::string& line, std::string& date, std::string& value) const
{
	std::stringstream ss(line);

	if (!std::getline(ss, date, '|'))
		return (false);
	if (!std::getline(ss, value))
		return (false);

	trim(date);
	trim(value);

	return (true);
}

/* ========================================================================== */
/*                               Helpers                                      */
/* ========================================================================== */

void BitcoinExchange::trim(std::string& str) const
{
	while (!str.empty() && std::isspace(str[0]))
		str.erase(str.begin());
	while (!str.empty() && std::isspace(str[str.size() - 1]))
		str.erase(str.end() - 1);
}

/* ========================================================================== */
/*                               Business Logic                               */
/* ========================================================================== */

void BitcoinExchange::storeRate(const std::string& date, const std::string& value)
{
	if (!isValidDate(date))
		return ;

	if (!isValidNumber(value))
		return ;
		
	float rate = std::atof(value.c_str());
	_exchangeRates[date] = rate;
}

float BitcoinExchange::getExchangeRate(const std::string& date) const
{
	std::map<std::string, float>::const_iterator it = _exchangeRates.lower_bound(date);

	if (it != _exchangeRates.end() && it->first == date)
		return (it->second);

	if (it == _exchangeRates.begin())
	{
		std::cerr << "Error: No exchange rate available for date => " << date << std::endl;
		return (0.0f);
	}
	
	--it;
	return (it->second);
}

float BitcoinExchange::computeResult(const std::string& date, const std::string& value) const
{
	float amount = std::atof(value.c_str());
	float rate = getExchangeRate(date);
	return (amount * rate);
}

/* ========================================================================== */
/*                               Processing                                   */
/* ========================================================================== */

void BitcoinExchange::processDatabaseLine(const std::string& line)
{
	std::string date, value;
	if (!parseDatabaseLine(line, date, value))
		return ;
	storeRate(date, value);
}

void BitcoinExchange::processInputLine(const std::string& line)
{
	if (line.empty())
		return ;

	std::string date, value;
	if (!parseInputLine(line, date, value))
	{
		std::cerr << "Error: Invalid input format => " << line << std::endl;
		return ;
	}
	if (!isValidInput(date, value))
		return ;

	float result = computeResult(date, value);
	printResult(date, std::atof(value.c_str()), result);
}

/* ========================================================================== */
/*                               Output                                       */
/* ========================================================================== */

void BitcoinExchange::printResult(const std::string& date, float amount, float result) const
{
	std::cout << date << " => " << amount << " = " << result << std::endl;
}

/* ========================================================================== */
/*                               Public Interface                             */
/* ========================================================================== */

void BitcoinExchange::processInput(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: Could not open file " + filename);

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
		processInputLine(line);
}

void BitcoinExchange::loadDatabase(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: Could not open file " + filename);

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		processDatabaseLine(line);
	}
}
