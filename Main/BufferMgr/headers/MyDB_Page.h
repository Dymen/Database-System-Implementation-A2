

/****************************************************
** COPYRIGHT 2016, Chris Jermaine, Rice University **
**                                                 **
** The MyDB Database System, COMP 530              **
** Note that this file contains SOLUTION CODE for  **
** A1.  You should not be looking at this file     **
** unless you have completed A1!                   **
****************************************************/

#ifndef PAGE_H
#define PAGE_H

#include <memory>
#include "../../Catalog/headers/MyDB_Table.h"
#include <string>

// create a smart pointer for pages
using namespace std;
class MyDB_Page;
typedef shared_ptr <MyDB_Page> MyDB_PagePtr;

// forward deifnition to handle circular dependencies
class MyDB_BufferManager;

class MyDB_Page {

public:

	// access the raw bytes in this page
	void *getBytes ();

	// let the page know that we have written to the bytes
	void wroteBytes ();

	// there are no more references to this page when this is called...
	// if the page owns any RAM, it should give it back to the parent
	// buffer manager
	~MyDB_Page ();

	// sets up the page... takes as input the relation that the page is
	// bound to (this should be a nullptr if this is a temp page) and
	// the position of the page in the file
	MyDB_Page (MyDB_TablePtr myTable, size_t i, MyDB_BufferManager &parent);

	// sets the bytes in the page
	void setBytes (void *bytes, size_t numBytes);

	// decrements the ref count
	void decRefCount ();

	// increments the ref cont
	void incRefCount ();

private:

	friend class MyDB_BufferManager;
	friend class PageComp;
	friend class CheckLRU;

	// a pointer to the raw bytes
	void *bytes;

	// the number of raw bytes available
	size_t numBytes;

	// tells us if this page needs to be written back
	bool isDirty;	

	// pointer to the parent buffer manager
	MyDB_BufferManager& parent;		

	// this is the relation that the page belongs to; is a nullptr if
	// this is a temp page that does not belong to any relation
	MyDB_TablePtr myTable;

	// this is the position of the page in the relation
	size_t pos;

	// this is the last time that the page had been accessed
	long timeTick;

	// the number of references
	int refCount;
};

#endif

