/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL) // Empty tree's height = -1
        return -1;

    // Recursive definition, get the height recursively
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // in-order-traversal

    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirrorHelperFunction(root);
}

template <typename T>
void BinaryTree<T>::mirrorHelperFunction(Node* subRoot){

    // Base case
    if (subRoot == NULL) {
        return;
    }

    mirrorHelperFunction(subRoot->left);
    mirrorHelperFunction(subRoot->right);

    Node* switch_temp = subRoot->left;
    subRoot->left = subRoot->right;
    subRoot->right = switch_temp;

}




/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here

    // Base case
    if(root == NULL){return true;}

    // Tree has only one node
    if(root->left == NULL && root->right == NULL){return true;}

    InorderTraversal<T> tree(root);
    TreeTraversal<int>::Iterator it = tree.begin();

    T value = (*it)->elem; // first value
    ++it;

    while(it != tree.end()){
        if(value > (*it)->elem){
            return false;
        } else {
            value = (*it)->elem; // Update value, make sure the non-decreasing sequence
        }
        ++it;
    }

    // If no violation, return true
    return true;

}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    return isOrderedRecursiveHelperFunction(root);
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursiveHelperFunction(const Node* subRoot) const
{
    // current subRoot->elem should larger or equal than right most value in its left subtree
    // current subRoot->elem should smaller or equal than left most value in its right subtree

    // Base case
    if (subRoot == NULL) { return true; }

    if(subRoot->left == NULL && subRoot->right == NULL){
        return true;
    }

    // std::cout << subRoot->elem << std::endl;

    bool result = true;

    if(subRoot->left != NULL){
        result = (subRoot->elem >= maxValueInLeftSubTree(subRoot->left));
    }

    if(subRoot->right != NULL){
        result = (subRoot->elem <= minValueInRightSubTree(subRoot->right));
    }

    return (result && isOrderedRecursiveHelperFunction(subRoot->left) && isOrderedRecursiveHelperFunction(subRoot->right));
   
}

template <typename T>
T BinaryTree<T>::maxValueInLeftSubTree(const Node* subRoot) const 
{
    if(subRoot->left == NULL && subRoot->right == NULL){
        return(subRoot->elem);	
    }
		
    if(subRoot->left != NULL && subRoot->right != NULL){

        T max_value = std::max(subRoot->elem, std::max(maxValueInLeftSubTree(subRoot->left), maxValueInLeftSubTree(subRoot->right)));
        return max_value;

    } else if (subRoot->right == NULL && subRoot->left != NULL){

        T max_value = std::max(subRoot->elem, maxValueInLeftSubTree(subRoot->left));
        return max_value;

    } else {

        T max_value = std::max(subRoot->elem, maxValueInLeftSubTree(subRoot->right));
        return max_value;  
    }

}


template <typename T>
T BinaryTree<T>::minValueInRightSubTree(const Node* subRoot) const{

    if(subRoot->left == NULL && subRoot->right == NULL){
        return(subRoot->elem);	
    }
		
    if(subRoot->left != NULL && subRoot->right != NULL){

        T min_value = std::min(subRoot->elem, std::min(minValueInRightSubTree(subRoot->left), minValueInRightSubTree(subRoot->right)));
        return min_value;

    } else if (subRoot->right == NULL && subRoot->left != NULL){

        T min_value = std::min(subRoot->elem, minValueInRightSubTree(subRoot->left));
        return min_value;

    } else {

        T min_value = std::min(subRoot->elem, minValueInRightSubTree(subRoot->right));
        return min_value;  
    }

}


/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths) const
{
    // your code here
    std::vector<T> path;
    getPathsHelperFunction(root, path, paths);
}

template <typename T>
void BinaryTree<T>::getPathsHelperFunction(const Node* subRoot, std::vector<T> path, std::vector<std::vector<T>> &paths) const
{
    // Base case
    if (subRoot == NULL){
        return; 
    }

    path.push_back(subRoot->elem); // Add current value to path

    if(subRoot->left == NULL && subRoot->right == NULL){
        paths.push_back(path);
    } else if(subRoot->left != NULL && subRoot->right == NULL){
        getPathsHelperFunction(subRoot->left, path, paths);
    } else if(subRoot->left == NULL && subRoot->right != NULL){
        getPathsHelperFunction(subRoot->right, path, paths);
    } else { // subRoot->left != NULL && subRoot->right != NULL
        getPathsHelperFunction(subRoot->left, path, paths);
        getPathsHelperFunction(subRoot->right, path, paths);
    }

}


/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    return sumDistancesHelperFunction(root, 0);
}

template <typename T>
int BinaryTree<T>::sumDistancesHelperFunction(const Node* subRoot, int count) const
{
    if(subRoot==NULL){
        return 0;
    }

    return count + sumDistancesHelperFunction(subRoot->left, count+1) + sumDistancesHelperFunction(subRoot->right, count+1);
}
