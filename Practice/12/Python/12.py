def fff(n):
    ff=1
    while n>1:
        ff*=n   
        n-=1    
    return ff

def Zad12():
    while True:
        try:
            n=int(input('>'))
            break
        except:
            print('Неправильный ввод')
            continue

    print(fff(n))

Zad12()
