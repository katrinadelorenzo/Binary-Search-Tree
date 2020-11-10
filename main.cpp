// Test driver
/* 
  Author: Katrina DeLorenzo 
  Last Modified: 11/24/19
  Known bug: GetNodesAtLevel doesn't fully work.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>

#include "TreeType.cpp"

using namespace std;

int main()
{
  char command;        // operation to be executed
  
  char item;
  char ret;
  string orderItem;
  int Max_Items = 100;
  char tempArray[Max_Items];
  int level;
  TreeType<char> tree;
  OrderType order;
  bool found;
  bool finished;
  int numCommands;
  string str;
  
  
  do
    { 
      cout <<"Choose what to do: \n";
      cout <<"-------------------------\n";
      cout <<"A: PutItem\n";
      cout <<"D: DeleteItem\n";
      cout <<"S: GetItem\n";
      cout <<"I: info. length, IsFull, height...\n";
      cout <<"P: PrintTree\n";
      cout <<"Q: SimplePrintTree\n";
      cout <<"R: (Iterator) ResetTree, GetNextItem\n";
      cout <<"C: MakeEmpty\n";
      cout <<"B: Build Tree from array\n";
      cout <<"E: Quit\n";
      cout <<"G: Get Nodes at Level \n";
      cout <<"-------------------------\n";
      
      cin >> command; 
      switch (command) 
	{ 
	case 'B': 
	  cout <<"Enter a string of chars to build a tree:\n";
	  cin >> str; 
	  
	  tree.MakeEmpty();
	  for (int i=0;i<str.length();i++)
	    {
	      ret = tree.GetItem(str[i], found);
	      if (!found)
		tree.PutItem (str[i]);
	    }
	  break; 
	case 'A': 
	  cout <<"Enter a char to insert:\n";
	  cin >> item; 
	  
	  item = tree.GetItem(item, found);
	  if (found)
	    cout << item << " already in list." << endl;
	  else 
	    {
	      tree.PutItem(item);
	      cout << item;
	      cout << " is inserted" << endl;
	    }
	  break; 
	case 'D': 
	  cout <<"Enter a char to delete:\n";
	  cin >> item;
	  tree.DeleteItem(item);
	  cout << item;
	  cout << " is deleted" << endl;
	  break;
    	case 'S': 
	  cout <<"Enter a char to search:\n";
	  cin >> item;
	  
	  item = tree.GetItem(item, found);
	  if (found)
	    cout << item << " found in list." << endl;
	  else cout << item  << " not in list."  << endl;  
	  break;
	case 'I':
	  cout << "Number of nodes is " << tree.GetLength() << endl;
	  
	  cout << "Height of tree is " << tree.Height() << endl;
	  
	  if (tree.IsEmpty())
	    cout << "Tree is empty." << endl;
	  else cout << "Tree is not empty."  << endl;  
	  
	  if (tree.IsFullTree())
	    cout << "Tree is full."  << endl;
	  else 
	    cout << "Tree is not full." << endl;  
	  break; 
	case 'P': 
	  tree.PrettyPrint();
	  cout << endl;
	  break;
	case 'Q':
	  tree.SimplePrettyPrint();
	  cout << endl;
	  break;
	case 'R': 
	  cout <<"traversal order (preorder, inorder or postorder)"; 
	  cin >> orderItem;
	  if (orderItem == "preorder")
	    order = PRE_ORDER;
	  else if (orderItem == "inorder")
	    order = IN_ORDER;
	  else order = POST_ORDER;    
	  
	  cout <<"traversing nodes in the given order:";
	  tree.ResetTree(order);
	  do {
	    item = tree.GetNextItem(order,finished);
	    cout << item;
	  } while (!finished); 
	  cout << endl;
	  break;
	case 'C':
	  tree.MakeEmpty();
	  cout << "Tree has been made empty." << endl;
	  break;
	case 'E':
	  cout <<"Ok, Exiting\n";
	  break;
	  /*case 'G':
	  cout << "Enter the level you would like to search" << endl;
	  cin >> level;
	  
	  tree.GetNodesAtLevel(tempArray,level);
	  */		       
	default:
	  cout << " Command not recognized." << endl;
	}
    } while (command != 'E');
  
  return 0;
}




