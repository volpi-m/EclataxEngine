/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** BeeSwarm
*/

#ifndef BEESWARM_HPP_
#define BEESWARM_HPP_

#include "Bee.hpp"
#include "SpawnerComponent.hpp"

namespace Game
{
    /// \class BeeSwarm
    /// \brief spawner for many bees
    class BeeSwarm : public IEnnemy
    {
    public:
        /// \brief Constructor
        BeeSwarm() = default;

        /// \brief Destructor
        ~BeeSwarm() = default;

        /// \brief Initilalize an entity
        /// \return a pointer to the new entity
        ECS::Entity *createEntity() override;

    private:
        /// \brief IA of entity, move the hive in a circular pattern
        /// \param entity : reference to an instance of this class
        static void IA(std::shared_ptr<ECS::Entity> &entity);
    };
}

#endif /* !BEESWARM_HPP_ */
