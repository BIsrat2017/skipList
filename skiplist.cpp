/*!
 * created by  Bisrat Asefaw
 * on November 12 , 2019
 * CSS 342
 *
 * SKIPLISt class that contains three methods and constructor and distructor.
 *  contructor that creates skip list and destructor
 *  ADD method that adds a node to the skiplist , REMOVE that removes node from the
 *  skiplist and contains that checks if there exists a node with the provided value
 */

#include <random>
#include <cassert>
#include <iostream>
#include <limits>
#include <cstdlib>
#include "skiplist.h"

/*!
 * conatructor of the skiplist that creates the frontGuard and rearGuard of the skip list and
 * puts a INT_MAX and INT_MIN in thier nide
 * @param depth equals the depth-1 LEVEl of the skiplist
 */
SkipList::SkipList(int depth) {
    this->depth = depth;
    this->frontGuards = new SNode *[depth];
    this->rearGuards = new SNode *[depth];
    for (int i = 0; i < depth; i++) {

        frontGuards[i] = new SNode(numeric_limits<int>::min());
        rearGuards[i] = new SNode(numeric_limits<int>::max());
        frontGuards[i]->next = rearGuards[i];
        rearGuards[i]->prev = frontGuards[i];
    }
    int j = 1;
    for (int i = 0; i < depth - 1; i++) {
        frontGuards[i]->upLevel = frontGuards[j];
        frontGuards[j]->downlevel = frontGuards[i];
        assert (frontGuards[i]->upLevel == frontGuards[j] && frontGuards[j]->downlevel == frontGuards[i]);
        rearGuards[i]->upLevel = rearGuards[j];
        rearGuards[j]->downlevel = rearGuards[i];
        assert (rearGuards[i]->upLevel == rearGuards[j] && rearGuards[j]->downlevel == rearGuards[i]);
        j++;
    }


}

/*!
 * distructor for skiplist class
 * deletes all node in each level and the front and rear guard 
 */
SkipList::~SkipList() {
    SNode *todelete= nullptr;
    for (int i = 0; i < depth; i++) {
         todelete= frontGuards[i];
        while (todelete != nullptr) {
            SNode *next = todelete->next;
            delete todelete;
            todelete = next;

        }
    }
    delete todelete;
    todelete= nullptr;
    delete[] frontGuards;
    delete[] rearGuards;
    frontGuards = nullptr;
    rearGuards = nullptr;
}

/*!
 * Add method that adds a node in a skiplist tree
 * @param data to be added to the skiplist
 * @return  true if the node is sucesfully added to the skip list and false otherwise
 */
bool SkipList::Add(int data) {

    SNode *nextNode = frontGuards[0]->next;
    while (nextNode->next != nullptr && nextNode->data < data) {
        nextNode = nextNode->next;
    }
    if (nextNode->data == data) {
        cout << "Duplicates are Not Allowed " << data << endl;
        return false;
    }
    SNode *newNode = new SNode(data);
    addBefore(newNode, nextNode);
    int i = 0;
    while (alsoHigher() && i < depth) {
        SNode *current;
        auto *newUpper = new SNode(data);
        newUpper->downlevel = newNode;
        newNode->upLevel = newUpper;
        current = newNode->prev;
        while (current->prev != nullptr && current->upLevel == nullptr) {
            current = current->prev;
        }
        if (current->upLevel != nullptr) {
            current = current->upLevel;
        } else {
            return false;
        }
        nextNode = current;
        while (nextNode->next != nullptr && nextNode->data < data) {
            nextNode = nextNode->next;
        }
        addBefore(newUpper, nextNode);
        newNode = newUpper;
        ++i;
    }
    return true;
}

/*!
 * remove method that removes a node from a skiplist tree
 * @param data the input data to be removed
 * @return true is removed and false if not removed
 */
bool SkipList::Remove(int data) {
    if (!Contains(data)) {
        return false;
    }
    SNode *down = nullptr;
    SNode *current = frontGuards[depth-1];
    while (current != nullptr) {
        while (current->next->data < data) {
            current = current->next;
        }
        if (current->next->data == data) {
            current = current->next;
            while (current != nullptr) {
                if (current->downlevel != nullptr) {
                    down = current->downlevel;
                }

                current->prev->next = current->next;
                current->next->prev =  current->prev;
                delete current;
                current = down;
                down = nullptr;
            }
        }
        else {
            current = current->downlevel;
        }

    }

    return true;

}

/*!
 * contains method that checks if the input value is in the skiplist tree
 * @param value input value to be checked
 * @return true is there exists a value that is equal to thr input value parameter and false otherwise
 */
bool SkipList::Contains(int value) {

    SNode *current = frontGuards[depth - 1];
    while (current != nullptr) {
        while (current->next->data < value) {
            current = current->next;
        }
        if (current->next->data == value) {
            return true;
        } else {
            current = current->downlevel;
        }

    }
    return false;
}

//! method that flips a coin each node has a 50% chance of being at higher level
//! \return true 50% chance of being at higher level or false
bool SkipList::alsoHigher() const {
    return rand() % 2 == 1;
}

/*!
 * Helper method addBefore given a SNode , place it before given next node
 * @param newNode new Node to insert
 * @param nextNode node next to the
 */
void SkipList::addBefore(SNode *newNode, SNode *nextNode) {
    assert(newNode != nullptr && nextNode != nullptr &&
           newNode->data < nextNode->data);
    SNode *temp;
    temp = nextNode->prev;
    newNode->next = nextNode;
    temp->next = newNode;
    nextNode->prev = newNode;
    newNode->prev = temp;
    assert (newNode->next == nextNode && nextNode->prev == newNode);
    assert (newNode->prev != nullptr && newNode->prev->data < newNode->data);
}

/*!
 * overloaded << operator of the class skip list
 * @param os the ostream object reference
 * @param list the skip list
 * @return string representation of the object SkipLIst
 */
ostream &operator<<(ostream &os, const SkipList &list) {

    int level = list.depth - 1;
    for (int i = level; i >= 0; i--) {
        SkipList::SNode *temp = list.frontGuards[i];
        os << "Level: " << i << " -- ";
        while (temp != nullptr) {
            os << temp->data << ", ";
            temp = temp->next;
        }
        os << endl;
    }
    return os;
}



/*!
 * constructor of the SNode node of the skiplist
 * @param data integer value of the node
 */
SkipList::SNode::SNode(int data) {

    this->data = data;
    this->next = nullptr;
    this->downlevel = nullptr;
    this->prev = nullptr;
    this->upLevel = nullptr;

}




