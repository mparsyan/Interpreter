#include "parser.h"

Parser::Parser(const std::string& filename) : m_filename(filename) {}

bool Parser::array_brackets(const std::string& str)
{
    if (str.empty() || str.back() != ']')
    {
        return false;
    }
    for (int i = 0; i < str.size(); ++i)
    {
        if (str[i] == '[')
        {
            return true;
        }
    }
    return false;
}

bool Parser::is_number(const std::string& str)
{
    std::stringstream iss(str);
    double number;
    return (iss >> number) ? true : false;
}

std::vector<std::string> Parser::tokenize(const std::string line)
{
    std::vector<std::string> tokens;
    std::istringstream iss(line);
    std::string token;
    
    while (iss >> token)
    {
        tokens.push_back(token);
    }

    return tokens;
}

Parser::variable Parser::get_variable(const std::string& variable_name)
{
    if (int_variables.find(variable_name) != int_variables.end())
    {
        return int_variables[variable_name];
    }
}

template <typename T,typename U>
bool Parser::comparison(const std::string& op, const T& value1, const U& value2)
{

}