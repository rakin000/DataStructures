#include <iostream> 
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;


class Graph{
    protected:
    const int _V;
    int _E;
    vector<int> *_adj;
    public:

    Graph(int V):
        _V(V),
        _E(0)
    {
        if( V < 0) 
            throw "negative" ;

        _adj = new vector<int>[V];

    }
    Graph(Graph &G):
        _V(G.V()),
        _E(G.E())
    {
        if( _V < 0) throw "negative" ;

        _adj = new vector<int>[_V] ;
        for(int v =0 ;v < G.V(); v++){
            for(int w : G._adj[v] )
                _adj[v].push_back(w);
        }
    }
    ~Graph(){
        delete [] _adj;
    }

    void validateVertex(int v){
        if( v < 0 || v >= _V)
            throw "v";
    }
    void clear(){
        for(int v=0;v<_V;v++)
            _adj[v].clear();
    }

    int V(){ return _V; }
    int E(){ return _E; }

    void addEdge(int v,int w){
        validateVertex(v);
        validateVertex(w);
        _E++;
        _adj[v].push_back(w);
        _adj[w].push_back(v);
    }

    vector<int> adj(int v) {
        validateVertex(v);
        return _adj[v];
    }

    int degree(int v) {
        validateVertex(v);
        return _adj[v].size();
    }    

    friend ostream& operator << (ostream &out, const Graph &G) {
        out << G._V << " vertices, " << G._E <<" edges \n";
        for (int v = 0; v < G._V; v++) {
            out << v << ": ";
            for (int w : G._adj[v]) {
                out << w << " ";
            }
            out << "\n";
        }
        return out ;
    }

 /*   friend istream& operator >> ( istream &in,Graph *G){
        std::cout << "Vertices: \n";
        int V,E;
        in >> V;
        std::cout<< "Edges: \n";
        in >> E;
        std::cout<<"Specify edges....(v w):: \n";
        Graph temp(V);
        for(int e=0;e<E;e++){
            int u,v;
            in >> u >> v;
            temp.addEdge(u,v);
        }

        G = &temp;
        return in;
    }*/
};

class Digraph : public Graph {
    public :
    Digraph(int V):
        Graph(V)
    {}

    Digraph(Digraph &G):
        Graph(G)
    {}
    
    // v to w
    void addEdge(int v,int w) {
        validateVertex(v); validateVertex(w);
        _E++;
        _adj[v].push_back(w);
    }
};


class Edge{
    int v;
    int w;
    double weight_;
    public:
    

    Edge(int v=0,int w=0,double weight=0.0):
        v(v), w(w), weight_(weight)
    {
        if(v < 0) throw "sda";
        if(w < 0) throw "sdsf";
    }

    Edge(const Edge &e):
        Edge(e.v,e.w,e.weight_)
    {

    }
    void operator=(const Edge &e){
        v = e.v;
        w = e.w;
        weight_ = e.weight_;
    }

    int either(){
        return v;
    }

    int other(int vertex){
        if( vertex == v ) return w;
        else if( vertex == w) return v;
        else throw "afsfd";
    }
    double weight(){ return weight_;}

    friend bool operator<(const Edge &e1,const Edge &e2){
        return e1.weight_ < e2.weight_ ;
    }
    friend bool operator>(const Edge &e1,const Edge &e2){
        return e1.weight_ > e2.weight_ ; 
    }
    friend ostream& operator<<(ostream &out, const Edge &E){
        out << E.v << "--" << "(" << E.weight_ << ")" << "--" << E.w ;
        return out;
    } 
};


class EdgeWeightedGraph{
    const int _V;
    int _E;
    vector<Edge> *_adj;

    public :

    EdgeWeightedGraph(int V):
        _V(V),
        _E(0)    
    {
        if( V < 0) throw "Number of vertices must be non zero.";

        _adj = new vector<Edge>[V] ;
    }

    EdgeWeightedGraph(const EdgeWeightedGraph &G):
        _V(G._V),
        _E(G._E)
    {
        _adj = new vector<Edge>[_V];

        for(int v=0;v<_V;v++){
            for(Edge e: G._adj[v])
                _adj[v].push_back(e);
        }
    }


    ~EdgeWeightedGraph(){
        delete [] _adj;
    }

    int V(){ return _V; }
    int E(){ return _E; }

    void validateVertex(int v){
        if( v < 0 || v >= _V)
            throw "Not inside";
    }    
    void clear(){
        for(int v=0;v<_V;v++)
            _adj[v].clear();
    }
    void addEdge(Edge e){
        int v = e.either();
        int w = e.other(v);
        validateVertex(v);
        validateVertex(w);
        _adj[v].push_back(e);
        _adj[w].push_back(e);
        _E++;
    }
    void addEdge(int v,int w,double weight){
        validateVertex(v);
        validateVertex(w);
        Edge e(v,w,weight);
        _adj[v].push_back(e);
        _adj[w].push_back(e);
        _E++;
    }

    vector<Edge>& adj(int v){
        validateVertex(v);
        return _adj[v];
    }

    int degree(int v){
        validateVertex(v);
        return _adj[v].size();
    }

    vector<Edge> edges(){
        vector<Edge> edges ;

        for(int v=0;v<_V;v++){
            int sloops = 0;
            for(Edge &e: _adj[v] ){
                if( e.other(v) > v){
                    edges.push_back(e);
                }
                else if( e.other(v) == v){
                    if( sloops&1 ) edges.push_back(e);
                    sloops++;
                }
            }
        }
        return edges;
    }

    friend ostream& operator << (ostream &out, const EdgeWeightedGraph &G) {
        out << G._V << " vertices, " << G._E <<" edges \n";
        for (int v = 0; v < G._V; v++) {
            out << v << ": ";
            for (Edge &e : G._adj[v]) {
                out << e << " ";
            }
            out << "\n";
        }
        return out ;
    }
};



void randomTreeGenerator(Graph& tree){
    tree.clear();
    vector<int> vertices(tree.V());

    for(int v = 1;v<tree.V();v++){
        int w = rand() % v;
        tree.addEdge(v,w);
    }
}