/*
** EPITECH PROJECT, 2019
** SFML.cpp
** File description:
** SFML object
*/

#include <cstring>
#include "SFML.hpp"

extern "C" IDisplayModule *entryPoint()
{
    return new graph::SFML;
}

/*
 * detectEvents -> void
 * detect all events related to the game library
 */

int graph::SFML::detectEvents()
{
  while (_window->pollEvent(_event)) {
    if (_event.type == sf::Event::Closed
        || (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape))
      return graph::input::QUIT;
    else if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Tab)
      return graph::input::MENU;
    else if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::A)
      return graph::input::PREVL;
    else if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::P)
      return graph::input::NEXTL;
    else if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Q)
      return graph::input::PREVG;
    else if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::M)
      return graph::input::NEXTG;
    else if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::R)
      return graph::input::RESTART;
    else if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Left)
      return graph::input::LEFT;
    else if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Right)
      return graph::input::RIGHT;
    else if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Up)
      return graph::input::UP;
    else if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Down)
      return graph::input::DOWN;
    else if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Space)
      return graph::input::SPACE;
    else if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Enter)
      return graph::input::ENTER;
  }
  return graph::input::EMPTY;
}

/*
 * loadAResource -> const std::string &
 * Loads a sprite into memory when needed by the library
 */

bool graph::SFML::loadAResource(const std::string &name)
{
  DIR *dir = opendir("./resources");
  struct dirent *stream = nullptr;

  if (!dir) {
    std::cerr << "Error : resources folder not found." << std::endl;
    return false;
  }
  stream = readdir(dir);
  for (; stream; stream = readdir(dir)) {
    if (std::strcmp(stream->d_name, ".") && std::strcmp(stream->d_name, "..")) {
      std::string str("./resources/");
      str += stream->d_name;
      if (!std::strncmp(stream->d_name, name.c_str(), name.size())) {
        if (createSprite(name, str)) {
          closedir(dir);
          return true;
        }
      }
    }
  }
  closedir(dir);
  return false;
}

/*
 * initLibrary -> void
 * initialise resources needed by the library
 */

void graph::SFML::initLibrary()
{
  if (!_font.loadFromFile("resources/pixelsix00.ttf"))
    return;
  _text.setFont(_font);
  _text.setString("");
  _text.setCharacterSize(20);
  _isInitialised = true;
}

/*
 * createSprites -> std::vector<std::string>
 * create all sprites needed by the program
 */

bool graph::SFML::createSprite(const std::string &resource, const std::string &path)
{
  sf::Sprite s;
  auto t = new sf::Texture;

  if (!t->loadFromFile(path))
    return false;
  _textures.push_back(t);
  _sprites.insert({resource, s});
  _sprites.at(resource).setTexture(*_textures.at(_textures.size() - 1));
  return true;
}

/*
 * initWindow -> void
 * Initialise window from the library
 */

void graph::SFML::initWindow()
{
  _window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "SFML window");
  _window->pollEvent(_event);
}

/*
 * drawAt -> const std::vector<int> & -> const std::vector<int> & -> const std::string &
 * Draws a sprite on the window / draw an artifact if the resource cannot be found
 */

void graph::SFML::drawAt(const std::vector<float> &coords, const std::vector<float> &size, const std::string &name)
{
  if (_sprites.find(name) == _sprites.end()) {
    if (_artifacts.find(name) != _artifacts.end()) {
      setDisplayOptions(1, coords, size, name);
      return;
    } else if (!loadAResource(name)) {
      if (_artifacts.find(name) == _artifacts.end()) {
        sf::RectangleShape shape((sf::Vector2f) {10.0f, 10.0f});
        shape.setFillColor(sf::Color(255, 0, 127));
        shape.setPosition(coords.at(0), coords.at(1));
        _artifacts.insert({name, shape});
      }
      _window->draw(_artifacts.at(name));
      return;
    }
  }
  setDisplayOptions(0, coords, size, name);
}

void graph::SFML::setDisplayOptions(int object, const std::vector<float> &coords,
                                    const std::vector<float> &size, const std::string &name)
{
  std::vector<float> coordsCpy(coords);
  sf::Vector2f v;
  int mul_x = coordsCpy.at(0) < 0 ? 1 : 20, mul_y = coordsCpy.at(1) < 0 ? 1 : 20;

  if (coords.at(0) < 0 || coords.at(1) < 0) {
    sf::FloatRect re = object == 1 ? _sprites.at(name).getLocalBounds() : _artifacts.at(name).getLocalBounds();
    sf::Vector2u sz = _window->getSize();

    coordsCpy.at(0) = coordsCpy.at(0) < 0 ? sz.x / 2 - re.width / 2 : coordsCpy.at(0);
    coordsCpy.at(1) = coordsCpy.at(1) < 0 ? sz.y / 2 - re.height / 2 : coordsCpy.at(1);
  }
  if (object == 0) {
    if (size.size() == 4)
      setSpriteRect(size, name);
    else
      _sprites.at(name).setScale(size.at(0), size.at(1));
    v = _sprites.at(name).getPosition();
    _sprites.at(name).move(coordsCpy.at(0) * mul_x - v.x, coordsCpy.at(1) * mul_y - v.y);
    _window->draw(_sprites.at(name));
  } else {
    v = _artifacts.at(name).getPosition();
    _artifacts.at(name).move(v.x - coordsCpy.at(0) * mul_x, v.y + coordsCpy.at(1) * mul_y);
    _artifacts.at(name).setScale(size.at(0), size.at(1));
    _window->draw(_artifacts.at(name));
  }
}

void graph::SFML::setSpriteRect(const std::vector<float> &size, const std::string &name)
{
  sf::IntRect rect = {(int)size.at(0), (int)size.at(1), (int)size.at(2), (int)size.at(3)};

  _sprites.at(name).setTextureRect(rect);
}

/*
 * drawText -> const std::vector<int> & -> const std::string &
 * draw a text at coords. Current position is multiplied by ten
 */

void graph::SFML::drawText(const std::vector<float> &coords, const std::string &txt)
{
  std::vector<float> coordsCpy(coords);
  int mul_x = coordsCpy.at(0) < 0 ? 1 : 20, mul_y = coordsCpy.at(1) < 0 ? 1 : 20;

  _text.setString(txt);
  if (coords.at(0) < 0 || coords.at(1) < 0) {
    sf::Vector2u sz = _window->getSize();
    sf::FloatRect re = _text.getLocalBounds();

    coordsCpy.at(0) = coordsCpy.at(0) < 0 ? sz.x / 2 - re.width / 2 : coords.at(0);
    coordsCpy.at(1) = coordsCpy.at(1) < 0 ? sz.y / 2 - re.height / 2 : coords.at(1);
    _text.setPosition(coordsCpy.at(0) * mul_x, coordsCpy.at(1) * mul_y);
  } else
    _text.setPosition(coordsCpy.at(0) * mul_x, coordsCpy.at(1) * mul_y);
  _window->draw(_text);
}

/*
 * clearWindow -> void
 * clears window
 */

void graph::SFML::clearWindow()
{
  _window->pollEvent(_event);
  _window->clear();
}

/*
 * drawWindow -> void
 * draw windows content
 */

void graph::SFML::drawWindow()
{
  _window->display();
}

void graph::SFML::changeColor(const std::string &name, graph::color color)
{
  if (_sprites.find(name) != _sprites.end()) {
    switch (color) {
      case graph::color::BLACK: _sprites.at(name).setColor(sf::Color::Black);
        break;
      case graph::color::WHITE: _sprites.at(name).setColor(sf::Color::White);
        break;
      case graph::color::RED: _sprites.at(name).setColor(sf::Color::Red);
        break;
      case graph::color::GREEN: _sprites.at(name).setColor(sf::Color::Green);
        break;
      case graph::color::BLUE: _sprites.at(name).setColor(sf::Color::Blue);
        break;
      case graph::color::YELLOW: _sprites.at(name).setColor(sf::Color::Yellow);
        break;
      case graph::color::MAGENTA: _sprites.at(name).setColor(sf::Color::Magenta);
        break;
      case graph::color::CYAN: _sprites.at(name).setColor(sf::Color::Cyan);
        break;
    }
  }
};