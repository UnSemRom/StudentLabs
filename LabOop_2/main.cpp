#include <QCoreApplication>
#include <m_vector.h>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    try {
        cout<<"Check_start"<<endl;

        m_vector<int> v1 = {1,2,3};
        m_vector<int>::m_Iterator it;

        cout<<"Complete the passage using an iterator on a vector."<<endl;
        for (it = v1.iterator_begin(); v1.iterator_end() != it ; ++it)
            cout << *it << endl;
        cout<<endl;

        cout<<"Iterator<T> next() "<<endl;
        it = v1.iterator_begin();
        it.next();
        if(*it != 2)
            throw out_of_range("Derived the wrong value");
        cout<<*it<<endl<<endl;

        cout<<"T value() "<<endl;
        if(*it != 2)
            throw out_of_range("Derived the wrong value");
        cout<<it.value()<<endl<<endl;

        cout<<"bool is_end() "<<endl;
        bool res1 = it.is_end(v1);
        if(res1 != 0)
            throw out_of_range("Derived the wrong value");
        cout<<res1<<endl<<endl;

        cout<<"Iterator &operator++()"<<endl;
        ++it;
        if(*it != 3)
            throw out_of_range("Derived the wrong value");
        cout<<*it<<endl<<endl;

        cout<<"T &operator*()"<<endl;
        if(*it != 3)
            throw out_of_range("Derived the wrong value");
        cout<<*it<<endl<<endl;

        cout<<"bool operator ==(Iterator &b)"<<endl;
        bool res2 = v1.iterator_end()==it;
        if(res2 != 1)
            throw out_of_range("Derived the wrong value");
        cout<<res2<<endl<<endl;

        cout<<"bool operator !=(Iterator &b)"<<endl;
        bool res3 = v1.iterator_end()!=it;
        if(res3 != 0)
            throw out_of_range("Derived the wrong value");
        cout<<res3<<endl<<endl;

        cout<<"m_vector<T>& operator =(const m_vector<T>& lst);"<<endl;
        m_vector<int> v2 = v1;
        for(int i = 0; i < 3; i++)
            if(v2[i] != i+1)
                throw out_of_range("Derived the wrong value");
        cout<<v2<<endl<<endl;

        cout<<"int get_length();"<<endl;
        if(v1.get_length() != 3)
            throw out_of_range("Derived the wrong value");
        cout<<v1.get_length()<<endl<<endl;

        cout<<"void set_elem(int index,const T& elem)"<<endl;
        cout<<v1<<endl;
        v1.set_elem(0,100);
        if (v1[0] != 100)
             throw out_of_range("Derived the wrong value");
        cout<<v1<<endl<<endl;

        cout<<"T& get_elem(int index);"<<endl;
        if(v1.get_elem(2) != 3)
            throw out_of_range("Derived the wrong value");
        cout<<v1.get_elem(2)<<endl<<endl;

        cout<<"T[] to_array(); "<<endl;
        int* arr  = v1.to_array();
        for(int i = 0; i < v1.get_length(); i++)
            cout<<arr[i]<<endl;
        cout<<endl;

        cout<<"T& operator[](int index);"<<endl;
        if(v1[0] != 100)
             throw out_of_range("Derived the wrong value");
        cout<<v1[0]<<endl<<endl;

        cout<<"m_vector<T>& operator +=(const m_vector<T>& vect); "<<endl;
        v1 = {-2,2,4};
        v2 = {2,-1,-2};
        v1+=v2;
        for (int i = 0; i < 3; i++)
            if(v1[i] != i)
                throw out_of_range("Derived the wrong value");
        cout<<v1<<endl<<endl;

        cout<<"m_vector<T>& operator -=(const m_vector<T>& vect); "<<endl;
        v1 = {1};
        v2 = {2};
        v1-=v2;
        if (v1[0] != -1)
            throw out_of_range("Derived the wrong value");
        cout<<v1<<endl<<endl;

        cout<<"m_vector<T>& operator *=(const T& val);"<<endl;
        v1*=2;
         if (v1[0] != -2)
             throw out_of_range("Derived the wrong value");
        cout<<v1<<endl<<endl;

        cout<<"m_vector<T>& operator /=(const T& val);"<<endl;
        v1/=2;
        if (v1[0] != -1)
            throw out_of_range("Derived the wrong value");
        cout<<v1<<endl<<endl;

        cout<<"template<typename _T> friend m_vector<_T> operator +(const m_vector<_T>& v1, const m_vector<_T>& v2);"<<endl;
        v1 = {5};
        v2 = {6};
        v1 = v1 + v2;
        if(v1[0] != 11)
             throw out_of_range("Derived the wrong value");
        cout<<v1<<endl<<endl;

        cout<<"template<typename _T>friend m_vector<_T> operator -(const m_vector<_T>& v1, const m_vector<_T>& v2);"<<endl;
        v1 = {5};
        v2 = {6};
        v1 = v1 - v2;
        if(v1[0] != -1)
             throw out_of_range("Derived the wrong value");
        cout<<v1<<endl<<endl;

        cout<<"template<typename _T> friend m_vector<_T> operator *(const m_vector<_T>& v1,  const T& val); "<<endl;
        v1 = v1 * 2;
        if(v1[0] != -2)
             throw out_of_range("Derived the wrong value");
        cout<<v1<<endl<<endl;

        cout<<"template<typename _T> friend m_vector<_T> operator /(const m_vector<_T>& v1, const T& val);"<<endl;
        v1 = v1 / 2;
        if(v1[0] != -1)
             throw out_of_range("Derived the wrong value");
        cout<<v1<<endl<<endl;

        cout<<"Iterator<T> iterator_begin()"<<endl;
         v2 = {6,7,8,9,100};
        it = v2.iterator_begin();
        if(*it != 6)
             throw out_of_range("Derived the wrong value");
        cout<<*it<<endl<<endl;

        cout<<"Iterator<T> iterator_end() "<<endl;
        it = v2.iterator_end();
        if(*it != 100)
             throw out_of_range("Derived the wrong value");
        cout<<*it<<endl<<endl;

    } catch (out_of_range e) {
        cout << e.what();
    }
    cout<<endl<<"Check_end"<<endl;
    return a.exec();
}
