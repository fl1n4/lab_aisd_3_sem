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
            os << temp->data<<" ";
            temp = temp->next;
        }
        return os;
    }
};

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
    for (int i = 0; i < size; ++i)
    {
        T value = rand() % 100; // Генерация случайного числа
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
LinkedList<T> addNumbers(const LinkedList<T>& num1, const LinkedList<T>& num2)
{
    LinkedList<T> result;
    int carry = 0;

    Node<T>* temp1 = num1.getHead();
    Node<T>* temp2 = num2.getHead();

    while (temp1 != nullptr || temp2 != nullptr || carry != 0)
    {
        int sum = carry;

        if (temp1 != nullptr)
        {
            sum += temp1->data;
            temp1 = temp1->next;
        }
        if (temp2 != nullptr)
        {
            sum += temp2->data;
            temp2 = temp2->next;
        }

        carry = sum / 10;
        result.push_tail(sum % 10);
    }

    return result;
}

template <typename T>
LinkedList<T> multiplyNumbers(const LinkedList<T>& num1, const LinkedList<T>& num2)
{
    LinkedList<T> result;

    int size1 = num1.getSize();
    int size2 = num2.getSize();

    LinkedList<T>* intermediateResults = new LinkedList<T>[size2];

    Node<T>* temp2 = num2.getHead();
    int index = 0;

    while (temp2 != nullptr)
    {
        LinkedList<T> tempResult;
        int carry = 0;

        Node<T>* temp1 = num1.getHead();

        for (int i = 0; i < index; ++i)
        {
            tempResult.push_tail(0);
        }

        while (temp1 != nullptr || carry != 0)
        {
            int product = carry;

            if (temp1 != nullptr)
            {
                product += temp1->data * temp2->data;
                temp1 = temp1->next;
            }

            carry = product / 10;
            tempResult.push_tail(product % 10);
        }

        intermediateResults[index] = tempResult;
        temp2 = temp2->next;
        ++index;
    }

    for (int i = 0; i < size2; ++i)
    {
        result = addNumbers(result, intermediateResults[i]);
    }

    delete[] intermediateResults;
    return result;
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
    std::cout << "List 9 after deleting nodes with value 2: ";
    LinkedList<int> number1;
    number1.push_head(9);
    number1.push_head(1);
    number1.push_head(2);

    LinkedList<int> number2;
    number2.push_head(5);
    number2.push_head(2);

    LinkedList<int> product = multiplyNumbers(number1, number2);

    std::cout << "proizdevenie: " << product << std::endl;

    LinkedList<int> num1;
    LinkedList<int> num2;

    // Добавляем цифры числа в список (в обратном порядке)
    num1.push_tail(2);
    num1.push_tail(4);
    num1.push_tail(3); // Представляет число 243

    num2.push_tail(5);
    num2.push_tail(6);
    num2.push_tail(4); // Представляет число 564

    // Складываем числа, представленные в виде списков
    LinkedList<int> sum = addNumbers(num1, num2);

    // Выводим результат на экран
    std::cout << "Sum: " << sum << std::endl; // Ожидаемый результат: 807 (243 + 564)
    return 0;
}