#pragma once
#include "List.h"

using namespace std;

struct place
{
	struct edge
	{
		place* from;
		place* to;
		int value;
		void push_back_edge_to(edge* value, place* to)
		{
			to->edges_to->push_back(value);
		}
		edge(place* from, place* to, int value)
		{
			this->from = from;
			this->to = to;
			this->value = value;
			push_back_edge_to(this, to);
		}
		edge()
		{
			from = NULL;
			to = NULL;
			value = 0;
		}
	};

	void push_back_edge(place* from, place* to, int value)
	{
		edge buf_e(from, to, value);
		edges_from->push_back(&buf_e);
	}
	string name;
	List<place::edge>* edges_from;
	List<place::edge>* edges_to;
	place(string name)
	{
		this->name = name;
		edges_from = new List<edge>();
		edges_to = new List<edge>();
	}
	place()
	{
		name = "";
		edges_from = NULL;
		edges_to = NULL;
	}
};
