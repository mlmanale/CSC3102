/**
 * Models an AVL tree.
 * @param <E> data type of elements of the tree
 * @author William Duncan, YOUR NAME
 * @see AVLTree
 * <pre>
 * Date: LAST DATE MODIFIED
 * CSC 3102 Programming Project # 2
 * Instructor: Dr. Duncan 
 *
 * DO NOT REMOVE THIS NOTICE (GNU GPL V2):
 * Contact Information: duncanw@lsu.edu
 * Copyright (c) 2022 William E. Duncan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>
 * </pre>
 */

#include "AVLTree.h"
#include <cstdlib>
#include <iostream>
#include <queue>
#include <cmath>
#include <sstream>

using namespace std;

/* Nested Node class definitions */

template <typename E>
AVLTree<E>::Node::Node(E s)
{
   data = s; //data in the note
   left = NULL; //left child
   right = NULL; //right child
   bal = EH; //balanced factor of this node
}

/* Outer AVLTree class definitions */

template <typename E>
AVLTree<E>::AVLTree()
{
   root = NULL;
   count = 0;
   cmp = [](E a, E b) -> int{return a < b? -1 : (a == b? 0 : 1);};
}

template <typename E>
AVLTree<E>::AVLTree(std::function<int(E,E)> fn)
{
    root = NULL;
    count = 0;
    if (cmp == nullptr) 
        cmp = fn;
}

template <typename E>
AVLTree<E>::~AVLTree()
{
   recDestroy(root);
}


template <typename E>
bool AVLTree<E>::isEmpty() const
{
   return root == NULL;
}

template<typename E>
void AVLTree<E>::insert(const E& obj)
{
   bool forTaller;
   Node* newNode = new Node(obj);
   /* If it is the first node in the tree */
   if (!inTree(obj))
      count++;
   root = insert(root, newNode, forTaller);
}

template<typename E>
bool AVLTree<E>::inTree(const E& item) const
{
   Node *tmp;
   if (isEmpty())
      return false;
   /*find where it is */
   tmp = root;
   while (1)
   {
      if (cmp(tmp->data,item) == 0)
         return true;
      if (cmp(tmp->data, item) > 0)
      {
         if (!(tmp->left))
            return false;
         /* continue searching */
         tmp = tmp->left;
      }
      else
      {
         if (!(tmp->right))
            return false;
         /* continue searching for insertion pt. */
         tmp = tmp->right;
      }
   }
}

template<typename E>
void AVLTree<E>::remove(const E& item)
{
   bool shorter;
   bool success;
   Node* newRoot;
   if (!inTree(item))
      return;
   newRoot = remove(root, item, shorter, success);
   if (success)
   {
      root = newRoot;
      count--;
   }
}

template<typename E>
const E& AVLTree<E>::retrieve(const E& key) const
{
   Node* tmp;
   if (isEmpty())
      throw AVLTreeException("AVL Tree Exception: tree empty on retrieve()");
   tmp = root;
   while(true)
   {
      if (cmp(tmp->data,key) == 0)
         return tmp->data;
      if (cmp(tmp->data, key) > 0)
      {
         if (tmp->left == NULL)
            throw new AVLTreeException("AVL Tree Exception: key not in tree call to retrieve()");
         tmp = tmp->left;
      }
      else
      {
         if (tmp->right ==  NULL)
            throw new AVLTreeException("AVL Tree Exception: key not in tree call to retrieve()");
         tmp = tmp->right;
      }
   }
   //return tmp->data;
}

template<typename E>
void AVLTree<E>::traverse(FuncType func)
{
   traverse(root,func);
}

template<typename E>
int AVLTree<E>::size() const
{
   return count;
}

/* BEGIN: Augmented Public Auxiliary Functions */

template <typename E>
vector<string> AVLTree<E>::genPaths()
{
    /**
    * This function generates the string representations of the 
    * root to leaf paths in this tree
    * @return a vector containing the string representations of the 
    * root-to-leaf paths of this tree
    */

   //implement this function
   return vector<string>(); 
}

template <typename E>
bool AVLTree<E>::isFibonacci() const
{
   /**
    * Determines whether this tree is a Fibonacci tree
    * @return true if this tree is a Fibonacci tree; otherwise, false
    */

    //implement this function
   return false;    
}

template<typename E>
int AVLTree<E>::height() const
{
    return height(root);
}

template<typename E>
int AVLTree<E>::fullCount() const
{
    /**
    * Gives the number of full nodes in this tree
    * @return the number of full nodes in this tree
    */

    //implement this function  
    return 0;
}

template <typename E>
int AVLTree<E>::fibonacci(int n)
{
   /**
     * An auxiliary function that iteratively computes a fibonacci number
     * @param n the position of the term in the fibonacci sequence
     * @return the nth fibonacci number or -1 if n < -1
     */

   //implement this method
   return 0;
}

/* END: Augmented Private Auxiliary Functions */


/* Private functions */

template<typename E>
void AVLTree<E>::recDestroy(Node* root)
{
   if (root)
   {
      if (root->left) recDestroy(root->left);
      if (root->right) recDestroy(root->right);
      delete root;
   }
   return;
}

template<typename E>
typename AVLTree<E>::Node* AVLTree<E>::insert(Node* curRoot, Node* newNode, bool& taller)
{
   if (curRoot == NULL)
   {
      curRoot = newNode;
      taller = true;
      return curRoot;
   }
   if (cmp(newNode->data,curRoot->data) < 0)
   {
      curRoot->left = insert(curRoot->left,newNode, taller);
      if (taller)
         switch(curRoot->bal)
         {
            case LH: // was left-high -- rotate
               curRoot = leftBalance(curRoot, taller);
               break;
            case EH: //was balanced -- now LH
               curRoot->bal = LH;
               break;  
            case RH: //was right-high -- now EH
               curRoot->bal = EH;
               taller = false;
               break;
         }
      return curRoot;
   }
   if (cmp(newNode->data,curRoot->data) > 0)
   {
      curRoot->right = insert(curRoot->right,newNode,taller);
      if (taller)
         switch(curRoot->bal)
         {
            case LH: // was left-high -- now EH
               curRoot->bal = EH;
               taller=false;
               break;
           case EH: // was balance -- now RH
              curRoot->bal = RH;
              break;
           case RH: //was right high -- rotate
              curRoot = rightBalance(curRoot,taller);
              break;
         }
      return curRoot;
   }
   else
   {
      curRoot->data = newNode->data;
      delete newNode;
      taller = false;
      return curRoot;
   }
}

template<typename E>
typename AVLTree<E>::Node* AVLTree<E>::leftBalance(Node* curRoot, bool& taller)
{
   Node* rightTree;
   Node* leftTree;   
   leftTree = curRoot->left;
   switch(leftTree->bal)
   {
      case LH: //left-high -- rotate right
         curRoot->bal = EH;
         leftTree->bal = EH;
         // Rotate right
         curRoot = rotateRight(curRoot);
         taller = false;
         break;
      case EH: // This is an error
         cerr<<"AVL Tree Error: error in balance tree in call to leftBalance()"<<endl;
         exit(-5);
         break;   
      case RH: // right-high - requires double rotation: first left, then right
         rightTree = leftTree->right;
         switch(rightTree->bal)
         {
            case LH:
               curRoot->bal = RH;
               leftTree->bal = EH;
               break;   
            case EH:
               curRoot->bal = EH;
               leftTree->bal = EH;   
               break;
            case RH:
               curRoot->bal = EH;
               leftTree->bal = LH;
               break;
         }
         rightTree->bal = EH;
         // rotate left
         curRoot->left = rotateLeft(leftTree);
         //rotate right
         curRoot = rotateRight(curRoot);
         taller= false;
   }
   return curRoot;
}

template<typename E>
typename AVLTree<E>::Node* AVLTree<E>::rightBalance(Node* curRoot, bool& taller)
{
   Node* rightTree;
   Node* leftTree;
   rightTree = curRoot->right;
   switch(rightTree->bal)
   {
      case RH: //right-high -- rotate left   
         curRoot->bal = EH;
         rightTree->bal = EH;
         // Rotate left
         curRoot = rotateLeft(curRoot);
         taller = false;
         break;
      case EH: // This is an error
         cerr<<"AVL Tree Error: error in balance tree in call to rightBalance()"<<endl;
         exit(1);
         break;
      case LH: // left-high - requires double rotation: first right, then left
         leftTree = rightTree->left;
         switch(leftTree->bal)
         {
            case RH:
               curRoot->bal = LH;
               rightTree->bal = EH;
               break;
            case EH:   
               curRoot->bal = EH;
               rightTree->bal = EH;    
               break;
            case LH:
               curRoot->bal = EH;
               rightTree->bal = RH;
               break;
         }
         leftTree->bal = EH;
         // rotate right
         curRoot->right = rotateRight(rightTree);
         //rotate left
         curRoot = rotateLeft(curRoot);
         taller = false;
   }
   return curRoot;
}

template<typename E>
typename AVLTree<E>::Node* AVLTree<E>::rotateLeft(Node* node)
{
   Node* tmp;
   tmp = node->right; 
   node->right = tmp->left;
   tmp->left = node;
   return tmp;
}

template<typename E>
typename AVLTree<E>::Node* AVLTree<E>::rotateRight(Node* node)
{
   Node* tmp;
   tmp = node->left;
   node->left = tmp->right;
   tmp->right = node;
   return tmp;
}   


template<typename E>
void AVLTree<E>::traverse(Node* node, FuncType func)
{
   if (node)
   {
      traverse(node->left,func);
      func(node->data);
      traverse(node->right,func);
   }
}


template<typename E>
typename AVLTree<E>::Node* AVLTree<E>::remove(Node* node,const E& key, bool& shorter, bool& success)
{
   Node* delPtr;   
   Node* exchPtr;
   Node* newRoot;
   if (node == NULL) 
   {
      shorter = false;
      success = false;
      return NULL;
   }
   if (cmp(key,node->data) < 0)
   {
      node->left = remove(node->left,key,shorter,success);
      if (shorter)
         node = deleteRightBalance(node,shorter);
   }
   else if (cmp(key,node->data) > 0)
   {
      node->right = remove(node->right,key,shorter,success);
      if (shorter)
         node = deleteLeftBalance(node,shorter);
   }
   else
   {
      delPtr = node;
      if (node->right == NULL)
      {
         newRoot = node->left;
         success = true;
         shorter = true;
         delete delPtr;
         return newRoot;
      }
      if(node->left == NULL)
      {
         newRoot = node->right;
         success = true;
         shorter = true;
         delete delPtr;
         return newRoot;
      }
      else
      {
         exchPtr = node->left;
         while(exchPtr->right != NULL)
            exchPtr = exchPtr->right;
         node->data = exchPtr->data;
         node->left = remove(node->left,exchPtr->data,shorter,success);
         if (shorter)
            node = deleteRightBalance(node,shorter);
      }
   }
   return node;
}


template<typename E>
typename AVLTree<E>::Node* AVLTree<E>::deleteRightBalance(Node* node,bool& shorter)
{
   Node* rightTree;
   Node* leftTree;
   switch(node->bal)
   {
      case LH: //deleted left -- now balanced  
         node->bal = EH;
         break;
         case EH: //now right high
         node->bal = RH;
         shorter = false;
         break;
      case RH: // right high -- rotate left
         rightTree = node->right;
         if (rightTree->bal == LH)
         {
            leftTree = rightTree->left;
            switch(leftTree->bal)
            {
               case LH:
                  rightTree->bal = RH;
                  node->bal = EH;
                  break;
               case EH:
                  node->bal = EH;
                  rightTree->bal = EH;
                  break;
               case RH:
                  node->bal = LH;
                  rightTree->bal = EH;
                  break;
            }
            leftTree->bal = EH;
            //rotate right, then left
            node->right = rotateRight(rightTree);
            node = rotateLeft(node);
         }
         else
         {
            switch(rightTree->bal)
            {
               case LH: 
               case RH:
                  node->bal = EH;
                  rightTree->bal = EH;
                  break;
               case EH:
                  node->bal = RH;
                  rightTree->bal = LH;
                  shorter = false;
                  break;
            }
            node = rotateLeft(node);
         }
      }
   return node;
}

template<typename E>
typename AVLTree<E>::Node* AVLTree<E>::deleteLeftBalance(Node* node,bool& shorter)
{
   Node* rightTree;
   Node* leftTree;
   switch(node->bal)
   {
      case RH: //deleted right -- now balanced  
         node->bal = EH;
         break;
      case EH: //now left high
         node->bal = LH;
         shorter = false;
         break;
      case LH: // left high -- rotate left
         leftTree = node->left;
         if (leftTree->bal == RH)
         {
            rightTree = leftTree->right;
            switch(rightTree->bal)
            {
               case RH:
                  leftTree->bal = LH;
                  node->bal = EH;
                  break;
               case EH:
                  node->bal = EH;
                  leftTree->bal = EH;
                  break;
               case LH:
                  node->bal = RH;
                  leftTree->bal = EH;
                  break;
            }
            rightTree->bal = EH;
            //rotate left, then right
            node->left = rotateLeft(leftTree);
            node = rotateRight(node);
         }
         else
         {
            switch(leftTree->bal)
            {
               case RH: 
               case LH:
                  node->bal = EH;
                  leftTree->bal = EH;
                  break;
               case EH:
                  node->bal = LH;
                  leftTree->bal = RH;
                  shorter = false;
                  break;
            }
            node = rotateRight(node);
         }
      }
   return node;
}
/* BEGIN: Augmented Private Auxiliary Functions */

template<typename E>
int AVLTree<E>::height(Node* node) const
{
   /**
     * Determines the height of the subtree rooted at the specified node
     * @param node a root of the subtree
     * @return the height of the tree rooted at the specified node
     */

    //implement this function
    return 0;    
}

template<typename E>
int AVLTree<E>::fullCount(Node* node) const
{
   /**
     * An auxiliary function that recursively counts the number of full
     * nodes in the subtree rooted at the specified node
     * @param node the root of a subtree
     * @return the number of full nodes in the subtree rooted at the specified node
     */

    //implement this method
    return 0;
}

template<typename E>  
void AVLTree<E>::genPaths(Node* node, string subPath, vector<string>& paths)
{
    /**
     * An auxiliary function that recursively generates the root-to-leaf 
     * subpaths in the tree rooted at the specified node
     * @param node the root of a subtree
     * @param subpath a string representation of a subpath 
     * @param paths an vector of strings representing root to leaf
     * paths in the tree rooted at the specified node
     */ 
    
    //Implement this method
}

/* END: Augmented Private Auxiliary Functions */   
   