#ifndef PAIRING_HEAP_
#define PAIRING_HEAP_

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "graph.hh"

using namespace std;

struct HeapNode {

    // int key;
    Node *graph_node;

    HeapNode *leftChild;
    HeapNode *nextSibling;

    HeapNode():
        graph_node(NULL), leftChild(NULL), nextSibling(NULL) {}

    HeapNode(Node *graph_node_, HeapNode *leftChild_, HeapNode *nextSibling_):
        graph_node(graph_node_), leftChild(leftChild_), nextSibling(nextSibling_) {}

    void addChild(HeapNode *node) {
        if(leftChild == NULL)
            leftChild = node;
        else {
            node->nextSibling = leftChild;
            leftChild = node;
        }
    }
};

bool Empty(HeapNode *node) {
    return (node == NULL);
}

HeapNode *Merge(HeapNode *A, HeapNode *B) {
    if(A == NULL) return B;
    if(B == NULL) return A;
    if(A->graph_node->d < B->graph_node->d) {
        A->addChild(B);
        return A;
    }
    else {
        B->addChild(A);
        return B;
    }

    return NULL; // Unreachable
}

Node *Top(HeapNode *node) {
    return node->graph_node;
}

HeapNode *Push(HeapNode *node, Node *graph_node_) {
    return Merge(node, new HeapNode(graph_node_, NULL, NULL));
}

HeapNode *TwoPassMerge(HeapNode *node) {
    if(node == NULL || node->nextSibling == NULL)
        return node;
    else {
        HeapNode *A, *B, *newNode;
        A = node;
        B = node->nextSibling;
        newNode = node->nextSibling->nextSibling;

        A->nextSibling = NULL;
        B->nextSibling = NULL;

        return Merge(Merge(A, B), TwoPassMerge(newNode));
    }

    return NULL; // Unreachable
}

HeapNode *Pop(HeapNode *node) {
    return TwoPassMerge(node->leftChild);
}

struct PairingHeap {
    HeapNode *root;

    PairingHeap():
        root(NULL) {}

    bool empty(void) {
        return ::Empty(root);
    }

    Node *top(void) {
        return ::Top(root);
    }

    void push(Node *graph_node_) {
        root = ::Push(root, graph_node_);
    }

    void pop(void) {
        root = ::Pop(root);
    }

    void join(PairingHeap other) {
        root = ::Merge(root, other.root);
    }
};

#endif
