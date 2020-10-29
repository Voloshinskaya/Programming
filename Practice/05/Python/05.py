while True:
    raw=input('Введите через пробел три числа : ') 
    raw=raw.split() 
    try:
        x0, v0, t = map(float, raw)
        break

    except:
        print(' error!')
        continue

a = 9.8
x_new = x0 + v0 * t - a * t * t / 2
print('расстояние=', x_new - x0)
