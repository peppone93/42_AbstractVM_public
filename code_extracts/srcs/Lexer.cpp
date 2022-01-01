/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 23:15:45 by gbianco           #+#    #+#             */
/*   Updated: 2020/12/21 23:15:48 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

std::string Lexer::m_instructions[] =
{ 
	"pop", "dump", "add", "sub", "mul", "div", "mod", "print", "exit",
	"min", "max", "pow", "sin", "cos", "lshift", "rshift",
	"push", "assert"
};

std::string Lexer::m_operands[] =
{ "int8", "int16", "int32", "float", "double" };

Lexer::Lexer() :
	m_lineIndex(0)
{}

Lexer::Lexer(Lexer const& copy) :
	m_lineIndex(copy.m_lineIndex)
{
	*this = copy;
}

Lexer& Lexer::operator=(Lexer const& copy)
{
	static_cast<void>(copy);
	return (*this);
}

Lexer::~Lexer()
{}

void Lexer::convertLine(std::string const& line, int const& lineIdx)
{
	eInstruction instruction;
	eOperandType operand;

	m_lineIndex = lineIdx;
	if (line.size())
	{
		size_t start(0);
		size_t end(line.find(' '));
		m_subline = line.substr(start, end);
		instruction = evaluateInstruction();
		if (instruction == Push || instruction == Assert)
		{
			start = end + 1;
			end = line.find('(', start);
			if (end == std::string::npos)
				throw Exceptions::SyntaxError(m_lineIndex);
			m_subline = line.substr(start, end - start);
			operand = evaluateOperand();
			start = end + 1;
			end = line.find(')', start);
			if (end == std::string::npos)
				throw Exceptions::SyntaxError(m_lineIndex);
			m_subline = line.substr(start, end - start);
			evaluateValue();
		}
		if (line.size() - 1 > end)
			throw Exceptions::SyntaxError(m_lineIndex); // if instructions are dirty
		m_token.push_back(std::to_string(instruction));
		if (instruction == Push || instruction == Assert)
		{
			m_token.push_back(std::to_string(operand));
			m_token.push_back(m_subline);
		}
	}
}

...

std::vector<std::string> const& Lexer::getTokens() const
{
	return m_token;
}
