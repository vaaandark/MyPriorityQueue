#ifndef _FIBONACCIHEAP_H
#define _FIBONACCIHEAP_H

#include <cstddef>
#define MAXDEGREE 16

template <typename KeyType>
class FibonacciHeap {

private:
    struct HeapNode {
        KeyType key;
        HeapNode *pre;
        HeapNode *next;
        HeapNode *child;
        size_t degree;
    };
    HeapNode* min = nullptr;
    size_t heap_size = 0;

    HeapNode *newNode(KeyType key);
    void deleteNodeFromList(HeapNode *p);
    void catNodes(HeapNode *p1, HeapNode *p2);
    HeapNode *beSon(HeapNode *p1, HeapNode *p2);
    void consolidate();
    
public:

    ~FibonacciHeap() {
        while (heap_size > 0) {
            this->pop();
        }
    }

    KeyType top() { return min->key; }

    bool empty() { return heap_size == 0; }

    size_t size() { return heap_size; }

    void push(KeyType key) {
        if (!this->min) {
            this->min = newNode(key);
        }
        else {
            HeapNode *p = newNode(key);
            catNodes(this->min, p);
            if (this->min->key > key) {
                this->min = p;
            }
        }
        this->heap_size++;
    }
    void pop() {
        if (!this->min) {
            return;
        }
        HeapNode *del = this->min;
        if (this->min->next == this->min) {
            this->min = this->min->child;
        } else {
            this->min = this->min->next;
            deleteNodeFromList(del);
            catNodes(del->child, this->min);
        }
        delete del;
        del = nullptr;
        this->consolidate();
        this->heap_size--;
    }
    void clear();



};

template <typename KeyType>
typename FibonacciHeap<KeyType>::HeapNode *FibonacciHeap<KeyType>::newNode(KeyType key) {
    HeapNode *p = new HeapNode;
    p->child = nullptr;
    p->next = p->pre = p;
    p->degree = 0;
    p->key = key;
    return p;
}

template <typename KeyType>
void FibonacciHeap<KeyType>::deleteNodeFromList(HeapNode *p) {
    if (!p) {
        return;
    }
    p->next->pre = p->pre;
    p->pre->next = p->next;
}

template <typename KeyType>
void FibonacciHeap<KeyType>::catNodes(HeapNode *p1, HeapNode *p2) {
    if (!p1 || !p2) {
        return;
    }
    p1->pre->next = p2;
    p2->pre->next = p1;
    HeapNode *tmp = p1->pre;
    p1->pre = p2->pre;
    p2->pre = tmp;
}

template <typename KeyType>
typename FibonacciHeap<KeyType>::HeapNode *FibonacciHeap<KeyType>::beSon(HeapNode *p1, HeapNode *p2) {
    if (!p1) {
        return p2;
    }
    if (!p2) {
        return p1;
    }
    if (p1->key > p2->key) {
        HeapNode *tmp = p1;
        p1 = p2;
        p2 = tmp;
    }
    p2->pre = p2->next = p2;
    deleteNodeFromList(p2);
    if (!p1->child) {
        p1->child = p2;
    } else {
        catNodes(p1->child, p2);
    }
    p1->degree++;
    return p1;

}

template <typename KeyType>
void FibonacciHeap<KeyType>::consolidate() {
    if (!this->min || this->min == this->min->next) {
        return;
    }
    HeapNode *i = this->min;
    HeapNode *addr[MAXDEGREE] = {nullptr};
    do {
        HeapNode *next = i->next;
        int d = i->degree;
        while (addr[d]) {
            i = beSon(addr[d], i);
            addr[d] = nullptr;
            d++;
        }
        addr[d] = i;
        i = next;
    } while (i != this->min);

    this->min = nullptr;

    int k;
    for (k = 0; k < MAXDEGREE; k++) {
        if (addr[k]) {
            addr[k]->pre = addr[k]->next = addr[k];
            if (!this->min) {
                this->min = addr[k];
            }
            else {
                catNodes(this->min, addr[k]);
                if (addr[k]->key < this->min->key) {
                    this->min = addr[k];
                }
            }
        }
    }

}

#endif /* _FIBONACCIHEAP_H */