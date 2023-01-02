//
// Created by Omer Bahat on 27/12/2022.
//

#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

#include <stdio.h>
#include <iostream>
#include <assert.h>

template<class T>
class Queue
{
public:
    class Node
    {
    public:
        T m_value;
        Node *m_nextNode;
        Node *m_previousNode;

        explicit Node(const T value, Node *nextNode, Node *previousNode);
        Node(const T value);
        Node(const Node &toClone);
    };
    class Iterator;
    Iterator begin();
    Iterator end();
    class ConstIterator;
    ConstIterator begin() const;
    ConstIterator end() const;

    class EmptyQueue{};

    Queue();
    ~Queue();
    Queue(const Queue &toClone);
    Queue<T> &operator=(const Queue &toAssign);
    void pushBack(const T &toPush);
    T &front() const;
    void popFront();
    int size() const;

private:
    int m_size;
    Node *m_head;
    Node *m_tail;
    static const int ONLY_BLANKS_SIZE = 2;
};


//
//start of Node definition section
//
template<class T>
Queue<T>::Node::Node(const T value, Queue::Node *nextNode, Queue::Node *previousNode)
{
    try
    {
        this->m_value = T(value);
    }
    catch(const std::bad_alloc &e){
//        delete this;
        throw std::bad_alloc();
    }
    this->m_nextNode = nextNode;
    this->m_previousNode = previousNode;
}
template<class T>
Queue<T>::Node::Node(const T value)
{
    try
    {
        this->m_value = T(value);
    }
    catch (const std::bad_alloc &e)
    {
        delete *this;
        throw;
    }
    m_nextNode = nullptr;
    m_previousNode = nullptr;
}
template<class T>
Queue<T>::Node::Node(const Node &toClone)
{
    try
    {
        this->m_value = T(toClone.m_value);
    }
    catch (const std::bad_alloc &e)
    {
        delete *this;
        throw;
    }
    this->m_previousNode = toClone->m_previousNode;
    this->m_nextNode = toClone->m_nextNode;
}
//
//end of Node definition section
//

//
//start of Iterator & constIterator definition section
//
template<class T>
class Queue<T>::Iterator
{
private:
    friend class Queue<T>;
    Node * m_currentNode;
    Queue<T> *m_queue;
    Iterator(Node *node, Queue<T> *queue);

public:
    T &operator*();
    Iterator& operator++();
    bool operator!=(const Iterator &iterator);
    Iterator(const Iterator&) = default;
    Iterator &operator=(const Iterator &iterator) = default;
    class InvalidOperation{};
};
template<class T>
class Queue<T>::ConstIterator
{
private:
    friend class Queue<T>;
    const Node *m_currentNode;
    const Queue<T> *m_queue;
    ConstIterator(const Node *node, const Queue<T> *queue);

public:
    const T &operator*() const;
    ConstIterator &operator++();
    bool operator!=(const ConstIterator &constIterator) const;
    ConstIterator(const ConstIterator&) = default;
    ConstIterator &operator=(const ConstIterator &constIterator)= default;
    class InvalidOperation{};
};

template<class T>
Queue<T>::Iterator::Iterator(Node *node, Queue<T> *queue): m_currentNode(node), m_queue(queue)
{}
template<class T>
Queue<T>::ConstIterator::ConstIterator(const Node *node, const Queue<T> *queue): m_currentNode(node), m_queue(queue)
{}

template<class T>
T& Queue<T>::Iterator::operator*()
{
    if(this->m_currentNode== nullptr)
    {
        throw Queue<T>::Iterator::InvalidOperation();
    }
    else
    {
        return this->m_currentNode->m_value;
    }
}
template<class T>
const T& Queue<T>::ConstIterator::operator*() const
{
    if(this->m_currentNode== nullptr)
    {
        throw Queue<T>::ConstIterator::InvalidOperation();
    }
    else
    {
        return this->m_currentNode->m_value;
    }
}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if(this->m_currentNode->m_previousNode==nullptr)
    {
        throw Queue<T>::Iterator::InvalidOperation();
    }
    else
    {
        this->m_currentNode = this->m_currentNode->m_previousNode;
        return *this;
    }
}
template<class T>
typename Queue<T>::ConstIterator &Queue<T>::ConstIterator::operator++()
{
    if(this->m_currentNode->m_previousNode==nullptr)
    {
        throw Queue<T>::ConstIterator::InvalidOperation();
    }
    else
    {
        this->m_currentNode = this->m_currentNode->m_previousNode;
        return *this;
    }
}

template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator &iterator)
{
    return this->m_currentNode!=iterator.m_currentNode;
}
template<class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator &constIterator) const
{
    return this->m_currentNode!=constIterator.m_currentNode;
}
//
//end of Iterator & constIterator definition section
//

//
//start of begin&end definition
//
template<class T>
typename Queue<T>::Iterator Queue<T>::begin()
{
    return Iterator(this->m_head->m_previousNode, this);

}
template<class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const
{
    return ConstIterator(this->m_head->m_previousNode, this);
}

template<class T>
typename Queue<T>::Iterator Queue<T>::end()
{
    return Iterator(this->m_tail, this);
}
template<class T>
typename Queue<T>::ConstIterator Queue<T>::end() const
{
    return ConstIterator(this->m_tail, this);
}
//
//end of begin&end definition
//

//
//start of queue definitions
//
template<class T>
Queue<T>::Queue()
{
    Node *tempHead = nullptr, *tempTail = nullptr;
    try
    {
        tempHead = new Node(T(), nullptr, nullptr);
        tempTail = new Node(T(), nullptr, nullptr);
    }
    catch(const std::bad_alloc &e)
    {
        delete tempHead;
        delete tempTail;
        throw;
    }
    tempTail->m_nextNode = tempHead;
    tempHead->m_previousNode = tempTail;
    this->m_head =tempHead;
    this->m_tail = tempTail;
    this->m_size = ONLY_BLANKS_SIZE;
}
template<class T>
Queue<T>::~Queue()
{
    Node * toDelete = this->m_tail;
    while(toDelete!=this->m_head)
    {
        this->m_tail = this->m_tail->m_nextNode;
        delete toDelete;
        toDelete = m_tail;
    }
    delete toDelete;
}
template<class T>
Queue<T>::Queue(const Queue &toClone):m_size(2)
{
    m_tail =new Node(T(), nullptr, nullptr);
    m_head =new Node(T(), nullptr, nullptr);
    m_tail->m_nextNode = m_head;
    m_head->m_previousNode = m_tail;
    try{
        for(const T& toPush : toClone)
        {
            this->pushBack(toPush);
        }
    }
    catch(const std::bad_alloc &e)
    {
        delete this;
        throw;
    }
}

template<class T>
Queue<T> &Queue<T>::operator=(const Queue<T> &toAssign)
{
    if(this==&toAssign)
    {
        return *this;
    }
    try
    {
        Queue<T> *tempQueue = nullptr;
        tempQueue = new Queue<T>();
//        tempQueue->m_head = new Node(T(), nullptr, nullptr);
//        tempQueue->m_tail = new Node(T(), nullptr, nullptr);
//        tempQueue->m_head->m_previousNode = tempQueue->m_tail;
//        tempQueue->m_tail->m_nextNode = tempQueue->m_head;
//        tempQueue->m_size = ONLY_BLANKS_SIZE;
        for(const T& toPush : toAssign)
        {
            tempQueue->pushBack(toPush);
        }
        Node *toDelete = m_tail->m_nextNode;
        while(toDelete!=m_head) {
            m_tail->m_nextNode = m_tail->m_nextNode->m_nextNode;
            delete toDelete;
            toDelete = m_tail->m_nextNode;
        }
        m_head = tempQueue->m_head;
        m_tail = tempQueue->m_tail;
        m_size = tempQueue->m_size;

    }
    catch (const std::bad_alloc &e)
    {
//        delete this;
        throw;
    }

    return *this;
}

template<class T>
void Queue<T>::pushBack(const T &toPush)
{
    Node *tempNode= nullptr;
    try
    {
        tempNode = new Node(toPush , nullptr, nullptr);
    }
    catch (const std::bad_alloc &e)
    {
//        delete this;
        throw std::bad_alloc();
    }
    tempNode->m_nextNode = m_tail->m_nextNode;
    tempNode->m_previousNode = m_tail;
    m_tail->m_nextNode = tempNode;
    tempNode->m_nextNode->m_previousNode = tempNode;
    ++m_size;
}

template<class T>
T &Queue<T>::front() const
{
    if(m_size==ONLY_BLANKS_SIZE)
    {
        throw Queue<T>::EmptyQueue();
    }
    return m_head->m_previousNode->m_value;
}

template<class T>
void Queue<T>::popFront()
{
    if(m_size==ONLY_BLANKS_SIZE)
    {
        throw Queue<T>::EmptyQueue();
    }
    else
    {
        Node *toDelete = m_head->m_previousNode;
        toDelete->m_previousNode->m_nextNode = m_head;
        m_head->m_previousNode = toDelete->m_previousNode;
        delete toDelete;
        --m_size;
    }
}

template<class T>
int Queue<T>::size() const
{
    return m_size-ONLY_BLANKS_SIZE;
}

template<class T, class FilterFlag>
Queue<T> filter(const Queue<T> &queue, FilterFlag filterFlag)
{
    try
    {
        //main problem to be expected is bad alloc, all the rest is pretty standard
        Queue<T> tempQueue;
        for(const T& iteratedValue : queue)
        {
            if(filterFlag(iteratedValue))
            {
                tempQueue.pushBack(iteratedValue);
            }
        }
        return tempQueue;
    }
    catch (const std::bad_alloc &e)
    {
        throw std::bad_alloc();
    }
}

template<class T, class TransformOperation>
void transform(Queue<T> &queueToTransform, TransformOperation &transformOperation)
{
    //instead of a for loop, we know we have to run the transform operation on each node in queue
    //and there are exactly size() elements in queue
    //we'll run size() times and each time do the transform operation on node in front of the queue and then push it to the back
    //after size() iterations the queue should be in its original order with all the nodes transformed according to the transform operation
    for(int i=0; i<queueToTransform.size();i++)
    {
        transformOperation(queueToTransform.front());
        queueToTransform.pushBack(queueToTransform.front());
        queueToTransform.popFront();
    }
}
//
//end of queue definitions
//
#endif //EX3_QUEUE_H
