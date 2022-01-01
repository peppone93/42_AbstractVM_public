/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractStack.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 23:15:24 by gbianco           #+#    #+#             */
/*   Updated: 2020/12/22 23:25:24 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractStack.hpp"

AbstractStack::AbstractStack(bool verbose) :
	m_operandFactory(),
	m_verbose(verbose)
{
	voidCollection[0] = &AbstractStack::pop;
	voidCollection[1] = &AbstractStack::dump;
	voidCollection[2] = &AbstractStack::add;
	voidCollection[3] = &AbstractStack::sub;
	voidCollection[4] = &AbstractStack::mul;
	voidCollection[5] = &AbstractStack::div;
	voidCollection[6] = &AbstractStack::mod;
	voidCollection[7] = &AbstractStack::print;
	voidCollection[8] = &AbstractStack::exit;
	voidCollection[9] = &AbstractStack::min;
	voidCollection[10] = &AbstractStack::max;
	voidCollection[11] = &AbstractStack::pow;
	voidCollection[12] = &AbstractStack::sin;
	voidCollection[13] = &AbstractStack::cos;
	voidCollection[14] = &AbstractStack::lshift;
	voidCollection[15] = &AbstractStack::rshift;
	operandCollection[0] = &AbstractStack::push;
	operandCollection[1] = &AbstractStack::assert;
}

AbstractStack::AbstractStack(AbstractStack const& copy)
{
	*this = copy;
}

AbstractStack& AbstractStack::operator=(AbstractStack const& copy)
{
	static_cast<void>(copy);
	return (*this);
}

AbstractStack::~AbstractStack()
{
	for (size_t i(0); i < size(); i++)
		delete at(i);
}

void AbstractStack::mul()
{
	if (size() < 2)
		throw Exceptions::MathError("Not enough terms for \033[32mMULTIPLICATION\033[0m");
	IOperand const* a = at(size() - 1);
	IOperand const* b = at(size() - 2);
	IOperand const* c = *a * *b;
	if (m_verbose)
		std::cout << "[\033[34mMultiplication\033[0m] " << Lexer::m_operands[a->getType()]
		<< "(" << C_GREEN << a->toString() << C_RESET << ") * "
		<< Lexer::m_operands[b->getType()] << "(" << C_GREEN << b->toString() << C_RESET << ")" << std::endl;	
	cleanElement();
	cleanElement();
	push_back(c);
}

...

void AbstractStack::rshift()
{
	if (size() < 1)
		throw Exceptions::Shift("Not enough terms for \033[32mRIGHT SHIFT\033[0m");
	IOperand const* A = back();
	if (A->getPrecision() > 2)
		throw Exceptions::Shift
			("Operation not allowed with floating type [\033[34m" + A->toString() + "\033[0m]");
	if (m_verbose)
		std::cout << "[\033[34mRight Shift\033[0m] " << Lexer::m_operands[A->getType()]
		<< "(" << C_GREEN << A->toString() << C_RESET << ")" << std::endl;
	IOperand const* b;
	long a(std::stol(A->toString()));
	b = m_operandFactory.createOperand(eOperandType(A->getPrecision()), std::to_string(a >> 1));
	cleanElement();
	push_back(b);
}

...