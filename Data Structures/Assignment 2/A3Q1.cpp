#include<iostream>
using namespace std;
void getcombination(int* &arr, int& size, int& index, bool& check, int& a);
void getcombination1(int* &arr, int& size, int& index, bool& check, int& a);
void print(int*&arr, int size);
bool placePosition(int x, int j, int* &s, int size);  //j is colum x is row
int chess = 1;
void main()
{

	int* queen;
	int size;//size of array
	cout << "Enter size of chess board:";
	cin >> size;
	if (size <= 0 || size == 1)
	{
		system("pause");
		return;
	}
	queen = new int[size];
	int k = 0;
	int j = 0;
	bool flag = false;

	getcombination(queen, size, k, flag, j);
	system("pause");
}

void getcombination(int* &arr, int& size, int& index, bool& check, int& value)
{

	if (check == false)
	{

		for (int i = index; i < size; i++)
		{

			if (value >= size)
			{
				int t = 0;
				if (index == 0)
				{
					index = -222;     //assigning grbage value if we want to remove last data
					return;
				}
				t = arr[index - 1] + 1;
				arr[index - 1] = -1234224;  //if we remove want to go last position   
				int z = index - 1;
				getcombination(arr, size, z, check, t);
				return;


			}
			for (int j = value; j < size; j++){
				if (placePosition(j, i, arr, size))  //check posiotn
				{
					arr[index] = j;
					index++;
					check = true;
					value = 0;
					break;

				}

			}
			if (!check)
			{
				check = false;
				break;
			}
			check = false;

		}

	}
	if (index != size)  //ressursive call
	{
		int t = 0;
		if (index != 0){

			t = arr[index - 1] + 1;
			arr[index - 1] = -1234224;
			int z = index - 1;
			getcombination(arr, size, z, check, t);
			return;
		}
	}
	if (index == size)  //for printing
	{
		getcombination1(arr, size, index, check, value);
		return;
	}

}



bool placePosition(int x, int j, int* &s, int size)  //j is colum x is row
{
	bool found = false;
	for (int i = 0; i < size; i++)
	{
		if (s[i] != x && (abs(i - j) != abs((x - s[i]))))
		{
			found = true;
		}
		else
		{
			return false;
		}
	}

	return found;
}
void print(int* &arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << "(" << i + 1 << "," << arr[i] + 1 << ")";
}
void getcombination1(int* &arr, int& size, int& z, bool& flag, int& j)
{
	if (arr[0] != -1234224)
	{
		cout << chess << ".";
		print(arr, size);
		cout << endl;
		int t = 0;
		j = arr[size - 1] + 1;
		arr[size - 1] = -1234;
		int z;
		z = size - 1;
		chess++;
		//cout << endl;
		getcombination(arr, size, z, flag, j);
		//cout << endl;
	}
}