#include<iostream>
using namespace std;
void coin(int n, int& player);
void main()
{
	int z = 1;
	while (z != -1)
	{
		cout << "Enter coins";
		cin >> z;
		int k = 1;
		coin(z, k);

		cout << "Winner is:" << k;
		cout << endl;
	}
	system("pause");
}
void coin(int n, int& player)
{
	if (n <= 0)
	{
		if (player == 1)
		{
			player = 2;
		}
		else
		{
			player = 1;
		}
		return;
	}
	else
	{
		if (n % 3 == 1 && n % 2 == 0)
		{
			cout << "Player " << player << " Select" << 4 << " Coins from " << n << " Coins" << endl;
			if (player == 1)
			{
				player = 2;
			}
			else
			{
				player = 1;
			}
			coin(n - 4, player);

			//sel 4
		}
		else if ((n % 3 == 1 && n % 2 == 0) || (n % 3 == 2 && n % 2 == 0) || (n % 3 == 2 && n % 2 == 1))
		{
			cout << "Player " << player << " Select" << 2 << " Coins from " << n << " Coins" << endl;
			if (player == 1)
			{
				player = 2;
			}
			else
			{
				player = 1;
			}
			coin(n - 2, player);

			//sel 2
		}
		else if (n % 3 == 0 && n % 2 == 0 || (n % 3 == 0 && n % 2 == 1))
		{
			cout << "Player " << player << " Select" << 1 << " Coins from " << n << " Coins" << endl;
			if (player == 1)
			{
				player = 2;
			}
			else
			{
				player = 1;
			}
			coin(n - 1, player);

			//sel 1
		}
		else if (n % 3 == 1 && n % 2 == 1)
		{
			cout << "Player " << player << " Select" << 1 << " Coins from " << n << " Coins" << endl;
			if (player == 1)
			{
				player = 2;
			}
			else
			{
				player = 1;
			}
			coin(n - 1, player);

			//sel1
		}
		else if (n % 3 == 1 && n % 2 == 2)
		{
			cout << "Player " << player << " Select" << 2 << " Coins from " << n << " Coins" << endl;
			if (player == 1)
			{
				player = 2;
			}
			else
			{
				player = 1;
			}
			coin(n - 2, player);

			//sel 2
		}
		else if (n % 3 == 2 && n % 2 == 0)
		{
			cout << "Player " << player << " Select" << 2 << " Coins from " << n << " Coins" << endl;
			if (player == 1)
			{
				player = 2;
			}
			else
			{
				player = 1;
			}
			coin(n - 2, player);

			//sel 2
		}

	}


}
