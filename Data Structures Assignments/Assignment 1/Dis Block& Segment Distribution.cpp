#include<iostream>
#include<string>


using namespace std;
void display();
/*Generic node*/
template<class Type>
struct node{
	Type data;
	node* next;
};

/*generic class ListIterator*/
template <class Type>
class listIterator
{
private:
	node<Type>* curr;
public:
	/*constructor*/
	listIterator()
	{
		curr = nullptr;
	}
	/*overloaded constructor*/
	listIterator(node<Type>* d)
	{
		curr = d;
	}
	/*derefercing*/
	Type& operator*(){
		Type d;
		if (curr != nullptr)
			return curr->data;
		else
			return d;
	}

	listIterator<Type>& operator++()
	{
		if (curr != nullptr)
			curr = curr->next;
		return *this;
	}
	bool operator!=(listIterator<Type>& list)
	{
		if (curr == list.curr)
		{
			return false;
		}
		else
		{
			return true;
		}


	}


};


/*Generic class singly link list*/
template <class Type>
class singlyLinkList
{
private:
	node<Type>* head;
public:
	/*constructor*/

	singlyLinkList()
	{
		head = nullptr;

	}
	/*destructor*/
	void removeAll()
	{
		if (head != nullptr) {
			node<Type>* temp;
			node<Type>* curr = head;

			while (curr != nullptr) {
				temp = curr;
				curr = curr->next;
				delete temp;
			}
		}

	}

	/*insert at start*/

	void insertAtStart(Type d)
	{
		node<Type>* temp = new node<Type>;

		temp->data = d;
		temp->next = head;
		head = temp;



	}
	//void insert()
	/*remove from start*/
	void removeFromStart()
	{
		if (head != nullptr) {
			node<Type>* temp = head;
			head = head->next;
			delete temp;

		}
	}
	void insertAtEnd(Type d) {
		node<Type>* temp = new node<Type>;
		temp->data = d;
		temp->next = nullptr;
		node<Type>* curr = head;
		if (head != nullptr) {
			while (curr->next != nullptr) {
				curr = curr->next;
			}
			curr->next = temp;
		}
		else {
			head = temp;
		}
	}

	/*remove from any node*/

	/*list is empty*/
	void isEmpty()
	{
		head = nullptr;

	}
	/*start beging*/
	listIterator<Type> begin()
	{
		listIterator<Type> list(head);
		return list;
	}
	/*return end of list */
	listIterator<Type> end()
	{
		listIterator<Type> list;
		return list;
	}
	void remove(Type d) {
		if (head != nullptr) {
			node<Type>* curr = head;
			node<Type>* prev = curr;
			while (curr != nullptr && curr->data != d) {
				prev = curr;
				curr = curr->next;
			}
			if (curr == head) {
				removeFromStart();
				return;
			}
			if (curr != nullptr) {
				prev->next = curr->next;
				delete curr;
			}
		}
	}

};

class block{
protected:
	int startSector;
	int EndSector;
public:
	block()
	{
		startSector = 0;
		EndSector = 0;
	}
	void displayblock()
	{
		printf("( %d ", startSector);
		printf(",%d", EndSector);
		printf("),");


	}
	block(int start, int end)
	{
		startSector = start;
		EndSector = end;
	}
	/*utility program to get blocks avalilbe*/
	void getavailabeblock(int& start, int& end)
	{
		start = startSector;
		end = EndSector;
	}
	/*utility program to update block*/
	void setavailabelblock(int& start, int& end)
	{
		startSector = start;
		EndSector = end;
	}
	block(const block &obj)
	{
		*this = obj;
	}
	block& operator=(const block& obj)                  //overloading assignment operator
	{
		startSector = obj.startSector;
		EndSector = obj.EndSector;
		return *this;
	}


};
/*class file to store the files of user*/

class files
{
protected:
	int size;
	char* name;
	singlyLinkList<block> linklist;
public:

	singlyLinkList<block> displayfiles()
	{
		singlyLinkList<block> d;
		printf("Size:%d", size);
		cout << endl;
		printf("Name:%s", name);
		cout << endl;
		//	cout << "Name:  "<< name << endl;
		printf("Available Blocks in file\n");

		for (listIterator<block> itr = linklist.begin(); itr != linklist.end(); itr++)
		{
			block b;


			b = *itr;

			int start, end;
			b.getavailabeblock(start, end);
			block b1(start, end);
			d.insertAtStart(b1);
			b.displayblock();
		}
		cout << endl;
		return d;
	}
	files()
	{
		size = 0;
		name = nullptr;

	}
	void getname(char* &n)
	{
		n = name;
	}
	void getSize(int& s)
	{
		s = size;
	}
	files(int s, char* n, int s1, int e)
	{
		size = s;
		name = new char;
		name = n;
		block data(s1, e);

		linklist.insertAtStart(data);

	}
	void insertblocks(int start, int end)
	{
		block b(start, end);
		linklist.insertAtStart(b);
	}
	bool operator!=(files& list)
	{
		bool found = true;
		for (int i = 0; list.name[i] != '\0'; i++)
		{
			if (list.name[i] != name[i])
				found = false;
		}

		return !found;
	}

	files(int fileSize, char* fileName)
	{
		size = fileSize;
		name = fileName;
	}
	files(char* n, int s, singlyLinkList<block> t)
	{
		name = n;
		size = s;
		listIterator<block> lit = t.begin();
		for (lit = t.begin(); lit != t.end(); lit++)
		{
			linklist.insertAtStart(*lit);
		}
	}
	files(const files & obj)                                  /*copy constructor*/
	{
		size = obj.size;
		name = new char();
		//	linklist = new singlyLinkList<block>();
		linklist.removeAll();
		*this = obj;

	}
	files& operator=(const files& obj)                  //overloading assignment operator
	{
		size = obj.size;
		name = obj.name;

		singlyLinkList<block> bloc;
		bloc = obj.linklist;
		listIterator<block> b;//.linklist.begin();
		int start = 0, end = 0;

		for (b = bloc.begin(); b != bloc.end(); b++){

			block c1 = *b;
			c1.getavailabeblock(start, end);
			block b1(start, end);
			linklist.insertAtStart(b1);
		}
		return *this;
	}


};
/*Block to hold the currently availbel sector and not available sector*/

/*class of file system*/
class filesystem : public files, block
{
private:

	singlyLinkList<block> pool; 							/*it will store the number of free block availbel*/

	singlyLinkList<files>  Linklistfile; 							/*it will store the file and the block contain by file*/



	int sizeOfSector; 												/*Group of character stored in disk called as sector*/

	int numofSector;   												/*how much sector user need*/

	int diskSize;
	int diskdata;

public:

	char* disk;             									/*it is disk of size of num of sector*/

	filesystem()   	/*deafult conctructor*/

	{
		sizeOfSector = 0;
		numofSector = 0;
	}

	filesystem(int sectorsize, int numsector)                     	/*constructor with parameter*/
	{
		sizeOfSector = sectorsize;
		numofSector = numsector;
		diskdata = 0;
		diskSize = sizeOfSector*numofSector;                      /*caluclating disk size*/
		disk = new char[diskSize];                         /*disk is intilazed according to user requirment*/
		for (int i = 0; i < diskSize; i++)
			disk[i] = '0';
		block data(0, sectorsize*numsector - 1);
		pool.insertAtStart(data);
		size = 0;                                             /*intilazing file to an empty state*/
		name = nullptr;

	}

	bool savefile(char* filename, string content, int filesize)                    /*program to save the file*/
	{

		if (diskSize <= 0)
		{
			return false;
		}
		name = filename;
		size = filesize;

		/*determin file is already avalible or not*/
		for (listIterator<files> itr = Linklistfile.begin(); itr != Linklistfile.end(); itr++)
		{
			files f = *itr;
			char* arr = new char;
			f.getname(arr);
			bool found = true;
			for (int i = 0; arr[i] != '\0'; i++)
			{
				if (arr[i] != name[i])
					found = false;
			}
			if (found)
			{
				cout << "File is already exist" << endl;
				return false;
			}
		}

		/*block iterator*/
		listIterator<block> ava;
		/*storing available pool in another pool*/
		singlyLinkList<block> storingblock, filepool;
		for (ava = pool.begin(); ava != pool.end(); ava++)
		{
			storingblock.insertAtEnd(*ava);
		}
		/*now decideing size of availble block if avalible then store other return false*/
		int start = 0, end = 0, sum = 0, length = 0, loopVar = 0, loopVar1 = 0;
		block da;
		for (ava = storingblock.begin(); ava != storingblock.end(); ava++)
		{
			da = *ava;
			da.getavailabeblock(start, end);
			sum = (end - start) + sum;
		}
		if (sum < filesize)
		{
			cout << "Your file size is too big" << endl;
			return false;
		}

		//storign data in disk
		int check = 0;
		length = content.length();   /*finding size of data*/
		for (ava = storingblock.begin(); ava != storingblock.end() && loopVar != length; ava++)
		{
			da = *ava;
			if (loopVar != length)
			{
				filepool.insertAtStart(*ava);
				da.getavailabeblock(start, end);

			}
			int j = 0;
			for (j = start; j < end&& loopVar != length; j++){

				disk[j] = content.at(loopVar);
				loopVar++;
			}

			if (loopVar != length && j < end)
			{

				loopVar1 = loopVar - loopVar1;
				pool.removeFromStart();
				if (start > start + loopVar1)
				{

					block p(start + loopVar1, start);				 //p(start, start + loopVar1);
					linklist.insertAtStart(p);
				}
				else
				{
					block p(start, start + loopVar1);				 //p(start, start + loopVar1);
					linklist.insertAtStart(p);

				}
				check = 1;
			}
			else if (check != 1)
			{
				check = 0;
				loopVar1 = loopVar - loopVar1;
				da.getavailabeblock(start, end);
				if (end != sizeOfSector*numofSector)
					pool.removeFromStart();


				if (start > start + loopVar1)
				{

					block p(start + loopVar1, start);				 //p(start, start + loopVar1);
					linklist.insertAtStart(p);
				}
				else
				{
					block p(start, start + loopVar1);				 //p(start, start + loopVar1);
					linklist.insertAtStart(p);

				}

				if (start + loopVar < end)
				{
					block p1(start + loopVar, end);

					pool.insertAtEnd(p1);
				}
				else if (start + loopVar != end)
				{
					block p1(end, start + loopVar);
					pool.insertAtEnd(p1);

				}



			}
			diskSize = diskSize - loopVar;
			diskdata = diskdata + loopVar;

		}



		files storagedata(name, size, linklist);
		linklist.isEmpty();	//CallOfthisfunctionisanAttemptoavoidcopingofpointers

		listIterator<files> iter = Linklistfile.begin();
		Linklistfile.insertAtStart(storagedata);   //storingData


		return true;

	}
	void displaydata()
	{
		listIterator<block> list;
		printf("List of availble blocks to save file: \n");

		for (list = pool.begin(); list != pool.end(); list++)
		{
			block b;
			b = *list;
			b.displayblock();
		}
		listIterator<files> list1;
		cout << endl;
		cout << "Data in Disk" << endl;
		cout << "(";
		for (int i = 0; i < diskdata; i++)
		{
			cout << disk[i] << ",";
		}
		cout << ")" << endl;
		int nofiles = 1;
		for (list1 = Linklistfile.begin(); list1 != Linklistfile.end(); list1++)
		{
			cout << endl;
			cout << "File no." << nofiles << endl;
			singlyLinkList<block> d;
			cout << "List of blocks in files:";
			files f;
			f = *list1;
			d = f.displayfiles();
			listIterator<block> it;
			cout << "Content:";
			for (it = d.begin(); it != d.end(); it++)
			{
				int start = 0, end = 0;
				block c = *it;
				c.getavailabeblock(start, end);
				for (int k = start; k < end; k++)
					cout << disk[k];
			}
			cout << endl;


			nofiles++;
		}
	}
	/*Reading of file with its name*/
	void readfile(char* filename)
	{

		listIterator<files> itr;
		for (itr = Linklistfile.begin(); itr != Linklistfile.end(); itr++)
		{
			files f;
			f = *itr;
			char* da = new char;
			f.getname(da);
			bool found = true;
			for (int i = 0; filename[i] != '\0'; i++)           //comparing filename with user typed name
			{
				if (filename[i] != da[i])
				{
					found = false;
					break;
				}
			}
			if (found)
			{
				singlyLinkList<block> d;
				d = f.displayfiles();
				listIterator<block> it;
				cout << "Content:";
				for (it = d.begin(); it != d.end(); it++)
				{
					int start = 0, end = 0;
					block c = *it;
					c.getavailabeblock(start, end);
					for (int k = start; k < end; k++)
						cout << disk[k];
				}
				cout << endl;
				break;
			}
			else
			{
				cout << endl;
				cout << "Files is not Available" << endl;
			}

		}

	}
	void deletedata(char* filename)
	{
		listIterator<files> itr;
		for (itr = Linklistfile.begin(); itr != Linklistfile.end(); itr++)
		{
			files f;
			f = *itr;
			char* da = new char[];
			f.getname(da);
			int di = 0;
			f.getSize(di);
			bool found = true;
			for (int i = 0; filename[i] != '\0'; i++)   //comparing file name Entered by user and avalible files 
			{
				if (filename[i] != da[i])
				{
					found = false;
					break;
				}
			}

			if (found)     /*if file is found*/
			{
				singlyLinkList<block> d;
				cout << "The content of your file is" << endl;
				d = f.displayfiles();
				listIterator<block> itr2;
				for (itr2 = d.begin(); itr2 != d.end(); itr2++)
				{
					block insertBlockinFile;
					insertBlockinFile = *itr2;
					int start = 0, end = 0;
					insertBlockinFile.getavailabeblock(start, end);
					block v(start, end);
					pool.insertAtStart(v);
				}
				Linklistfile.remove(f);
				diskSize = diskSize + di;
				break;

			}
			else
			{
				cout << endl;     /*display an error message*/
				cout << "\tFile Not Available!!" << endl;
			}
		}
	}
	/*destrutor to delete filesystem object*/
	~filesystem()
	{
		delete[] disk;
		Linklistfile.removeAll();
		pool.removeAll();
	}
};
void main()
{
	int choice = 0;                                              /*variable to perform an action*/

	int sectorsize, numofsector;

	cout << "Enter size of sector: ";                         /*getting size of sector form user*/
	cin >> sectorsize;

	cout << "Enter number of sector:";                       /*getting number of sector*/
	cin >> numofsector;


	filesystem file(sectorsize, numofsector);              /*intilazing file according to user requirement*/

	int size;
	display();
	cout << "Enter your choice:";
	cin >> choice;

	//getline(cin, filename);
	char* filename = new char[];
	string datainfile;
	char* data = new char[];
	bool isfileSave;

	while (choice != -1)
	{
		switch (choice)
		{
		case 1:
			cin.getline(filename, 200);
			cout << "Enter file name: ";
			cin.getline(filename, 200);
			cout << "Enter file data: ";
			getline(cin, datainfile);
			cout << "File size: ";
			cin >> size;
			isfileSave = file.savefile(filename, datainfile, size);
			filename = new char;
			break;
		case 2:
			cout << "Enter file name";
			cin.getline(data, 200);
			cin.getline(data, 200);
			file.readfile(data);
			data = new char;
			break;
		case 3:
			cout << "Enter file name";
			cin.getline(data, 200);
			cin.getline(data, 200);
			file.deletedata(data);
			data = new char;

			break;

		case 4:
			file.displaydata();
			break;
		case -1:
			break;
		default:
			break;
		}
		cout << endl;

		display();
		cout << "Enter your choice:";
		cin >> choice;

	}//end of while


	system("pause");
}
void display()
{
	cout << "Select from menu" << endl << endl;
	cout << "\t1.Save file" << endl;
	cout << "\t2.Read file" << endl;
	cout << "\t3.Delete file" << endl;
	cout << "\t4.Display All files" << endl;
	cout << "\t5.Press -1 for exit" << endl;

}
