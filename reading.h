#pragma once
#include "utilites.h"

using namespace std;

List<place>* read_file(ifstream& input_file)
{
	ifstream check("Text_input.txt", ios::binary | ios::ate);
	if (check.tellg() == 0)
		throw out_of_range("No symbols in file");
	check.close();
	List<place>* list_s = new List<place>();
	string name;
	char buf = NULL;
	int counter = 0;
	int saving = 0;
	input_file.seekg(0);
	Node<place>* save1 = NULL, * save2 = NULL;
	Node<place>* list_iterator = NULL;
	while (!input_file.eof())
	{
		input_file.get(buf);
		if (buf != ';')
			name.push_back(buf);
		else
		{
			if (counter == 2)
			{
				saving = input_file.tellg();
				if (name != "N/A")
				{
					input_file.seekg(saving - name.size() - 1);
					input_file >> saving;
					save1->value.push_back_edge(&save1->value, &save2->value, saving);
					input_file.get(buf);
				}
				name.clear();
				while (!input_file.eof())
				{
					input_file.get(buf);
					if (buf != ';')
						name.push_back(buf);
					else break;
				}
				saving = input_file.tellg();
				if (name != "N/A")
				{
					input_file.seekg(saving - name.size() - 1);
					input_file >> saving;
					save2->value.push_back_edge(&save2->value, &save1->value, saving);
					input_file.get(buf);
				}
				counter = 0;
				input_file.get(buf);
			}
			else
			{
				if (check_name(list_s, name))
				{
					place new_place(name);
					list_s->push_back(&new_place);
				}
				list_iterator = list_s->Get_Root();
				while (list_iterator != NULL)
				{
					if (list_iterator->value.name == name)
					{
						counter == 0 ? save1 = list_iterator : save2 = list_iterator;
						break;
					}
					else
						list_iterator = list_iterator->next;
				}

				counter++;
			}
			name.clear();
		}
	}
	return list_s;
}
