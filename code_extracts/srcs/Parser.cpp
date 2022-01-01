/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 23:15:54 by gbianco           #+#    #+#             */
/*   Updated: 2020/12/25 15:39:26 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

...

void Parser::cleanLine()
{
	m_lineIndex++;
	if (m_line.size())
	{
		std::regex multiSpace("[\\s]+"); // sequence of spaces or tabs
		std::regex allowed("^[0-9a-z()\\s\\-.]+$"); // only valid characters 

		m_line = std::regex_replace(m_line, multiSpace, " ");
		int pos(m_line.find(';'));
		if (pos > -1) // - 1 = not found
		{
			m_line.erase(m_line.find(';')); // remove all after ';'
			if (!m_line.size())
				return;
		}
		if (m_line[0] == ' ')
			m_line.erase(0, 1); // delete first space (index 0, 1 delete)
		if (m_line.size() > 0 && m_line[m_line.size() - 1] == ' ')
			m_line.erase(m_line.size() - 1, 1); // delete last space
		if (m_line.size() && !std::regex_search(m_line, allowed))
			throw Exceptions::SyntaxError(m_lineIndex);
	}
}

...