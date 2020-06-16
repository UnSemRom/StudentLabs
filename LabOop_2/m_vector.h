#ifndef M_VECTOR_H
#define M_VECTOR_H
#include <iostream>
#include <initializer_list>

template<class T> class m_vector
{
private:
    int size;
    int capacity;
    T* elems;

public:
    m_vector() : size(0), elems(0), capacity(0) {};

    explicit m_vector(int s) : size(s), elems(new T[s]), capacity(s)
    {
        for (int i = 0; i < size; ++i)
            elems[i] = T();
    }

    m_vector(const m_vector<T>& vect) : size(vect.size), elems(new T[vect.size]), capacity(vect.capacity)
    {
        for (int i = 0; i < vect.size; ++i)
            elems[i] = vect.elems[i];
    }

    m_vector(std::initializer_list<T> const &lst) : size(lst.size()), capacity(lst.size()), elems(new T[lst.size()])
    {
        for (int i = 0; i < lst.size(); i++)
            elems[i] = *(lst.begin() + i);
    }

    ~m_vector()
    {
        delete[] elems;
    }

    m_vector<T>& operator =(const m_vector<T>& lst)
    {
        if (this == &lst)
            return *this;

        int newSize = lst.size;
        int newCapacity = lst.capacity;
        T* newElems = new T[lst.capacity];

        for (int i = 0; i < newCapacity; i++)
            newElems[i] = lst.elems[i];

        delete[] elems;

        elems = new T[newCapacity];
        size = newSize;
        capacity = newCapacity;

        for(int i = 0; i < size; i++)
            elems[i] = newElems[i];

        delete[] newElems;

        return *this;
    }

    int get_length()
    {
        return size;
    }

    void set_elem(int index, const T& elem)
    {
        if (index >= capacity)
            throw std::out_of_range("Bad index");
        elems[index] = elem;
    }

    T& get_elem(int index)
    {
        if (index >= capacity)
            throw std::out_of_range("Bad index");
        return elems[index];
    }

    T* to_array()
    {
        T* newElems = new T[size];
        for (int i = 0; i < size; i++)
            newElems[i] = elems[i];
        return newElems;
    }

    T& operator [](int index)
    {
        if (index >= capacity)
            throw std::out_of_range("Bad index");

        return elems[index];
    }

    template<typename _T> friend std::ostream& operator <<(std::ostream& os, const m_vector<_T>&lst)
    {
        os << "[";
        for (int i = 0; i < lst.size; ++i) {
            os << lst.elems[i];
            if (i != lst.size - 1)
                os << ", ";
        }
        os << "]";
        return os;
    }

    m_vector<T>& operator +=(const m_vector<T>& vect)
    {
        if(size != vect.size)
            throw std::out_of_range("Vectors dimensions are not equal");
        for (int i = 0; i < size; i++)
            elems[i] = elems[i]+vect.elems[i];
        return *this;
    }

    m_vector<T>& operator -=(const m_vector<T>& vect)
    {
        if(size != vect.size)
            throw std::out_of_range("Vectors dimensions are not equal");
        for (int i = 0; i < size; i++)
            elems[i] = elems[i]-vect.elems[i];
        return *this;
    }
    m_vector<T>& operator *=(const T& val)
    {
        for (int i = 0; i < size; i++)
            elems[i] *= val;

        return *this;
    }

    m_vector<T>& operator /=(const T& val)
    {
        for (int i = 0; i < size; i++)
            elems[i] /= val;

        return *this;
    }

    template<typename _T> friend m_vector<_T> operator +(const m_vector<_T>&v1, const m_vector<_T>&v2)
    {
        if(v1.size != v2.size)
            throw std::out_of_range("Vectors dimensions are not equal");
        else{
            m_vector<_T> res(v1.size);
            for (int i = 0; i < v1.size; i++)
                res.elems[i] = v1.elems[i]+v2.elems[i];
            return res;

        }
    }

    template<typename _T> friend m_vector<_T> operator -(const m_vector<_T>&v1, const m_vector<_T>&v2)
    {
        if(v1.size != v2.size)
            throw std::out_of_range("Vectors dimensions are not equal");
        else{
            m_vector<_T> res(v1.size);
            for (int i = 0; i < v1.size; i++)
                res.elems[i] = v1.elems[i]-v2.elems[i];
            return res;
    }
}
    template<typename _T> friend m_vector<_T> operator *(const m_vector<_T>&v1, const T& val)
    {
        m_vector<_T> res(v1.size);
        for (int i = 0; i < v1.size; i++) {
            res.elems[i] = v1.elems[i] * val;
        }
        return res;
    }

    template<typename _T> friend m_vector<_T> operator /(const m_vector<_T>&v1, const T& val)
    {
        m_vector<_T> res(v1.size);
        for (int i = 0; i < v1.size; i++) {
            res.elems[i] = v1.elems[i] / val;
        }
        return res;
    }

    class m_Iterator;

    m_Iterator iterator_begin()
    {
        m_Iterator it(elems);
        return it;
    }
    m_Iterator iterator_end()
    {
        m_Iterator it(elems + size - 1);
        return it;
    }

};


template<class T> class m_vector<T>::m_Iterator {
private:
    T* ptr;

public:
    m_Iterator() : ptr(nullptr) {};

    m_Iterator(T *c_obj) : ptr(c_obj) {};

    ~m_Iterator() = default;

    m_Iterator & operator++(){
        ptr++;
        return *this;
    }

    m_Iterator & operator--(){
        ptr--;
        return *this;
    }

    m_Iterator & next() {
        ptr++;
        return *this;
    }

    T value() {
        return *ptr;
    }

    bool is_end(m_vector<T> b) {
        return ptr == b.elems + b.size;
    }

    bool operator ==(m_Iterator &b) const {
        return ptr == b.ptr;
    }

    bool operator != (m_Iterator &b) const {
        return ptr != b.ptr;
    }

    T& operator *() {
        return *ptr;
    }
};

#endif // M_VECTOR_H
