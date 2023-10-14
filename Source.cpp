//Chad Huntebrinker
//CS 303

#include<list>
#include<iostream>
#include<iterator>
#include<utility>
#include<string>
#include<cmath>
using namespace std;

void addPair(list<pair<string, char>>*& hashTable, int hashSize, string key, char userChar);
void deleteItem(list<pair<string, char>>*& hashTable, int hashSize, string key, char userChar);
void goThruHashTable(list<pair<string, char>>* hashTable, int hashSize);
void reHash(list<pair<string, char>>* &hashTable, int &hashSize);

void main() {

	//First, we are going to populate the hashtable with some values.
	//Put those values in an array.
	pair<string, char> orig[] = { pair<string,char>("r98",'A'),
									pair<string,char>("11y",'L'),
									pair<string,char>("q54",'G'),
									pair<string,char>("p88",'O'),
									pair<string,char>("bb1",'R'),
									pair<string,char>("www",'I'),
									pair<string,char>("nbn",'T'),
									pair<string,char>("pop",'H'),
									pair<string,char>("87u",'M'),
									pair<string,char>("ede",'S'),
									pair<string,char>("kk8",'Z'),
									pair<string,char>("711",'L'),
									pair<string,char>("mom",'G'),
									pair<string,char>("28m",'O')
	};

	int dataSize = *(&orig + 1) - orig;
	int hashSize = 20;
	char userInput, userValue;
	list<pair<string, char>>* hashTab = new list<pair<string, char>>[hashSize];
	int index;
	string userKey;

	//Create the original hashtable
	for (int i = 0; i < dataSize; i++) {
		index = 0;
		for (int x = 2; x >= 0; x--) {
			index += ((int)((orig[i].first)[x]) * (int)pow(31, x));	//((int)orig[i]* 31) % 11;
		}
		index %= hashSize;

		hashTab[index].push_back(orig[i]);
	}

	//Make a loop for the user input.
	do {
		cout << "Enter 1 for Add" << endl;
		cout << "Enter 2 for Delete" << endl;
		cout << "Enter 3 for Traverse" << endl;
		cout << "Enter 4 for Re-Hash" << endl;
		cout << "Enter 5 for Quit" << endl << endl;
		cin >> userInput;

		if (userInput == '1') {
			cout << "Please enter the key of the value you want to add (must be 3 characters): ";
			cin >> userKey;
			cout << "Please enter the character you want to add: ";
			cin >> userValue;

			addPair(hashTab, hashSize, userKey, userValue);
		}
		else if (userInput == '2') {
			cout << "Please enter the key of the value you want to delete (must be 3 characters): ";
			cin >> userKey;
			cout << "Please enter the character you want to delete: ";
			cin >> userValue;
			
			deleteItem(hashTab, hashSize, userKey, userValue);
		}
		else if (userInput == '3') {
			goThruHashTable(hashTab, hashSize);
		}
		else if (userInput == '4') {
			reHash(hashTab, hashSize);
		}
	} while (userInput != '5');

	delete[] hashTab;
	system("pause");
}

//This function adds a new value to the hashtable from the user's inputted key and value.
void addPair(list<pair<string, char>>* &hashTable, int hashSize, string key, char userChar) {
	pair<string, char> temp(key, userChar);
	
	int index = 0;
	for (int x = 2; x >= 0; x--) {
		index += ((int)((temp.first)[x]) * (int)pow(31, x));
	}
	index %= hashSize;
	hashTable[index].push_back(temp);
}

//This function deletes a value from the hashtable if both the user's key and value match up
//to a key and value in the hash table.  Otherwise, an error message is outputted.
void deleteItem(list<pair<string, char>>* &hashTable, int hashSize, string key, char userChar) {

	pair<string, char> temp(key, userChar);

	int index = 0;
	
	//Find the index of the value.
	for (int x = 2; x >= 0; x--) {
		index += ((int)((temp.first)[x]) * (int)pow(31, x));
	}
	index %= hashSize;

	list<pair<string, char>>::iterator b = hashTable[index].begin();
	list<pair<string, char>>::iterator e = hashTable[index].end();
	for (; b != e; b++) {
		
		//If the keys and values match up, delete them.
		if (b->second == userChar && b->first == key) {
			hashTable[index].remove(*b);
			break;
		}
		
		//Otherwise, output an error message.
		else {
			cout << "This item does not exist with that key." << endl;
		}
	}

}

//This function iterates and outputs the hashtable.
void goThruHashTable(list<pair<string, char>>* hashTable, int hashSize) {
	for (int i = 0; i < hashSize; i++) {
		cout << i << ": ";

		list<pair<string, char>>::iterator b = hashTable[i].begin();
		list<pair<string, char>>::iterator e = hashTable[i].end();
		for (; b != e; b++) {
			cout << b->second << "->";
		}
		cout << "NULL" << endl;
	}
}

//This function rehashes the hashtable only if the user's inputted size is larger than the size
//of the current hashtable.
void reHash(list<pair<string, char>>* &hashTable, int &hashSize) {
	int newSize;
	int index;

	//Make sure the user's inputted size is larger than the original size.
	do {
		cout << "Please enter the new size you want the hashTable to be: ";
		cin >> newSize;
		if (newSize <= hashSize) {
			cout << "Incorrect value.  Must be greater than the size of the current Hashtable." << endl << endl;
		}
	} while (newSize <= hashSize);

	list<pair<string, char>>* newHashTable = new list<pair<string, char>>[newSize];

	//Rehash the old hashtable's values into the new hashtable
	for (int i = 0; i < hashSize; i++) {
		list<pair<string, char>>::iterator b = hashTable[i].begin();
		list<pair<string, char>>::iterator e = hashTable[i].end();
		index = 0;

		while (b != e) {
			for (int x = 2; x >= 0; x--) {
				index += ((int)((b->first)[x]) * (int)pow(31, x));	//((int)orig[i]* 31) % 11;
			}
			index %= newSize;
			newHashTable[index].push_back(*b);
			++b;
		}
	}

	//Delete the old hashTable's values and put in the new one.
	delete[] hashTable;
	hashTable = newHashTable;
	hashSize = newSize;
}