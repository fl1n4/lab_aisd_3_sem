#include <iostream>
#include <random>

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

    void push_tail(const T& data);
    void push_tail(const LinkedList<T>& otherList);
    void push_head(const T& data);
    void push_head(const LinkedList<T>& otherList);
    void pop_head();
    void pop_tail();
    void delete_node(const T& data);
    int getSize() const;

    LinkedList<T>& operator=(const LinkedList<T>& other);
    friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {
        Node<T>* temp = list.head;

        // Пропускаем ведущие нули
        while (temp != nullptr && temp->data == 0 && temp->next != nullptr) {
            temp = temp->next;
        }

        // Выводим оставшееся число
        while (temp != nullptr) {
            os << temp->data<<" ";
            temp = temp->next;
        }

        return os;
    }
};

template <typename T>
T getRandomNumber(T min, T max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> distrib(min, max);
    T result = distrib(gen);
    return (result < 0) ? (-result) % 10 : result % 10;
}

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr) {}
template <typename T>
void LinkedList<T>::append(const T& data)
{
    Node<T>* newNode = new Node<T>(data);
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node<T>* temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
template <typename T>
void LinkedList<T>::clear()
{
    while (head != nullptr)
    {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
}
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : head(nullptr)
{
    Node<T>* temp = other.head;
    while (temp != nullptr)
    {
        append(temp->data);
        temp = temp->next;
    }
}
template <typename T>
LinkedList<T>::LinkedList(int size) : head(nullptr) 
{
    for (int i = 0; i < size; ++i) {
        T value = getRandomNumber(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
        append(value);
    }
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
    if (this != &other)
    {
        clear();
        Node<T>* temp = other.head;
        while (temp != nullptr)
        {
            append(temp->data);
            temp = temp->next;
        }
    }
    return *this;
}
template <typename T>
Node<T>* LinkedList<T>::getHead() const
{
    return head;
}
template <typename T>
void LinkedList<T>::push_tail(const T& data)
{
    Node<T>* newNode = new Node<T>(data);
    if (head == nullptr)
    {
        head = newNode;
    }
    else {
        Node<T>* temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
template <typename T>
void LinkedList<T>::push_tail(const LinkedList<T>& otherList)
{
    Node<T>* temp = otherList.head;
    while (temp != nullptr) {
        push_tail(temp->data);
        temp = temp->next;
    }
}
template <typename T>
void LinkedList<T>::push_head(const T& data)
{
    Node<T>* newNode = new Node<T>(data);
    newNode->next = head;
    head = newNode;
}
template <typename T>
void LinkedList<T>::push_head(const LinkedList<T>& otherList)
{
    LinkedList<T> tempList(otherList);
    Node<T>* temp = tempList.head;

    if (temp == nullptr)
    {
        return;
    }

    while (temp->next != nullptr)
    {
        temp = temp->next;
    }

    while (temp != nullptr)
    {
        push_head(temp->data);
        temp = temp->next;
    }
}
template <typename T>
void LinkedList<T>::pop_head()
{
    if (head != nullptr)
    {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
}
template <typename T>
void LinkedList<T>::pop_tail()
{
    if (head == nullptr)
    {
        return;
    }

    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
        return;
    }

    Node<T>* temp = head;
    while (temp->next->next != nullptr)
    {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
}
template <typename T>
void LinkedList<T>::delete_node(const T& data)
{
    Node<T>* current = head;
    Node<T>* previous = nullptr;

    while (current != nullptr)
    {
        if (current->data == data)
        {
            if (previous == nullptr)
            {
                pop_head();
                current = head;
            }
            else
            {
                previous->next = current->next;
                delete current;
                current = previous->next;
            }
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }
}
template <typename T>
int LinkedList<T>::getSize() const
{
    int size = 0;
    Node<T>* temp = head;
    while (temp != nullptr)
    {
        ++size;
        temp = temp->next;
    }
    return size;
}

template <typename T>
LinkedList<T> addNumbers(const LinkedList<T>& num1, const LinkedList<T>& num2) {
    T number1 = convertListToNumber(num1);
    T number2 = convertListToNumber(num2);

    T sum = number1 + number2;

    LinkedList<T> resultList;
    addDigitsToList(resultList, sum);

    return resultList;
}
template <typename T>
LinkedList<T> multiplyNumbers(const LinkedList<T>& num1, const LinkedList<T>& num2) {
    T number1 = convertListToNumber(num1);
    T number2 = convertListToNumber(num2);

    T product = number1 * number2;

    LinkedList<T> resultList;
    addDigitsToList(resultList, product);

    return resultList;
}
template <typename T>
void addDigitsToList(LinkedList<T>& list, T number) {
    list.clear();
    while (number > 0) {
        T digit = number % 10;
        list.push_head(digit);
        number /= 10;
    }
}
template <typename T>
T convertListToNumber(const LinkedList<T>& list) {
    Node<T>* current = list.getHead();
    T number = 0;

    while (current != nullptr) {
        number = number * 10 + current->data;
        current = current->next;
    }

    return number;
}
int main()
{
    // Пример использования класса LinkedList
    LinkedList<int> list1; // Конструктор по умолчанию
    list1.append(1);
    list1.append(2);
    list1.append(3);

    std::cout << "List 1: "<<list1<<std::endl;

    LinkedList<int> list2(list1); // Конструктор копирования
    std::cout << "List 2 (copy of List 1): ";

    LinkedList<int> list3(5); // Конструктор, заполняющий список случайными значениями
    std::cout << "List 3 (filled with random values): "<<list3<<std::endl;

    LinkedList<int> list4;
    list4 = list2;
    std::cout << "List 4 (assigned from List 2): " << list4 << std::endl;

    LinkedList<int> list5;
    list5.push_tail(4);
    list5.push_tail(5);
    std::cout << "List 5 (pushed individual elements): " << list5 << std::endl;

    LinkedList<int> list6;
    list6.append(6);
    list6.append(7);
    std::cout << "List 6: " << list6 << std::endl;

    list5.push_tail(list6);
    std::cout << "List 5 after push_tail of List 6: " << list5 << std::endl;

    LinkedList<int> list7;
    list7.push_head(3);
    list7.push_head(2);
    std::cout << "List 7 (pushed individual elements to head): " << list7 << std::endl;

    LinkedList<int> list8;
    list8.append(0);
    list8.append(1);
    std::cout << "List 8: " << list8 << std::endl;

    list7.push_head(list8);
    std::cout << "List 7 after push_head of List 8: " << list7 << std::endl;

    LinkedList<int> list9;
    list9.append(1);
    list9.append(2);
    list9.append(3);
    std::cout << "Initial list 9: " << list9 << std::endl;

    list9.pop_head();
    std::cout << "List 9 after pop_head: " << list9 << std::endl;

    list9.pop_tail();
    std::cout << "List 9 after pop_tail: " << list9 << std::endl;

    list9.append(2);
    list9.append(2);
    list9.append(4);
    std::cout << "List 9 with duplicates: " << list9 << std::endl;

    list9.delete_node(2);
    std::cout << "List 9 after deleting nodes with value 2: " << list9 << std::endl;
    LinkedList<int> number1;
    addDigitsToList(number1, 12);
    

    LinkedList<int> number2;
    addDigitsToList(number2, 56);

    LinkedList<int> product = multiplyNumbers(number1, number2);

    std::cout << "proizdevenie: " << product << std::endl;

    LinkedList<int> num1;
    LinkedList<int> num2;

    addDigitsToList(num1, 12);
    addDigitsToList(num2, 59);

    // Складываем числа, представленные в виде списков
    LinkedList<int> sum = addNumbers(num1, num2);
    std::cout << "Sum: " << sum << std::endl;
    return 0;
}