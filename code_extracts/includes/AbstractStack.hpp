/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractStack.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 23:16:13 by gbianco           #+#    #+#             */
/*   Updated: 2020/12/21 23:16:15 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTSTACK_HPP
#define ABSTRACTSTACK_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <cmath>
#include "options.hpp"
#include "Lexer.hpp"
#include "Exceptions.hpp"
#include "IOperand.hpp"
#include "OperandFactory.hpp"

#undef assert

class IOperand;
class OperandFactory;

class AbstractStack : public std::deque<IOperand const*>
{
	public:
		AbstractStack(bool verbose);
		AbstractStack(AbstractStack const& copy);
		AbstractStack& operator=(AbstractStack const& copy);
		~AbstractStack();

		void pop();
		void dump();
		void add();
		void sub();
		void mul();
		void div();
		void mod();
		void print();
		void exit();
		void min();
		void max();
		void pow();
		void sin();
		void cos();
		void lshift();
		void rshift();
		void push(IOperand const* operand);
		void assert(IOperand const* operand);

		void (AbstractStack::* voidCollection[16])(void);
		void (AbstractStack::* operandCollection[2])(IOperand const* operand);

		void cleanElement();

	private:
		OperandFactory	m_operandFactory;
		bool 			m_verbose;
};

#endif //!ABSTRACTSTACK_HPP
