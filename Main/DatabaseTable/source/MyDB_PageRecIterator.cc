//
// Created by Dan Ye on 2/7/16.
//
#ifndef A2_MYDB_PAGERECITERATOR_CC
#define A2_MYDB_PAGERECITERATOR_CC

#include "../headers/MyDB_PageRecIterator.h"

using namespace std;

MyDB_PageRecIterator::MyDB_PageRecIterator(MyDB_RecordPtr recordPtr, MyDB_PageHandle pageHandle, size_t pageSize) {
    _curOffset = sizeof(MyDB_PageInfo);
    _pageHandle = pageHandle;
    _pageSize = pageSize;
    _recordPtr = recordPtr;
}

MyDB_PageRecIterator::~MyDB_PageRecIterator(){
    _pageHandle = nullptr;
    _recordPtr = nullptr;
}

void MyDB_PageRecIterator::getNext() {
    char* bytes = (char*)_pageHandle->getBytes();
    MyDB_PageInfo *temp = (MyDB_PageInfo *) bytes;

    if (_curOffset >= temp->_lastByte)
        return;
    _recordPtr->fromBinary(bytes + _curOffset);
    _curOffset += _recordPtr->getBinarySize();
}

bool MyDB_PageRecIterator::hasNext() {
    char* bytes = (char*)_pageHandle->getBytes();
    MyDB_PageInfo *temp = (MyDB_PageInfo *) bytes;

    if (_curOffset >= temp->_lastByte)
        return false;
    return true;
}

#endif //A2_MYDB_PAGERECITERATOR_CC