#include <iostream>
#include <sstream>
#include "graphs.hpp"

int main(int argc, char *argv[])
{
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " n" << std::endl;
    return 1;
  }
  std::istringstream isstr(argv[1]);
  int n;
  isstr >> n;
  Graph* theGraph = new Graph(n);
  theGraph->printAdjacencyList();
  theGraph->printAdjacencyMatrix();
  Graph graphCopy(*theGraph);
  delete theGraph;
  graphCopy.printAdjacencyList();
  graphCopy.printAdjacencyMatrix();
  graphCopy.writeDotFile();
  return 0;
}
