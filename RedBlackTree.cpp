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
void insertNode(Node*, Node*);
void insertFixup(Node*, Node*);
void leftRotate(Node*, Node*);
void rightRotate(Node*, Node*);
void printTree(Node*, int depth);


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
    Node* newNode = new Node;
    newNode->value = atoi(ptr);
    insertNode(tree, newNode);
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
    Node* newNode = new Node;
    newNode->value = atoi(data);
    insertNode(tree, newNode);
  }
}

//adds a node to tree
void insertNode(Node* tree, Node* newNode) {
  Node* parent = NULL;
  Node* current = tree;
  while (current) {
    parent = current;
    if (newNode->value < current->value) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  
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
void insertFixup(Node* tree, Node* newNode) {

}

//rotates tree to the left
void leftRotate(Node* tree, Node* parent) {

}

//rotates tree to the right
void rightRotate(Node* tree, Node* parent) {

}

//visually prints out tree horizontally using recursion
void printTree(Node* root, int depth) {
  if (!root) {return;} //root is complete
  
  printTree(root->right, depth+1); //print top (right) root

  for (int i = 0; i < depth; i++) { //spacing
    cout << "   ";
  }
  if (root->isBlack) {
    cout << "\033[37m" << root->value << "\033[0m" << endl; //print data w/ white text (black node)
  } else {
    cout << "\033[31m" << root->value << "\033[0m" << endl; //print data w/ red text (red node)
  }

  printTree(root->left, depth+1); //print bottom (left) root
}
