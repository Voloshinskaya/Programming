#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
//#include <sstream> // adds: std::stringstream

using json = nlohmann::json;
using namespace std;


int main()
{
    setlocale(LC_ALL, "Russian");
    // динамические массивы и вектора и как с ними работать пока изучаю. 
    // этот массив пришлось захардкорить на 15 int-ов, 
    // т.е. "userId">14 уже не будет работать...

    int ar[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

    //std::ifstream inFile;
    //inFile.open("in.json");
    //std::stringstream strStream;
    //strStream << inFile.rdbuf();
    //std::string str = strStream.str();
    //json j = json::parse(str);

    std::ifstream inFile("in.json");
    json j;
    inFile >> j;

    for (int i = 0; i < j.size(); i++) {
        if (j[i]["completed"].get<bool>()) {
            ar[j[i]["userId"].get<int>()] += 1;
        }
    }

    json j2 = json::array();

    for (int i = 0; i < sizeof(ar) / sizeof(int); i++) {
        if (ar[i]) {
            j2.push_back({ {"task_completed", ar[i] } , {"userId", i } }); // тут всё в порядке. без null

            // закомменченый вариант давал всё время null в начале j2. почему?
            //j2[i] = json::object();
            //j2[i].push_back({ "task_completed", ar[i] }); j2[i].push_back({ "userId", i });
        }
    }

    std::cout << j2.dump(4);

    std::ofstream outFile("out.json"); //std::fstream stream("out.json");
    outFile << j2;
    return 0;
}
