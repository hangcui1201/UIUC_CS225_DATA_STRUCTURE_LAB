#include "abstractsyntaxtree.h"

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
    // BinaryTree that has std::string for nodes and return the calculated result from that AST

    typename BinaryTree<std::string>::Node* const root = getRoot();
    return evalHelperFunction(root);
}

double AbstractSyntaxTree::evalHelperFunction(const Node* subRoot) const{

    // reference: https://www.geeksforgeeks.org/evaluation-of-expression-tree/

    // Base case
    if(subRoot == NULL){
        return 0;
    }

    // leaf node
    if (subRoot->left == NULL && subRoot->right == NULL){
        double value = std::stod(subRoot->elem);
        return value;
    } 

    double l_value = evalHelperFunction(subRoot->left);
    double r_value = evalHelperFunction(subRoot->right);

    // Check which operator to apply 
    if (subRoot->elem == "+"){
        return l_value + r_value; 
    } 
        
    if (subRoot->elem == "-"){
        return l_value - r_value; 
    }

    if (subRoot->elem == "*"){
        return l_value * r_value; 
    }
  
    return l_value / r_value; 

}

