# include "rdb_main.hpp"

HeapMgr Mgr;

HeapMgr::HeapMgr() {
    clear();
}

void* HeapMgr::insertAddress(void* address) {
    if (!address)
        return NULL;
    push_back(address);
    return address;
}

void HeapMgr::clearHeap() {
    MgrIt it = begin();
    while (it != end()) {
        free(*it);
        it++;
    }
    clear();
}