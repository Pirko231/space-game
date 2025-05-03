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

    float musicVolume{100.f};
    int mapSize{1};
    float mapScale{2.f};
    float playerViewZoom{0.15f};
    int asteroidAmount{30};
    int asteroidDamage{30};
    float asteroidHealth{30};
    float throttle{0.005f};
    sf::Angle shipRotationSpeed{sf::degrees(1.f)};
    float health{100.f};
    float energy{100.f};
    float energyRefill{0.1f};
    float range{2000.f};
    float radarObjectSize{2.f};
    float scannerRange{4000.f};
    float scannerObjectSize{1.f};
    float scannerEnergyUse{1.f};
    int shieldProtection{30};
    float shieldEnergyUse{0.5f};
    float laserSpeed{3.f};
    int laserDamage{10};
    float laserLifetime{600.f};
    float rocketSpeed{4.f};
    int rocketDamage{50};
    sf::Angle rocketRotationSpeed{sf::degrees(3.f)};
    int rocketCooldown{10};
    float rocketLifetime{800.f};
    int mineDamage{20};
    float mineLifetime{2000.f};
    int mineCooldown{10};

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
                "Map scale:" << mapScale << ";\n" <<
                "Player view zoom (experimental):" << playerViewZoom << ";\n" <<
                "Asteroid amount:" << asteroidAmount << ";\n" <<
                "Asteroid damage:" << asteroidDamage << ";\n" <<
                "Asteroid health:" << asteroidHealth << ";\n" <<
                "Ship throttle:" << throttle << ";\n" <<
                "Ship rotation speed:" << shipRotationSpeed.asDegrees() << ";\n" <<
                "Player health:" << health << ";\n" <<
                "Player energy:" << energy << ";\n" <<
                "Energy refill:" << energyRefill << ";\n" <<
                "Radar range:" << range << ";\n" <<
                "Radar object size:" << radarObjectSize << ";\n" <<
                "Scanner range:" << scannerRange << ";\n" <<
                "Scanner object size:" << scannerObjectSize << ";\n" <<
                "Scanner energy use:" << scannerEnergyUse << ";\n" <<
                "Shield protection:" << shieldProtection << ";\n" <<
                "Shield energy use:" << shieldEnergyUse << ";\n" <<
                "Laser speed:" << laserSpeed << ";\n" <<
                "Laser damage:" << laserDamage << ";\n" <<
                "Laser lifetime:" << laserLifetime << ";\n" <<
                "Rocket speed:" << rocketSpeed << ";\n" <<
                "Rocket damage:" << rocketDamage << ";\n" <<
                "Rocket rotation speed:" << rocketRotationSpeed.asDegrees() << ";\n" <<
                "Rocket cooldown:" << rocketCooldown << ";\n" <<
                "Rocket lifetime:" << rocketLifetime << ";\n" <<
                "Mine damage:" << mineDamage << ";\n" <<
                "Mine lifetime:" << mineLifetime << ";\n" <<
                "Mine cooldown:" << mineCooldown << ";\n";
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
                mapScale = std::stof(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                playerViewZoom = std::stof(data);
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
                asteroidHealth = std::stof(data);
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
                shipRotationSpeed = sf::degrees(std::stof(data));
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
                energyRefill = std::stof(data);
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
                radarObjectSize = std::stof(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                scannerRange = std::stof(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                scannerObjectSize = std::stoi(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                scannerEnergyUse = std::stof(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                shieldProtection = std::stoi(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                shieldEnergyUse  = std::stof(data);
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
                laserLifetime = std::stof(data);
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
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                mineDamage = std::stoi(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                mineLifetime = std::stof(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
            }
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                mineCooldown = std::stoi(data);
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