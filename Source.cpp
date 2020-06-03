#include "reading.h"

using namespace std;

void main()
{
	ifstream input_file("Text_input.txt");
	List<place>* list_of_p = read_file(input_file);
	int start = 0, finish = 0;
	int** matrix = new int* [list_of_p->size_t()];
	for (int i = 0; i < list_of_p->size_t(); i++)
		matrix[i] = new int[list_of_p->size_t()];
	cout << "Select start:\n";
	for (int i = 1; i <= list_of_p->size_t(); i++)
	{
		cout << i << ". " << list_of_p->at(i - 1).name << endl;
	}
	cin >> start;
	cout << "Select end- ";
	cin >> finish;
	fill_adjacency_matrix(list_of_p, matrix);
	int** main_matrix = fill_main_matrix(count_edges(list_of_p), list_of_p, &list_of_p->at(start - 1), &list_of_p->at(finish - 1));
	recreate_way(list_of_p, &list_of_p->at(start - 1), &list_of_p->at(finish - 1), main_matrix);
}