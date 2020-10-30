def st(b, n):
    stepen=1
    while n>0:
        stepen*=b
        n-=1
    return stepen


def Zad11():
    while True:
        try:
            b=float(input('>'))
            n=int(input('>'))
            break
        except:
            print('Неправильный ввод')
            continue

    print(st(b, n))

Zad11()