#ifndef PARSER_H
#define PARSER_H

#include <map>
#include <string>
#include <vector>
#include <variant>
#include <sstream>
#include <unordered_map>

class Parser
{
private:
    using variable = std::variant<int, char, bool, std::string, std::vector<int>>;

    std::string m_filename;
    std::unordered_map<std::string, int> int_variables;
    std::unordered_map<std::string, bool> bool_variables;
    std::unordered_map<std::string, char> char_variables;
    std::unordered_map<std::string, float> float_variables;
    std::unordered_map<std::string, double> double_variables;
    std::unordered_map<std::string, std::string> string_variables;

    std::map<std::string, std::vector<int>> int_array;
    std::map<std::string, std::vector<bool>> bool_array;
    std::map<std::string, std::vector<char>> char_array;
    std::map<std::string, std::vector<float>> float_array;
    std::map<std::string, std::vector<double>> double_array;

private:
    std::string trim(const std::string& str);
    bool array_brackets(const std::string& str);
    bool is_number(const std::string& str);
    std::vector<std::string> tokenize(const std::string line);
    variable get_variable(const std::string& variable_name);
    
    template <typename T, typename U>
    bool comparison(const std::string& op, const T& value1, const U& value2);


public:
    Parser(const std::string& filename);

    void parsing_file(const std::string& filename);


public:
    std::vector<std::string> tokenize(const std::string& line);
};

#endif  // PARSER_H