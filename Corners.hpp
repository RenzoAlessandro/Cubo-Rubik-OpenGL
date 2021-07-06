#ifndef CORNERS_H
#define CORNERS_H

#include "Cube.hpp"
#include "Cross.hpp"

class Corners {

public:
  void solveCorners(TCube&);
  int checkCorners(TCube&);
  int checkBottomLayer(TCube &cube);
  std::string corners_moves;

};

#endif
