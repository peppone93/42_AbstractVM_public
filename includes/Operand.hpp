/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 23:16:33 by gbianco           #+#    #+#             */
/*   Updated: 2020/12/22 21:31:00 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <string>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <cmath>
#include "options.hpp"
#include "OperandFactory.hpp"

struct sOptions;

template <typename T>
class Operand : public IOperand
{
public:
	Operand();

	Operand(eOperandType type, T value) :
		m_value(value),
		m_type(type),
		m_precision(type)
	{
		if (type > 2)
		{
			...
		}
		else
			m_toStr = std::to_string(value);
	}

	Operand(const Operand& copy)
	{
		*this = copy; 
	}

	Operand& operator=(const Operand& copy)
	{
		if (this != &copy)
		{
			m_value = copy.m_value;
			m_type = copy.m_type;
			m_precision = copy.m_precision;
			m_toStr = copy.m_toStr;
		}
		return (*this);
	}

	virtual ~Operand(void) {};

	int getPrecision(void) const
	{
		return m_precision;
	}

	eOperandType getType(void) const
	{
		return m_type;
	}

	IOperand const* operator+(IOperand const& rhs) const
	{
		int precision(std::max(getPrecision(), rhs.getPrecision()));
		if (precision < 3)
		{
			long a(std::stol(toString()));
			long b(std::stol(rhs.toString()));
			return (m_operandFactory.createOperand(eOperandType(precision), std::to_string(a + b)));
		}
		long double a(std::stold(toString()));
		long double b(std::stold(rhs.toString()));
		std::stringstream preciseValue;
		long double value = a + b;
		preciseValue.precision(sOptions::accuracy);
		if (std::abs(value) < std::pow(10, -sOptions::accuracy))
			preciseValue << std::defaultfloat << value;
		else
			preciseValue << std::fixed << std::setprecision(sOptions::accuracy) << value;
		return (m_operandFactory.createOperand(eOperandType(precision), preciseValue.str()));
	}

...

private:
	OperandFactory	m_operandFactory;
	T				m_value;
	eOperandType	m_type;
	std::string		m_toStr;
	int				m_precision;
};

#endif // !OPERAND_HPP
