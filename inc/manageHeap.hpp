#ifndef __HEAP_H__
#define __HEAP_H__

#include <iostream>
#include <iterator>
#include <deque>
#include <list>

using namespace std;

struct HeapMgr : public deque<void *> {
    public:
        typedef HeapMgr::iterator MgrIt;
        HeapMgr();
        void* insertAddress(void *);
        void _clearHeap();
};

extern HeapMgr Mgr;

#define clearHeap Mgr._clearHeap()
#define gc_insert(address) (Mgr.insertAddress((address)))

#endif