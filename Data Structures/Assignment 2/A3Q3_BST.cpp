//
#include <iostream>
using namespace std;
void print1();
template <class type>

struct bnode {
	type data;
	bnode* left;
	bnode* right;
};



template <class type>
class bst {
	bnode<type> *root;
public:
	bst()
	{
		root = nullptr;
	}  //constructor
	bnode<type>* search(type d, bnode<type>* root1)
	{
		if (root1 == nullptr)
			return root1;
		else
		{
			if (root1->data == d)
				return root1;
			else if (root1->data > d)
				return search(d, root1->left);
			else
				return search(d, root1->right);
		}
	}  //search code
	bnode<type>* search(type d)
	{
		return search(d, root);
	}
	//insert code
	bool insert(type d, bnode<type> * &root)
	{
		bnode<type>* r = root;
		if (root == nullptr)
		{
			bnode<type>* curr = new bnode<type>;
			curr->left = nullptr;
			curr->right = nullptr;
			curr->data = d;
			root = curr;
			return true;
		}
		else if (r->data == d)
		{
			cout << "Data is already inserted";
			return false;
		}
		else if (r->data > d)
			return insert(d, r->left);   //resurion call on left tree below
		else if (r->data < d)
			return insert(d, r->right);  //resurion call on larger
	}
	void insert(type d)
	{
		insert(d, root);
	}
	type removepredecessor(bnode<type> *&curr)
	{
		bnode<type>* child = curr;
		while (child->right != nullptr)
		{

			child = child->right;
		}
		type temp = child->data;
		remove(temp, curr);
		return temp;
	}
	bool remove(type d, bnode<type>*& root)
	{
		if (root == nullptr)
			return false;
		else if (root->data == d)
		{
			bnode<type> *temp = root;
			if (root->left == nullptr &&root->right == nullptr)  //iif one node leave
			{
				delete root;
				root = nullptr;
				return true;
			}

			else if ((root->left == nullptr) && (root->right != nullptr))  //one child
			{
				root = root->right;
				delete temp;
				return true;
			}
			else if ((root->left != nullptr) && (root->right == nullptr))  //one child
			{
				root = root->left;
				delete temp;
				return true;
			}
			else if ((root->left != nullptr) && (root->right != nullptr))  //incase of tooo many
			{
				root->data = removepredecessor(root->left);
				return true;
			}
		}
		else if (root->data < d)
		{
			return remove(d, root->right);
		}
		else if (root->data > d)
		{
			return remove(d, root->left);
		}
	}
	void remove(type d)
	{
		remove(d, root);
	}
	void inorder(bnode<type>* root)
	{
		if (root != nullptr)
		{
			inorder(root->left);
			cout << root->data << endl;
			inorder(root->right);
		}
	}
	void inorder()
	{
		inorder(root);
	}
	void preorder(bnode<type>* root)
	{
		if (root != nullptr)
		{
			cout << root->data << endl;
			inorder(root->left);
			inorder(root->right);
		}
	}
	void preorder()
	{
		preorder(root);
	}
	void postorder(bnode<type>* root)
	{
		if (root != nullptr)
		{
			inorder(root->left);
			inorder(root->right);
			cout << root->data << endl;
		}
	}
	void postorder()
	{
		postorder(root);
	}
	bnode<type>* getroot()
	{
		return this->root;
	}
	~bst()
	{
		if (root != nullptr)
			delete root;
		root = nullptr;
	}
};



void main() {
	bst<int> b;
	bnode<int>* add;
	int k = 0;
	int p;

	print1();
	cout << endl;
	cout << "Enter your choice:";
	cin >> k;

	while (k != -1)
	{

		switch (k)
		{
		case 1:
			cout << "Enter element to insert";
			cin >> p;
			b.insert(p);
			break;
		case 2:
			cout << "Enter element to remove:";
			cin >> p;
			b.remove(p);
			break;
		case 3:
			cout << "Enter element to search";
			cin >> p;
			add = b.search(p);
			if (add != nullptr)
				cout << "Address of node is" << add << endl;
			else
			{
				cout << "No node find:" << endl;
			}
			add = nullptr;
			break;
		case 4:
			b.inorder();
			break;
		case 5:
			b.postorder();
			break;
		case 6:
			b.preorder();
			break;
		default:
			break;
		}

		print1();
		cout << endl;
		cout << "Enter your choice:";
		cin >> k;
		system("cls");

	}
	system("pause");
}
void  print1()
{
	cout << "Enter 1 for insert:" << endl;
	cout << "Enter 2 for remove:" << endl;
	cout << "Enter 3 for search:" << endl;
	cout << "Enter 4 for print inorder" << endl;
	cout << "Enter 5 for print in postorder" << endl;
	cout << "Enter 6 for print in preoreder" << endl;
}

