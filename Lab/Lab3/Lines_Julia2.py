import random as rnd 
from tkinter import *
from PIL import Image, ImageTk
class pf():
    def __init__(self, lab, start, end):
        self.found=False                    # пока думаем, что прохода нет, попробуем доказать обратное!
        self.end=end
        self.bad = set()                    # сюда будем прятать все несвободные координаты
        for y in range(len(lab)):           #
            self.bad.add((len(lab[y]), y))  # это своеобразныз "забор" по краям лабиринта: правая
            self.bad.add((-1, y))           # и левая стенки, чтоб не "выпасть" за пределы лабиринта
            for x in range(len(lab[y])):
                self.bad.add((x, -1))       # соответственно верхняя стенка
                self.bad.add((x, len(lab))) # и нижняя стенка "забора". Да!! мы их добавляем много раз, но set() нам это простит :)
                if lab[y][x].color:         # если обнаружен шарик (цвет поля НЕ равен 0),
                    self.bad.add((x, y))    # тоже отправляем его в препятствия
        self.path(start)                    # теперь пробуем продраться через препятствия
    def path(self, point):
        if point==self.end:                 # о! путь найден! останавливаем рекурсию
            self.found=True                 # и выходим с победой!
            return
        x,y=point                           # так... работаем по новой точке.
        self.bad.add(point)                 # запихиваем её в уже занятые раз мы уже на ней стоим
        if (x+1,y) not in self.bad: self.path((x+1,y)) # если можно пойти вправо, идём
        if (x-1,y) not in self.bad: self.path((x-1,y)) # влево, делаем тоже самовызов
        if (x,y+1) not in self.bad: self.path((x,y+1)) # вниз и
        if (x,y-1) not in self.bad: self.path((x,y-1)) # вверх

# Главная процедура проверки нажатий на объекты поля: шарики и пустые клетки
def pole_click(event): #event *args, **kargs
    global pole, selected, etap #print(event.widget.cord) .color
    #print(event.widget.cord, event.widget.color, 'Sel:', '-' if not selected else (selected.cord, selected.color) )
    if gameend!="": return          # конец игры. не обрабатываем поле. ждём пока нажмут "Новая игра"

    x,y=event.widget.cord           # получаем координаты клетки, по которой кликнули
    if event.widget.color:          # click по какому-то шару - цвет шара не равен 0 (0-пустая клетка)
        unselest_ball()             # разпомечаем ранее выбранный шар
        pole[y][x].configure(image=img[event.widget.color][1]) # устанавливаем фон с пометкой на клетке с новым шаром
        selected=event.widget;      # сохраняем новый помеченный шар
        return

    if not event.widget.color and not selected: return # click по пустому полю при невыбранном шаре

    # click по пустому полю и есть выбранный шар. пробуем переставить его на это пустое поле
    lab=pf(pole, selected.cord, (x,y))  # вызываем класс поиска пути, чтоб проверить есть ли проход
    if not lab.found: return            # путь на свободную клетку не найден. выходим

    pole[y][x].color = selected.color   # перемещаем шар на новую позицию
    pole[y][x].configure(image=img[selected.color][0]) # и цвет тоже помечаем
    if line_check((x,y), set([pole[selected.cord[1]][selected.cord[0]]])): balls_add()

def update_score(set_score): # обновляем счёт
    global C, score, count
    score=set_score
    C.delete(count)
    count=C.create_text(90,100, text=str(score), anchor=NW, font="Times 17 bold", fill="white")
    C.update()

def line_check(point, also_del=set()): # проверка линий на заполненность после появления любого шара
    global score, pole
    px, py=point # для удобства сохраняем координаты проверяемого поля в новые переменные
    pc=pole[py][px].color # это цвет шара на нём
    balls_to_del=set() # сюда будем склавывать все найденные для удаления шары
    for vect in ((0, 1),(1, 0),(1, 1),(1, -1)): # четыре линии для проверки: |,-,\,/
        cx=px+vect[0]*(-1)*10                   # уходим по обратному вектору точно за пределы поля,
        cy=py+vect[1]*(-1)*10                   # чтобы захватить все клетки линии
        mark=False                              # это флаг для алгоритма поиска. равен True, если мы уже попадали в область поля хоть раз
        line_balls_to_del=set()                 # временнуй контейнер для удаляемых шаров на одной линии
        while (not mark) or (0<=cx<=8 and 0<=cy<=8): # двигаемся по линии пока не дойдём и не пройдём всё поле навылет
            cx+=vect[0]                         # делаем один
            cy+=vect[1]                         # шажок по вектору
            if 0<=cx<=8 and 0<=cy<=8:           # если мы по координатам находимся в зоне поля
                if pole[cy][cx].color==pc:      # да ещё и цвет совпадает с тем, что мы ищем
                    line_balls_to_del.add(pole[cy][cx]) # срочно помечаем, что этот шар нужно убрать
                else:
                    if len(line_balls_to_del)>=5: break # цвет не совпал. хм. может линия закончилась? выходим
                    else:  line_balls_to_del=set() # так. или это дырка или мы ещё вообще ничего не понаходили. чистим контейнер от неполной линии
                mark=True # надо пометить, что мы уже идем по полю и как встретим "не поле", значит поле уже прошли и надо будет выходить
        balls_to_del|=line_balls_to_del if len(line_balls_to_del)>=5 else set() # если нашли что стирать за время прохода по линии, ссыпаем всё в общий контейнер
    update_score(score+2*len(balls_to_del)) # посчитаем, сколько насобирали шариков: по 2 очка за шар. и обновим счёт на экране
    balls_to_del|=also_del # добавим ещё на удаление тот шар, который мы забыли удалить со старого места, когда перекатывали шар на новое
    for i in balls_to_del: # удаляем все ненужные шары
        i.configure(image=img[0][0]) # картинку
        i.color=0                   # и цвет
    return False if len(balls_to_del)>=5 else True # возвращаем True, если ничего не нашли и надо добавить 3 новых шара на поле

def unselest_ball():
    if selected:                                        # уже есть выбранный шар надо отменить выбор
        sx,sy = selected.cord
        pole[sy][sx].configure(image=img[selected.color][0])

def generate_hlp():
    for i in range(3): # наполняем Позсказку случайными маленькими шариками
        hlp[i].color=rnd.randint(1,7)
        hlp[i].configure(image=img[hlp[i].color][2])

def get_free_cells(): # проверка свободного места на поле
    return [pole[y][x].cord for y in range(9) for x in range(9) if not pole[y][x].color]

def balls_add(*args, **kargs):
    unselest_ball() # разпомечаем шар, если был какой-то помечен
    if gameend!="":             return      # если "конец игры", то никаких новых шаров пусть жмёт на Новая Игра
    if len(get_free_cells())<3: end_game()  # ой, место на поле закончилось - игра закончена
    for i in range(3):                      # Выдаём три шара из Помощи
        free=get_free_cells()               # получаем массив свободных мест на поле
        xp,yp=free[rnd.randint(0,len(free)-1)] # выбираем одно случайное свободное место
        pole[yp][xp].color = hlp[i].color                           # и савим туда
        pole[yp][xp].configure(image=img[pole[yp][xp].color][0])    #   шар из Помощи
        line_check((xp,yp)) # может ему повезло и шар попал и сразу закрыл какую-то линию?
    generate_hlp() # генерируем новую Помощь

def end_game():
    global gameend
    C.delete(gameend) # стираем старую надпись (но, вроде, не должно было быть), если была и выводим печальную новую "Всё проиграли"
    gameend=C.create_text(10,460, text='Всё, проиграли', anchor=NW, font="Times 15 bold", fill="white") # это переводит игру в режим ожидания

def restart_game(*args, **kargs):
    global gameend, pole
    update_score(0) # сбрасываем счёт
    if gameend!="": # устанавливаем режим игры в Игра, убираем надпись Вы проиграли
        C.delete(gameend)
        gameend=""
    for y in range(9):      # чистим поле от остатков прошлой игры
        for x in range(9):
            pole[y][x].color=0
            pole[y][x].configure(image=img[0][0])
    unselest_ball() # чистим помеченный шарик, если он был
    generate_hlp()  # генерируем новую помощь
    balls_add()     # выкатываем на поле три новеньких шарика из Помощи

### Переменные игры ###################################################################################
pole=[]         # массив с Label игрового поля
hlp=[]          # массив из 3-х элементов Помощи (в виде виджета сразу - маленькие такие шарики)
selected=None   # тут храним выбранный шарик (в виде виджета сразу)
score=0         # самая важная переменная!
gameend=""      # это место для надписи "Всё, проиграли". Если оно пусто, игра идёт, если нет, значит ждём пока нажмут Новая Игра

root = Tk()                     # создали окно Tkinter
root.title("Lines 2")           # поменяли название в шапке
root.geometry('850x640+200+100')# установили размер окна 850x640 и чтоб при выводе было посередине 200+100
root.resizable(0, 0)            # нельзя менять размеры окна

bgg=ImageTk.PhotoImage(Image.open(r"page-bgr.png")) # фон окна Tkinter
for y in range(5): # застилаем окно серой плиткой
    for x in range(7):
        Label(root, image=bgg, bd=0).place(x=128*x, y=128*y) #сама плитка

C=Canvas(root, width='150', height='640', bd=0, highlightthickness=0, relief='ridge');
C.place(x=635,y=0) # создаём канвас, чтобы нормально на нём писать, всё, что нужно
for y in range(5):
    C.create_image(  0, y*128, image=bgg, anchor=NW) # и внутри канваса укладываем
    C.create_image(128, y*128, image=bgg, anchor=NW) # такую же серую плитку. Почему она серая, а не розовая? :)

C.create_text(10,40, text='Линии 2', anchor=NW, font="Times 17 bold", fill="white") # надписи разные
C.create_text(10,100, text='Счёт:', anchor=NW, font="Times 17 bold", fill="white")
count=C.create_text(90,100, text='10000', anchor=NW, font="Times 17 bold", fill="white") # это место, где мы будем счёт нисать постоянно

b_img=Image.open("btn_bg.png").crop((0,0,120,35)).convert('RGBA') # пришлось для кнопки сделать картинку
bgg_b=ImageTk.PhotoImage(b_img)
NewTurn=Button(root, text="Сделать ход", font="Times 11", highlightthickness=0, bd=0, image=bgg_b, compound='center', fg='white', padx=0, pady=0)
NewTurn.bind("<Button-1>", balls_add)
NewTurn.place(x=644,y=160) # тут понятно

C.create_text(10,250, text='Подсказка:', anchor=NW, font="Times 13 bold", fill="white")
Restart=Button(root, text="Новая игра", font="Times 15", highlightthickness=0, bd=0, image=bgg_b, compound='center',fg='white', padx=0, pady=0)
Restart.bind("<Button-1>", restart_game)
Restart.place(x=644,y=360) # тут тоже. две кнопки сделали

bgg_c   = Image.open("cell-bgr.png") # это всё как делать картинку для шариков и как большую картинку впихивать
empty   = bgg_c.crop((0, 0,69, 69)).convert('RGBA') # в маленькую даже если она плохо впихивается
empty_s = Image.open("page-bgr.png").crop((0,0,35,35)).convert('RGBA') # почти дословно скоприровано из методички
sel     = bgg_c.crop((0,69,69,138)).convert('RGBA')
img=[[ImageTk.PhotoImage(empty), ImageTk.PhotoImage(empty_s)]]
pic_size_same_as_bgr   = Image.new("RGBA", (69,69))
pic_size_same_as_bgr_s = Image.new("RGBA", (35,35))
for ball_file in ['aqua','blue','green','pink','red','violet','yellow']: # список файлов с шариками
    img.append([])
    ball_img=Image.open('ball-'+ball_file+'.png')

    ball=ball_img.crop((0,0,55,57)).convert('RGBA')                         # вырезали первый шар
    ball_over_bgr = Image.alpha_composite(empty, pic_size_same_as_bgr)
    ball_over_bgr.paste(ball, (5,7), ball)
    img[-1].append(ImageTk.PhotoImage(ball_over_bgr)) # img[0] - картинка с непомеченным большим шариком

    ball_over_bgr = Image.alpha_composite(sel, pic_size_same_as_bgr)
    ball_over_bgr.paste(ball, (5,7), ball)
    img[-1].append(ImageTk.PhotoImage(ball_over_bgr))# img[0] - картинка с помеченным большим шариком

    ball=ball_img.crop((13, 57*3+23, 50,57*4)).convert('RGBA')                         # вырезали малый шар
    ball_over_bgr = Image.alpha_composite(empty_s, pic_size_same_as_bgr_s)
    ball_over_bgr.paste(ball, (5,7), ball)
    img[-1].append(ImageTk.PhotoImage(ball_over_bgr))# img[0] - картинка с маленьким шариком для помощи
pole=[] # формитуем игровое поле и проставляем его пустыми клеточками
for y in range(9):
    pole.append([]) # добавляем новый ряд поля
    for x in range(9):
        pole[y].append(Label(root, image = img[0][0], bd=0))
        pole[y][x].bind("<Button-1>", pole_click) # назначаем функцию при клике на поле (любую клетку)
        pole[y][x].cord = (x,y)     # добавляем дополнительный параметр с координатами клетки
        pole[y][x].color = 0        # и её цветом, чтобы можно было понять, куда преподаватель попал мышкой
        pole[y][x].place(x=x*69+10, y=y*69+10) # метод place оказался удачным решением... как же я намучилась с grid и pack до этого!!!!!!!
hlp=[] # формируем масси Label для Помощи
for i in range(3):
    hlp.append(Label(root, image = img[1][-1], bd=0))   # сама Label
    hlp[i].color = 1                                    # первый попавшийся цвет, всё равно сейчас его при генерации новой помощи затрут
    hlp[i].place(x=640+i*50, y=280)                     # ставим всё это справа

generate_hlp()  # а вот и то, о чём я говорила! затираем старые картинки Помощи и генерируем туда случайные
balls_add()     # добавляем на поле три новеньких блестященьких случайноцветных шарика!
root.mainloop() # Поехали!
