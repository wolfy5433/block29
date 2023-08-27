#include "FineGrainedQueue.h"

FineGrainedQueue::Node::Node(int OutsideValue)
{
    value = OutsideValue;
    next = nullptr;
}

FineGrainedQueue::FineGrainedQueue()
{
    head = nullptr;
}

void FineGrainedQueue::addValue(int value)
{
    Node* newNode = new Node(value);

    if (head == nullptr)
    {
        head = newNode;
        return;
    }
    Node* last = head;
    while (last->next != nullptr)
    {
        last = last->next;
    }
    last->next = newNode;
    return;
}

FineGrainedQueue::Node* FineGrainedQueue::find(Node* node, int position, int currentPosition)
{
    if (position == currentPosition || node->next == nullptr)
    {
        return node;
    }
    else if ((position > currentPosition) && (node->next != nullptr))
    {
        ++currentPosition;
        find(node->next, position, currentPosition);
    }
    else
    {
        return nullptr;
    }
}

void FineGrainedQueue::insertIntoMiddle(int value, int pos)
{
    Node* previous;
    Node* newNode;

    queue_mutex.lock();
    previous = find(head, pos - 1, 1);
    newNode = new Node(value);
    queue_mutex.unlock();

    previous->node_mutex.lock();
    newNode->node_mutex.lock();
    newNode->next = previous->next;
    previous->next = newNode;
    previous->node_mutex.unlock();
    newNode->node_mutex.unlock();
}

void FineGrainedQueue::remove(int value)
{
    Node* previous;
    Node* current;

    queue_mutex.lock();

    previous = this->head;
    current = this->head->next;

    previous->node_mutex.lock();
    queue_mutex.unlock();

    if (current)
    {
        current->node_mutex.lock();
    }
    while (current)
    {
        if (current->value == value)
        {
            previous->next = current->next;
            previous->node_mutex.unlock();
            current->node_mutex.unlock();
            delete current;
            return;
        }
        Node* pre_previous = previous;
        previous = current;
        current = current->next;
        pre_previous->node_mutex.unlock();
        if (current)
        {
            current->node_mutex.lock();
        }
    }
    previous->node_mutex.unlock();
}

void FineGrainedQueue::show()
{
    for (Node* ptr = head; ptr != nullptr; ptr = ptr->next)
    {
        std::cout << ptr->value << " ";
    }
    std::cout << std::endl;
}