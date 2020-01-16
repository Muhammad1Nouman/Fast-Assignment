#include<iostream>
#include<stdlib.h>
using namespace std;
int number = 1;  //varible to show all possibilities
void displayChessBoard(int**arr, int size);
class Stack
{
	int* s;
	int size;
	int stkptr;
public:
	Stack(int n = 0)
	{
		size = n;
		s = new int[n];
		stkptr = 0;
	}
	Stack(const Stack& obj)
	{
		size = obj.size;
		s = new int[size];
		stkptr = obj.stkptr;
		int* arr = new int[size];
		for (int i = 0; i < size; i++)
			arr[i] = obj.s[i];
		for (int k = 0; k < size; k++)
			s[k] = arr[k];
	}
	Stack& operator=(const Stack& obj)
	{
		size = obj.size;
		s = new int[size];
		stkptr = obj.stkptr;
		int* arr = new int[size];
		for (int i = 0; i < size; i++)
			arr[i] = obj.s[i];
		for (int k = 0; k < size; k++)
			s[k] = arr[k];
		return *this;
	}

	bool IsEmpty()
	{
		if (stkptr == 0)
			return true;
		else
			return false;
	}
	bool Isfull()
	{
		if (stkptr == size)
			return true;
		else
			return false;
	}
	bool Push(int d)
	{
		if (!Isfull()){
			s[stkptr] = d;
			stkptr++;
			return true;

		}
		else
			return false;
	}
	bool pop(int& d)
	{
		if (!IsEmpty()){
			stkptr--;
			d = s[stkptr];
			return true;
		}
		else
		{
			return false;
		}
	}
	int top(int& d)
	{
		if (!IsEmpty())
		{
			d = s[stkptr - 1];
			return (stkptr - 1);
		}
		else
			return (stkptr - 1);
	}
	bool placePosition(int x, int j)
	{
		bool found = false;
		for (int i = 0; i < stkptr; i++)
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
	void stackdisplay()
	{
		for (int i = 0; i < stkptr; i++)
			cout << "(" << i + 1 << "," << s[i] + 1 << ")";
	}

};
void main()
{
	int size;
	int** chessBoard;
	int colum, row;

	cout << "Enter chess Board Size:";
	cin >> size;

	chessBoard = new int*[size];
	for (int k = 0; k < size; k++)
		chessBoard[k] = new int[size];
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			chessBoard[i][j] = 0;
		}

	}

	Stack queen(size);
	queen.Push(0);    /*intializing default value*/
	row = queen.top(colum);  /*get top of the stack*/
	chessBoard[0][0] = 0;

	bool succfullplace = false;

	for (int i = row + 1; i < size; i++)
	{
		if (queen.IsEmpty())   /*if all possible combinations are checked*/
		{
			break;
		}
		for (int j = 0; j < size; j++)
		{
			if (queen.placePosition(j, i))   /*function to determine the position isSafe*/
			{
				queen.Push(j);
				chessBoard[i][j] = j;
				row = queen.top(colum);
				succfullplace = true;
				break;
			}


		}
		/*if queen is not safe*/
		while (!succfullplace)
		{
			if (!queen.IsEmpty())
			{
				queen.pop(colum);
			}
			else
			{
				succfullplace = true;
			}

			if (i != 0){    /**/
				chessBoard[i - 1][colum] = 0;
			}
			else
			{
				chessBoard[i][colum] = 0;
			}
			if (i != 0)    /*outer loop varilble it will not going less than 0*/
				i = i - 1;  /*then decrement it*/

			if (i == 0)
			{
				if (colum < size - 1){
					queen.Push(colum + 1);
					chessBoard[i][colum] = 0;
					chessBoard[i][colum + 1] = colum + 1;
					succfullplace = true;  /*if we are at row 1*/
					cout << endl;

				}
			}
			/*if we are at other posiont then row 1*/
			if ((colum < size - 1) && i != 0)
			{

				for (int k = colum; k < size - 1; k++){
					if (queen.placePosition(k + 1, i))
					{
						chessBoard[i][k] = 0;
						chessBoard[i][k + 1] = k + 1;
						queen.Push(k + 1);
						succfullplace = true;
						break;
					}
				}
			}

		}
		if (queen.Isfull())
		{
			/*if all chess board is fill then go to the next possible soltuin*/
			int d = 0;
			cout << endl;
			cout << number << ":";
			queen.stackdisplay();
			number++;
			cout << endl;
			bool Isokay = false;

			while (!Isokay)
			{
				if (!queen.IsEmpty())
				{
					queen.pop(colum);
				}
				else
				{
					Isokay = true;
				}
				if (i == 0)
				{
					if (colum<size - 1)
						queen.Push(colum + 1);
					Isokay = true;
				}
				if ((colum < size - 1) && i != 0){
					for (int k = colum + 1; k < size; k++)
					{
						if (queen.placePosition(k, i))
						{
							queen.Push(k);
							Isokay = true;
							break;
						}
					}
				}
				/*if we place at our desire position then break then not decremtn outer loop variable*/
				if (i != 0 && !Isokay)
					i = i - 1;

			}

		}//Isfull

		succfullplace = false;

	}

	system("pause");
}
void displayChessBoard(int**arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

}