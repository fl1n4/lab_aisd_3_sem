#include <iostream>
#include <cstdlib> // Для использования функции rand()

template <typename T>
class Node
{
public:
    T data;
    Node<T>* next;

    Node(const T& data);
};
template <typename T>
Node<T>::Node(const T& data) : data(data), next(nullptr) {}

template <typename T>
class LinkedList
{
private:
    Node<T>* head;

public:
    LinkedList();
    LinkedList(const LinkedList<T>& other);
    LinkedList(int size);
    ~LinkedList();

    Node<T>* getHead() const;

    void append(const T& data);
    void clear();

    void display();
    void push_tail(const T& data);
    void push_tail(const LinkedList<T>& otherList);
    void push_head(const T& data);
    void push_head(const LinkedList<T>& otherList);
    void pop_head();
    void pop_tail();
    void delete_node(const T& data);
    int getSize() const;

    LinkedList<T>& operator=(const LinkedList<T>& other);
    friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list)
    {
        Node<T>* temp = list.head;
        while (temp != nullptr)
        {
            os << temp->data;
            temp = temp->next;
        }
        return os;
    }
};