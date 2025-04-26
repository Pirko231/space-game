#pragma once
#include <fstream>
#include <iostream>

namespace util
{
class ConfigLoader
{
    std::string filename{"settings.conf"};
public:
    static ConfigLoader& get()
    {
        static ConfigLoader configLoader;
        return configLoader;
    }

    int mapSize{1};
    int asteroidAmount{100};
    int asteroidDamage{30};
    float throttle{0.005f};
    float range{2000.f};
    float health{100.f};
    float energy{100.f};
    float laserSpeed{3.f};
    int laserDamage{10};
    float rocketSpeed{4.f};
    int rocketDamage{50};
    sf::Angle rocketRotationSpeed{sf::degrees(3.f)};
    int rocketCooldown{10};
    float rocketLifetime{800.f};

    ~ConfigLoader()
    {
        //std::fstream file;
        //file.open(filename, std::ios::in);
        std::ofstream stream(filename, std::ios::trunc | std::ios::out);
    if (stream.good())
    {
        stream << "DANGER - modification of special characters might result in program malfunction. In that case delete this file.\n!--------------Settings--------------!\n";
            stream << 
                "Map size:" << mapSize << ";\n" <<
                "Asteroid amount:" << asteroidAmount << ";\n" <<
                "Asteroid damage:" << asteroidDamage << ";\n" <<
                "Ship throttle:" << throttle << ";\n" <<
                "Radar range:" << range << ";\n" <<
                "Player health:" << health << ";\n" <<
                "Player energy:" << energy << ";\n" <<
                "Laser speed:" << laserSpeed << ";\n" <<
                "Laser damage:" << laserDamage << ";\n" <<
                "Rocket speed: " << rocketSpeed << ";\n" <<
                "Rocket damage: " << rocketDamage << ";\n" <<
                "Rocket rotation speed: " << rocketRotationSpeed.asDegrees() << ";\n" <<
                "Rocket cooldown: " << rocketCooldown << ";\n" <<
                "Rocket lifetime: " << rocketLifetime << ";\n";
    }
    else 
    {
        std::cerr << "Couldn't open file\n";
    }
    stream.close();
    }
private:
    ConfigLoader()
    {
        std::fstream file;
        file.open(filename, std::ios::in | std::ios::out);
        std::string dump;
        std::string data;
        if (file.is_open())
        {
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                mapSize = std::stoi(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                asteroidAmount = std::stoi(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                asteroidDamage = std::stoi(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                throttle = std::stof(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                range = std::stof(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                health = std::stof(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                energy = std::stof(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                laserSpeed = std::stof(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                laserDamage = std::stoi(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                rocketSpeed = std::stof(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                rocketDamage = std::stoi(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                rocketRotationSpeed = sf::degrees(std::stof(data));
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                rocketCooldown = std::stoi(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                rocketLifetime = std::stof(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }

            file.close();
        }
        else
            std::cerr << "Config File could not open";
    }
    
};

};