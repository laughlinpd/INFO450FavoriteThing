// Plant2.cpp : Defines the entry point for the console application.
//

// Plant.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int READERROR = 100;
const int WRITEERROR = 200;
const int ARRAYSIZE = 100;

class Plant
{

	string PlantName;
	string PlantType;
	string PlantCharacter;
	int	PlantQuantity;
public:
	Plant();
	Plant(string name, string type, string character, int quantity);
	void CapturePlantItem();
	void ShowPlantItem();
	int SavePlantItem(ofstream &outfile);
};

class PlantList
{
	Plant **list;
	int numrecords;
	int listsize;
	int ReallocateArray();
public:
	PlantList();
	~PlantList();
	void GetUserInput();
	void ShowPlantList();
	int SavePlantList(string filename);
	int ReadPlantList(string filename);
};

// default constructor - initialize empty
Plant::Plant()
{
	PlantName = ""; PlantType = ""; PlantCharacter = ""; PlantQuantity = 0;
}
// overload constructor inialize w/ values
Plant::Plant(string name, string type, string character, int quantity)
{
	PlantName = name;
	PlantType = type;
	PlantCharacter = character;
	PlantQuantity = quantity;
}
// Capture Item from end users
void Plant::CapturePlantItem()
{
	cout << "Plant Name? -->";
	getline(cin, PlantName);
	cout << "Plant Type?  -->";
	getline(cin, PlantType);
	cout << "Plant Characteristics? -->";
	getline(cin, PlantCharacter);
	cout << "Quanity? -->";
	cin >> PlantQuantity;
	cin.ignore();
	cin.clear();
}
// Display item to console
void Plant::ShowPlantItem()
{
	cout << "Name : " << PlantName << " \nType : " << PlantType << " \nCharacteristic : " << PlantCharacter << " \nQuantity : " << PlantQuantity << endl << endl;
}
// Save Plant item to file given input file stream
int Plant::SavePlantItem(ofstream& outfile)
{
	if (outfile.is_open())
	{
		outfile << PlantName << "|" << PlantType << "|" << PlantCharacter << '|' << PlantQuantity << endl;
		return 0;
	}
	else
	{
		return WRITEERROR;
	}
}

// Plant LIst constructor -allocate default space for array
PlantList::PlantList()
{
	list = new Plant*[ARRAYSIZE];
	numrecords = 0;
	listsize = ARRAYSIZE;
}
// deconstructor - free allocated memory
PlantList::~PlantList()
{
	for (int i = 0; i < numrecords; i++)
	{
		delete list[i];
	}
	delete[]list;
}
// Reallocate memory if already at array capacity
int PlantList::ReallocateArray()
{
	Plant **temp;
	temp = new Plant*[listsize + ARRAYSIZE];
	listsize = listsize + ARRAYSIZE;
	for (int i = 0; i < numrecords; i++)
	{
		temp[i] = list[i];
	}
	delete[]list;
	list = temp;


	return 0;
}

// get user input for the list
void PlantList::GetUserInput()
{
	string answer = "y";
	bool Check = true;
	cout << "Enter Item Y/N?" << endl;
	getline(cin, answer);
	while (answer == "Y" || answer == "y")
	{
		list[numrecords] = new Plant();
		list[numrecords]->CapturePlantItem();

		for (int i = 0; i < numrecords; i++)
		{
			if (list[numrecords] = list[i])
			{
				Check = false;
			}
			i++;
		}

		if (Check == false)
		{
			cout << "Error: Duplicate entered" << endl;
			delete list[numrecords];
			cout << "enter another plant Y/N?" << endl;
			getline(cin, answer);
			Check = true;
			continue;
		}

		numrecords++;
		cout << "enter another item Y/N?" << endl;
		getline(cin, answer);

	}


}
// Show list to the console
void PlantList::ShowPlantList()
{
	for (int i = 0; i < numrecords; i++)
		list[i]->ShowPlantItem();
}
// Save entire list to file, given full-path file name
int PlantList::SavePlantList(string filename)
{
	ofstream output(filename, ios::trunc);
	if (output)
	{
		for (int i = 0; i < numrecords; i++)
		{
			list[i]->SavePlantItem(output);
		}
		output.close();

		return 0;
	}
	else
	{
		return WRITEERROR;
	}
	//TBD
	return 0;
}
// Read Plant list from a file, given full-path filename
// If file not found or error, return error code
int PlantList::ReadPlantList(string filename)
{
	string iname, itype, icharacter, iqty;
	ifstream infile(filename, ios::in);
	if (!infile)
	{
		cout << "File could not be opened for reading" << endl;
		return READERROR;
	}


	while (!infile.eof())
	{
		if (numrecords == listsize)
		{
			ReallocateArray();
		}
		getline(infile, iname, '|');
		if (!iname.empty())
		{


			getline(infile, itype, '|');
			getline(infile, icharacter, '|');
			getline(infile, iqty);
			int qty = stoi(iqty);
			list[numrecords] = new Plant(iname, itype, icharacter, qty);
			numrecords++;
		}
	}
	infile.close();
	return 0;
}


int main()
{
	string filename;
	PlantList myPlant;
	string answer;
	cout << "Please enter full-path filename, ending filename will be saved as plant.txt" << endl;
	getline(cin, filename);
	int error;
	error = myPlant.ReadPlantList(filename);
	if (error)
	{
		cout << "Cannot read Plant - continue creating new list? Y/N -->";
		getline(cin, answer);
		if (answer != "Y" && answer != "y")
		{
			return 1;
		}
	}
	myPlant.GetUserInput();
	myPlant.SavePlantList(filename);
	system("CLS");
	myPlant.ShowPlantList();
	system("PAUSE");
	return 0;
}

