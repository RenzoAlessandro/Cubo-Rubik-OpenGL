#ifndef EDGES_H
#define EDGES_H

#include "Cube.hpp"

class Edges {

public:
  void solveEdges(TCube &cube);
  void solveEdge(TCube &cube);
  int checkEdges(TCube &cube);
  std::string edges_moves;
};

#endif
