#include "frame.h"
#include "error_codes.h"

frame::frame(console* parent, int number_of_rows, int number_of_columns)
{
	parent_console = parent;
	frame_id = parent_console->add_frame();

	total_rows = number_of_rows;

	total_columns = number_of_columns;
	int x = 0;
	int y = 0;
	ascii_io::get_terminal_size(x, y);
	int column_size = int(x / float(number_of_columns));
	for (int i = 0; i < number_of_columns; i++)
	{
		lane column;
		column.index = i;
		column.size = column_size;
		columns.push_back(column);
	}
}

unsigned int frame::get_column_size(unsigned int column)
{
	unsigned int size = 0;
	for (unsigned int i = 0; i < columns.size(); i++)
	{
		if (columns[i].index == column)
		{
			size = columns[i].size;
			break;
		}
	}
	return size;
}

int frame::set_column_size(unsigned int column, unsigned int spacing)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < columns.size(); i++)
	{
		if (columns[i].index == column)
		{
			columns[i].size = spacing;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

void frame::display()
{
	parent_console->display();
}

void frame::set_controls(int select, int quit, int up, int down, int right, int left)
{
	_select = select;
	_quit = quit;
	_up = up;
	_down = down;
	_right = right;
	_left = left;
}

int frame::get_selection()
{
	int input = 0;
	int selected_row = 0;
	int selected_column = 0;
	int selected_id = -1;
	do
	{
		highlight(selected_row, selected_column);
		display();
		input = ascii_io::getchar();
		if (input == _select)
		{
			widget_info item;
			get_widget(selected_row, selected_column, item);
			if (item.widget_type == MENU)
			{
				selected_id = item.id;
				break;
			}
			
		}
		else if (input == _up)
		{
			if ((selected_row - 1) >= 0)
			{
				selected_row--;
			}
		}
		else if (input == _down)
		{
			if ((selected_row + 1) < total_rows)
			{
				selected_row++;
			}
		}
		else if (input == _right)
		{
			if ((selected_column + 1) < total_columns)
			{
				selected_column++;
			}
		}
		else if (input == _left)
		{
			if ((selected_column - 1) >= 0)
			{
				selected_column--;
			}
		}
	} while (input != _quit);
	return selected_id;
}

int frame::add_widget()
{
	int id = generate_widget_id();
	widget_info new_widget;
	new_widget.id = id;
	widgets.push_back(new_widget);
	return id;
}

int frame::set_position(int id, int row, int column)
{
	int status = ELEMENT_NOT_FOUND;
	if ((row < total_rows) && (row >= 0) && (column < total_columns) && (column >= 0))
	{
		for (unsigned int i = 0; i < widgets.size(); i++)
		{
			if (widgets[i].id == id)
			{
				widgets[i].row = row;
				widgets[i].column = column;
				status = SUCCESS;
				break;
			}
		}
	}
	else
	{
		status = INVALID_INDEX;
	}
	return status;
}

int frame::set_output(int id, const std::string& output)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].output = output;
			parent_console->set_output(frame_id, get_frame_output());
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_allignment(int id, std::string allignment)
{
	int status = ELEMENT_NOT_FOUND;
	if ((allignment == right_allignment_keyword) || (allignment == left_allignment_keyword) || (allignment == center_allignment_keyword))
	{
		for (unsigned int i = 0; i < widgets.size(); i++)
		{
			if (widgets[i].id == id)
			{
				widgets[i].allignment = allignment;
				parent_console->set_output(frame_id, get_frame_output());
				status = SUCCESS;
				break;
			}
		}
	}
	return status;
}

int frame::set_spacing(int id, int top, int bottom, int right, int left)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].top_spacing = top;
			widgets[i].bottom_spacing = bottom;
			widgets[i].right_spacing = right;
			widgets[i].left_spacing = left;
			parent_console->set_output(frame_id, get_frame_output());
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_widget_type(int id, int type)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].widget_type = type;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_vertical_border(int id, char border)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].vertical_border = border;
			parent_console->set_output(frame_id, get_frame_output());
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_horizontal_border(int id, char border)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].horizontal_border = border;
			parent_console->set_output(frame_id, get_frame_output());
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_corner_border(int id, char border)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].corner_border = border;
			parent_console->set_output(frame_id, get_frame_output());
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_highlight_character(int id, char character)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].highlight_character = character;
			parent_console->set_output(frame_id, get_frame_output());
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::add_border(int id)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].add_border = true;
			parent_console->set_output(frame_id, get_frame_output());
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::highlight(int row, int column)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i].row == row) && (widgets[i].column == column))
		{
			widgets[i].highlight = true;
			status = SUCCESS;
		}
		else if(widgets[i].highlight)
		{
			widgets[i].highlight = false;
		}
	}
	parent_console->set_output(frame_id, get_frame_output());
	return status;
}

bool frame::widget_exists(int id)
{
	bool exists = false;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			exists = true;
			break;
		}
	}
	return exists;
}

int frame::generate_widget_id()
{
	int id = widgets.size();
	return id;
}

std::vector<int> frame::get_row_ids(int row)
{
	std::vector<int> ids;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].row == row)
		{
			ids.push_back(widgets[i].id);
		}
	}
	return ids;
}

std::vector<int> frame::sort_row_ids(std::vector<int> ids)
{
	std::vector<int> sorted_ids;
	unsigned int length = ids.size();
	for (unsigned int i = 0; i <length; i++)
	{
		int index = get_min_id_index(ids);
		sorted_ids.push_back(ids[index]);
		ids.erase(ids.begin() + index);
	}
	return sorted_ids;
}

int frame::get_min_id_index(std::vector<int> ids)
{
	int min_index = 0;
	if (ids.size() > 0)
	{
		min_index = 0;
		int min_id = ids[0];
		for (unsigned int i = 1; i < ids.size(); i++)
		{
			if (ids[i] < min_id)
			{
				min_index = i;
				min_id = ids[i];
			}
		}
	}
	return min_index;
}

bool frame::in_range(int value, int begin, int end)
{
	bool in = false;
	if ((value >= begin) || (value < end))
	{
		in = true;
	}
	return in;
}

std::string frame::get_output(int id)
{
	std::string output = "";
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			output = widgets[i].output;
		}
	}
	return output;
}

int frame::get_widget(int id, widget_info& return_value)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			return_value = widgets[i];
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::get_widget(int row, int column, widget_info& return_value)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i].row) == row && (widgets[i].column == column))
		{
			return_value = widgets[i];
			status = SUCCESS;
			break;
		}
	}
	return status;
}

unsigned int frame::get_widget_width(const widget_info& item)
{
	int raw_width = get_column_size(item.column) - item.left_spacing - item.right_spacing;
	if (item.add_border)
	{
		raw_width = raw_width - 4;
	}
	unsigned int width = 0;
	if (raw_width >= 0)
	{
		width = raw_width;
	}
	return width;
}

std::vector<std::string> frame::get_widget_lines(int id)
{
	widget_info item;
	get_widget(id, item);
	std::string left_spacing = get_spacing(item.left_spacing, ' ');
	std::string right_spacing = get_spacing(item.right_spacing, ' ');
	unsigned int width = get_widget_width(item);
	std::string active_spacing = get_spacing(width, ' ');
	std::vector<std::string> widget_lines;
	std::vector<std::string> user_lines = split_string(item.output, '\n');
	std::string line = "";
	for (int i = 0; i < item.top_spacing; i++)
	{
		widget_lines.push_back(active_spacing);
	}

	for (unsigned int i = 0; i < user_lines.size(); i++)
	{
		if (user_lines[i] == "\n")
		{
			line = fill_line(line, width, item.allignment);
			widget_lines.push_back(line);
			line = "";
		}
		else
		{
			std::vector<std::string> words = split_string(user_lines[i], ' ');
			for (unsigned int j = 0; j < words.size(); j++)
			{
				if ((((line + words[j]).length())) < width)
				{
					line = line + words[j];
				}
				else if (words[j].length() > width)
				{
					std::string first_section = "";
					std::string second_section = "";
					cut_word(words[j], width - line.length(), first_section, second_section);
					line = line + first_section;
					widget_lines.push_back(line);
					line = "";
					second_section.insert(0, "-");
					words.insert(words.begin() + (j + 1), second_section);
				}
				else
				{
					line = fill_line(line, width, item.allignment);
					widget_lines.push_back(line);
					if ((words[j] != " ") && item.widget_type == TEXTBOX)
					{
						line = words[j];
					}
					else
					{
						line = "";
					}
					
				}
			}
		}
	}
	if (line != "")
	{
		line = fill_line(line, width, item.allignment);
		widget_lines.push_back(line);
		line = "";
	}

	for (int i = 0; i < item.bottom_spacing; i++)
	{
		widget_lines.push_back(active_spacing);
	}

	for (unsigned int i = 0; i < widget_lines.size(); i++)
	{
		widget_lines[i].insert(0, left_spacing);
		widget_lines[i] = widget_lines[i] + right_spacing;
	}

	return widget_lines;
}

std::vector<std::string> frame::split_string(std::string str, char split_character)
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

std::string frame::get_spacing(unsigned int length, char space_char)
{
	std::string spacing = "";
	for (unsigned int i = 0; i < length; i++)
	{
		spacing = spacing + space_char;
	}
	return spacing;
}

std::string frame::fill_line(std::string input, unsigned int length, std::string allignment)
{
	if (allignment == left_allignment_keyword)
	{
		while (input.length() < length)
		{
			input = input + " ";
		}
	}
	else if (allignment == center_allignment_keyword)
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
	else if (allignment == right_allignment_keyword)
	{
		while (input.length() < length)
		{
			input.insert(0, " ");
		}
	}
	return input;
}

std::vector<std::string> frame::add_lines(std::vector<std::string> lines, unsigned int number_of_added_lines, unsigned int line_length)
{
	std::string line = get_spacing(line_length, ' ');
	for (unsigned int i = 0; i < number_of_added_lines; i++)
	{
		lines.push_back(line);
	}
	return lines;
}

std::string frame::fuse_columns_into_row(std::vector<std::vector<std::string>> columns_content)
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
		columns_content[column] = add_lines(columns_content[column], max_length - columns_content[column].size(), get_column_size(1));
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

void frame::cut_word(const std::string& word, unsigned int length, std::string& first_section, std::string& second_section)
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

std::string frame::get_frame_output()
{
	std::string frame_output = "";
	std::vector<std::vector<std::string>> columns_output;
	for (int i = 0; i < total_rows; i++)
	{
		std::vector<int> row_ids = get_row_ids(i);
		row_ids = sort_row_ids(row_ids);
		for (unsigned int j = 0; j < row_ids.size(); j++)
		{
			std::vector<std::string> widget_lines;
			widget_lines = get_widget_lines(row_ids[j]);
			widget_info item;
			get_widget(row_ids[j], item);
			if (item.add_border)
			{
				widget_lines.insert(widget_lines.begin(), get_spacing(item.left_spacing, ' ') + std::string(1, item.corner_border) + get_spacing(get_widget_width(item) + 2, item.horizontal_border) + std::string(1, item.corner_border) + get_spacing(item.right_spacing, ' '));
				for (unsigned int k = 1; k < widget_lines.size(); k++)
				{
					widget_lines[k].insert(item.left_spacing, std::string(1, item.vertical_border) + " ");
					widget_lines[k].insert(widget_lines[k].length() - item.right_spacing, " " + std::string(1, item.vertical_border));
				}
				widget_lines.push_back(get_spacing(item.left_spacing, ' ') + std::string(1, item.corner_border) + get_spacing(get_widget_width(item) + 2, item.horizontal_border) + std::string(1, item.corner_border) + get_spacing(item.right_spacing, ' '));
			}

			if (item.highlight)
			{
				(widget_lines[0])[item.left_spacing] = item.highlight_character;
				(widget_lines[0])[widget_lines[0].length() - 1 - item.right_spacing] = item.highlight_character;
				(widget_lines[widget_lines.size() - 1])[item.left_spacing] = item.highlight_character;
				(widget_lines[widget_lines.size() - 1])[widget_lines[widget_lines.size() - 1].length() - 1 - item.right_spacing] = item.highlight_character;
			}

			columns_output.push_back(widget_lines);
		}
		frame_output = frame_output + fuse_columns_into_row(columns_output);
		columns_output.clear();
	}
	return frame_output;
}