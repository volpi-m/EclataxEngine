/*
** EPITECH PROJECT, 2019
** IDisplayModule.hpp
** File description:
** IDisplayModule interface
*/

#ifndef IDisplayModule_HPP
#define IDisplayModule_HPP

#include <iostream>
#include <dirent.h>
#include <dlfcn.h>
#include <vector>
#include <string>
#include <memory>

namespace graph {
  enum color { BLACK, WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN};
  enum input { QUIT, EMPTY, MENU, PREVL, NEXTL, PREVG, NEXTG, RESTART, LEFT, RIGHT, UP, DOWN, SPACE, ENTER};
}

class IDisplayModule {

public:
  virtual ~IDisplayModule() = default;
  virtual const std::string &getName() const = 0;
  virtual int detectEvents() = 0;
  virtual void initLibrary() = 0;
  virtual void initWindow() = 0;
  virtual bool isInitialised() = 0;
  virtual void clearWindow() = 0;
  virtual void drawWindow() = 0;
  virtual void disableLib() = 0;
  virtual void changeColor(const std::string &, graph::color) = 0;

  virtual void drawAt(const std::vector<float> &, const std::vector<float> &, const std::string &) = 0;
  virtual void drawText(const std::vector<float> &, const std::string &) = 0;
};

#endif /* !IDisplayModule_HPP */