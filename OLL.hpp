#ifndef OLL_H
#define OLL_H

#include <iostream>
#include "Cube.hpp"
#include <iostream>

class OLL {

public:
  void solveOLL(TCube&);
  int findState(TCube&); //Rotate U 4 times, check each cube state against file
  int findEdges(TCube&);
  void solveCase(TCube&, int);
  int checkOLL(TCube&);
  int checkEdges(TCube&);
  std::string oll_moves;
};

#endif
