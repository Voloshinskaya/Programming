
from tkinter import *
import requests
import json

def RefreshData(r):
    error=False
    ret={}
    try:
        req = requests.get('http://localhost:3000/raw')
        print(req)
    except:
        error=True
    else:
        if req.status_code!=200:
            print(req.status_code)
            error=True
        else:
            ret = req.json()
            if "temp" not in ret:
                error=True
    if error:
        TownName["text"]="Ошибка"
        Description["text"]="сервер недоступен"
        Temperature["text"]="--°C"
    else:
        TownName["text"]="Симферополь"
        Description["text"]=ret["description"].encode('l1').decode()
        Temperature["text"]=str(int(ret["temp"]))+"°C"

m = Tk()
m.geometry("170x250+300+400")
m.resizable(0, 0)
m.overrideredirect(1)


TownName   =Label(m, text = "", height=1, width=20, bg='orange', font=("Helvetica", 14, 'bold'))
Description=Label(m, text = "", height=1, width=30, bg='orange', font=("Helvetica",  9, 'bold'))
Temperature=Label(m, text = "", height=2, width=10, bg='white' , font=("Helvetica", 48, 'bold'))
LowBlok    =Label(m,            height=3, width=30, bg="orange")

TownName.pack(side=TOP)
Description.pack(side=TOP)
Temperature.pack(side=TOP)
LowBlok.pack(side=BOTTOM)

RefreshData(None)
RefreshData(None)
m.bind("<Button-1>", RefreshData)
mainloop()
