#pragma once
#include <fstream>
#include <iostream>

class ConfigLoader
{
public:
    ConfigLoader& get()
    {
        static ConfigLoader configLoader;
        return configLoader;
    }

    int asteroidAmount{};
    int asteroidDamage{};
private:
    ConfigLoader()
    {
        std::fstream file{filename, std::ios::in | std::ios::out};
        std::string dump;
        std::string data;
        if (file.is_open())
        {
            std::getline(file, dump, ':');
            std::getline(file, data, ';');
            try
            {
                asteroidAmount = std::stoi(data);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
                asteroidAmount = 100;
            }
        }
    }
    std::string filename{"settings.conf"};
};