#pragma once

#include <string>
#include <vector>

class validate_board_config
{
public:
	int validate(std::string content, bool debug);

private:
	struct row_column
	{
		std::string row;
		std::string column;
	};
	int validate_parenthesis(std::string content);
	int validate_parameters(std::string content, bool action_tile_field);
	int validate_number_of_parameters(std::string content, int number_of_parameters);
	int validate_array_index(std::string content, int max_row, int max_column);
	int validate_board_index(std::string content, int max_row, int max_column);
	int validate_number_of_entries(std::string content, int number_of_entries);
	int validate_hyphen_range(std::string content);
	void get_board_dimensions(std::string content, int& row, int& column);
	bool multiple(std::vector<row_column> storage, row_column element);
	bool is_number(std::string number_string);
	int get_rows(std::string content);
	int get_columns(std::string content);
};