#include <iostream>
#include <locale>
#include "cpp_httplib/httplib.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <stdio.h>
#include <string>

using json = nlohmann::json;
using namespace httplib;

json cash;
int vremya = 0;

int poisk(int time) { //[-1,0,max]
    if (cash.is_null()) { return -1; };
    int index = -1;
    for (int i = 0; i < cash.size(); i++) {
        if (time <= cash["hourly"][i]["dt"].get<int>()) { index = i;  break; }
    }
    return index;
}

//vremya get_vremya()=>> true/false
bool get_vremya() {

    Client vremya_server("http://worldtimeapi.org");
    auto result = vremya_server.Get("/api/timezone/Europe/Simferopol");

    if (result) {
        if (result->status == 200) {
            json worldtime;
            worldtime = json::parse(result->body);
            vremya = worldtime["unixtime"].get<int>();
            return true;
        }
        else std::cout << "Error time server." << result->status << std::endl;
    }
    else {
        auto err = result.error();
        std::cout << "Error code: " << err << std::endl;
    }
    return false;
}

bool get_pogoda() {
    Client pogoda_server("http://api.openweathermap.org");
    auto result = pogoda_server.Get("/data/2.5/onecall?lat=44.9572&lon=34.1108&lang=ru&units=metric&exclude=current,minutely,daily,alerts&appid=6b2179096d37f4e85bd682f63abd3b67");

    if (result) {
        if (result->status == 200) {
            cash = json::parse(result->body);
            return true;
        }
        else std::cout << "Error time server." << result->status << std::endl;
    }
    else {
        auto err = result.error();
        std::cout << "Error code: " << err << std::endl;
    }
    return false;
}

bool raw(const Request& req, Response& res) {

    int now = get_vremya();
    if (!now) { return false; }

    int index = poisk(vremya);
    if (index == -1) {
        if (!get_pogoda()) { return false; }
        index = poisk(vremya);
        if (index == -1) { return false; }
    }
    json reply;
    reply = cash["hourly"][index]["weather"][0];

    reply.push_back({ "temp", cash["hourly"][index]["temp"].get<int>() });

    res.set_content(reply.dump(4), "text/plain");
    return true;
}

bool root(const Request& req, Response& res) {
    int now = get_vremya();
    if (!now) { return false; }

    int index = poisk(vremya);
    if (index == -1) {
        if (!get_pogoda()) { return false; }
        index = poisk(vremya);
        if (index == -1) { return false; }
    }

    std::string wiget_file_name = R"(iframe.html)";

    std::ifstream InFile(wiget_file_name);
    std::string all_line;

    if (InFile.is_open()) {
        getline(InFile, all_line, '\0');
        InFile.close();
    }
    else { return false; }

    std::string srch = "{hourly[i].temp}";
    std::size_t position = all_line.find(srch);
    if (position != std::string::npos)
    {
        all_line.replace(position, srch.size(), std::to_string(cash["hourly"][index]["temp"].get<int>()));
    }

    srch = "{hourly[i].weather[0].icon}";
    position = all_line.find(srch);
    if (position != std::string::npos)
    {
        all_line.replace(position, srch.size(), cash["hourly"][index]["weather"][0]["icon"].get<std::string>());
    }

    srch = "{hourly[i].weather[0].description}";
    position = all_line.find(srch);
    if (position != std::string::npos)
    {
        all_line.replace(position, srch.size(), cash["hourly"][index]["weather"][0]["description"].get<std::string>());
    }

    res.set_content(all_line, "text/html");
    return true;
}


int main() {
    setlocale(LC_ALL, "Russian");

    Server svr;
    svr.Get("/raw", raw);
    svr.Get("/", root);

    std::cout << "Weather server started\n";

    svr.listen("localhost", 3000);
    return 0;
}