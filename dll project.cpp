#include <iostream>
#include <string> 

using namespace std;
class node {
private:
	node* left;
	node* right;
	int id;
	string name;
	float gpa;
	bool edge;
public:
	node(node* front, node* back) {
		this->left = front;
		this->right = back;
		this->edge = true;
	}
	node(node* front, node* back, int id, string name, float gpa) {
		this->left = front;
		this->right = back;
		this->id = id;
		this->name = name;
		this->gpa = gpa;
		this->edge = false;
	}

	int getID() {
		return id;
	}
	string getName() {
		return name;
	}
	float getGPA() {
		return gpa;
	}
	node* getLeft() {
		return left;
	}
	node* getRight() {
		return right;
	}
	void setLeft(node* front) {
		left = front;
	}

	void setRight(node* back) {
		right = back;
	}
	bool getEdge() {
		return edge;
	}

	void printnode() {
		if (this->edge == false) {
			cout << "Name: " << this->getName() << endl;
			cout << "ID: " << this->getID() << endl;
			cout << "GPA: " << this->getGPA() << endl;

		}
	}
};



string entername() {
	string name;
	cout << "Please enter the name of the student."<< endl;
	cin.ignore();
	getline(cin, name);
	return name;
}

float enterGPA() {
	float gpa;
	cout << "Please enter the GPA of the student." << endl;
	cin >> gpa;
	while (gpa < 0 && gpa > 4) {
		cout << "I am sorry, GPAs must be equal to or between 0 and 4. Please enter a valid value."<< endl;
		cin >> gpa;
	}
	return gpa;
}


int enterID() {
	int id;
	cout << "Please enter the ID of the student." << endl;
	cin >> id;
	while (id < 1000 && id > 9999) {
		cout << "I am sorry, IDs must be equal to or between 1000 and 9999. Please enter a valid value." << endl;
		cin >> id;
	}
	return id;
}
int enterIDMod() {
	int id;
	cout << "Please enter the ID of the student you would like to modify." << endl;
	cin >> id;
	while (id < 1000 && id > 9999) {
		cout << "I am sorry, IDs must be equal to or between 1000 and 9999. Please enter a valid value." << endl;
		cin >> id;
	}
	return id;
}


node* getNode(int ID, node * current) {
	if (current->getRight()->getEdge() == true) { return current; }

	while (!current->getRight()->getEdge()) {
		if (current->getID() < ID && current->getRight()->getID() > ID) { return current; }
		current = current->getRight();
	}
	return current;
	}


node* findNode(int ID, node* current) {
	while (current->getRight() != nullptr) {
		if (ID == current->getID()) { return current; }
		current = current->getRight();}
	return nullptr;
}


void insertNode(node* left, node* insert) {
	node* right = left->getRight();
	insert->setLeft(left);
	insert->setRight(right);
	left->setRight(insert);
	right->setLeft(insert);
}

void deletenode(node* node) {
	node->getLeft()->setRight(node->getRight());
	node->getRight()->setLeft(node->getLeft());
	delete node;
}

void printList(node* current) {
	while (current->getRight() != nullptr) {
		current->printnode();
		current = current->getRight();
	}
}

void purgeList(node* current) {
	node* temp = current->getRight();
	while (temp->getEdge() == false) {
		node* temp2 = temp->getRight();
		deletenode(temp);
		temp = temp2;
	}
}


void initialize(node* left, node* right, bool &initialized) {
	if (!initialized) {
		initialized = true;
		left->setRight(right);
		right->setLeft(left);
		cout << "List initailized."<< endl;
	}
	else {
		cout << "The list is already created!" << endl;
	}
}

void deinitialize(node* left, node* right) {
	left->setLeft(nullptr);
	left->setRight(nullptr);
	right->setLeft(nullptr);
	right->setRight(nullptr);
}

void addnode(node* left, node* right, bool initialized) {
	if (initialized) {
		int id = enterID();

		if (findNode(id, left) == nullptr) {
			string name = entername();
			float GPA = enterGPA();
			node* newnode = new node(nullptr, nullptr, id, name, GPA);
			insertNode(getNode(id, left), newnode);
			cout << "Node successfully added." << endl;
		}
		else {
			cout << "That student is already present in the list! Please try again." << endl;
		}
	}
	else {
		cout << "The list has not been created! Please try again." << endl;
	}
}


void displaynode(node* left, node* right, bool initialized) {
	if (initialized && !left->getRight()->getEdge()) {
		int id = enterID();
		if (findNode(id, left) != nullptr) { getNode(id, left)->printnode(); }
		else { cout << "That student is not present! Please try again." << endl; }
	}
	else if (initialized && left->getRight()->getEdge()) { cout << "The list is empty! Please try again" << endl; }
	else { cout << "The list has not been created! Please try again." << endl; }
}

void modifynode(node* left, node* right, bool initialized) {
	if (initialized && !left->getRight()->getEdge()) {
		int id = enterIDMod();
		node* temp = findNode(id, left);
		if (temp != nullptr) {
			cout << "For the new list:"<< endl;
				int newid = enterID();
				if (findNode(newid,left) == nullptr) {
					string name = entername();
					float gpa = enterGPA();
					node* newnode = new node(nullptr, nullptr, newid, name, gpa);
					deletenode(findNode(id,left));
;					insertNode(getNode(newid, left),
	newnode);
				}
				else {
					cout << "That student is already present! Please try again." << endl;
				}
				
		}

		else { cout << "That student is not present! Please try again." << endl; }
	}
	else if (initialized && left->getRight()->getEdge()) { cout << "The list is empty! Please try again" << endl; }
	else { cout << "The list has not been created! Please try again." << endl; }
}

void deleteNode(node* left, node* right, bool initialized) {
	if (initialized && !left->getRight()->getEdge()) {
		int id = enterID();
		if (findNode(id, left) != nullptr) {
			deletenode(findNode(id, left));
			cout << "Node successfully deleted." << endl;
		}
		else { cout << "That node is not present! Please try again." << endl; }
	}
	else if (initialized && left->getRight()->getEdge()) { cout << "The list is empty! Please try again"<< endl; }
	else { cout << "The list has not been created! Please try again." << endl; }
}

void printList(node* left, node* right, bool initialized) {
	if (initialized == false) {
		cout << "The list has not been created! Please try again."<< endl;
	}
	else if (left->getRight()->getEdge()) {
		cout << "The list is empty! Please try again."<< endl;
	}
	else {
		node* current = left;
		printList(current);
	}

}

void deleteList(node* left,node* right, bool &initialized) {
	if (initialized) {
		purgeList(left);
	}
	else if (left->getRight()->getEdge()) {
		cout << "The list is already empty! Please try again." << endl;
	}
	else { cout << "The list has not been created! Please try again." << endl; }

}


int main() {
	bool initialized = false;
	node* left = new node(nullptr, nullptr);
	node* right = new node(nullptr, nullptr);
	while (true) {
		cout << "This is a program that stores student names, IDs, and GPAs in a doubly linked list. It organizes them by ID. What would you like to do?" << endl;
		cout << "1 - Create the list." << endl;
		cout << "2 - Add a node." << endl;
		cout << "3 - Delete a node" << endl;
		cout << "4 - Modify a node." << endl;
		cout << "5 - Display a node." << endl;
		cout << "6 - Display the list." << endl;
		cout << "7 - Purge the list." << endl;
		cout << "8 - Exit." << endl;
		int in;

		cin >> in;
		switch (in) {
		case (1):
			initialize(left, right, initialized);
			break;
		case(2):
			addnode(left, right, initialized);
			break;
		case(3):
			deleteNode(left, right, initialized);
			break;
		case(4):
			modifynode(left, right, initialized);
			break;
		case(5):
			displaynode(left, right, initialized);
			break;
		case(6):
			printList(left, right, initialized);
			break;
		case(7):
			deleteList(left, right, initialized);
			break;
		case(8):
			cout << "Thank you for using this program!" << endl;
			return 0;
		default:
			cout << "Invalid input! Please try again!" << endl;
		}

	}
}