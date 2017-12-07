/*
 * Gwendolyn Brunot
 * heap.cpp - heap class implementation file
 */

#include "Heap.hpp"
#include <vector>
#include <iostream>

using namespace std;

// add an element to the tree
void Heap::enqueue(HNode* n) {
    // add a new leaf
    if(tree.size()==0) {
        tree.push_back(0);
    }
    
    position = tree.size()-1;
        
    // store the new element in the vacant spot
    tree[position] = n;
    
    // fix the tree
    fix_up(position);
    
    // update position
    position++;
        
    // update the count variable
    count++;
}

// remove the smallest element
HNode* Heap::dequeue() {
    // store the current root node (smallest element)
    HNode* smallest = tree[1];
    
    // remove the last element
    int lastIndex = tree.size() - 1;
    HNode* last = tree.back();
    tree.pop_back();
    
    if(lastIndex > 1) {
        tree[1] = last;
        fix_down(1);
    }
    // update count variable
    --count;
    return smallest;
}

// fix the heap from a specific index up
void Heap::fix_up(const int& index) {
    int curIndex = index;
    int parent = (index/2);
    
    if(index == 1) {
        return;
    }
    
    else if(tree[index]->weight < tree[parent]->weight) {
        HNode* temp = tree[parent];
        tree[parent] = tree[index];
        tree[index] = temp;
        fix_up(parent);
    }
}

// fix the tree after replacing the smallest element
void Heap::fix_down(const int& pos) {
    int index = pos;
    int left = 2*index+2;
    int right = 2*index+1;
    
    if(tree[index]->left && tree[index]->right) {
        if(tree[index]->left->weight > tree[index]->right->weight) {
            if(tree[index]->weight < tree[index]->right->weight) {
                HNode* temp = tree[index];
                tree[index] = tree[right];
                tree[right] = temp;
                fix_down(right);
            }
            else if(tree[index]->left->weight < tree[index]->right->weight) {
                if(tree[index]->weight < tree[index]->left->weight) {
                    HNode* temp = tree[index];
                    tree[index] = tree[left];
                    tree[left] = temp;
                    fix_down(left);
                }
            }
        }
    }
    
    else if(!tree[index]->right && tree[index]->left) {
        if(tree[index]->weight < tree[index]->left->weight) {
            HNode* temp = tree[index];
            tree[index] = tree[right];
            tree[right] = temp;
        }
    }
}

void Heap::clear() {
    tree.clear();
}
