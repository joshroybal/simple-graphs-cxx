#ifndef GRAPHS_HPP
#define GRAPHS_HPP

#include <vector>
#include <map>

// simple graph class for now
class Graph {
  public:
    void readNodes();
    void readEdges();
    void randomGraph(int);
    void printNodes() const;
    void printEdges() const;
    void printGraph() const;
    void printAdjacencyMap() const;
    void printAdjacencyMatrix() const;
    void writeDotFile() const;
  private:
    std::vector<int> nodes_;
    std::vector<std::pair <int, int> > edges_;
    std::map<int, std::vector<int> > adjacencymap_;
    std::vector<std::vector<int> > adjacencymatrix_;
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
