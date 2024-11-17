#include <iostream>


template <typename T> class FuncListItem {
    private:
        T *value;
        FuncListItem<T> *next_ptr, *prev_ptr;
    public:
        FuncListItem();
        FuncListItem(T *value);
        ~FuncListItem();
        void set_value(T *value);
        void set_next_ptr(FuncListItem<T> *next_ptr);
        void set_prev_ptr(FuncListItem<T> *prev_ptr);
        T *get_value();
        FuncListItem<T> *get_next_ptr();
        FuncListItem<T> *get_prev_ptr();
};


template <typename T> FuncListItem<T>::FuncListItem() {
    this->value = nullptr;
    this->next_ptr = nullptr;
    this->prev_ptr = nullptr;
}

template <typename T> FuncListItem<T>::FuncListItem(T *value) {
    this->value = value;
    this->next_ptr = nullptr;
    this->prev_ptr = nullptr;
}

template <typename T> FuncListItem<T>::~FuncListItem() {
    delete(this->value);

    if (this->next_ptr == nullptr) {
        if (this->prev_ptr != nullptr) {
            this->prev_ptr->next_ptr = nullptr;
            this->prev_ptr = nullptr;
        }
    } else {
        if (this->prev_ptr == nullptr) {
            this->next_ptr->prev_ptr = nullptr;
            this->next_ptr = nullptr;
        } else {
            this->prev_ptr->next_ptr = this->next_ptr;
            this->next_ptr->prev_ptr = this->prev_ptr;
            this->prev_ptr = nullptr;
            this->next_ptr = nullptr;
        }
    }
}

template <typename T> void FuncListItem<T>::set_value(T *value) {
    this->value = value;
}

template <typename T> void FuncListItem<T>::set_next_ptr(FuncListItem<T> *next_ptr) {
    this->next_ptr = next_ptr;
}

template <typename T> void FuncListItem<T>::set_prev_ptr(FuncListItem<T> *prev_ptr) {
    this->prev_ptr = prev_ptr;
}

template <typename T> T *FuncListItem<T>::get_value() {
    return this->value;
}

template <typename T> FuncListItem<T> *FuncListItem<T>::get_next_ptr() {
    return this->next_ptr;
}

template <typename T> FuncListItem<T> *FuncListItem<T>::get_prev_ptr() {
    return this->prev_ptr;
}


template <typename T> class FuncList {
    private:
        FuncListItem<T> *head, *tail;
    public:
        FuncList();
        FuncList(T *arr, int len);
        ~FuncList();
        FuncList<T> &operator>>(T item);
        FuncList<T> &operator<<(T item);
        void print(std::ostream &out_stream);
};


template <typename T> FuncList<T>::FuncList() {
    this->head = nullptr;
    this->tail = nullptr;
}

template <typename T> FuncList<T>::FuncList(T *arr, int len) {
    this->head = nullptr;
    this->tail = nullptr;

    for (int i = 0; i < len; i++) {
        *this << arr[i];
    }
}

template <typename T> FuncList<T>::~FuncList() {
    FuncListItem<T> *current = this->head, *next;

    this->head = nullptr;
    this->tail = nullptr;

    while (current != nullptr) {
        next = current->get_next_ptr();
        delete(current);
        current = next;
    }
}

template <typename T> FuncList<T> &FuncList<T>::operator>>(T item) {
    T *value = new T;
    *value = item;

    FuncListItem<T> *new_item = new FuncListItem<T>(value);

    if (this->head == nullptr) {
        this->head = new_item;
        this->tail = this->head;
    } else {
        this->head->set_prev_ptr(new_item);
        new_item->set_next_ptr(this->head);
        this->head = new_item;
    }

    return *this;
}

template <typename T> FuncList<T> &FuncList<T>::operator<<(T item) {
    T *value = new T;
    *value = item;

    FuncListItem<T> *new_item = new FuncListItem<T>(value);

    if (this->head == nullptr) {
        this->head = new_item;
        this->tail = this->head;
    } else {
        this->tail->set_next_ptr(new_item);
        new_item->set_prev_ptr(this->tail);
        this->tail = new_item;
    }

    return *this;
}

template <typename T> void FuncList<T>::print(std::ostream &out_stream) {
    FuncListItem<T> *current = this->head;

    out_stream << "[";

    while (current != nullptr) {
        out_stream << *(current->get_value()) << ((current->get_next_ptr() != nullptr) ? ", " : "");
        current = current->get_next_ptr();
    }

    out_stream << "]\n";
}


int main(int argc, char **argv) {
    int a[5] = {1, 2, 3, 4, 5};
    FuncList<int> func_list = FuncList<int>(a, 5);

    func_list.print(std::cout);
    func_list << 5 << 10 << 6 >> 4;
    func_list.print(std::cout);

    return 0;
}