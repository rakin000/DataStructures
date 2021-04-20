#include <iostream>
#include <exception>
using namespace std;
template<class Type>class stack{
    class node{
        public:
        Type value;
        node *next;

        node(Type value){
            this->value = value;
            next = NULL;
        }
        node(){
            next = NULL;
        }
        ~node(){
          // cout<<"called "<<value<<endl;
            delete next;
        }
    };
    node *_top;
    node *_bottom;
    int N ;
    public:
    stack(){
		_top = NULL;
		_bottom = NULL;
    }
    ~stack(){
        delete _top;
    }
    int size(){
        return N;
    }
    bool empty(){
        return (_top == NULL);
    }
    void push(Type value){
        node *new_top = new node(value);
        if( _top == NULL ){
            _bottom = new_top ;
        }
        new_top->next = _top;
        _top = new_top;
        ++N;
    }
    Type pop(){
        if(_top == NULL) throw underflow_error("empty stack");
        node *old_top = _top ;
        Type val = old_top->value;

        _top = _top->next;
        if( _top == NULL )
            _bottom = NULL;

        old_top->next = NULL;
        delete old;
        --N;
        return val;
    }
    Type& top(){
        if(_top == NULL) throw underflow_error("empty stack");
        return _top->value;
    }
    Type& bottom(){
        if( _bottom == NULL ) throw underflow_error("empty stack");
        return _bottom->value;
    }
};
