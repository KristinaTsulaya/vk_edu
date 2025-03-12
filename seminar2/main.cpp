#include <iostream>

template <typename T>
class Node {
public:
    T value;
    Node* next; // нода хранит указатель на следующую ноду
    Node(T val_) : value(val_), next(nullptr) {}
};

template <typename T>
class List {
public:
    Node<T>* head; /// указатель на голову
    Node<T>* tail; /// указатель на хвост

    List(): head(nullptr), tail(nullptr) {}
    
    void push_back(T value) {
        Node<T>* new_node = new Node<T>(value);
        if (head == nullptr)
            head = tail = new_node;
        else {
            tail->next = new_node;
            tail = new_node;
        }
    }
};

template <typename T>
bool check_circular_list(Node<T>* head) {
    if (head == nullptr || head->next == nullptr)
        return false;
    
    Node<T>* slow = head;
    Node<T>* fast = head->next; // именно на следующий после головы, чтобы попасть в while

    while(slow != fast) {
        if (fast == nullptr || fast->next == nullptr)
            return false;
        
        slow = slow->next;
        fast = fast->next->next;
    } 
    
    return true;
}

template <typename T>
void reverse_list(List<T>& list) {
    Node<T>* prev = nullptr;
    Node<T>* current = list.head;
    Node<T>* old_head = list.head;

    while(current != nullptr) {
        Node<T>* next = current->next; // Нужно сохранить next, чтобы не потерять связь со следующим узлом при разрыве.
        current->next = prev; // разрываем связь
        prev = current; // смещаем указатели
        current = next;
    }

    list.head = prev;
    list.tail = old_head;
}

template <typename T>
T find_mid(List<T>& list) {
    Node<T>* fast = list.head;
    Node<T>* slow = list.head;

    while(fast != nullptr && fast->next != nullptr) { // Это гарантирует, что fast->next->next не вызовет ошибки при четном количестве узлов
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow->value;
}

template <typename T>
void pop(List<T>& list, T value) {
    Node<T>* dummy = new Node<T>(0); // фиктивный узел
    dummy->next = list.head;
    Node<T>* prev = dummy;
    Node<T>* current = list.head;

    while (current) {
        if (current->value == value) {
            // Если удаляемый узел — это хвост, обновляем tail
            if (current == list.tail) {
                list.tail = prev;
            }
            prev->next = current->next;
            delete current;
            current = prev->next; // Переходим к следующему узлу
        } else {
            prev = current;
            current = current->next;
        }
    }

    list.head = dummy->next;

    // Если список стал пустым — обнуляем tail
    if (list.head == nullptr) {
        list.tail = nullptr;
    }

    delete dummy;
}


int main() {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    reverse_list(list);
}