#include <iostream>
#include <iomanip>
#include <vector>
#include <assert.h>
#include "TreeType.h"
#include <queue>
using namespace std;



///////////////////
// Public Member functions:: 
///////////////////
template<class ItemType>
TreeType<ItemType>::TreeType()
{
  root = NULL;
}


//Initialize the tree (binary search tree) with items given in the
// array (length of the array is passed as "len"
template <class ItemType>
TreeType<ItemType>::TreeType (ItemType items[], int len)
{

   //sort the array (using bubble sort or selection sort)

   // You should consider calling a recursive function to 
   //    create a balanced BST tree 

}



// Calls recursive function DestroySubTree to destroy the tree.
template<class ItemType>
TreeType<ItemType>::~TreeType()
{
  DestroySubTree(root);
}


template<class ItemType>
void TreeType<ItemType>::MakeEmpty()
{
  DestroySubTree(root);
  //root = NULL;
}


// Calls recursive function CopyTree to copy originalTree into root.
template<class ItemType>
TreeType<ItemType>::TreeType(const TreeType& originalTree)
{
  CopyTree(root, originalTree.root);
}

// Calls recursive function CopyTree to copy originalTree 
// into root.
template<class ItemType>
void TreeType<ItemType>::operator= (const TreeType& originalTree)
{
  if (&originalTree == this)
    return;             // Ignore assigning self to self
  DestroySubTree(root);      // Deallocate existing tree nodes
  CopyTree(root, originalTree.root);

}

// Returns true if there is no room for another item 
//  on the free store; false otherwise.
template<class ItemType>
bool TreeType<ItemType>::IsFull() const
{
  TreeNode* location;
  try
  {
    location = new TreeNode;
    delete location;
    return false;
  }
  catch(std::bad_alloc exception)
  {
    return true;
  }
}

template <class ItemType>
bool TreeType <ItemType> :: IsFullTree(TreeNode* root)
{
  if (root == NULL) // if the tree is empty
    return true;
  if ((root->left == NULL) && (root->right == NULL)) // if root has no children
    return true;
  if ((root -> left) && (root -> right)) // if the root has 2 children
    return (IsFullTree(root->left) && IsFullTree(root->right)); //recursively go through tree to check if children trees are full
  return false; // if else return false
// Returns true if the tree is empty; false otherwise.
}

template <class ItemType>
bool TreeType <ItemType> :: IsFullTree() const
{
  return IsFullTree(root);
}

template<class ItemType>
bool TreeType<ItemType>::IsEmpty() const
{
  return root == NULL;
}


// Calls recursive function CountNodes to count the 
// nodes in the tree.
template<class ItemType>
int TreeType<ItemType>::GetLength() const
{
  return CountNodesInSubTree(root);

}
/*
template <class ItemType>
int TreeType<ItemType>::GetNodesAtLevel(ItemType itemsArray[ ], int level)
{
  return GetNodesAtLevel(root, itemsArray, level);
}
*/
//Return the height of the tree 
template<class ItemType>
int TreeType<ItemType>::Height() const
{
    return (GetHeightSubTree(root));
}


// Calls recursive function Retrieve to search the tree for item.
template<class ItemType>
ItemType TreeType<ItemType>::GetItem(ItemType item, bool& found) const
{
  RetrieveInSubTree(root, item, found);
  return item;
}



// Calls recursive function Insert to insert item into tree.
template<class ItemType>
void TreeType<ItemType>::PutItem(ItemType item)
{
  InsertInSubTree(root, item);
}


// Calls recursive function Delete to delete item from tree.
template<class ItemType>
void TreeType<ItemType>::DeleteItem(ItemType item)
{
  DeleteInSubTree(root, item);
}



// Calls recursive function PrintTree to print items in the tree.
template<class ItemType>
void TreeType<ItemType>::Print(ostream& outFile) const
{
  PrintTree(root, outFile);
}


// Iterator: inorder, preorder, postorder traversal of the tree nodes
template<class ItemType>
void TreeType<ItemType>::ResetTree(OrderType order)
// Calls function to create a queue of the tree elements in 
// the desired order.
{
  switch (order)
  {
    case PRE_ORDER : PreOrder(root, preQue);
                     break;
    case IN_ORDER  : InOrder(root, inQue);
                     break;
    case POST_ORDER: PostOrder(root, postQue);
                     break;
  }
}



// Returns the next item in the desired order.
// Post: For the desired order, item is the next item in the queue.
//       If item is the last one in the queue, finished is true; 
//       otherwise finished is false.
template<class ItemType>
ItemType TreeType<ItemType>::GetNextItem(OrderType order, bool& finished)
{
  finished = false;
  ItemType item;
  switch (order)
  {
    case PRE_ORDER  : item = preQue.front();
		      preQue.pop();
                      if (preQue.empty())
                        finished = true;
                      break;
    case IN_ORDER   : item = inQue.front();
		      inQue.pop();
                      if (inQue.empty())
                        finished = true;
                      break;
    case  POST_ORDER: item = postQue.front();
		      postQue.pop();
                      if (postQue.empty())
                        finished = true;
                      break;
  }
  return item;
}

///////////////////////////////////
// Private member functions: they are static member functions that are called by public member functions to help
//  out certain tasks. Some and most of them are recursive functions. 
//  Recursive ideas: 
//   it performs the operation on a BST tree by recursively on a sub-tree
//    so the root of the tree or subtree is passed by parameter! 
//////////////////////////////


// Post: tree pointer is set to NULL; 
//       all nodes in the tree rooted at "tree" have been deallocated.
template<class ItemType>
void TreeType<ItemType>::DestroySubTree(TreeNode* & subTreeRoot)
{
  if (subTreeRoot != NULL)
  {
    DestroySubTree(subTreeRoot->left);
    DestroySubTree(subTreeRoot->right);

    delete subTreeRoot;

    subTreeRoot = NULL;

  }
}

// Pre: originalTree is the address of the root node for a tree 
// Post: copy is the root of a tree that is a duplicate of tree rooted at originalTree
template<class ItemType>
void TreeType<ItemType>::CopySubTree(TreeNode* & copyTreeRoot, const TreeNode* originalTreeRoot)
{
  if (originalTreeRoot == NULL)
    copyTreeRoot = NULL;
  else
  {
    copyTreeRoot = new TreeNode;
    copyTreeRoot->info = originalTreeRoot->info;

    CopySubTree(copyTreeRoot->left, originalTreeRoot->left);
    CopySubTree(copyTreeRoot->right, originalTreeRoot->right);
  }
}




// Post: returns the total number of nodes in the tree that rooted at "tree" 
template<class ItemType>
int TreeType<ItemType>::CountNodesInSubTree(TreeNode* subTreeRoot)
{
  if (subTreeRoot == NULL)
    return 0;
  else 
    return CountNodesInSubTree(subTreeRoot->left) + CountNodesInSubTree(subTreeRoot->right) + 1;
}

template<class ItemType>
void TreeType<ItemType>::GetSmallest(ItemType &smallest) const
{
  smallest = GetSmallestInSubTree(root,smallest);
}

template <class ItemType>
void TreeType<ItemType>::GetSmallestInSubTree(TreeNode * subTreeRoot, ItemType &smallest)
{
  while (subTreeRoot -> left != NULL) {
    subTreeRoot = subTreeRoot -> left;
  }
  smallest = subTreeRoot -> info;
}

// Sets data to the info member of the right-most node in tree.
// i.e., the largest item 
template<class ItemType>
void TreeType<ItemType>::GetLargestInSubTree(TreeNode* subTreeRoot, ItemType& data)
{
  while (subTreeRoot->right != NULL)
  {
    subTreeRoot = subTreeRoot->right;
  }
  data = subTreeRoot->info;
}

//return the height of the tree given by the rootNode 
// height of a tree is defined to be the deepest level of the tree
template<class ItemType>
int TreeType<ItemType>::GetHeightSubTree (TreeNode * subTreeRoot)
{
   if (subTreeRoot==NULL)
	return 0;
   else {
	int left = GetHeightSubTree (subTreeRoot->left);
        int right = GetHeightSubTree (subTreeRoot->right); 
	if (left<=right)
		return right+1;
        else
		return left+1;
   }
}

/* return the number of nodes in the given level, itemArray[0...] stores the items values precondition: level <= 0
*/
/*
template <class ItemType>
int TreeType<ItemType>::GetNodesAtLevel (TreeNode * subTreeRoot, ItemType itemsArray[ ], int level)
{
  queue <TreeNode*> curLevelNodes; //creation of empty queue
  queue <TreeNode*> nextLevelNodes;


  
  if (subTreeRoot == NULL)
    return 0;

  
  curLevelNodes.push(subTreeRoot);


  for (int i = 1; i <= level; i++) {
    while (curLevelNodes.empty() == false)
      {
	
	curLevelNodes.pop();
	
	if (subTreeRoot->left != NULL) {
	  nextLevelNodes.push(subTreeRoot->left);
	}
	if (subTreeRoot->right != NULL) {
	  nextLevelNodes.push(subTreeRoot->right);
	}
      }
    swap(nextLevelNodes, curLevelNodes);
  }
  for (int i = 0; i < curLevelNodes.size(); i++)
    {
      itemsArray[i] = curLevelNodes.front();
      curLevelNodes.pop();
    }

  int n = sizeof(itemsArray);
  int size = n/sizeof(char);
  return size;
}
*/
      


// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item's,
//       found is true and item is set to a copy of someItem; 
//       otherwise found is false and item is unchanged.
template<class ItemType>
void TreeType<ItemType>::RetrieveInSubTree(TreeNode* subTreeRoot, ItemType& item, bool& found)
{
   if (subTreeRoot == NULL)
    found = false;                     // item is not found.
   else if (item < subTreeRoot->info)      
    RetrieveInSubTree(subTreeRoot->left, item, found); // Search left subtree.
   else if (item > subTreeRoot->info)
    RetrieveInSubTree(subTreeRoot->right, item, found);// Search right subtree.
   else
   {
      item = subTreeRoot->info;                 // item is found.
      found = true;
   }
} 

// Inserts item into tree rooted at @param subTreeRoot 
// Post:  item is in tree; search property is maintained.
template<class ItemType>
void TreeType<ItemType>::InsertInSubTree(TreeNode* & subTreeRoot, ItemType item)
{
  if (subTreeRoot == NULL)
  {// Insertion place found.
    subTreeRoot = new TreeNode;
    subTreeRoot->right = NULL;
    subTreeRoot->left = NULL;

    subTreeRoot->info = item;
  }
  else if (item < subTreeRoot->info)
    InsertInSubTree(subTreeRoot->left, item);    // Insert in left subtree.
  else
    InsertInSubTree(subTreeRoot->right, item);   // Insert in right subtree.
} 


// Deletes item from a tree rooted at @param subTreeRoot
// Post:  item is not in tree.
template<class ItemType>
void TreeType<ItemType>::DeleteInSubTree(TreeNode* & subTreeRoot, ItemType item)
{
  if (item < subTreeRoot->info)
    DeleteInSubTree(subTreeRoot->left, item);   // Delete item from left subtree.
  else if (item > subTreeRoot->info)
    DeleteInSubTree(subTreeRoot->right, item);  // Delete item from right subtree.
  else // item==subTreeRoot->info 
    DeleteNode(subTreeRoot);           // delete the node subTreeRoot
}   




// Deletes the node pointed to by node.
// Post: The user's data in the node pointed to by node is no 
//       longer in the tree.  If node is a leaf node or has only one 
//       non-NULL child pointer the node pointed to by node is 
//       deleted, and node is updated to point to the non-NULL child,
//       otherwise, the user's data in node is replaced by its 
//       logical predecessor and the predecessor's node is deleted.
template<class ItemType>
void TreeType<ItemType>::DeleteNode(TreeNode* & node)
{
  ItemType data;
  TreeNode* tempPtr;

  tempPtr = node;
  if (node->left == NULL)
  { //If the node has no left child 
    node = node->right;
    delete tempPtr;
  }
  else if (node->right == NULL)
  { //if the node has no right child 
    node = node->left;
    delete tempPtr;
  }
  else
  { //The node has left and right children 
    GetSmallestInSubTree(node->right, data);
    node->info = data; //store the predecessor's node's info in node ...
    DeleteInSubTree(node->right, data);  // Delete data from the right tree... (which is a leaf node).

  }
}



template<class ItemType>
void TreeType<ItemType>::PreOrder(TreeNode* subTreeRoot, queue<ItemType> & preQue)
// Post: preQue contains the tree items in preorder.
{
  if (subTreeRoot != NULL)
  {
    preQue.push(subTreeRoot->info);
    PreOrder(subTreeRoot->left, preQue);
    PreOrder(subTreeRoot->right, preQue);
  }
}


template<class ItemType>
void TreeType<ItemType>::InOrder(TreeNode* subTreeRoot, queue<ItemType> & inQue)
// Post: inQue contains the tree items in inorder.
{
  if (subTreeRoot != NULL)
  {
    InOrder(subTreeRoot->left, inQue);
    inQue.push(subTreeRoot->info);
    InOrder(subTreeRoot->right, inQue);
  }
}


// Post: postQue contains the tree items in postorder.
template<class ItemType>
void TreeType<ItemType>::PostOrder(TreeNode* subTreeRoot, queue<ItemType> & postQue)
{
  if (subTreeRoot != NULL)
  {
    PostOrder(subTreeRoot->left, postQue);
    PostOrder(subTreeRoot->right, postQue);
    postQue.push(subTreeRoot->info);
  }
}


// Prints info member of items in tree in sorted order on outFile.
template<class ItemType>
void TreeType<ItemType>::PrintTree(TreeNode* subTreeRoot, ostream& outFile)
{
  if (subTreeRoot != NULL)
  {
    PrintTree(subTreeRoot->left, outFile);   // Print left subtree.
    outFile << subTreeRoot->info;
    PrintTree(subTreeRoot->right, outFile);  // Print right subtree.
  }
}

//Display the items stored in the parent of the node, the grandparent, and so on starting from root (ancestor of all nodes), ... all the way to the parent of the node
template <class ItemType>
void TreeType<ItemType>::PrintAncestors (ItemType value)
{
  TreeNode *p;
  p = root; // create new node, assign to root

  while (p->info != value) // traverse through tree, display
    {
      cout << p->info << endl;
      if (p->info < value)
	p = p-> right;
      else
	p = p-> left;
    }
}
  
    
  
    
  


///////////////////////////////
//Pretty print
///////////////////////////////
 
//Store the nodes at the depth-level of the tree (given at root)
//in the vector of vals 
//Precondition: root!=NULL, depth >= 0 
template<class ItemType>
void TreeType<ItemType>::getLine (TreeNode * subTreeRoot, int depth, vector<char> & vals)
{
   assert (subTreeRoot!=NULL && depth>=0);

   if (depth==0){ //base case 
       	vals.push_back (subTreeRoot->info);
   } 
   else {	//general case ... 
   	if (subTreeRoot->left != NULL)
           getLine (subTreeRoot->left, depth-1, vals);
   	else //EZ if (depth-1<=0)
        {
	   int cnt=1;
	   for (int i=0;i<depth-1;i++)
		cnt*=2;
	   for (int i=0;i<cnt;i++)
           	vals.push_back ('#');
	} 
    
   	if (subTreeRoot->right!=NULL)
		getLine (subTreeRoot->right, depth-1, vals);
   	else //if (depth-1<=0)
        {
	   int cnt=1;
	   for (int i=0;i<depth-1;i++)
		cnt*=2;
	   for (int i=0;i<cnt;i++)
           	vals.push_back ('#');
	}
   } 

}

template<class ItemType>
void TreeType<ItemType>::printRow (TreeNode * p, int height, int depth)
{
	vector<char> vec;

        getLine(p, depth, vec);

        cout << setw((height - depth)*2); // scale setw with depth
        bool toggle = true; // start with left
        if (vec.size() > 1) {
                //for (int v : vec) {
                for (int i=0; i<vec.size(); i++){
                        if (vec[i] != ' ') {
                                if (toggle)
                                        cout << "/" << "   ";
                                else
                                        cout << "\\" << "   "; //this will display 
                        }
                        toggle = !toggle;
                }
                cout << endl;
                cout << setw((height - depth)*2);
	}
        for (int i=0;i<vec.size();i++) 
                if (vec[i] != ' ')
                        cout << vec[i] << "   ";
        cout << endl;

}

template<class ItemType>
void TreeType<ItemType>::SimplePrintRow (TreeNode * p, int height, int depth)
{
	vector<char> vec;

        getLine(p, depth, vec);

        for (int i=0;i<vec.size();i++) 
                if (vec[i] != ' ')
                        cout << vec[i];
                else 
		{
			assert (false);
			cout << "# " ;
		}
	cout <<endl;

}

template<class ItemType>
void TreeType<ItemType>::PrettyPrint () const
{
   int height = GetHeightSubTree (root); //*2;
   for (int i=0;i<=height;i++)
   {
       printRow (root, height, i);
   }
}


template<class ItemType>
void TreeType<ItemType>::SimplePrettyPrint () const
{
   int height = GetHeightSubTree (root); //*2;
   for (int i=0;i<=height;i++)
   {
       SimplePrintRow (root, height, i);
   }
}
//End of Pretty print
///////////////////////////////
