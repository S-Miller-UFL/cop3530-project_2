#pragma once
/*
* we need to get the size of the map,n, and make an nxn matrix
* at every index of our matrix,we will look at the column number and get the node at that column number, M.
* we will input into the specified index 1/outdegree(M).
*/
class mtrx
{
public:
	void create_matrix(int,int);
	std::vector<std::vector<int>>* get_matrix();
	std::vector<std::vector<int>>& insert_at_index(int, int, int);

private:
	int rows, columns = 0;
	std::vector<std::vector<int>> rows_vector;
	std::vector<std::vector<int>>* matrix;
	/*
	int* arr_columns;
	int** arr_rows;
	int*** matrix;
	*/
};
void mtrx::create_matrix(int rows, int columns)
{
	this->rows = rows;
	this->columns = columns;

	for (int i = 0; i < rows; i++)
	{
		std::vector<int> columns_vector;
		for (int i = 0; i < columns; i++)
		{
			columns_vector.push_back(0);
		}
		rows_vector.push_back(columns_vector);
	}
	matrix = &rows_vector;
	/*
	arr_columns[] = ;
	for (int i = 0; i < rows; i++)
	{
		arr_columns[i] = 0;

	}
	//arr_rows
	matrix = new int**[rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new int*[columns];
	}
	*/
}
std::vector<std::vector<int>>* mtrx::get_matrix()
{
	return matrix;
}

std::vector<std::vector<int>>& mtrx::insert_at_index(int row, int column, int value)
{
	this->rows_vector.at(row).at(column) = value;
	return rows_vector;
}
