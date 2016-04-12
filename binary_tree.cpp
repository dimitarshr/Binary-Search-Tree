#include "binary_tree.h"

// Creates an empty binary tree
binary_tree::binary_tree()
{
	tree = nullptr;
}

// Creates a binary tree with an initial value to store
binary_tree::binary_tree(int value)
{
	tree = new node;
	tree->data = value;
}

// Creates a binary tree from a collection of existing values
binary_tree::binary_tree(const std::vector<int> &values)
{	// By using the 'insert' method I create a new binary tree with the values from the vector. 
	for (int index = 0; index < values.size();index++)
	{
		insert(values[index]);
	}
}
// Creates a copy of existing Binary Search Tree by using the root node.
// This function returns a node pointer to the new Binary Search Tree
node* newTree(node *root){
	node *new_root;
	// If the current node of the provided Binary Search Tree is not empty this part of the code is executed recursively
	if (root!=nullptr){
		// For every node I store the value, the right and left pointers, until I reach I 'nullptr'.
		(new_root) = new node;
		(new_root)->data = root->data;
		(new_root)->left = newTree(root->left);
		(new_root)->right = newTree(root->right);
	}
	// Once I reach the end of the Binary Seach Tree I return 'nullptr'.
	else
		return nullptr;
	return new_root;
}

// Creates a binary tree by copying an existing tree
binary_tree::binary_tree(const binary_tree &rhs)
{
	// I use the 'newTree' method to copy the Binary Search Tree in the current object. 
	this->tree = newTree(rhs.tree);
}

// This function is of type void and deletes all the existing nodes in order to free the allocated memory on the heap.
void deleteTree(node** treeRoot){
		// Recursively I am iterating to the most left node.
		if ((*treeRoot)->left != nullptr)
			deleteTree(&(*treeRoot)->left);
		// Recursively I am iterating to the most right node.
		if ((*treeRoot)->right != nullptr)
			deleteTree(&(*treeRoot)->right);
		// When I reach the end of the Binary Search Tree I start deleting the nodes and setting the to 'nullptr'.
		delete *treeRoot;
		*treeRoot = nullptr;
}
// Destroys (cleans up) the tree
binary_tree::~binary_tree()
{	// If the root of the Binary Search Tree is not empty I will start deleting all the nodes.
	if (tree!=nullptr)
		deleteTree(&tree);
}

// This function creates a node with associated value.
void insertPrivate(node **treeNode, int value){
	// If the current node of the Binary Search Tree is empty I create the root and store the value.
    if (*treeNode == nullptr){
        *treeNode = new node;
        (*treeNode)->data = value;
    }
	// If the Binary Search Tree is not empty I iterate through it to find the best place to store the new value.
    else{
		// If the value is smaller than the value of the current node I go to the left.
        if (value < (*treeNode)->data)
            insertPrivate(&((*treeNode)->left), value);
		// If the value is smaller than the value of the current node I go to the right.
		else if (value > (*treeNode)->data)
            insertPrivate(&((*treeNode)->right), value);
    }
}

// Adds a value to the tree
void binary_tree::insert(int value)
{	// If the value does not exist in the current Binary Search Tree and insert it with the 'insertPrivate' method.
	 if (!exists(value))
		insertPrivate(&tree, value);
}

// This fuunction retruns the smallest value of the right subtree of the current Binary Search Tree.
int smallestRightValue(node* root){
    while (root->left != nullptr){
        root = root->left;
    }
    return root->data;
}

// This function return a node pointer to the Binary Seach Tree from which we remove a value.
node* removeNode(int value, node* treeRoot){
	// First I iterate through the Binary Search Tree to find the node with the associated value.
	// If the value of the current node is greater than the wanted value, I go to the left.
	if (value < treeRoot->data)
		treeRoot->left = removeNode(value, treeRoot->left);
	// If the value of the current node is greater than the wanted value, I go to the right.	
	else if (value > treeRoot->data)
		treeRoot->right = removeNode(value, treeRoot->right);
	// When I find the node with the wanted value this part of code is executed.
	// There are three case which are considered.
	else{
		// The first case if when the node with the wanted value has no children.
		if (treeRoot->right == nullptr && treeRoot->left == nullptr){
			// Then I just delete the node and set it to 'nullptr'.
			delete treeRoot;
			treeRoot = nullptr;
		}
		// The second case has two subcases.
		// The first one is when the node with the wanted value has one left child.
		else if (treeRoot->right == nullptr){
			// I store the node of the left child of this node and afted this I delete it.
			node* newRoot = treeRoot->left;
			delete treeRoot;
			// Here I connect the rest of the subtree with the Binary Search Tree.
			treeRoot = newRoot;
		}
		// The second one is when the node with the wanted value has one right child.
		else if (treeRoot->left == nullptr){
			// I store the node of the right child of this node and afted this I delete it.
			node* newRoot = treeRoot->right;
			delete treeRoot;
			// Here I connect the rest of the subtree with the Binary Search Tree.
			treeRoot = newRoot;
		}
		// The third case is when the node has two children.
		else{
			// I change the value of the current node with the smallest value of the right subtree.
			treeRoot->data = smallestRightValue(treeRoot->right);
			// Now I have two nodes with the same value. I again call the 'removeNode' method in order to remove the duplicate from the right subtree.
			treeRoot->right = removeNode(treeRoot->data, treeRoot->right);
		}
	}
	return treeRoot;
}

// Removes a value from the tree
void binary_tree::remove(int value)
{	// Before I start removing a value, first I check if the value exists in the Binary Search Tree.
	if (exists(value)){
		this->tree = removeNode(value, tree);
	}
}
// This function is of type bool and checks if the given value exists in the Binary Seacrh Tree.
bool existsPrivate(node *root, int value){
	// While the current node is different from 'nullptr' I continue searching for the value.
	while (root!=nullptr){
		// If I find the correct value, I stop iterating the through the while loop.
		if (root->data == value)
			break;
		// If the wanted value us smaller than the value of the current node, I go to the left.
		else if (value < root->data)
			root = root->left;
		// If the wanted value us greater than the value of the current node, I go to the right.
		else if (value > root->data)
			root = root->right;
	}
	// If the node after the iteration is 'nullptr', that means that there was no match.
	if (root == nullptr)
		return false;
	// If I find a match I retrun 'true'.
	if (root->data == value)
		return true;
	return false;
}

// Checks if a value is in the tree
bool binary_tree::exists(int value) const
{
	return existsPrivate(tree, value); 
}
// This function returns a string of the inordered values of the Binary Search Tree.
std::string inorderPrivate(node *root){
		if (root->left != nullptr && root->right != nullptr)
			return 	inorderPrivate(root->left) + " " + std::to_string(root->data) + " " + inorderPrivate(root->right);
		else if (root->left == nullptr && root->right == nullptr)
			return 	std::to_string(root->data);
		else if (root->left == nullptr)
			return 	std::to_string(root->data) + " " + inorderPrivate(root->right);
		else
			return 	inorderPrivate(root->left) + " " + std::to_string(root->data);
}

// Prints the tree to standard out in numerical order
std::string binary_tree::inorder() const
{
	if (tree != nullptr){
		return inorderPrivate(tree);
	}
	else {
		return std::string("");
	}
}

std::string preorderPrivate(node* root){
	if (root->left != nullptr && root->right != nullptr)
		return std::to_string(root->data) + " " + preorderPrivate(root->left) + " " + preorderPrivate(root->right);
	else if (root->left == nullptr && root->right == nullptr)
		return std::to_string(root->data);
	else if (root->left == nullptr)
		return std::to_string(root->data) + " " + preorderPrivate(root->right);
	else
		return std::to_string(root->data) + " " + preorderPrivate(root->left);
}

// Prints the tree in pre-order
std::string binary_tree::preorder() const
{
	if (tree != nullptr)
		return preorderPrivate(tree);
	else 
		return std::string("");
}

std::string postorderPrivate(node* root){
	if (root->left != nullptr && root->right != nullptr)
		return postorderPrivate(root->left) + " " + postorderPrivate(root->right) + " " + std::to_string(root->data);
	else if (root->left == nullptr && root->right == nullptr)
		return std::to_string(root->data);
	else if (root->left == nullptr)
		return postorderPrivate(root->right) + " " + std::to_string(root->data);
	else
		return postorderPrivate(root->left) + " " + std::to_string(root->data);
}

// Prints the tree in post-order
std::string binary_tree::postorder() const
{
	if (tree != nullptr)
		return postorderPrivate(tree);
	else
		return std::string("");
}

// Copy assignment operator
binary_tree& binary_tree::operator=(const binary_tree &other)
{
	node* new_node =  newTree((other.tree));
	deleteTree (&(this->tree));
	this->tree = new_node;
	return *this;
}

// Checks if two trees are equal
bool binary_tree::operator==(const binary_tree &other) const
{
	if (this->inorder() == other.inorder())
		return true;
	return false;
}

// Checks if two trees are not equal
bool binary_tree::operator!=(const binary_tree &other) const
{
	if (this->inorder() != other.inorder())
		return true;
	return false;
}

// Inserts a new value into the binary tree
binary_tree& binary_tree::operator+(int value)
{
	this->insert(value);
    return *this;
}

// Removes a value from the binary tree
binary_tree& binary_tree::operator-(int value)
{
	this->remove(value);
	return *this;
}

// Reads in values from an input stream into the tree
std::istream& operator>>(std::istream &in, binary_tree &value)
{
	int data;
	while (in){
		in >> data;
		value.insert(data);
	}
    return in;
}

// Writes the values, in-order, to an output stream
std::ostream& operator<<(std::ostream &out, const binary_tree &value)
{
	out << value.inorder();
    return out;
}