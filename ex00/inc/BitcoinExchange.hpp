/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:26:04 by mcaro-ro          #+#    #+#             */
/*   Updated: 2026/05/06 18:37:03 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>
# include <fstream>

class BitcoinExchange
{
	private:
		std::map<std::string, float> _exchangeRates;

		// ------ Validation ------
		bool isValidNumber(const std::string& str) const;

		/* Validates the value format and range for Bitcoin amounts.
		*
		* EXPECTED FORMAT: Positive decimal number (e.g., "123.45", "0.1", "1000")
		* - Only digits and at most one decimal point allowed
		* - Cannot start or end with decimal point
		* - Cannot be just a single decimal point
		*
		* VALUE RANGE: [0.0, 1000.0]
		* - Minimum 0.0: Zero amount is technically valid but unusual
		* - Maximum 1000.0: Reasonable upper limit for Bitcoin exchange amounts
		*   Prevents processing of unrealistically large transactions
		*
		* PARAM: value - The string to validate (expected: numeric string)
		* RETURN: true if the value is valid, false otherwise
		*/
		bool isValidValue(const std::string& value) const;
		
		/* Validates the date format and range.
		*
		* EXPECTED FORMAT: "YYYY-MM-DD"
		* - Characters at positions 4 and 7 MUST be '-' (separators)
		* - This ensures the string has the correct format before parsing
		*
		* YEAR RANGE: [2009, 2100]
		* - 2009: Bitcoin was created on January 3, 2009 by Satoshi Nakamoto
		*   No exchange rate data exists before this date
		* - 2100: Arbitrary but reasonable upper limit for future validations
		*
		* PARAM: date - The string to validate (expected: "YYYY-MM-DD")
		* RETURN: true if the date is valid, false otherwise
		*/
		bool isValidDate(const std::string& date) const;
		bool isValidInput(const std::string& date, const std::string& value) const;

		// ------ Parsing ------
		bool parseDatabaseLine(const std::string& line, std::string& date, std::string& value) const;
		bool parseInputLine(const std::string& line, std::string& date, std::string& value) const;

		// ------ Helpers ------
		void trim(std::string& str) const;
		
		// ------ Processing ------
		void processDatabaseLine(const std::string& line);
		void processInputLine(const std::string& line);
		
		// ------ Business Logic ------
		void storeRate(const std::string& date, const std::string& value);
		float computeResult(const std::string& date, const std::string& value) const;
		
		/* Retrieves the Bitcoin exchange rate for a given date.
		*
		* LOGIC:
		* - Uses lower_bound to find the first date >= requested date
		* - If exact match found, returns that rate
		* - Otherwise, use the rate from the previous date (--it)
		* - If iterator is at beginning (no earlier dates), error and return 0.0
		*
		* This implements "previous available rate" rule used in financial data.
		*
		* PARAM: date - The date to lookup (format: "YYYY-MM-DD")
		* RETURN: Exchange rate as float, or 0.0f if no valid rate found
		*/
		float getExchangeRate(const std::string& date) const;
		
		// ------ Output ------
		void printResult(const std::string& date, float amount, float result) const;

	public:
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange(void);

		void loadDatabase(const std::string& filename);
		void processInput(const std::string& filename);
};

#endif
