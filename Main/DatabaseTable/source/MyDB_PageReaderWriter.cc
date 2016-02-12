
#ifndef PAGE_RW_C
#define PAGE_RW_C

#include "../headers/MyDB_PageReaderWriter.h"

MyDB_PageReaderWriter::MyDB_PageReaderWriter(){
	_pageSize = 0;
	_pageHandle = nullptr;
	_recordPtr = nullptr;
}

//'newPage' variable is set to TRUE only when loading data from file
MyDB_PageReaderWriter::MyDB_PageReaderWriter(bool newPage, size_t pageSize, MyDB_PageHandle pageHandle, MyDB_RecordPtr recordPtr) {
	_pageSize = pageSize;
	_pageHandle = pageHandle;
	_recordPtr = recordPtr;
	if (newPage) {
		//Initialize header saving page information
		MyDB_PageInfo initInfo(sizeof(MyDB_PageInfo));
		char *bytes = (char*)pageHandle->getBytes();
		memcpy(bytes, &initInfo, sizeof(MyDB_PageInfo));
	}
}

MyDB_PageReaderWriter::~MyDB_PageReaderWriter(){
	_pageHandle = nullptr;
	_recordPtr = nullptr;
}

//Refresh data saved in the PageReaderWriter
void MyDB_PageReaderWriter :: reload(bool newPage, size_t pageSize, MyDB_PageHandle pageHandle, MyDB_RecordPtr recordPtr){
	_pageSize = pageSize;
	_pageHandle = pageHandle;
	_recordPtr = recordPtr;
	if (newPage) {
		MyDB_PageInfo initInfo(sizeof(MyDB_PageInfo));
		char *bytes = (char*)pageHandle->getBytes();
		memcpy(bytes, &initInfo, sizeof(MyDB_PageInfo));
	}
}

//Clear only needs to modify the data saved in the header of pageInfo
void MyDB_PageReaderWriter :: clear () {
	char* bytes = (char*)_pageHandle->getBytes();
	MyDB_PageInfo *temp = (MyDB_PageInfo *) bytes;
	temp->_lastByte = sizeof(MyDB_PageInfo);
	_pageHandle->wroteBytes();
}

MyDB_PageType MyDB_PageReaderWriter :: getType () {
	return MyDB_PageType :: RegularPage;
}

MyDB_RecordIteratorPtr MyDB_PageReaderWriter :: getIterator (MyDB_RecordPtr recordPtr) {
	MyDB_PageRecIterator* it = new MyDB_PageRecIterator(recordPtr, _pageHandle, _pageSize);
	shared_ptr<MyDB_RecordIterator> ptr((MyDB_RecordIterator*)it);
	return ptr;
}

void MyDB_PageReaderWriter :: setType (MyDB_PageType toMe) {
	_pageType = toMe;
}

bool MyDB_PageReaderWriter :: append (MyDB_RecordPtr recordPtr) {
	char* bytes = (char*)_pageHandle->getBytes();
	MyDB_PageInfo *temp = (MyDB_PageInfo *) bytes;
	if (recordPtr->getBinarySize() + temp->_lastByte > _pageSize)
		return false;
	recordPtr->toBinary(bytes+temp->_lastByte);
	temp->_lastByte += recordPtr->getBinarySize();
	memcpy(bytes, temp, sizeof(MyDB_PageInfo));
	_pageHandle->wroteBytes();
	return true;
}

#endif
