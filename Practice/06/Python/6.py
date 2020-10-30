

def KvUr():
    res=''
    while True:
        try:
            a, b, c = map(float, input('Введите a, b, c: ').split())
            break

        except:
            print('Ошибка ввода.\n')
            continue
    if a==0:
        if b!=0:
            res='x = ' + str(-c/b)
        else: # b==0
            if c==0:
                res='x - любое число.'
            else: #c!=0
                res='такого не может быть. ' + str(c) + ' не равно 0.'

    else: # a!=0 - т.е. это квадратное уравнение.
        D = b*b - 4*a*c # дискриминант

        if D<0:
            res='уравнение не имеет действительных корней.'
        elif D==0:
            rtes='x = ' + str(-b/2/a) #   -b/(2*a)   -b*0.5/a)
        else:
            res='x1 = ' + str(   (-b - (D**0.5) ) / a * 0.5 )
            res=res + '\nx2 = ' + str(   (-b + (D**0.5) ) / a * 0.5 )

    print(res)


KvUr()
