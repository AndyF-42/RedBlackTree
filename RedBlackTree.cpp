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
};

//function prototypes
Node* addNode(Node*, int);
void getInput(Node*&);
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
      getInput(tree);
    } else if (strcmp(input, "READ") == 0) {
      
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


//adds a node to tree via console or file input
Node* addNode(Node* tree, int newValue) {
  if (!tree) { //if null, this is where to add
    tree = new Node;
    tree->value = newValue;
    return tree;
  }
  if (tree->value < newValue) { //recursively go left or right until you are where you need to add
    tree->right = addNode(tree->right, newValue);
  } else if (tree->value > newValue) {
    tree->left = addNode(tree->left, newValue);
  }
  return tree;
}

//get input through console or through a file
void getInput(Node* &tree) {
  char method[10];
  cout << "Add by FILE or by CONSOLE? ";

  char data[300];
  int i = 0;
  while (true) {
    cin >> method;

    if (strcmp(method, "FILE") == 0) { //if FILE option, open and read file
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
        tree = addNode(tree, atoi(data));
      }
      break;
    } else if (strcmp(method, "CONSOLE") == 0) {
      cout << "Please enter a series of space separated integers between 1 and 999:" << endl;
      cin.get();
      cin.get(data, 300);
      cin.get();

      //use string tokenizer to split on spaces and copy into the tree
      char *ptr;
      ptr = strtok(data, " ");

      while (ptr) {
        tree = addNode(tree, atoi(ptr)); //parse and add the int
        ptr = strtok(NULL, " ");
      }
      break;
    } else {
      cout << "Please enter either FILE or CONSOLE: ";
    }
  }
  cout << "Added." << endl;
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
