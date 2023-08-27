#pragma once
#include <iostream>
#include <mutex>

class FineGrainedQueue
{
private:
    struct Node
    {
        int value;
        Node* next;
        std::mutex node_mutex;
        Node(int OutsideValue);
    };
    Node* head;
    std::mutex queue_mutex;

public:
    FineGrainedQueue();
    void insertIntoMiddle(int value, int pos);
    void addValue(int value);
    void remove(int value);
    void show();
    Node* find(Node* node, int position, int currentPosition);
};