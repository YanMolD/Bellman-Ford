#pragma once
#include "Structures.h"

using namespace std;

int find_place_pos(string name, List<place>* list_p)
{
	Node<place>* buf = list_p->Get_Root();
	int counter = 0;
	while (buf != NULL)
	{
		if (buf->value.name == name)
			return counter;
		else
			buf = buf->next;
		counter++;
	}
	throw out_of_range("No places with that name");
}

bool check_name(List<place>* places, string name)
{
	Node<place>* buf = places->Get_Root();
	while (buf != NULL)
	{
		if (buf->value.name == name)
			return false;
		else
			buf = buf->next;
	}
	return true;
}

int count_edges(List<place>* list_p)
{
	Node<place>* buf = list_p->Get_Root();
	int counter = 0;
	while (buf != NULL)
	{
		counter += buf->value.edges_from->size_t();
		buf = buf->next;
	}
	return counter;
}

void fill_adjacency_matrix(List<place>* list_p, int** matrix)
{
	Node<place>* buf_place = list_p->Get_Root();
	Node<place::edge>* buf_edge;
	for (int i = 0; i < list_p->size_t(); i++)
		for (int j = 0; j < list_p->size_t(); j++)
			matrix[i][j] = 0;
	for (int i = 0; i < list_p->size_t(); i++, buf_place = buf_place->next)
	{
		buf_edge = buf_place->value.edges_from->Get_Root();
		for (int j = 0; j < buf_place->value.edges_from->size_t(); j++, buf_edge = buf_edge->next)
			matrix[i][find_place_pos(buf_edge->value.to->name, list_p)] = buf_edge->value.value;
	}
	for (int i = 0; i < list_p->size_t(); i++)
	{
		for (int j = 0; j < list_p->size_t(); j++)
		{
			cout << matrix[i][j] << "   ";
		}
		cout << endl << endl;
	}
}

int** fill_main_matrix(int amount_of_edges, List<place>* list_p, place* start, place* end)
{
	if (start == end)
		throw invalid_argument("You are already there");
	int buffer = count_edges(list_p);
	int** matrix = new int* [buffer];
	for (int i = 0; i < buffer; i++)
		matrix[i] = new int[list_p->size_t()];
	for (int i = 0; i < buffer; i++)
		for (int j = 0; j < list_p->size_t(); j++)
			matrix[i][j] = 0;
	int save_pos = 0;
	for (int i = 1; i < amount_of_edges; i++)
	{
		for (int j = 0; j < list_p->size_t(); j++)
		{
			if (i == 1)
				for (int l = 0; l < start->edges_from->size_t(); l++)
					matrix[i][find_place_pos(start->edges_from->at(l).to->name, list_p)] = start->edges_from->at(l).value;
			else
			{
				if (matrix[i - 1][j] != 0)
				{
					for (int l = 0; l < list_p->at(j).edges_from->size_t(); l++)
					{
						for (int l = 0; l < list_p->at(j).edges_from->size_t(); l++)
						{
							save_pos = find_place_pos(list_p->at(j).edges_from->at(l).to->name, list_p);
							matrix[i][save_pos] =
								(matrix[i][save_pos] == 0 ?
									matrix[i - 1][j] + list_p->at(j).edges_from->at(l).value :
									(matrix[i][save_pos] > matrix[i - 1][j] + list_p->at(j).edges_from->at(l).value ?
										matrix[i - 1][j] + list_p->at(j).edges_from->at(l).value :
										matrix[i][save_pos]));
						}
					}
				}
			}
		}
		/*for (int f = 0; f < list_p->size_t(); f++)
		{
			cout << matrix[i][f] << "    ";
		}
		cout << endl << endl;*/
	}
	return matrix;
}

int recreate_way(List<place>* list_p, place* start, place* end, int** matrix)
{
	int f = find_place_pos(end->name, list_p);
	int aog_buf = count_edges(list_p);
	int min_way_value = matrix[aog_buf - 1][f];
	int amount_of_edges = 0;
	for (int i = 0; i < aog_buf; i++)
	{
		if ((matrix[i][f] != 0) && (matrix[i][f] < min_way_value))
		{
			min_way_value = matrix[i][f];
			amount_of_edges = i;
		}
	}
	List<place>* List_of_p_way = new List<place>();
	List_of_p_way->push_front(&list_p->at(f));
	while (amount_of_edges != 0)
	{
		for (int i = 0; i < List_of_p_way->Get_Root()->value.edges_to->size_t(); i++)
		{
			if (matrix[amount_of_edges][f] - List_of_p_way->Get_Root()->value.edges_to->at(i).value ==
				matrix[amount_of_edges - 1][find_place_pos(List_of_p_way->Get_Root()->value.edges_to->at(i).from->name, list_p)])
			{
				amount_of_edges--;
				f = find_place_pos(List_of_p_way->Get_Root()->value.edges_to->at(i).from->name, list_p);
				List_of_p_way->push_front(&list_p->at(f));
				break;
			}
		}
	}
	Node<place>* buf = List_of_p_way->Get_Root();
	while (buf->next != NULL)
	{
		cout << "From " << buf->value.name << " to " << buf->next->value.name << " ";
		buf = buf->next;
	}
	if (min_way_value == 0)
		throw logic_error("No way to this place");
	cout << endl << "Total way will be " << min_way_value;
	return min_way_value;
}