
#ifndef PAGE_RW_C
#define PAGE_RW_C

#include "../headers/MyDB_PageReaderWriter.h"
#include "../../Catalog/headers/MyDB_PageType.h"

void MyDB_PageReaderWriter :: clear () {
}

MyDB_PageType MyDB_PageReaderWriter :: getType () {
	return MyDB_PageType :: RegularPage;
}

MyDB_RecordIteratorPtr MyDB_PageReaderWriter :: getIterator (MyDB_RecordPtr) {
	return nullptr;
}

void MyDB_PageReaderWriter :: setType (MyDB_PageType) {
}

bool MyDB_PageReaderWriter :: append (MyDB_RecordPtr) {
	return true;
}

#endif
