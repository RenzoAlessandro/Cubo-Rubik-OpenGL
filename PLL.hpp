#ifndef PLL_H
#define PLL_H

#include "Cube.hpp"

class PLL {

public:
  void solvePLL(TCube &);
  void adjustUFace(TCube &);
  void solveCorners(TCube &);
  int checkCorners(TCube &);
  int checkEdges(TCube &);
  void solveEdges(TCube &);
  std::string pll_moves;
};

#endif
