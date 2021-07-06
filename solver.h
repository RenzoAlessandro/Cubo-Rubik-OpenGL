#ifndef SOLVER_H
#define SOLVER_H
#include "Cube.hpp"
#include "Cross.hpp"
#include "Corners.hpp" // Aristas - Cruz Blanca
#include "Edges.hpp"   // Aristas - Primeras dos Capas F2L
#include "OLL.hpp"     // Orientacion de la ultima capa
#include "PLL.hpp"     // Permutacion de la ultima capa
#include <iostream>
#include <vector>

size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}

std::string format(std::string s) {
  std::string formatted;

  for (int i=0; i<s.length(); ++i) {
    if (s[i] == '\'') {
      formatted += s[i-1];
      formatted += s[i-1];
    }
    else if (s[i] == '2') {
      formatted += s[i-1];
    }
    else if (s[i] == ' ') {

    }
    else {
      formatted += s[i];
    }
  }

  return formatted;

}


std::vector<std::string> process(std::string argString){
  TCube myCube(false);
  Cross cross;
  Corners corners;
  Edges edges;
  OLL oll;
  PLL pll;
  std::string scramble = format(argString);
  myCube.moves(scramble);
  cross.solveCross(myCube);
  corners.solveCorners(myCube);
  edges.solveEdges(myCube);
  oll.solveOLL(myCube);
  pll.solvePLL(myCube);

  std::string Cross_string = cross.cross_moves;
  std::string F2L_string   = corners.corners_moves + edges.edges_moves;
  std::string OLL_string   = oll.oll_moves;
  std::string PLL_string   = pll.pll_moves;

  std::string FridrichSolve = Cross_string + F2L_string + OLL_string + PLL_string;

  std::cout << "\033[93mSECUENCIA DE FRIDRICH:\033[0m" << std::endl;
  std::cout <<   "\033[96mPASO 1. Cruz Blanca: \033[0m\n" + Cross_string +
               "\n\033[96mPASO 2. Primeras dos Capas (F2L): \033[0m\n" + F2L_string +
               "\n\033[96mPASO 3. Orientacion de la ultima capa (OLL): \033[0m\n" + OLL_string +
               "\n\033[96mPASO 4. Permutacion de la ultima capa (PLL): \033[0m\n" + PLL_string +
               "\n------------------------------------------------------------------------" << std::endl;

  std::vector<std::string> in;
  split(FridrichSolve, in, ' ');
  return in;
}

#endif SOLVER_H