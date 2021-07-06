#ifndef CROSS_H
#define CROSS_H

#include "Cube.hpp"

class Cross {
public:
  void solveCross(TCube&);
  int checkCross(TCube&);
  void solveEdge(TCube&);
  std::string cross_moves;
};

#endif
