#include "missileManager.hpp"

bool MissileManager::create(IMissileFactory& factoryType, sf::Vector2f pos, sf::Vector2f dir)
{
    //UWAGA, do funkcji nadal wysylane jest dir a nie moveBy
    sf::Vector2f _moveBy{dir.x - pos.x, dir.y - pos.y};   
    if (_moveBy.x == 0.f && _moveBy.y == 0.f)
        return false;

    if (!rocketTimer.hasTimePassed() || rocket.has_value())
    {
        try
        {
            dynamic_cast<RocketFactory &>(factoryType);
            return false;
        }
        catch (const std::exception &e)
        {
        }
    }

    missiles.push_back(factoryType.create(pos, dir));

    if (dynamic_cast<Rocket*>((missiles.end() - 1)->get()))
    {
        rocket.emplace(static_cast<Rocket*>((missiles.end() - 1)->get()));
        rocketTimer.restart();
    }
    
    //rocket.emplace(static_cast<Rocket*>((missiles.end() - 1)));
    /*try
    {
        //dynamic_cast<RocketFactory&>(factoryType);
        rocket.emplace(dynamic_cast<Rocket*>(missiles.end()->get()));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }*/
    
    //if (dynamic_cast<RocketFactory&>(factoryType))
        //rocket.emplace(static_cast<Rocket*>(missiles.end()->get()));
    return true;
}

void MissileManager::handleEvents(const std::optional<sf::Event>& ev)
{
    for (auto& i : missiles)
        i->handleEvents(ev);
}

void MissileManager::update()
{
    rocketTimer.update();
    for (std::size_t i = 0; i < missiles.size(); i++)
    {
        missiles[i]->update();
        if (missiles[i]->shouldDelete())
        {
            if (rocket.has_value() && dynamic_cast<Rocket*>(missiles[i].get()))
                rocket.reset();
            missiles.erase(missiles.begin() + i);
            i--;
        }
    }
}
