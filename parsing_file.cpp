#include "parser.h"

#include <stack>
#include <fstream>
#include <iostream>

std::string Parser::trim(const std::string& str)        // remove leading and tailing whitespace characters
{
    if (str.empty())
    {
        return "";
    }

    size_t start = 0;
    while (start < str.length() && std::isspace(str[start]))
    {
        ++start;
    }
    if (start == str.length())
    {
        return "The string contains only whitespace";
    }

    size_t end = str.length() - 1;
    while (end > start && std::isspace(str[end]))
    {
        --end;
    }
    return str.substr(start, end - start + 1);
}

void Parser::parsing_file(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("ailed to open file");
    }    

    bool comment_block = false;

    std::string line;
    int line_count;

    while (std::getline(file, line))
    {
        ++line_count;
        line = trim(line);

        size_t comment_start = line.find("/*");
        size_t comment_end = line.find("*/");

        if (comment_start != std::string::npos)
        {
            if (comment_end != std::string::npos && comment_start < comment_end)
            {
                line = line.substr(0, comment_start) + line.substr(comment_end + 2);
            }
            else
            {
                comment_block = true;
                line = line.substr(0, comment_start);
            }
        }
        else  if (comment_block)
        {
            comment_end = line.find("*/");
            if (comment_end != std::string::npos)
            {
                comment_block = false;
                line = line.substr(comment_end + 2);
            }
            else
            {
                line = "";
            }
        }

        size_t line_comment = line.find("//");
        if (line_comment != std::string::npos)
        {
            line = line.substr(0, line_comment);
        }

        // Check parentheses

        int brace_count = 0;
        std::stack<char> result;
        for (int i = 0; i < line.size(); ++i)
        {
            if (line[i] == '(') 
            {
                result.push(line[i]);
                brace_count++;
                continue;
            }
            else if (line[i] == ')')
            {
                if (result.empty() || result.top() != '(')
                {
                    return;
                }
                else
                {
                    result.pop();
                }
                --brace_count;
                continue;;
            }

            if (line[i] == '{') 
            {
                result.push(line[i]);
                brace_count++;
                continue;
            }
            else if (line[i] == '}')
            {
                if (result.empty() || result.top() != '{')
                {
                    return;
                }
                else
                {
                    result.pop();
                }
                --brace_count;
                continue;;
            }

            if (line[i] == '[') 
            {
                result.push(line[i]);
                brace_count++;
                continue;
            }
            else if (line[i] == ']')
            {
                if (result.empty() || result.top() != '[')
                {
                    return;
                }
                else
                {
                    result.pop();
                }
                --brace_count;
                continue;;
            }
        }
        if (brace_count != 0)
        {
            throw std::runtime_error("You missed or overused { or }");
        }
    }
    file.close();
}