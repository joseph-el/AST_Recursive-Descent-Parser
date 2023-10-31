#ifndef __HEAP_H__
#define __HEAP_H__

#include"token.hpp"

struct HeapMgr : public deque<void *> {
    public:
        typedef HeapMgr::iterator MgrIt;
        HeapMgr();
        bool insertAddress(void *);
        void clearHeap();
};

extern HeapMgr Mgr;

#endif