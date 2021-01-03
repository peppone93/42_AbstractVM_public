/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 23:15:59 by gbianco           #+#    #+#             */
/*   Updated: 2020/12/24 00:56:02 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

int sOptions::accuracy = DefaultACCURACY;

bool fillTokenList(Parser& parser, Lexer& lexer, bool& print)
{
	bool stopExecution(false);

	while (parser.readLine())
	{
		try {
			parser.cleanLine();
			lexer.convertLine(parser.getLine(), parser.getLineIndex());
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
			if (!stopExecution)
				stopExecution = true;
		}
	}
	if (stopExecution)
		return false;
	if (print)
		lexer.printTokens();
	return true;
}

bool handleTokenList(AbstractStack& abstractStack, Parser& parser,
	std::vector<std::string> const& token)
{
	IOperand const* temp;

	try {
		unsigned int instruction;
		static unsigned int i;

		for (; i < token.size(); i++)
		{
			instruction = parser.parseInstruction(token[i]);
			if (instruction > VoidOPERANDS - 1)
			{
				temp = parser.parseAdvancedInstruction(token[i + 1], token[i + 2]);
				(abstractStack.*(abstractStack.operandCollection[instruction - VoidOPERANDS]))(temp);
				i += 2;
			}
			else
			{
				(abstractStack.*(abstractStack.voidCollection[instruction]))();
				if (instruction == Exit)
					return true;
			}
		}
	}

	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		return true;
	}
	return false;
}

void standardMode(Parser& parser, sOptions& options)
{
	Lexer			lexer;
	
	if (options.filemode)
		parser.readFile();
	else
		parser.readStandardInput();
	if (fillTokenList(parser, lexer, options.tokenFlag) == false)
		return ;

	AbstractStack	abstractStack(options.verboseFlag);
	if (handleTokenList(abstractStack, parser, lexer.getTokens()) == false)
		throw Exceptions::ExitError();
}

void interactiveMode(Parser& parser, sOptions& options)
{
	AbstractStack	abstractStack(options.verboseFlag);
	Lexer			lexer;
	std::string		str;

	while (getline(std::cin, str))
	{
		try {
			parser.setLine(str);
			parser.cleanLine();
			lexer.convertLine(parser.getLine(), parser.getLineIndex());
			if (options.tokenFlag)
				lexer.printTokens();
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
				continue ;
		}
		if (handleTokenList(abstractStack, parser, lexer.getTokens()) == true)
			return ;
	}
}

void optionSelector(int ac, char** av, sOptions& options)
{
	if (ac < 1 || ac > 6)
		throw Exceptions::InvalidArguments();
	for (int i(1); i < ac; i++)
	{
		std::string const temp(av[i]);
		if (av[i][0] == '-') // check flags
		{
			size_t size(strlen(av[i]));
			switch (av[i][1])
			{
			case 'v':
				if (options.verboseFlag || size != 2)
					throw Exceptions::InvalidArguments();
				options.verboseFlag = true;
				break;
			case 'i':
				if (options.interactiveFlag || size != 2)
					throw Exceptions::InvalidArguments();
				options.interactiveFlag = true;
				break;
			case 't':
				if (options.tokenFlag || size != 2)
					throw Exceptions::InvalidArguments();
				options.tokenFlag = true;
				break;
			case 'p':
				if (options.precisionFlag || size < 2 || size > 4)
					throw Exceptions::InvalidArguments();
				options.precisionFlag = true;
				if (!isdigit(av[i][2]) || (av[i][3] && !isdigit(av[i][3])))
					throw Exceptions::InvalidArguments();
				sOptions::accuracy = atoi(&av[i][2]);
				break;
			default :
				throw Exceptions::InvalidArguments();
			}
		}
		else if (Parser::checkFile(temp))
		{
			if (options.filemode)
				throw Exceptions::InvalidArguments();
			options.filemode = true;
			options.filename = temp;	
		}
		else
			throw Exceptions::InvalidArguments();
	}
}

int main(int ac, char** av)
{
	sOptions	options{};

	try	{
		optionSelector(ac, av, options);

		Parser		parser(options.filename);

		if (options.interactiveFlag && !options.filemode)
			interactiveMode(parser, options);
		else
			standardMode(parser, options);
		}

	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		}
	return 0;
}
