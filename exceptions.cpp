#include <iostream>
#include "exceptions.h"

using std::cout;
using std::endl;
void OutOfRange::what() const {
    switch (m_flag) {
    case(1):
            cout << "Error: empty array, no elements to pop." << endl;
            break;
    case(2):
            cout << "Position " << m_index << " is out of boundary. Length of linked list is " << m_len << "." << endl;
            break;
     default:
            cout << "Unknown exception." << endl;
    }
    
}