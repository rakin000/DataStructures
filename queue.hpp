#include <iostream>
#include <exception>
using namespace std;

template<class T> class queue{
    struct node{
        T value;
        node *next;

        node(T value){
            this->value = value;
            next = NULL;
        }
        node(){
            next = NULL;
        }
        ~node(){
            delete next ;
        }
    };
    node *_front;
    node *_back;
    int N;
    public:
    queue(){
        _front = NULL;
        _back = NULL;
        N = 0;
    }
    ~queue(){
        /* ... */
        delete _front;
    }

    int size(){
        return N;
    }
    bool empty(){
        return (_front == NULL);
    }
    void push(T value){
        if( _front == NULL ){
            _front = new node(value);
            _back = _front ;
        }
        else {
            _back->next = new node(value);
            _back = _back->next;
        }
        ++N;
    }
    T pop(){
        if(_front == NULL) throw underflow_error("empty queue");
        T temp = _front->value;
        _front = _front->next;
        --N;
        return temp;
    }
    T& front(){
        if(_front == NULL) throw underflow_error("empty queue");
        return _front->value;
    }
    T& back(){
        if( _back == NULL ) throw underflow_error("empty queue");
        return _back->value;
    }
};

template<class T> class array_queue{
    static int const CAPACITY = 4;
    int _front;
    int _back;
    int cap ;
    int N ;
    T *a;
    public:
    array_queue(int cap=CAPACITY){
        this->cap = cap;
        N = 0;
        a = new T[cap];
        _front = 0;
        _back = 0;
    }
    ~array_queue(){
        delete [] a;
    }

    int size(){
        return N;
    }
    bool empty(){
        return (N==0);
    }
    void push(T value){
        if( size() == cap ){
            int nCap = 2*cap;
            T* temp = new T[nCap];
            int i=0;
            temp[i++] = a[_front]; // when full, front == back... 
            _front = (_front+1)%cap;
            while( _front != _back ){
                temp[i++] = a[_front];
                _front=(_front+1)%cap;
            }

            delete [] a;
            a = temp;
            cap = nCap;
            _front = 0;
            _back = i;
        }

        a[_back] = value;
        _back = (_back+1)%cap;
        ++N;
    }
    T pop(){
        if( empty() ) throw underflow_error("empty queue");

        if( size() > CAPACITY && size() == cap/4 ){            
            int nCap = (cap/2 > CAPACITY) ? cap/2: CAPACITY;
            T* temp = new T[nCap] ;
            int i=0;
            while( _front != _back ){
                temp[i++] = a[_front];
                _front = (_front+1)%cap;
            }

            delete [] a;
            a = temp;
            cap = nCap;
            _front = 0;
            _back = i;
        }

        T t = a[_front];
        _front = (_front+1)%cap;
        --N;
        return t;
    }
    T& front(){
        cout<<_front<<endl;
        if( empty() ) throw underflow_error("empty queue");
        return a[_front];
    }
    T& back(){
        cout<<_back<<endl;
        if( empty() ) throw underflow_error("empty queue");
        return a[_back] ;
    }
};


void test(){
    // testing ;

    queue<int> qq;
    array_queue<int> q;

    while(1){



    }
}