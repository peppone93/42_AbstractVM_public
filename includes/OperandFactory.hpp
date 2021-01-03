/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 23:16:38 by gbianco           #+#    #+#             */
/*   Updated: 2020/12/21 23:16:40 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDFACTORY_HPP
#define OPERANDFACTORY_HPP

#include <iostream>
#include <string>
#include <cstdint>
#include <cfenv>
#include <cfloat>
#include "options.hpp"
#include "IOperand.hpp"
#include "Exceptions.hpp"

class OperandFactory
{
public:
	OperandFactory();
	OperandFactory(OperandFactory const& copy);
	OperandFactory& operator=(OperandFactory const& copy);
	~OperandFactory();

	IOperand const* createOperand(eOperandType type, std::string const& value) const;

private:
	IOperand const* createInt8(std::string const& value) const;
	IOperand const* createInt16(std::string const& value) const;
	IOperand const* createInt32(std::string const& value) const;
	IOperand const* createFloat(std::string const& value) const;
	IOperand const* createDouble(std::string const& value) const;
	static IOperand const*(OperandFactory::* ptr[])(std::string const& value) const;
};

#endif //!OPERANDFACTORY_HPP
