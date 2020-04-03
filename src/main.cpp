/**
 *  @file     src/main.cpp
 *  @author   Arthur Lang on the 2020-03-31
 *  @date     2020-03-31
 * 
 *  project: EclataxEngine
 * 
 */

#include "ECS.hpp"

int main(int argc, char const **argv)
{
    Module::EntityComponentSystem ecs;

    std::shared_ptr<ECS::Entity> entity = std::make_shared<ECS::Entity>("tag 1");
    ecs.addEntity(entity);

    std::cout << "Entity tag: " << ecs.entity(1)->tag() << std::endl;

    return 0;
}