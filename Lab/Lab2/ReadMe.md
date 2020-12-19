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
<p align="center"><img src=""></p>
<p align="center">Рис 2. Демонстрация работы кода.</p>

<p>&nbsp;&nbsp;&nbsp;&nbsp;Хочется сказать, что серверный код обслуживает также добавление webhook-ов. Он осуществляет это через post-запросы.</p>

<p align="center"><img src="image/image4.png"></p>
<p align="center">Рис 3. Редактирование webhook-ов.</p>

<p align="center"><></p>
<p align="center">Рис 4. Внешний вид таблички заказов.</p>

<p>&nbsp;&nbsp;&nbsp;&nbsp;Далее предоставлен полный текст серверного приложения (с++):</p>


```c++

#include <iostream> //#include <cmath> //#include <iomanip>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
using namespace httplib;
using json = nlohmann::json;

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

