/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** Mobgenerator definition
*/

#pragma once

/// \namespace Game
/// \brief Used for the game part classes
namespace Game {

    /// \class MobGenerator
    /// \brief Handle all interaction with mob as shared librairies
    class MobGenerator {

        public:
            /// \brief constructor
            /// Initialize MobGenerator class
            MobGenerator();
            /// \brief destructor
            /// Destroy MobGenerator class
            ~MobGenerator();

        private:
            static int difficultie;
            
    };
}