#include "format_tools.h"

std::vector<std::string> format_tools::split_string(std::string str, char split_character)
{
	std::string section = "";
	std::vector<std::string> sections;
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (str[i] == split_character)
		{
			sections.push_back(section);
			if (section != std::string(1, split_character))
			{
				sections.push_back(std::string(1, split_character));
			}
			section = "";
		}
		else
		{
			section = section + str[i];
		}
	}

	if (section != "")
	{
		sections.push_back(section);
	}

	return sections;
}

void format_tools::cut_word(const std::string& word, unsigned int length, std::string& first_section, std::string& second_section)
{
	first_section = "";
	second_section = "";
	if (length > word.length())
	{
		length = word.length();
	}

	for (unsigned int i = 0; i < length; i++)
	{
		first_section = first_section + word[i];
	}

	for (unsigned int i = length; i < word.length(); i++)
	{
		second_section = second_section + word[i];
	}
}

std::string format_tools::get_spacing(unsigned int length, char space_char)
{
	std::string spacing = "";
	for (unsigned int i = 0; i < length; i++)
	{
		spacing = spacing + space_char;
	}
	return spacing;
}

std::string format_tools::fill_line(std::string input, unsigned int length, std::string allignment)
{
	if (allignment == left_alignment_keyword)
	{
		while (input.length() < length)
		{
			input = input + " ";
		}
	}
	else if (allignment == center_alignment_keyword)
	{
		bool begin = true;
		while (input.length() < length)
		{
			if (begin)
			{
				input.insert(0, " ");
				begin = false;
			}
			else
			{
				input = input + " ";
				begin = true;
			}
		}
	}
	else if (allignment == right_alignment_keyword)
	{
		while (input.length() < length)
		{
			input.insert(0, " ");
		}
	}
	return input;
}

std::vector<std::string> format_tools::add_lines(std::vector<std::string> lines, unsigned int number_of_added_lines, unsigned int line_length)
{
	std::string line = get_spacing(line_length, ' ');
	for (unsigned int i = 0; i < number_of_added_lines; i++)
	{
		lines.push_back(line);
	}
	return lines;
}

std::string format_tools::fuse_columns_into_row(std::vector<std::vector<std::string>> columns_content, unsigned int widget_width_with_spacing)
{
	std::string row = "";
	unsigned int max_length = 0;
	for (unsigned int column = 0; column < columns_content.size(); column++)
	{
		if (columns_content[column].size() > max_length)
		{
			max_length = columns_content[column].size();
		}
	}

	for (unsigned int column = 0; column < columns_content.size(); column++)
	{
		columns_content[column] = format_tools::add_lines(columns_content[column], max_length - columns_content[column].size(), widget_width_with_spacing);
	}

	for (unsigned int line = 0; line < max_length; line++)
	{
		for (unsigned int column = 0; column < columns_content.size(); column++)
		{
			row = row + (columns_content[column])[line];
		}
		row = row + "\n";
	}
	return row;
}

std::vector<std::string> format_tools::get_lines(const std::string& output_string)
{
	std::vector<std::string> output_lines;
	std::string line = "";
	for (unsigned int i = 0; i < output_string.length(); i++)
	{
		line = line + output_string[i];
		if (output_string[i] == '\n')
		{
			output_lines.push_back(line);
			line = "";
		}
	}
	if (line != "")
	{
		output_lines.push_back(line);
	}
	return output_lines;
}

std::vector<std::string> format_tools::remove_trailing_whitespace(const std::vector<std::string>& lines)
{
	std::vector<std::string> updated_lines;
	std::string line = "";
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		for (unsigned int j = 0; j < lines[i].length(); j++)
		{
			line = line + (lines[i])[j];
		}

		unsigned int line_length = line.length() - 1;
		for (int j = line_length; j >= 0; j--)
		{
			if (line[j] == ' ')
			{
				line.erase(j);
			}
			else if (line[j] != '\n')
			{
				break;
			}
		}
		if ((line != "\n") && (line != ""))
		{
			updated_lines.push_back(line);
		}
		line = "";
	}
	return updated_lines;
}

void format_tools::mask_string(std::string& output, const std::string& old_output)
{
	std::vector<std::string> new_output_lines = get_lines(output);
	std::vector<std::string> old_output_lines = remove_trailing_whitespace(get_lines(old_output));
	for (unsigned int i = 0; i < old_output_lines.size(); i++)
	{
		if (i < new_output_lines.size())
		{
			if (old_output_lines[i].length() > new_output_lines[i].length())
			{
				while ((old_output_lines[i].length() - new_output_lines[i].length()) != 0)
				{
					new_output_lines[i].insert(new_output_lines[i].length() - 2, " ");
				}
			}
		}
		else
		{
			std::string spacer = "";
			for (unsigned int j = 0; j < old_output_lines[i].length(); j++)
			{
				spacer = spacer + " ";
			}
			new_output_lines.push_back(spacer);
		}
	}

	output = "";
	for (unsigned int i = 0; i < new_output_lines.size(); i++)
	{
		output = output + new_output_lines[i];
	}
}