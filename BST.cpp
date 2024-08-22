#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}

bool BST::display( int order, int source) {



	if (root == nullptr) {
		cout << "The tree is empty." << endl;
		return false;
	}


	ofstream out;

	cout << "Display in ascending order(1)\nDisplay in descending order(2)\n";
	cin >> order;

	cout << "Display on screen(1)\nDisplay in file(2)\n";
	cin >> source;


	if (order == 1)
	{

		if (source == 1) {
			cout << "\nDisplaying in ascending order:\n";
			inOrderPrint();
		}
		else
		{
			out.open("student - info.txt");

			if (out.is_open()) {
				cout << "\nSuccessfully print to file in ascending order\n";
				streambuf* coutBuf = cout.rdbuf();
				cout.rdbuf(out.rdbuf());
				inOrderPrint();
				cout.rdbuf(coutBuf);
				out.close();
			}
		}
	}
	else if(order==2)
	{
		if (source == 1)
		{
			cout << "\nDisplaying in descending order:\n";
			inOrderPrintReverse(root);
		}
			
		else
		{
			out.open("student - info.txt");

			if (out.is_open())
			{
			
				out.open("student-info.txt");
				if (out.is_open()) 
				{
					cout << "\nSuccessfully print to file in descending order\n";
					inOrderPrintReverseToFile(root, out);
					out.close();
				}
			}

		}
	}

		return true;
}



void BST::inOrderPrintReverse(BTNode* cur) {
	if (cur == nullptr) return;
	inOrderPrintReverse(cur->right);//visit right first then to left
	cur->item.print(cout);
	inOrderPrintReverse(cur->left);
}

void BST::inOrderPrintReverseToFile(BTNode* cur, ofstream& out)
{
	if (cur == nullptr) return;
	inOrderPrintReverseToFile(cur->right, out);
	cur->item.print(out);
	inOrderPrintReverseToFile(cur->left, out);
}

bool BST::printPath()
{

	int arr[10];
	BTNode* cur = root;

	if (root == nullptr) {
		cout << "The tree is empty." << endl;
		return false;
	}
	cout << "Below are all the external paths for the tree:\n";
	printPathRootToLeaf(cur, arr, 0);
	
}

void BST::printPathRootToLeaf(BTNode* cur, int arr[], int index)
{
	if (cur == nullptr)
		return;

	arr[index] = cur->item.id;

	if (cur->left == nullptr && cur->right == nullptr)
	{
		
		for (int i = 0; i <= index; i++)
		{
			cout << arr[i] << " ";
		}
		cout << "\n\n";
	}
	printPathRootToLeaf(cur->left, arr, index + 1);
	printPathRootToLeaf(cur->right, arr, index + 1);

}




bool BST::deepestNodes()
{
	BTNode* cur = root;
	int arr[10];

	if (root == nullptr) {
		cout << "The tree is empty." << endl;
		return false;
	}
	cout << "Deepest nodes in the tree:\n";
	printDeepest(cur, arr, 0);

}

void BST::printDeepest(BTNode* cur, int arr[], int index)
{
	if (cur == nullptr)
		return;

	arr[index] = cur->item.id;

	if (cur->left == nullptr && cur->right == nullptr)
	{

		cout << arr[index];
		cout << "\n\n";
	}
	printDeepest(cur->left, arr, index + 1);
	printDeepest(cur->right, arr, index + 1);

}



bool BST::printLevelNodes()
{
	if (root == nullptr) {
		cout << "Tree is empty!" << endl;
		return false;
	}

	Queue q;
	BTNode* cur = nullptr;
	int level = 0;

	q.enqueue(root);

	while (!q.empty()) {
		int levelSize = q.size();
		cout << "Nodes at level " << level + 1 << ": ";

		for (int i = 0; i < levelSize; i++) {
			q.dequeue(cur);

			cout << cur->item.id << " ";

			if (cur->left != NULL) {
				q.enqueue(cur->left);
			}
			if (cur->right != NULL) {
				q.enqueue(cur->right);
			}
		}

		cout << endl;
		level++;
	}

	cout << "\n";
	return true;
}


bool BST::CloneSubtree(BST clonedTree,type item) {


	if (root == nullptr) {
		cout << "Cannot clone subtree. Tree is empty." << endl;
		return false;
	}

	cout << "Enter the id where you want to start the clone:";
	cin >> item.id;



	BTNode* foundNode = search(item); // Find the node with the specified item value
	if (foundNode == nullptr) {
		cout << "Cannot clone subtree. Item not found." << endl;
		return false;
	}

	clonedTree.root = cloneSubtree(foundNode);	// Clone the subtree starting from the found node and store it in the clonedTree

	cout << "Cloned subtree successfully." << endl;


	cout << "Cloned Subtree:" << endl;
	clonedTree.inOrderPrint();
	cout << endl;

	return true;
}

BTNode* BST::cloneSubtree(BTNode* node) {
	if (node == nullptr)
		return nullptr;

	// Create a new node with the same data as the current node
	BTNode* newNode = new BTNode(node->item);

	// Recursively clone the left and right subtrees
	newNode->left = cloneSubtree(node->left);
	newNode->right = cloneSubtree(node->right);

	return newNode;
}



BTNode* BST::search(type item) {
	BTNode* current = root;

	while (current != nullptr) {
	
		if (current->item.id == item.id) 	{
			return current;
		}
		
		else if (item.id < current->item.id) 
		{
			current = current->left;
		}

		else 
			current = current->right;  
		
	}

	return nullptr;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}




