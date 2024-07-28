//------------------------------------------------------------------------------
//-----double linked list for handling of levels--------------------------------
//------------------------------------------------------------------------------

#include <cstddef>
#include <stdexcept>
#include <iostream>

using size_t = std::size_t;
template <typename T>

class List {
public:
    List() = default;
    ~List() = default;

    void pushBack(T item);
    void pushFront(T item);

    void popFront();
    void popBack();

    void remove(T item);

    void print() const;

    inline size_t size() const {return listSize;}
    inline bool empty() const {return !listSize;}
private:
    struct Container {  //container object
        Container* previous;
        Container* next;
        T item;
    };

public:
    class Iterator {    //iterator object
    public:
        Iterator(Container* container, List<T>* list);
        ~Iterator() = default;

        Iterator& operator++();
        Iterator& operator--();

        inline bool operator==(const Iterator& other) {return ((this->container == other.container) &&  (this->list == other.list));}
        inline bool operator!=(const Iterator& other) {return ((this->container != other.container) ||  (this->list != other.list));}

        T& operator*();
    private:
        Container* container;
        List<T>* list;
    };

private:
    Container* firstItem = nullptr;
    Container* lastItem = nullptr;

    size_t listSize = 0;

public:
    Iterator begin() {return Iterator(firstItem, this);}
    Iterator end() {return Iterator(nullptr, this);}
};

template<typename T>
void List<T>::pushBack(T item) {
    Container* newContainer = new Container{lastItem, nullptr, item};   //create new container on heap
    if(listSize) {   //list already has items
        lastItem->next = newContainer;  //link newContainer
    } else {
        firstItem = newContainer;
    }
    lastItem = newContainer;    //newContainer is lastItem
    ++listSize;
}

template<typename T>
void List<T>::pushFront(T item) {
    Container* newContainer = new Container {nullptr, firstItem, item};  //create new container on heap
    if(listSize) {  //list already has items
        firstItem->previous = newContainer;   //link newContainer
    } else {
        lastItem = newContainer;
    }
    firstItem = newContainer;   //newContainer is new firstItem
    ++listSize;
}

template<typename T>
void List<T>::popFront() {
    if (listSize) {
        Container* newFirstItem = firstItem->next;
        delete firstItem;
        firstItem = newFirstItem;
        firstItem->previous = nullptr;
        --listSize;
    } else {
        throw std::out_of_range("couldn't popFront() empty list");
    }
}

template<typename T>
void List<T>::popBack() {
    if(listSize) {
        Container* newLastItem = lastItem->previous;  //save newLastItem
        delete lastItem;    //delete old lastItem
        lastItem = newLastItem; //connect
        lastItem->next = nullptr;    //reset
        --listSize;
    } else {
        throw std::out_of_range("couldn't popBack() empty list");
    }
}

template<typename T>
void List<T>::remove(T item) {
    Container* currentItem = firstItem;
    while(currentItem != nullptr) {
        if(currentItem->item == item) {
            Container* previousItem = currentItem->previous;
            Container* nextItem = currentItem->next;

            if(previousItem == nullptr && nextItem == nullptr) {    //was only item
                firstItem = nullptr;
                lastItem = nullptr;
            } else if(previousItem == nullptr) {   //was first item
                firstItem = nextItem;
                nextItem->previous = nullptr;
            } else if (nextItem == nullptr) {  //was last item
                lastItem = previousItem;
                previousItem->next = nullptr;
            } else {    //item was inbetween
                previousItem->next = nextItem;
                nextItem->previous = previousItem;
            }
            Container* oldItem = currentItem;
            currentItem = nextItem;
            delete oldItem;
            --listSize;
        } else {
            currentItem = currentItem->next;
        }
    }
}

template<typename T>
void List<T>::print() const {
    if(listSize) {
        std::cout << "content of list:" << std::endl;
        Container* currentItem = firstItem;
        while(currentItem != nullptr) {
            std::cout << currentItem->item << std::endl;
            currentItem = currentItem->next;
        }
    } else {
        std::cout << "list is empty, nothing to print" << std::endl;
    }
}

template<typename T>
List<T>::Iterator::Iterator(List::Container* container, List<T>* list) :
        container(container), list(list){
}

template<typename T>
T& List<T>::Iterator::operator*() {
    if(dynamic_cast<Container*>(container)) {
        return container->item;
    } else {
        throw std::invalid_argument("Iterator is invalid");
    }
}

template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator--() {
    if (dynamic_cast<Container*>(container)) {
        container = container->previous;
        return *this;
    } else {
        throw std::invalid_argument("Iterator is invalid");
    }
}

template<typename T>
typename List<T>::Iterator &List<T>::Iterator::operator++() {
    if (dynamic_cast<Container*>(container)) {
        container = container->next;
        return *this;
    } else {
        throw std::invalid_argument("Iterator is invalid");
    }
}
