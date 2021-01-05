#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

//Node struct
struct Node {
  int value = -1;
  bool isBlack = false;
  Node* left = NULL;
  Node* right = NULL;
  Node* parent = NULL;
};

//function prototypes
void consoleInput(Node*&);
void fileInput(Node*&);
void insertNode(Node*&, int);
void insertFixup(Node*&, Node*&);
void leftRotate(Node*&, Node*&);
void rightRotate(Node*&, Node*&);
void printTree(Node*, int);


int main() {
  cout << "Welcome to Red-Black Tree!" << endl;
  cout << "Valid commands: ADD, READ, PRINT, and QUIT" << endl;

  Node* tree = NULL;

  char input[20];
  while (strcmp(input, "QUIT") != 0) {
    cout << ">> ";
    cin >> input;
    if (strcmp(input, "ADD") == 0) {
      consoleInput(tree);
    } else if (strcmp(input, "READ") == 0) {
      fileInput(tree);
    } else if (strcmp(input, "PRINT") == 0) {
      cout << "White text = Black node" << endl;
      cout << "Red text = Red node" << endl;
      printTree(tree, 0);
    } else if (strcmp(input, "QUIT") != 0) { //anything else besides QUIT is invalid
      cout << "Invalid command." << endl;
    }
  }
  cout << "Goodbye!" << endl;

  return 0;
}


//get input through console or through a file
void consoleInput(Node* &tree) {
  char data[300];
  cout << "Please enter a series of space separated integers between 1 and 999:" << endl;
  cin.get();
  cin.get(data, 300);
  cin.get();

  //use string tokenizer to split on spaces and copy into the tree
  char *ptr;
  ptr = strtok(data, " ");

  while (ptr) {
    insertNode(tree, atoi(ptr));
    ptr = strtok(NULL, " ");
  }
}

void fileInput(Node* &tree) {
  char data[300];
  char fileName[30];
  cout << "File name: ";
  cin >> fileName;

  ifstream numbers;
  srand(time(0));
  numbers.open(fileName);
  if (!numbers) {
    cout << "Could not find/open " << fileName;
    exit(1);
  }
  while (numbers >> data) { //copy all the numbers into the tree
    insertNode(tree, atoi(data));
  }
}

//adds a node to tree
void insertNode(Node* &tree, int newValue) {
  Node* parent = NULL;
  Node* current = tree;
  while (current) {
    parent = current;
    if (newValue < current->value) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  
  Node* newNode = new Node;
  newNode->value = newValue;
  newNode->parent = parent;
  
  if (!parent) {
    tree = newNode;
  } else if (newNode->value < parent->value) {
    parent->left = newNode;
  } else {
    parent->right = newNode;
  }

  insertFixup(tree, newNode);
}

//fixes tree to have proper red and black properties
void insertFixup(Node* &tree, Node* &newNode) {
  cout << "hi" << endl;
  while (newNode->parent && newNode->parent->isBlack == false) {
    if (newNode->parent == newNode->parent->parent->left) { //if newNode's parent is a left child
      Node* uncle = newNode->parent->parent->right;
      if (uncle->isBlack == false) {
	newNode->parent->isBlack = true;
	uncle->isBlack = true;
	newNode->parent->parent->isBlack = false;
	newNode = newNode->parent->parent;
      } else { //uncle is black
	if (newNode == newNode->parent->right) {
	  newNode = newNode->parent;
	  leftRotate(tree, newNode);
	}
	newNode->parent->isBlack = true;
	newNode->parent->parent->isBlack = false;
	rightRotate(tree, newNode->parent->parent);
      }
    } else { //same thing, but uncle is left
      Node* uncle = newNode->parent->parent->left;
      if (uncle && uncle->isBlack == false) {
	newNode->parent->isBlack = true;
	uncle->isBlack = true;
	newNode->parent->parent->isBlack = false;
	newNode = newNode->parent->parent;
      } else { //uncle is black
	cout << "yo im chillin doh" << endl;
	if (newNode == newNode->parent->left) {
	  newNode = newNode->parent;
	  rightRotate(tree, newNode);
	}
	newNode->parent->isBlack = true;
	newNode->parent->parent->isBlack = false;
	leftRotate(tree, newNode->parent->parent);
	printTree(tree, 0);
      }
    }
    tree->isBlack = true;
  }
  tree->isBlack = true;
}

//rotates tree to the left
void leftRotate(Node* &tree, Node* &parent) {
  printTree(tree, 0);
  cout << parent->parent->value << endl;
  Node* child = parent->right;
  parent->right = child->left; //parent's new right is child's left
  cout << parent->value << endl;
  if (child->left) {
    child->left->parent = parent; //update child's left parent
    cout << "uh" << endl;
  }
  child->parent = parent->parent; //update child's parent BAD BAD BAD
  cout << parent->value << endl;
  printTree(tree, 0);
  if (!parent->parent) { //if parent had no parent, it was root (child is now parent) 
    cout << "why??" << endl;
    tree = child;
  } else if (parent == parent->parent->left) { //update old parent's parent's child to be the old child (left or right) 
    parent->parent->left = child;
  } else {
    parent->parent->right = child;
  }
  child->left = parent; //finally, hook up old child's left to now be parent (and old parent's parent is old child)
  parent->parent = child;
}

//rotates tree to the right. Same idea as left rotate, but flipped
void rightRotate(Node* &tree, Node* &parent) {
  Node* child = parent->left;
  parent->left = child->right;
  if (child->right) {
    child->right->parent = parent;
  }
  child->parent = parent->parent;
  if (!parent->parent) {
    tree = child;
  } else if (parent == parent->parent->right) {
    parent->parent->right = child;
  } else {
    parent->parent->left = child;
  }
  child->right = parent;
  parent->parent = child;
}

//visually prints out tree horizontally using recursion
void printTree(Node* root, int depth) {
  if (!root) {return;} //root is complete
  
  printTree(root->right, depth+1); //print top (right) root

  for (int i = 0; i < depth; i++) { //spacing
    cout << "          ";
  }
  if (root->isBlack) {
    cout << "\033[37m" << root->value << "\033[0m" << "p: ";
    if (root->parent) {
      cout << root->parent->value << endl;
    } else {
      cout << "null" << endl;
    }
    //  << endl; //print data w/ white text (black node)
  } else {
    cout << "\033[31m" << root->value << "\033[0m" << "p: "; //endl; //print data w/ red text (red node)
    if (root->parent) {
      cout << root->parent->value << endl;
    } else {
      cout << "null" << endl;
    }
  }

  printTree(root->left, depth+1); //print bottom (left) root
}
