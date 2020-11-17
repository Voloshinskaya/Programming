#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

int main()
{
    setlocale(LC_ALL, "Russian");
    std::ifstream in_file("in.json");
    json j2 = json::array();
    if (in_file.is_open());
    {
        std::cout << "Файл открыт:"<< std::endl;
        json j;
        in_file >> j;
        std::cout << j;
    }
    else { cout << "Ошибка! Не удалось открыть файл!" << std::endl; }
    }

}
