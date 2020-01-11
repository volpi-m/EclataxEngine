/*
** EPITECH PROJECT, 2019
** bootstrap.hpp
** File description:
** bootstrap class
*/

#ifndef SFMLLIB_HPP
#define SFMLLIB_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "IDisplayModule.hpp"

namespace graph {
    class SFML : public IDisplayModule {

     public:
      SFML() : _isInitialised(false), _name("SFML") {initLibrary();}
      ~SFML() final = default;

      // Overriding functions
      const std::string &getName() const final { return _name; };
      int detectEvents() final;
      void initLibrary() final;
      bool isInitialised() final {return _isInitialised;};
      void initWindow() final;

      // Methods
      bool createSprite(const std::string &, const std::string &);
      void setSpriteRect(const std::vector<float> &, const std::string &);
      void setDisplayOptions(int, const std::vector<float> &,
          const std::vector<float> &, const std::string &);
      bool loadAResource(const std::string &);
      void drawAt(const std::vector<float> &, const std::vector<float> &, const std::string &) final;
      void drawText(const std::vector<float> &, const std::string &) final;
      void clearWindow() final;
      void drawWindow() final;
      void disableLib() final {delete _window;};
      void changeColor(const std::string &, graph::color) final;

     private:
      bool _isInitialised;
      std::string _name;
      std::unordered_map<std::string, sf::Sprite> _sprites;
      std::unordered_map<std::string, sf::RectangleShape> _artifacts;
      std::vector<sf::Texture *> _textures;
      sf::Font _font;
      sf::Text _text;
      sf::RenderWindow *_window;
      sf::Event _event;
    };
}

#endif /* !SFMLLIB_HPP */
