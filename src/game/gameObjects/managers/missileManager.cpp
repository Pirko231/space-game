#include "missileManager.hpp"

bool MissileManager::create(IMissileFactory& factoryType, sf::Vector2f pos, sf::Vector2f dir)
{
    //UWAGA, do funkcji nadal wysylane jest dir a nie moveBy
    sf::Vector2f _moveBy{dir.x - pos.x, dir.y - pos.y};   
    if (_moveBy.x == 0.f && _moveBy.y == 0.f)
        return false;

    
    try
    {
        dynamic_cast<MineFactory &>(factoryType);
        if (mineTimer.hasTimePassed())
            mineTimer.restart();
        else
            return false;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
        

    if (!rocketTimer.hasTimePassed() || rocket.has_value())
    {
        try
        {
            dynamic_cast<RocketFactory &>(factoryType);
            if (rocket.has_value())
                rocket.value()->del();
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
    return true;
}

void MissileManager::handleEvents(const Pressed& pressed) const
{
    for (auto& i : missiles)
        i->handleEvents(pressed);
}

void MissileManager::update(bool* rocketRecentlyDeleted)
{
    rocketTimer.update();
    mineTimer.update();
    
    if( rocket.has_value())
    {
        
        rocketTimerText.setString(std::to_string(util::framesToSeconds(rocket.value()->getLifeTime())));
        sf::Vector2f pos {rocket.value()->getGlobalBounds().getCenter()};
        rocketTimerText.setPosition({pos.x - 70.f, pos.y + 30.f});
    }
    for (std::size_t i = 0; i < missiles.size(); i++)
    {
        missiles[i]->update();
        if (missiles[i]->shouldDelete())
        {
            if (rocket.has_value() && dynamic_cast<Rocket*>(missiles[i].get()))
            {
                rocket.reset();
                *rocketRecentlyDeleted = true;
            }
            missiles.erase(missiles.begin() + i);
            i--;
        }
    }
}
