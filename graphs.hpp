#ifndef GRAPHS_HPP
#define GRAPHS_HPP

#include <string>
#include <vector>
#include <map>

// simple graph class for now
class Graph {
  public:
    Graph() { nodes_ = readnodes_(); edges_ = readedges_(); }
    Graph(int n) { randomgraph_(n); }
    // Graph(int n, int m);
    Graph(const Graph& g) { copy(g); }
    void printNodes() const { printnodes_(); }
    void printEdges() const { printedges_(); }
    void printGraph() const { printgraph_(); }
    void printAdjacencyList() const { printadjacencymap_(); }
    void printAdjacencyMatrix() const { printadjacencymatrix_(); }
    void writeDotFile() const { writedotfile_(); }
  private:
    std::vector<int> nodes_;
    std::vector<std::pair <int, int> > edges_;
    std::map<int, std::vector<int> > adjacencymap_;
    std::vector<std::vector<int> > adjacencymatrix_;
    void copy(const Graph& g);
    std::vector<int> readnodes_();
    std::vector<std::pair<int, int> > readedges_();
    void randomgraph_(int);
    std::vector<std::pair<int,std::string> > colornodes_() const;
    std::vector<int> degreesort_() const;
    int degree_(int) const;
    std::vector<int> adjacent_(int) const;
    std::vector<int> nonadjacent_(int) const;
    bool adjacentp_(int, int) const;
    bool noneadjacentp_(int, const std::vector<int>&) const;
    void printvector_(const std::vector<int>&) const;
    void printnodes_() const;
    void printedges_() const;
    void printgraph_() const;
    void printadjacencymap_() const;
    void printadjacencymatrix_() const;
    void writedotfile_() const;
};

#endif
