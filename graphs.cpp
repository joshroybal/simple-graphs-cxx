#include <iostream>
#include <fstream>
#include <algorithm>
#include "graphs.hpp"

// public Graph class methods
void Graph::readNodes()
{
  nodes_ = readnodes_();
}

void Graph::readEdges()
{
  edges_ = readedges_();
}

void Graph::randomGraph(int n)
{
  randomgraph_(n);
}

void Graph::printNodes() const
{
  printnodes_();
}

void Graph::printEdges() const
{
  printedges_();
}

void Graph::printGraph() const
{
  printgraph_();
}

void Graph::printAdjacencyMap() const
{
  printadjacencymap_();
}

void Graph::printAdjacencyMatrix() const
{
  printadjacencymatrix_();
}

void Graph::writeDotFile() const
{
  writedotfile_();
}

// private Graph class methods
std::vector<int> Graph::readnodes_()
{
  int n;
  std::cout << "n = ";
  std::cin >> n;
  std::vector<int> v;
  for (int i = 0; i < n; ++i) v.push_back(i);
  for (int i = 0; i < n; ++i) adjacencymap_[i] = std::vector<int>();
  return v;
}

std::vector<std::pair<int, int> > Graph::readedges_()
{
  int m;
  std::cout << "m = ";
  std::cin >> m;
  std::vector<std::pair<int, int> > e;
  for (int i = 0; i < m; ++i) {
    int node1;
    int node2;
    std::cin >> node1 >> node2;
    std::pair<int,int> edge(node1, node2);
    e.push_back(edge);
    adjacencymap_[node1].push_back(node2);
    adjacencymap_[node2].push_back(node1);
  }
  return e;
}

void Graph::randomgraph_(int n)
{
  srand(time(0));
  // int n = 2 + (10 * (rand() / float(RAND_MAX)));
  for (int i = 0; i < n; ++i) nodes_.push_back(i);
  for (int i = 0; i < n; ++i) adjacencymap_[i] = std::vector<int>();
  for (int i = 0; i < n; ++i) adjacencymatrix_.push_back(std::vector<int>());
  for (int i = 0; i < n; ++i) 
    for (int j = 0; j < n; ++j)
      adjacencymatrix_[i].push_back(0);
  for (int i = 0; i < n - 1; ++i)
    for (int j = i + 1; j < n; ++j) {
      int choice = 2 * (rand() / float(RAND_MAX));
      if (choice > 0) {
        std::pair<int,int> edge(i, j);
        edges_.push_back(edge);
        adjacencymap_[i].push_back(j);
        adjacencymap_[j].push_back(i);
        adjacencymatrix_[i][j] = 1;
        adjacencymatrix_[j][i] = 1;
      }
    }
}

std::vector<std::pair<int,std::string> > Graph::colornodes_() const
{
  std::string colors[] = {"red","orange","yellow","green","blue","indigo","violet","brown","cyan","maroon","gray","slategray","darkgray","white","black"};
  std::vector<std::pair<int, std::string> > nodecolors;
  
  std::vector<int> nodes = degreesort_();

  int coloridx = 0;
  while (nodes.size() > 0) {
    // find nodes not adjacent to head of vector
    std::vector<int> tmp = nonadjacent_(nodes.front());
    std::vector<int> assigned;
    std::vector<int>::const_iterator cit;
    for (cit = tmp.begin(); cit != tmp.end(); ++cit) {
      if (std::count(nodes.begin(), nodes.end(), *cit) > 0
          &&
          noneadjacentp_(*cit, assigned) == true) { // assign node color
        nodecolors.push_back(std::pair<int,std::string>(*cit,colors[coloridx]));
        assigned.push_back(*cit);
        nodes.erase(std::remove(nodes.begin(), nodes.end(), *cit), nodes.end());
        if (nodes.size() == 0) return nodecolors;
      }
    }
    ++coloridx;
    if (coloridx == 15) return nodecolors;
  }

  return nodecolors;
}

// no plans for huge graphs so selection sort should be fine
std::vector<int> Graph::degreesort_() const
{
  int n = adjacencymap_.size();
  std::vector<int> index(n);
  for (int i = 0; i < n; ++i) index[i] = i; // initialize index
  if (n <= 1) return index;
  // selection sort
  for (int i = 0; i < n - 1; ++i) {
    int maxidx = i;
    for (int j = i + 1; j < n; ++j) {
      if (adjacencymap_.at(index[j]).size() > adjacencymap_.at(index[maxidx]).size())
        maxidx = j;
    }
    int tmp = index[i];
    index[i] = index[maxidx];
    index[maxidx] = tmp;
  }
  return index;
}

int Graph::degree_(int v) const
{
  return adjacencymap_.at(v).size();
}

std::vector<int> Graph::adjacent_(int v) const
{
  return adjacencymap_.at(v);
}

std::vector<int> Graph::nonadjacent_(int v) const
{ // to be refactored with set_difference
  std::vector<int> res;
  std::vector<int> adj = adjacent_(v);
  std::vector<int>::const_iterator cit;
  for (cit = nodes_.begin(); cit != nodes_.end(); ++cit)
    if (std::count(adj.begin(), adj.end(), *cit) == 0)
      res.push_back(*cit);
  return res;
}

bool Graph::adjacentp_(int v1, int v2) const
{ // careful approach - scan all the edges
  std::pair<int,int> e1(v1, v2);
  std::pair<int,int> e2(v2, v1);
  std::vector<std::pair<int,int> >::const_iterator cit;
  for (cit = edges_.begin(); cit != edges_.end(); ++cit)
    if (*cit == e1 || *cit == e2)
      return true;
  return false;
}

bool Graph::noneadjacentp_(int node, const std::vector<int>& nodes) const
{
  std::vector<int>::const_iterator cit;
  /* for (cit = nodes.begin(); cit != nodes.end(); ++cit)
    if (adjacentp_(node, *cit) == true)
      return false; */
  for (cit = nodes.begin(); cit != nodes.end(); ++cit) {
    if (std::count(adjacencymap_.at(*cit).begin(), adjacencymap_.at(*cit).end(), node) > 0)
      return false;
  }
  return true;
}

void Graph::printvector_(const std::vector<int>& v) const
{
  std::vector<int>::const_iterator cit;
  for (cit = v.begin(); cit != v.end(); ++cit) std::cout << ' ' << *cit;
  std::cout << std::endl;
}

void Graph::printnodes_() const
{
  std::cout << "{";
  std::vector<int>::const_iterator cit;
  for (cit = nodes_.begin(); cit != nodes_.end(); ++cit) {
    std::cout << *cit;
    if (cit + 1 != nodes_.end()) std::cout << ",";
  }
  std::cout << "}" << std::endl;
}

void Graph::printedges_() const
{
  std::cout << "{";
  std::vector<std::pair<int,int> >::const_iterator cit;
  for (cit = edges_.begin(); cit != edges_.end(); ++cit) {
    std::cout << "{" << cit->first << "," << cit->second << "}";
    if (cit + 1 != edges_.end()) std::cout << ",";
  }
  std::cout << "}" << std::endl;
}

void Graph::printgraph_() const
{
  printnodes_();
  printedges_();
}

void Graph::printadjacencymap_() const
{
  std::map<int, std::vector<int> >::const_iterator key;
  std::vector<int>::const_iterator value;
  for (key = adjacencymap_.begin(); key != adjacencymap_.end(); ++key) {
    std::cout << key->first << ": ";
    for (value = key->second.begin(); value != key->second.end(); ++value) {
      std::cout << *value;
      if (value + 1 != key->second.end()) std::cout << ',';
    }
    std::cout << '\n';
  }
}

void Graph::printadjacencymatrix_() const
{
  std::vector<std::vector<int> >::const_iterator row;
  std::vector<int>::const_iterator col; 
  for (row = adjacencymatrix_.begin(); row != adjacencymatrix_.end(); ++row) {
    for (col = row->begin(); col != row->end(); ++col)
      std::cout << ' ' << *col;
    std::cout << std::endl;
  }
}

void Graph::writedotfile_() const
{
  std::vector<std::pair<int,std::string> > nodecolors = colornodes_();
  std::ofstream fout("graph.gv", std::ofstream::out);
  fout << "graph { layout=circo;\n";
  fout << "node [shape=circle margin=0 height=0 width=0 style=filled]";
  std::vector<std::pair<int,int> >::const_iterator eit;
  for (eit = edges_.begin(); eit != edges_.end(); ++eit)
    fout << char(97+eit->first) << " -- " << char(97+eit->second) << '\n';
  std::vector<std::pair<int,std::string> >::const_iterator nit;
  for (nit = nodecolors.begin(); nit != nodecolors.end(); ++nit)
    fout << char(97+nit->first) << " [fillcolor=" << nit->second << "]\n";
  fout << "}" << std::endl;
  fout.close();
  std::cout << "dot data dumped to file graph.gv" << std::endl;
}
