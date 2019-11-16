/*!
 * created by  Bisrat Asefaw
 * on November 12 , 2019
 * CSS 342
 *
 * SKIPLISt test Class that contains three methods to test the working correctly of
 * the skiplist constructor and distructor. this class also tests the working of the skiplist
 * methods such as the ADD method that adds a node to the skiplist , REMOVE that removes node from the
 *  skiplist and contains that checks if there exists a node with the provided value
 */

#include <iostream>
#include <cassert>
#include "skiplist.h"

/*!
 * test fror ADD randomly generated integers
 */
void test4() {

    SkipList s(5);
    for (int i = 0; i < 20; ++i) {
        int number = rand() % 100;
        s.Add(number);
        cout << "After adding " << number << endl;
        cout << s << endl;
    }

}

/*!
 * test for SkipList contains method
 */
void testContains() {
    SkipList skip(4);
    skip.Add(11);
    skip.Add(14);
    skip.Add(1);
    skip.Add(19);
    skip.Add(5);

    assert(!skip.Add(19));
    assert(skip.Contains(19));
    assert(skip.Remove(19));
    assert(!skip.Contains(19));
    assert(skip.Add(19));

    assert(!skip.Add(1));
    assert(skip.Contains(1));
    assert(skip.Remove(1));
    assert(!skip.Contains(1));
    assert(skip.Add(1));


    assert(!skip.Contains(21));
    assert(!skip.Contains(16));
}

/*!
 * test for SkipList remove method
 */
void testRemove() {
    SkipList test(6);
    test.Add(11);
    test.Add(14);
    test.Add(1);
    test.Add(30);
    test.Add(100);
    test.Add(200);
    test.Add(24);

    assert(test.Contains(200));
    assert(test.Remove(200));
    assert(!test.Contains(200));
    assert(test.Remove(1));
    assert(!test.Contains(1));
    assert(!test.Remove(90));
    assert(!test.Remove(10));

    assert(test.Contains(11));
    assert(test.Contains(100));
    assert(test.Remove(11));
    assert(test.Remove(100));
    assert(!test.Contains(21));
    assert(!test.Contains(16));
    assert(!test.Remove(21));
    assert(!test.Remove(16));


}

/*!
 * excutable part of the program main
 * @return
 */
int main() {

    testRemove();
    testContains();
    test4();
    cout<<endl<<"Passed all test cases";
    return 0;
}