/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 23:15:50 by gbianco           #+#    #+#             */
/*   Updated: 2020/12/22 21:30:14 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandFactory.hpp"
#include "Operand.hpp"

IOperand const*(OperandFactory::*OperandFactory::ptr[])(std::string const& value) const =
{
	&OperandFactory::createInt8,
	&OperandFactory::createInt16,
	&OperandFactory::createInt32,
	&OperandFactory::createFloat,
	&OperandFactory::createDouble,
};

OperandFactory::OperandFactory()
{}

OperandFactory::OperandFactory(OperandFactory const& copy)
{
	*this = copy;
}

OperandFactory& OperandFactory::operator=(OperandFactory const& copy)
{
	static_cast<void>(copy);
	return (*this);
}

OperandFactory::~OperandFactory()
{}

IOperand const* OperandFactory::
	createOperand(eOperandType type, std::string const& value) const
{
	...
}

...