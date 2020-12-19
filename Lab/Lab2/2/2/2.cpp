#include <iostream>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace httplib;
using namespace std;
using json = nlohmann::json;

json config;    // конфигурация webhook
json korzinka;  // корзина товаров
json tovar;     // один товар.
json reply;     // ответ для Алисы
json body;      // ответ от Алисы

string user_id;     // понятно
string session_id;  // сессия
bool mute = false;  // режим для глухонемой Алисы
bool help = false;  // окно помощи активно, заказы не принимаем

json but_shablon = json::parse(u8R"({ "title": " ", "hide" : true })");
vector<string> buy_screen_buttons{ u8"Молчать", u8"Говорить", u8"Помощь" };
vector<string> help_screen_buttons{ u8"Выход из режима справки",
                       u8"Молчать", u8"Говорить", u8"Помощь", u8"Что в корзине",
                       u8"Очистить корзину",    u8"Сумма", "Добавить в корзину",
                       u8"Убрать из корзины",   u8"Покупка завершена" };

vector<string> buy_words{ u8"Добавить в корзину", u8"добавить в корзину" };
vector<string> in_korzina_words{ u8"Что в корзине", u8"что в корзине" };

string original_utterance = "";

void construct_buttons(vector<string>& vect) {
    if (reply["response"]["buttons"].size() != 0) {
        reply["response"]["buttons"] = json::array();
    }
    for (int i = 0; i < vect.size(); i++) {

        if ((mute && vect[i] == u8"Молчать") || (!mute && vect[i] == u8"Говорить")) continue;

        json bbb = but_shablon;
        //json::object();
        //bbb = json::parse(R"( {"title": "", "hide" : true) })");

        bbb["title"] = vect[i];
        reply["response"]["buttons"].push_back(bbb);
    }

}

void check_mute() {
    if (mute) {
        reply["response"]["tts"].get<string>() == "sil <[500]>";
    }
}

void clean_korzinka() {
    korzinka = json::parse(u8R"( { "user_id": "", "check" : [] })");
}
void clean_tovar() {
    tovar = json::parse(u8R"({ "item": "", 
                                "price" : 0 })");
}
void clean_reply() {
    reply = json::parse(u8R"({ "response": { 
                                                "text": " ", 
                                                "tts": " ", 
                                                "buttons": [],
                                                "end_session": false }, 
                                                "version": "1.0"})");
}

// "", если строка не найдена в векторе или то, что нашли
string is_substring(string string_main, vector<string>& vect) {
    string found = "";
    for (int i = 0; i < vect.size(); i++) {
        if (string_main.find(vect[i]) != std::string::npos) {
            found = vect[i];
            break;
        }
    }
    return found;
}

int good_name_position(string data) {
    int cnt = 1;                                 // points to the next token
    while (data.find(" ") != std::string::npos) {
        cnt += 1;
        data.replace(data.find(" "), size(" "), "");
    }
    return cnt;
}


void analize() {

    if (empty(body["session"]["user"]["user_id"])) {
        user_id = "anonymous";
        korzinka["user_id"] = "anonymous";
    }
    else {
        user_id = body["session"]["user"]["user_id"];
        korzinka["user_id"] = body["session"]["user"]["user_id"];
    }

    session_id = body["session"]["session_id"];
    string poisk = "";

    clean_reply();
    original_utterance = body["request"]["original_utterance"].get<string>();

    poisk = is_substring(original_utterance, buy_words);
    if (poisk != "") {                                                  // покупка
        construct_buttons(buy_screen_buttons);

        string what_add = body["request"]["nlu"]["tokens"][good_name_position(poisk)];

        int price = 0;
        for (unsigned i = 0; i < body["request"]["nlu"]["entities"].size(); i++) {
            if (body["request"]["nlu"]["entities"][i]["type"] != "YANDEX.NUMBER") continue;
            price = body["request"]["nlu"]["entities"][i]["value"];
            break;
        }

        if (price == 0) {
            reply["response"]["text"] = u8"Команда не распознана";
            reply["response"]["tts"] = u8"Команда не распознана";
        }
        else {
            clean_tovar();
            tovar["item"] = what_add;
            tovar["price"] = price;
            reply["response"]["text"] = u8"Ok";
            reply["response"]["tts"] = u8"Ok";
            korzinka["check"].push_back(tovar);
        }
        return;
    }

    poisk = is_substring(original_utterance, in_korzina_words);
    construct_buttons(buy_screen_buttons);
    if (poisk != "") {                                      // что в корзине
        int cnt = 0;
        string answ = u8"Товар в корзине:";

        for (unsigned i = 0; i < korzinka["check"].size(); i++) {
            answ.append("\n").append(string(korzinka["check"][i]["item"])).append("\t");
            answ.append(to_string(korzinka["check"][i]["price"]));
            cnt += 1;
        }

        if (cnt == 0) { // если не найдено в корзине
            reply["response"]["text"] = u8"Корзина пуста";
            reply["response"]["tts"] = u8"Корзина пуста";
        }
        else {
            reply["response"]["text"] = answ;
            reply["response"]["tts"] = answ;
        }
        return;
    }

    check_mute();

    if (body["session"]["new"]) {
        construct_buttons(buy_screen_buttons);
        reply["response"]["text"] = u8"Здравствуйте! Я помогу вам с покупками.";
        reply["response"]["tts"] = u8"Здравствуйте! Я помогу вам с покупками.";
    }

}


void gen_response(const Request& req, Response& res) {

    body = json::parse(req.body.c_str());

    analize();

    res.set_content(reply.dump(), "text/json; charset=UTF-8");
}


void gen_responseWebhook(const Request& req, Response& res) {

    if (req.method == "POST" && req.has_param("del")) {
        auto remove_site = req.get_param_value("del");
        for (int i = 0; i < config["webhooks"].size(); i++)  // если пришло удаление, ищем название 
        {                                                    // сата для удаления в config
            if (config["webhooks"][i] == remove_site) {
                config["webhooks"].erase(i);                // стираем его
                break;                                      // выходи - два файла не приходят
            }
            ofstream config_file_new("webhook.json");           // открываем файл для записи
            config_file_new << config;                          // записываем туда конфиг
            config_file_new.close();                            // закрываем файл после записи в него
        }
    }
    else if (req.method == "POST" && req.has_param("set")) {     // надо новый сайт добавить
        auto add_site = req.get_param_value("set");
        config["webhooks"].push_back(add_site);              // добавляем его в конец
        ofstream config_file_new("webhook.json");            // открываем файл для записи
        config_file_new << config;                           // записываем туда конфиг
        config_file_new.close();                             // закрываем файл после записи в него
    }

    ifstream webhookHTML("webhookHTML.html");
    if (!webhookHTML.is_open()) {
        cout << "Ошибка!! webhookHTML.html не найден.\n"; return;
    }

    string webhookHTML_data;
    std::getline(webhookHTML, webhookHTML_data, '\0');  // читаем файл как одну строку, целиком
    webhookHTML.close();                                // закрываем считанный шаблонный файл
    string sites;                                       // тут будем делать вставку сайтов

    for (int i = 0; i < config["webhooks"].size(); i++) {
        sites.append(u8R"(<div class = "form-row align-items-center"><div class = "col"><input type = "text" value = ")").append(config["webhooks"][i]).append(u8R"(" class = "form-control mb-2" disabled></div><div class = "col"><button type = "submit" name = "del" value = ")").append(config["webhooks"][i]).append(u8R"(" class = "btn btn-danger mb-2">Удалить</button></div></div>)");
    }

    webhookHTML_data.replace(webhookHTML_data.find("{webhooks_list}"), size("{webhooks_list}"), sites);
    res.set_content(webhookHTML_data, "text/html; charset=UTF-8");  // ответ на Get запрос
}


int main() {

    ifstream config_file("webhook.json");
    if (!config_file.is_open())
    {
        json config = json::parse(R"({"webhooks": []})");  // создаём новый json конфиг
        ofstream config_file_new("webhook.json");            // открываем файл для записи
        config_file_new << config;                          // записываем туда новый конфиг
        config_file_new.close();                            // закрываем файл после записи в него
    }
    else {                      // если всё в порядке и нашелся конфиг на диске, 
        config_file >> config;  // читаем его
        config_file.close();    // закрываем файл после чтения
    }


    // запускаем сервер
    Server svr;
    svr.Post("/", gen_response);             // сюда присылает Алиса
    svr.Post("/webhooks", gen_responseWebhook); // сюда приходят и Post и Get запросы для редактирования
    svr.Get("/webhooks", gen_responseWebhook);  // конфига webhook
    std::cout << "Start server... OK\n";

    svr.listen("localhost", 3000);         // Запускаем сервер
}
