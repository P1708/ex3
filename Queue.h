//
// Created by Omer Bahat on 27/12/2022.
//

#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

#include <stdio.h>
#include <iostream>

const int ONLY_BLANKS_SIZE = 2;

template<class T>
class Queue {
public:
    class Node
    {
    public:
        T m_data;
        Node *m_next;
        Node *m_previous;
        bool m_isBlank;
        Node(const T data);
        Node(const Node &toCopy);
        explicit Node(T m_data, Node *m_next, Node *m_previous, bool m_isBlank);

    };
    Queue();
    ~Queue();
    Queue(const Queue &toCopy);
    Queue<T>& operator=(const Queue &toCopy);
    /// Inserts a node to the back of the queue, a copy of the node is created
    /// \param nodeToAdd - node to insert a copy of
    void pushBack(const T &nodeToAdd);
    /// Returns value at front of the queue
    /// \return m_data of node at front of the queue
    T &front() const;
    ///pops out node at front of the queue, returns nothing
    void popFront();
    /// Gets length of queue
    /// \return int containing length of queue, if queue is empty, 0
    int size() const;

    class Iterator;
    Iterator begin();
    Iterator end();

    class ConstIterator;
    ConstIterator begin() const;
    ConstIterator end() const;

    class EmptyQueue{};

private:
    int m_size;
    Node *m_head;
    Node *m_tail;
};

template<class T>
///node constructor using only data to copy
Queue<T>::Node::Node(const T data):m_data(data)
{
}

template<class T>
///node constructor using node to copy
Queue<T>::Node::Node(const Queue::Node &toCopy)
{
    //problems may arise from copying more complex data (node data type is unknown to us) we'll use try catch if alloc of data to copy failed
    try
    {
        this->m_data = T(toCopy.m_data);
    }
    catch (const std::bad_alloc)
    {
        delete *this;
        throw;
    }
    //rest of copy is simple, no needed to try catch for malloc
    this->m_next = toCopy.m_next;
    this->m_previous = toCopy.m_previous;
    this->m_isBlank = toCopy.m_isBlank;

}

template<class T>
Queue<T> &Queue<T>::operator=(const Queue<T> &toCopy)
{
    if(this== &toCopy)
    {
        return *this;
    }
    //instead of creating a whole new queue, well add/remove the amount of nodes needed so sizes will match
    //and then just implement the values of each node accordingly
    int sizeDiff = this->size()-toCopy.size();
    while(sizeDiff>0)
    {
        this->popFront();
        --sizeDiff;
    }
    while(sizeDiff>0)
    {
        try
        {
            this->pushBack(T());
            --sizeDiff;
        }
        catch (std::bad_alloc)
        {
            delete &toCopy;
            throw;
        }
    }
    assert(this->size()==toCopy.size());
    Queue<T>::Iterator newQueueIterator = this->begin();
    Queue<T>::ConstIterator oldQueueIterator = toCopy.begin();
    for(int i=0;i<toCopy.size();i++)
    {
        *newQueueIterator=*oldQueueIterator;
        ++newQueueIterator;
        ++oldQueueIterator;
    }
    return *this;

}

template<class T>
///explicit node constructor using "full data"
Queue<T>::Node::Node(T data, Queue::Node *next, Queue::Node *previous, bool isBlank): m_data(data)
{
    this->m_next = next;
    this->m_previous = previous;
    this->m_isBlank = isBlank;
}

template<class T>
///default Queue constructor, we use 2 blank nodes, for head and tail of queue
Queue<T>::Queue()
{
    Node *headTemp = new Node(T(), nullptr, nullptr, true);
    Node *tailTemp = new Node(T(), nullptr, nullptr, true);
    headTemp->m_previous = tailTemp;
    tailTemp->m_next = headTemp;
    m_head = headTemp;
    m_tail = tailTemp;
    m_size = ONLY_BLANKS_SIZE;
}

template<class T>
Queue<T>::~Queue()
{
    Node *toDelete = this->m_tail;
    while(toDelete!=this->m_head)
    {
        this->m_tail = this->m_tail->m_next;
        delete toDelete;
        toDelete = this->m_tail;
    }
    delete this->m_tail;
}

template<class T>
Queue<T>::Queue(const Queue<T> &toCopy)
{
    try
    {
        *this = Queue();
        for(Queue<T>::ConstIterator elem =toCopy.begin(); elem!=toCopy.end(); ++elem )
        {
            this->pushBack(elem.m_currentNode->m_data);
        }

    }
    catch (const std::bad_alloc) {
        delete this;
        throw;
    }
}

template<class T, class FilterFlag>
Queue<T> &filter(const Queue<T> &queueToFilter, FilterFlag filterFlag);

template<class T, class TransformOperation>
void transform(Queue<T> &queueToTransform, TransformOperation &transformOperation);



//Iterator & ConstIterator "section"

//iterator & constIterator class def
template<class T>
class Queue<T>::Iterator
{
private:
    friend class Queue<T>;
    Queue<T> *m_queue;
    Node *m_currentNode;
    //exists for begin and end, private to not obstruct encapsulation, only available from friend class: queue<T>
    Iterator(Queue<T> *queue, Node *currentNode);

public:
    Iterator(const Iterator &toCopy)=default;

    Iterator &operator=(const Iterator &iterator)=default;
    Iterator &operator++();
    T &operator*();

    bool operator!=(const Iterator &iterator);

    class InvalidOperation{};

};
template<class T>
class Queue<T>::ConstIterator
{
private:
    friend class Queue<T>;
    const Queue<T> *m_queue;
    const Node *m_currentNode;
    //exists for begin and end, private to not obstruct encapsulation, only available from friend class: queue<T>
    ConstIterator(const Queue<T> *queue, Node *currentNode);

public:
    ConstIterator(const ConstIterator &toCopy) = default;

    ConstIterator &operator=(ConstIterator &constIterator)=default;
    ConstIterator &operator++();
    const T &operator*() const;

    bool operator!=(const ConstIterator &constIterator) const;

    class InvalidOperation{};


};
//iterator & constIterator operator++ def
template<class T>
typename Queue<T>::Iterator &Queue<T>::Iterator::operator++()
{
    //check if current node is the tail pointer
    if(this->m_currentNode->m_previous== nullptr)
    {
        throw Queue<T>::Iterator::InvalidOperation();
    }
    else
    {
        this->m_currentNode=this->m_currentNode->m_previous;
        return *this;
    }
}
template<class T>
typename Queue<T>::ConstIterator &Queue<T>::ConstIterator::operator++()
{
    //check if current node is the tail pointer
    if(this->m_currentNode->m_previous== nullptr)
    {
        throw Queue<T>::ConstIterator::InvalidOperation();
    }
    else
    {
        this->m_currentNode=this->m_currentNode->m_previous;
        return *this;
    }
}
//iterator & constIterator operator* def
template<class T>
T &Queue<T>::Iterator::operator*()
{
    //TO_DELETE_COMMENT- may need changing
    //making sure not to access blank node
    if(this->m_currentNode)
    {
        return this->m_currentNode->m_data;
    }
    throw Queue<T>::Iterator::InvalidOperation();
}
template<class T>
const T &Queue<T>::ConstIterator::operator*() const
{
    //TO_DELETE_COMMENT- may need changing
    if(this->m_currentNode)
    {
        return this->m_currentNode->m_data;
    }
    throw Queue<T>::ConstIterator::InvalidOperation();
}
//iterator & constIterator operator!= def
template<class T>
bool Queue<T>::Iterator::operator!=(const Queue::Iterator &iterator)
{
    //TO_DELETE_COMMENT- may need adding brackets to boolean statement
    return this->m_currentNode!=iterator.m_currentNode;
}
template<class T>
bool Queue<T>::ConstIterator::operator!=(const Queue::ConstIterator &constIterator) const
{
    //TO_DELETE_COMMENT- may need adding brackets to boolean statement
    return this->m_currentNode!=constIterator.m_currentNode;
}
//iterator & constIterator private constructor def
template<class T>
Queue<T>::Iterator::Iterator(Queue<T> *queue, Queue::Node *currentNode):m_queue(queue), m_currentNode(currentNode)
{}
template<class T>
Queue<T>::ConstIterator::ConstIterator(const Queue<T> *queue, Queue::Node *currentNode):m_queue(queue), m_currentNode(currentNode)
{}
//iterator & constIterator queue::begin() def
template<class T>
typename  Queue<T>::Iterator Queue<T>::begin()
{
    return Iterator(this, this->m_head->m_previous);
}
template<class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const
{
    return ConstIterator(this, this->m_head->m_previous);
}
//iterator & constIterator queue::end() def
template<class T>
typename  Queue<T>::Iterator Queue<T>::end()
{
    return Iterator(this, this->m_tail);
}
template<class T>
typename Queue<T>::ConstIterator Queue<T>::end() const
{
    return ConstIterator(this, this->m_tail);
}

//end of Iterator & ConstIterator "section"



template<class T>
void Queue<T>::pushBack(const T &nodeToAdd)
{
    Node *tempNode = nullptr;
    //create a node with correct data & pointing to the right nodes
    try
    {
        tempNode = new Node(nodeToAdd, this->m_tail->m_next, this->m_tail, false);
    }
    catch (const std::bad_alloc)
    {
        delete this;
        throw;
    }
    //point surrounding nodes to newly created and increasing queue size
    this->m_tail->m_next->m_previous = tempNode;
    this->m_tail->m_next = tempNode;
    ++this->m_size;
}
template<class T>
T & Queue<T>::front() const {
    if(size()==0)
    {
        throw Queue<T>::EmptyQueue();
    }
    return m_head->m_previous->m_data;
}
template<class T>
void Queue<T>::popFront()
{
    if(size()==0)
    {
        throw EmptyQueue();
    }
    else
    {
        Node *toDelete = this->m_head->m_previous;
        this->m_head->m_previous->m_previous->m_next = this->m_head;
        this->m_head->m_previous= this->m_head->m_previous->m_previous;
        delete toDelete;
        --this->m_size;
    }
}
template<class T>
int Queue<T>::size() const
{
    return this->m_size - ONLY_BLANKS_SIZE;//we have blank nodes, need to not add them into consideration
}

template<class T, class FilterFlag>
Queue<T> &filter(const Queue<T> &queue, FilterFlag filterFlag)
{
    try
    {
        //main problem to be expected is bad alloc, all the rest is pretty standard
        Queue<T> *tempQueue = new Queue<T>();
        for(const T& iteratedValue : queue)
        {
            if(filterFlag(iteratedValue))
            {
                tempQueue->pushBack(iteratedValue);
            }
        }
        return *tempQueue;
    }
    catch (const std::bad_alloc)
    {
        throw;
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


#endif //EX3_QUEUE_H
