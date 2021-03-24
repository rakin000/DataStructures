#include <bits/stdc++.h>

class TST{
    static const int DEFAULT_VALUE = -1;
    class Node{
        public :
        char c;
        int val;
        Node *left,*right,*mid;
        Node(char c){
            this->c = c;
            this->val = DEFAULT_VALUE;
            left = NULL;
            right = NULL;
            mid = NULL;
        }
        ~Node(){
            del(this);
        }
        
        void del(Node *x){
            if(x != NULL){
                del(x->left);
                del(x->mid);
                del(x->right);
            }
            delete x;
        }
    };
    int N = 0;
    Node *root;

    Node* put(Node *x,std::string &s,int &val,int d){
        if( x == NULL){
            x = new Node(s[d]);
        }

        if(s[d] < x->c) x->left = put(x->left,s,val,d);
        else if(s[d] > x->c) x->right = put(x->right,s,val,d);
        else if( d < s.length()-1 ) x->mid = put(x->mid,s,val,d+1);
        else{
            if(x->val == DEFAULT_VALUE) ++N;
            x->val = val;
        }
        return x;
    }
    
    Node* get(Node *x,std::string &s,int d){
        if(x == NULL){
            return NULL;
        }

        if( s[d] < x->c) return get(x->left,s,d);
        else if( s[d] > x->c ) return get(x->right,s,d);
        else if( d < s.length()-1 ) return get(x->mid,s,d+1);
        else return x;
    }

    void collect(std::vector<std::string> &words, std::vector<int> &vals, Node *x, std::string s){
        if( x == NULL) return ;
        collect(words, vals, x->left, s);
        if( x->val != DEFAULT_VALUE ){
            words.push_back(s+x->c);
            vals.push_back(x->val);
        }
        collect(words, vals, x->mid, s+x->c);
        collect(words, vals, x->right,s);
        return ;        
    }

    public:
    TST(){
        root = NULL;
    }   
    ~TST(){
    }

    void clear(){
        // delete root ; this doesn't work... possible explanation: the Node itself deletes itself ;
        root = NULL;
    }
    void put(std::string s,int val){
        root = put(root,s,val,0);
    }
    

    int get(std::string s){
        Node *x = get(root,s,0);
        if( x == NULL) return DEFAULT_VALUE;
        return (x->val) ;
    }

    bool contains(std::string s){
        return get(root,s,0) != NULL; 
    }
    int size(){
        return N;
    }
    void erase(std::string s){
        Node *x = get(root,s,0);
        if(x->val == DEFAULT_VALUE){}
        else {
            --N;
            x->val = DEFAULT_VALUE;
        }

    }

    int operator[](std::string s){
        return get(s);
    }
    std::vector<std::string> prefixWith(std::string s){
        std::vector<std::string> sp;
        std::vector<int> vals;
        Node *x = get(root,s,0); 
        collect(sp, vals, x->mid, s);
        return sp;
    }

    std::vector<std::string> getAll(){
        std::vector<std::string> sp;
        std::vector<int> vals;
        collect(sp, vals, root, "");
        return sp;
    }            
};