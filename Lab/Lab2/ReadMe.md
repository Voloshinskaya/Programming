## Программирование
​Автор: Волашинская Юлия
​<br><h3> Первый семестр </h3>
<p align="center">МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ<br>
Федеральное государственное автономное образовательное учреждение высшего образования<br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"<br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ<br>
Кафедра компьютерной инженерии и моделирования</p>
<br>
<h3 align="center">Отчёт по лабораторной работе № 2<br> по дисциплине "Программирование"</h3>
<br><br>
<p>студента 1 курса группы ИВТ-б-о-201(2)<br>
Волошинской Юлии Евгеньевной<br>
направления подготовки 09.03.01 "Информатика и вычислительная техника"</p>
<br><br>
<table>
<tr><td>Научный руководитель<br> старший преподаватель кафедры<br> компьютерной инженерии и моделирования</td>
<td>(&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br><br>
<p align="center" > Симферополь, 2020</p>
<hr>



<h1>Лабораторная работа №2 Алиса</h1>
   
<h2>Цель работы:</h2>
<ul>
<li>Получить представления о структуре post-запроса;</li>
<li>Изучить webhooks как метод взаимодействия web-приложений;</li>
</ul>

<h2>Постановка задачи</h2>

<ul>
<li>Разработайте и зарегистрируйте навык для Алисы на сервисе ЯндексюДиалоги;</li>
<li>В качестве backend-a для навыка реализуйте приложение на языке С++ выполняющее следующие функции:</li>
<ul>
<li>Составление продуктовой корзины:</li>
<ul>
<li>Добавление продукта в корзину;</li>
<li>Удаление продукта из корзины;</li>
<li>Очистка корзины;</li>
<li>Вывод списка товаров в корзине;</li>
<li>Подсчёт стоимости товаров в корзине.</li>
</ul>
<li>Вывод справочной информации по навыку;</li>
<li>Регистрацию webhook-ов сторонних сервисов;</li>
<li>Отправку данных на сторонние сервисы. </li>
</ul>
<li>В качестве стороннего сервиса реализуйте приложение на языке Python выполняющее следующие функции:</li>
<ul>
<li>Ожидание данных о покупке;</li>
<li>Сохранение поступивших данных в excel-документ.</li>
</ul>
</ul>
Далее указаны все подробности.
<p>&nbsp;&nbsp;&nbsp;&nbsp;</p><br>&nbsp;&nbsp;&nbsp;&nbsp;

<h2>Ход работы</h2>

<p>&nbsp;&nbsp;&nbsp;&nbsp;Я зарегистрировала на ресурсе Яндекс.Диалоги новый диалог c названием "Мазлов Иван Покупки". Также я провела все нужные нам настройки и, конечно,  подключила к нему тунель ngrok.</p>
<p align="center"><img src="image/image1.png"></p>
<p align="center">Рис 1. Настройка диалога.</p>

<p>&nbsp;&nbsp;&nbsp;&nbsp;Для начала я изучила как принцип работы Webhook, а после узнала как с его помощью взаимодействовать с Яндекс-Алисой. В приложении можно найти детальный список ответов от сервиса и список всех необходимых для работы с ним полей.
Далее мне необходимо было написать программный код на с++ для работы с сервисом. Это одна из самых сложных частей работы.</p>

<p>&nbsp;&nbsp;&nbsp;&nbsp;Хочется сказать, что серверный код обслуживает также добавление webhook-ов. Он осуществляет это через post-запросы.</p>

<p align="center"><img src="image/image2.png"></p>
<p align="center">Рис 2. Редактирование webhook-ов.</p>

<p>&nbsp;&nbsp;&nbsp;&nbsp;Далее предоставлен полный текст серверного приложения (с++):</p>


```c++
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
                       u8"Убрать из корзины",   u8"Покупка завершена"};

vector<string> buy_words{ u8"Добавить в корзину", u8"добавить в корзину" };
vector<string> in_korzina_words{u8"Что в корзине", u8"что в корзине"};

string original_utterance = "";

void construct_buttons (vector<string>& vect) {
    if (reply["response"]["buttons"].size() != 0) {
        reply["response"]["buttons"] = json::array();
    }
    for (int i = 0; i < vect.size(); i++) {

        if ((mute && vect[i] == u8"Молчать") || (!mute && vect[i] == u8"Говорить")) continue;

        json bbb = but_shablon;
        //json::object();
        //bbb = json::parse(R"( {"title": "", "hide" : true) })");

        bbb["title"]=vect[i];
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
        json config = json::parse(R"({"webhooks": []})") ;  // создаём новый json конфиг
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

```


<p>&nbsp;&nbsp;&nbsp;&nbsp;Далее предоставлен полный текст серверного приложения (python):</p>  

```python

from openpyxl import Workbook
from openpyxl import load_workbook
from openpyxl.styles import Font, PatternFill, Alignment
from flask import Flask, request
import json
import datetime
import time
Lab2Mazlov   = 'Lab2-Mazlov'
xls_filename = 'data.xlsx'
buffer       = []
max_buffer_size = 2
from openpyxl import Workbook
from openpyxl import load_workbook
from flask import Flask, request
import json
import datetime

file      = 'data_julia.xlsx'
cash      = []
cash_size = 5

app = Flask(__name__)
@app.route('/', methods=['POST'])
def index():
    global cash_size, file, cash

    data = request.json

    for msg in data['check']:
        cash.append( [data['user_id'],
                        str(datetime.datetime.now()),
                        msg['item'],
                        msg['price']
                        ])
        if len(cash) >= cash_size:
            try:
                w_book  = load_workbook(file)
                w_sheet = w_book.active
                w_book.save(file)
                w_book.close()

            except FileNotFoundError:
                w_book = Workbook()
                w_sheet = w_book.active
                w_sheet.append(['N', 'User ID', 'Date time', 'Item', 'Price'])
                w_book.save(file)

            except Exception as e:
                print('Произошла ошибка!', e)
                return "Ok"

            w_book = load_workbook(file)
            w_sheet = w_book.active

            last_raw = w_sheet.max_row

            for new_raw in cash:
                new_raw=[last_raw]+new_raw
                w_sheet.append(new_raw)
                last_raw+=1
            w_book.save(file)
            w_book.close()
            cash=[]

    return "Ok"

if __name__ == "__main__":
    app.run()


if __name__ == "__main__":
    app.run()

```

<h2>Вывод</h2>
<p>&nbsp;&nbsp;&nbsp;&nbsp;В ходе выполнения данной лабораторной работы я ознакомилась с огромным количеством новой информации. Я применила полученную информацию на практике, что позволило лучше разобраться в данной теме. Пришлось ознакомиться с новыми интересными и нужными технологиями. </p>

