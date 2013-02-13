/*
 * lists.h --
 *
 * algorithms related to the calculation of the words
 *
 * Tue, Feb 12, 2013  3:57:22 PM: initial release by Todd Xue
 */

#ifndef _lists_h
#define _lists_h

/**
 * some lists operations
 */
template <typename T> struct list {
    list<T>* next;
    T data;
};

template <typename T> struct head {
    list<T>* next;
};

template <typename T> struct free_list {
    list<T>* nodes;
    head<T> head;

    free_list(int n) { 
        nodes = new list<T>[n];
        head.next = nodes[0];
        for (int i = 0; i < n-1; ++i)
            nodes[i].next = &nodes[i+1];
        nodes[n-1].next = 0;
    }
    ~free_list()     { 
        delete[] nodes; 
    }

    list<T>* alloc() {
        list<T>* node = head.next;
        if (head.next)
            head.next = head.next->next;
        return node;
    }

    void free(list<T>* node) {
        node->next = head.next;
        head.next = node;
    }
};

#endif
