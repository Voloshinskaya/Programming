while True:
    raw=input('Введите через пробел два целых числа : ') 
    raw=raw.split() 
    try:
        a=int(raw[0])
        b=int(raw[1])
        break

    except:
        print(' error!')
        continue
# при помощи доп. переменной
tmp = a
a = b
b = tmp
print(a, b)
# без доп. переменной
a, b = b, a
print(a, b)
