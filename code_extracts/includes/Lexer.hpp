/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 23:16:28 by gbianco           #+#    #+#             */
/*   Updated: 2020/12/21 23:16:32 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include "Exceptions.hpp"
#include "IOperand.hpp"

#define N_INSTRUCTIONS 18
#define N_OPERANDTYPES 5

enum eInstruction
{
	Pop,
	Dump,
	Add,
	Sub,
	Mul,
	Div,
	Mod,
	Print,
	Exit,
	Min,
	Max,
	Pow,
	Sin,
	Cos,
	Lshift,
	Rshift,
	Push,
	Assert
};

class Lexer
{
public:
	Lexer();
	Lexer(Lexer const& copy);
	Lexer& operator=(Lexer const& copy);
	~Lexer();

	void convertLine(std::string const& line, int const& lineIdx);
	eInstruction evaluateInstruction();
	eOperandType evaluateOperand();
	void evaluateValue();
	void printTokens() const;
	std::vector<std::string> const& getTokens() const;

	static std::string m_instructions[];
	static std::string m_operands[];

private:
	std::vector<std::string> m_token;
	std::string m_subline;
	unsigned int m_lineIndex;
};

#endif //!LEXER_HPP
