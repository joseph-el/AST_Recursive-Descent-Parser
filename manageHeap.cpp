#include "manageHeap.hpp"

HeapMgr Mgr;

HeapMgr::HeapMgr() {
    clear();
}

bool HeapMgr::insertAddress(void* address) {
    if (!address)
        return false;
    push_back(address);
    return true;
}

void HeapMgr::clearHeap() {
    MgrIt it = begin();
    while (it != end()) {
        delete *it;
        it++;
    }
    clear();
}