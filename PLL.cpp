#include "PLL.hpp"
#include "Cube.hpp"
#include <iostream>

void PLL::solvePLL(TCube &cube) {
  adjustUFace(cube);
  while (!checkCorners(cube)) {
    solveCorners(cube);
    adjustUFace(cube);
  }

  while (!checkEdges(cube)) {
    solveEdges(cube);
  }
}

void PLL::adjustUFace(TCube &cube) {
  while (cube.cubies[2][5] != 5 || cube.cubies[0][2] != 2) {
    pll_moves += cube.moves("U");
  }
}

void PLL::solveEdges(TCube &cube) {
  if (cube.cubies[1][2] == 5 && cube.cubies[1][3] == 2 && cube.cubies[1][4] == 4 && cube.cubies[1][5] == 3) {
    pll_moves += cube.moves("RRURURRRUUURRRUUURRRURRR");
  }
  else if (cube.cubies[1][2] == 3 && cube.cubies[1][3] == 5 && cube.cubies[1][4] == 4 && cube.cubies[1][5] == 2) {
    pll_moves += cube.moves("RUUURURURUUURRRUUURR");
  }
  else if (cube.cubies[1][2] == 4 && cube.cubies[1][3] == 5 && cube.cubies[1][4] == 2 && cube.cubies[1][5] == 3) {
    pll_moves += cube.moves("RRLLDRRLLUURRLLDRRLL");
  }
  else if (cube.cubies[1][2] == 3 && cube.cubies[1][3] == 2 && cube.cubies[1][4] == 5 && cube.cubies[1][5] == 4) {
    pll_moves += cube.moves("URRRUUURUUURURUUURRRURURRUUURRRU");
  }
  else {
    pll_moves += cube.moves("RRURURRRUUURRRUUURRRURRR");
    adjustUFace(cube);
    pll_moves += cube.moves("RRLLDRRLLUURRLLDRRLL");
    pll_moves += cube.moves("RRURURRRUUURRRUUURRRURRR");
    adjustUFace(cube);
  }
}

void PLL::solveCorners(TCube &cube) {
  if (cube.cubies[2][2] == 4 && cube.cubies[0][3] == 5 && cube.cubies[2][3] == 2
  && cube.cubies[0][4] == 3 && cube.cubies[2][4] == 3 && cube.cubies[0][5] == 4) {
    pll_moves += cube.moves("RRRFRRRBBRFFFRRRBBRR");
  }
  else if (cube.cubies[2][2] == 4 && cube.cubies[0][3] == 5 && cube.cubies[2][3] == 3
  && cube.cubies[0][4] == 4 && cube.cubies[2][4] == 2 && cube.cubies[0][5] == 3) {
    pll_moves += cube.moves("RBBBRRRFRBRRRFFLLLBLFLLLBBBL");
  }
  else {
    pll_moves += cube.moves("RRRFRRRBBRFFFRRRBBRR");
  }
}

int PLL::checkCorners(TCube &cube) {
  if (cube.cubies[0][2] != 2 || cube.cubies[2][2] != 2 || cube.cubies[0][3] != 3 || cube.cubies[2][3] != 3 || cube.cubies[0][4] != 4 || cube.cubies[2][4] != 4 || cube.cubies[0][5] != 5 || cube.cubies[2][5] != 5) {
    return 0;
  }
  else
    return 1;
}

int PLL::checkEdges(TCube &cube) {
    if (cube.cubies[1][2] == 2 && cube.cubies[1][3] == 3 && cube.cubies[1][4] == 4 && cube.cubies[1][5] == 5) {
      return 1;
    }
    else {
      return 0;
    }
}
