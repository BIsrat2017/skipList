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

#include <ostream>

#ifndef ASSIGNMENT4_SKIPLIST_H
#define ASSIGNMENT4_SKIPLIST_H
using namespace std;

class SkipList {

public:
    //static  int counter;
   // friend function is used to display all the elements of SkipList
    friend ostream &operator<<(ostream &os, const SkipList &list);

    //default skiplist. has depth of 1, just one doubly-liked list
    explicit SkipList(int depth = 1);

    // destructor
    virtual ~SkipList();

    //return true if successfully added, with no deuplicates
    bool Add(int data);

    //bool true if successfully removed
    bool Remove(int data);

    //return true if found in skipList
    bool Contains(int data);




private:
/*!
 *   SNode class that used to creat node in SkipLis class
 *   this class contains constructor to instantiate the instance variable of the node DATA
 *   and pointers to point to the next, previos, uplevel and downlevel nodes
 */
    class SNode {

    public:

        // friend class skiplist.;
        //Snode stores int data
        explicit SNode(int data);

        //data for SNode
        int data;
        //link to the next SNode
        SNode *next;
        //Link to the prev SNode
        SNode *prev;
        //link to up one level
        SNode *upLevel;
        //Link down one level
        SNode *downlevel;
    };

    // depth of skiplist. , levels are 0 to depth-1
    int depth;


    // array of depth SNode* objects as frontGuards Linking levels
    // if depth=2, we'd have frontGuards[0] and frontGuards[1]
    SNode **frontGuards;

    //array of depth SNode* objects as rearGuards Linking levels
    SNode **rearGuards;

    //given a SNode , place it before given next node
    void addBefore(SNode *newNode, SNode *nextNode);

    //return true 50% chance of being at higher level
    // each node has a 50% chance of being at higher level
    bool alsoHigher() const;

};


#endif //ASSIGNMENT4_SKIPLIST_H
