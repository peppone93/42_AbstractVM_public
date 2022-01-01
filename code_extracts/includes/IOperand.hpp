/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 23:16:24 by gbianco           #+#    #+#             */
/*   Updated: 2020/12/21 23:16:27 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
#define IOPERAND_HPP

enum eOperandType
{
	Int8,
	Int16,
	Int32,
	Float,
	Double
};

class IOperand
{
public:
	virtual int getPrecision(void) const = 0; // Precision of the type of the instance
	virtual eOperandType getType(void) const = 0; // Type of the instance
	virtual IOperand const* operator+(IOperand const& rhs) const = 0; // Sum
	virtual IOperand const* operator-(IOperand const& rhs) const = 0; // Difference
	virtual IOperand const* operator*(IOperand const& rhs) const = 0; // Product
	virtual IOperand const* operator/(IOperand const& rhs) const = 0; // Quotient
	virtual IOperand const* operator%(IOperand const& rhs) const = 0; // Modulo
	virtual std::string const& toString(void) const = 0; // String representation of the instance
	virtual ~IOperand(void) {}
};

#endif // !IOPERAND_HPP