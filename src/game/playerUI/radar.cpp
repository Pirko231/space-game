#include "radar.hpp"

Radar::Radar() : sprite{util::AssetLoader::get().radar}
{
    sprite.setScale({0.16f,0.16f});

    p1.setFillColor(sf::Color::Green);
    p1.setSize({2.f,2.f});
    p1.setOrigin(p1.getGlobalBounds().getCenter());

    p2.setSize({2.f,2.f});
    p2.setOrigin(p2.getGlobalBounds().getCenter());
    p2.setFillColor(sf::Color::White);

    rocket.setSize({1.f,1.f});
    rocket.setFillColor(sf::Color::Red);
    
    scale = range / sprite.getGlobalBounds().size.x;
}

void Radar::update(const Player* player, sf::Vector2f viewCenter)
{
    if (viewCenter == sf::Vector2f{})
        viewCenter = player->getCenter();
    if (!p2Pointer)
    {
        if (player == p1Hitbox)
            p2Pointer = p2Hitbox;
        if (player == p2Hitbox)
            p2Pointer = p1Hitbox;
    }

    findTargets(viewCenter);
    removeTargets(viewCenter);
    convertCoordinates(viewCenter);
    manageP2(viewCenter);
    manageRocket(viewCenter);
    p1.setPosition(sprite.getGlobalBounds().getCenter());
}

void Radar::findTargets(sf::Vector2f playerPos)
{
    sf::FloatRect hitbox{{playerPos.x - range / 2.f, playerPos.y - range / 2.f}, {range, range}};
    for (auto& i : asteroids->getAsteroids())
    {
        //zeby uniknac powtorzen
        if (!isRepeated(&i) || currentlyDisplayed.empty())
        {
            //pierwsze wrzucenie do radaru (razem z adresem)
            if (hitbox.findIntersection(i->getGlobalBounds()))
            {
                sf::RectangleShape shape{objectSize};
                currentlyDisplayed.push_back({std::move(shape), &i});
            }
        }
    }
}

void Radar::removeTargets(sf::Vector2f playerPos)
{
    sf::FloatRect hitbox{{playerPos.x - range / 2.f, playerPos.y - range / 2.f}, {range, range}};
    for (std::size_t i = 0; i < currentlyDisplayed.size(); i++)
        if (currentlyDisplayed[i].second->get())
        {
            if (!hitbox.findIntersection(currentlyDisplayed[i].second->operator->()->getGlobalBounds()))
            {
                currentlyDisplayed.erase(currentlyDisplayed.begin() + i);
                i--;
            }
        }
        else
        {
            currentlyDisplayed.erase(currentlyDisplayed.begin() + i);
            i--;
        }
            
}

void Radar::convertCoordinates(sf::Vector2f playerPos)
{
    sf::Vector2f basePos{sprite.getGlobalBounds().getCenter()};
    for (auto& [shape, adress] : currentlyDisplayed)
    {
        sf::Vector2f pos{adress->operator->()->getGlobalBounds().position};
        pos -= playerPos;
        pos /= scale;
        pos += basePos;

        shape.setPosition(pos);
    }
}

void Radar::manageP2(sf::Vector2f playerPos)
{
    sf::FloatRect hitbox{{playerPos.x - range / 2.f, playerPos.y - range / 2.f}, {range, range}};
    sf::Vector2f basePos{sprite.getGlobalBounds().getCenter()};

    if (hitbox.findIntersection(p2Pointer->getGlobalBounds()))
    {
        //wyswietlanie drugiego gracza
        sf::Vector2f p2Pos{p2Pointer->getGlobalBounds().position};
        p2Pos -= playerPos;
        p2Pos /= scale;
        p2Pos += basePos;

        p2.setPosition(p2Pos);
    }
}

void Radar::manageRocket(sf::Vector2f playerPos)
{
    sf::FloatRect hitbox{{playerPos.x - range / 2.f, playerPos.y - range / 2.f}, {range, range}};
    sf::Vector2f basePos{sprite.getGlobalBounds().getCenter()};

    if (!p2Pointer->getMissileManager()->getRocket().has_value())
    {
        drawRocket = false;
        return;
    }
    
    //od tego momentu rakieta ma wartosc
    
    if (hitbox.findIntersection(p2Pointer->getMissileManager()->getRocket().value()->getGlobalBounds()))
    {
        //wyswietlanie rakiety
        sf::Vector2f rocketPos{p2Pointer->getMissileManager()->getRocket().value()->getGlobalBounds().position};
        rocketPos -= playerPos;
        rocketPos /= scale;
        rocketPos += basePos;

        //rocket.setOrigin(p2Pointer->getMissileManager()->getRocket().value()->getGlobalBounds().getCenter());
        rocket.setPosition(rocketPos);
        drawRocket = true;
    }
}

bool Radar::isRepeated(const std::unique_ptr<Asteroid>* obj)
{
    if (!currentlyDisplayed.empty())
        for (auto& [shape, adress] : currentlyDisplayed)
            if (obj == adress)
                return true;
    return false;
}