#include <string>
#include <fstream>
#include <queue>

using namespace std;

enum OrderType {PRE_ORDER, IN_ORDER, POST_ORDER};

template <class ItemType>
class TreeType
{
public:
  TreeType();                     // constructor
  TreeType(const TreeType& originalTree); // copy constructor
  TreeType (ItemType items[], int items_len); //create a balanced BST from
  	// data given in items array

  ~TreeType();                    // destructor

  void operator=(const TreeType& originalTree);
 
  void MakeEmpty();
  bool IsEmpty() const;
  bool IsFull() const;
  bool IsFullTree() const;
  int GetLength() const; 
  int Height() const;

  ItemType GetItem(ItemType item, bool& found) const;
  void PutItem(ItemType item);
  void DeleteItem(ItemType item);
  //int GetNodesAtLevel(ItemType itemsArray[], int level);
  
  //Iterators 
  void ResetTree(OrderType order); 
  ItemType GetNextItem(OrderType order, bool& finished);
  void GetSmallest(ItemType &smallest) const;
  void Print(std::ostream& out) const;
  void PrettyPrint() const;
  void SimplePrettyPrint() const;
  void PrintAncestors(ItemType Item);

private:
  struct TreeNode
  {
    ItemType info;
    TreeNode* left;
    TreeNode* right;
  };

  TreeNode* root;
  queue<ItemType> preQue;
  queue<ItemType> inQue;
  queue<ItemType> postQue;

  //Private helper functions 
  //Static member functions have no calling object. 
  static bool IsFullTree(TreeNode* root);
  static void DestroySubTree(TreeNode* & subTreeRoot);
  //static int GetNodesAtLevel (TreeNode * subTreeRoot, ItemType itemsArray[ ], int level);
  static void CopySubTree(TreeNode* & copy, const TreeNode* originalTree);
  static int CountNodesInSubTree(TreeNode* subTreeRoot);
  static int GetHeightSubTree (TreeNode * subTreeRoot);
  static void GetSmallestInSubTree(TreeNode * subTreeRoot, ItemType &smallest);
  static void GetLargestInSubTree(TreeNode* subTreeRoot, ItemType& data);

  static void RetrieveInSubTree(TreeNode* subTreeRoot, ItemType & item, bool& found);
  static void InsertInSubTree(TreeNode*& subTreeRoot, ItemType item);


  //Delete the tree node pointed to by @param node
  static void DeleteNode(TreeNode* & node);

  //Delete item from the subtree rooted at tree 
  static void DeleteInSubTree(TreeNode*& subTreeRoot, ItemType item);

   
  // Enqueues tree items in preorder.
  static void PreOrder(TreeNode* subTreeRoot, queue<ItemType> & outputQueue);
  // Enqueues tree items in inorder.
  static void InOrder(TreeNode* subTreeRoot, queue<ItemType> & outputQueue);
  // Enqueues tree items in postorder.
  static void PostOrder(TreeNode* subTreeRoot, queue<ItemType> & outputQueue);

  static void PrintTree(TreeNode* subTreeRoot, ostream& outFile);

  //Helper functions for pretty print
  static void getLine (TreeNode * root, int depth, vector<char> & vals);
  static void printRow (TreeNode * p, int height, int depth);
  static void SimplePrintRow (TreeNode * p, int height, int depth);
};

