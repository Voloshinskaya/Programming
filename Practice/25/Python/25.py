import random


def BozoSort(ar, b=True, c=False, S=True):

    def BozoSortInts(a, b, c, S):
        while True:
            rand_num=random.randint(1,3)
            if rand_num==1:
                a, b = b, a
            if rand_num==2:
                a, c = c, a
            else:
                b, c = c, b

            if S:
                if a<=b and b<=c and a<=c:   break
            else:
                if a>=b and a>=c and b>=c:   break

        return [a,b,c]

    def BozoSortArray1(a, S):
        sorted = False
        while not sorted:
            change1=change2=0
            while change1==change2:
                change1=random.randint(0, len(a)-1)
                change2=random.randint(0, len(a)-1)

            a[change1], a[change2] = a[change2] , a[change1]

            sorted = True

            for i in range(len(a)-1):
                if S and a[i]>a[i+1]:
                    sorted = False
                    break
                elif not S and a[i]<a[i+1]:
                    sorted = False
                    break
        return a

    def BozoSortArray2(a, S):
        sorted = False
        while not sorted:
            x1,y1,x2,y2=0,0,0,0
            while (x1==x2 and y1==y2):
                x1=random.randint(0,len(a[0])-1)
                y1=random.randint(0,len(a)-1)
                x2=random.randint(0,len(a[0])-1)
                y2=random.randint(0,len(a)-1)
            a[y1][x1], a[y2][x2] = a[y2][x2], a[y1][x1]
            sorted = True
            tmp=a[0][0]
            for y in range(len(a)):
                for x in range(len(a[0])):
                    if S and tmp>a[y][x]:
                        sorted = False
                        break
                    elif not S and tmp<a[y][x]:
                        sorted = False
                        break
                    tmp=a[y][x]
                if not sorted: break
        d=[]
        for y in range(len(a)):
            for x in range(len(a[0])):
                d.append(a[y][x])
        return d

    if type(ar)==int and type(b)==int and type(c)==int and type(S)==bool: # 3 int
        return BozoSortInts(ar,b,c,S)
    elif type(ar)==list and type(b)==bool and type(c)==bool and type(S)==bool:
        if type(ar[0])==int:    # одномерный массив
            return BozoSortArray1(ar, b)
        else:                   # двумерный
            return BozoSortArray2(ar, b)
    else:
        print("Ошибочные данные")
        return []

def array_print(a):
    for i in a:
        print(i, " ", sep='', end='')
    print()


n=int(input('Введите n:'))
ar_dim2_size=int(n**0.5)
ar=list(map(int, input().split()))

ar_dim1=ar[:]
array_print(BozoSort(ar_dim1))
ar_dim1=ar[:]
array_print(BozoSort(ar_dim1, False))

ar_dim2=[]
for y in range(ar_dim2_size):
    ar_dim2.append([])
    for x in range(ar_dim2_size):
        ar_dim2[y].append( ar[y*ar_dim2_size+x] )

array_print(BozoSort(ar_dim2))

ar_dim2=[]
for y in range(ar_dim2_size):
    ar_dim2.append([])
    for x in range(ar_dim2_size):
        ar_dim2[y].append( ar[y*ar_dim2_size+x] )

array_print(BozoSort(ar_dim2, False))

a, b, c = ar[:][0], ar[:][1], ar[:][2]
array_print(BozoSort(a, b, c))

a, b, c = ar[:][0], ar[:][1], ar[:][2]
array_print(BozoSort(a, b, c, False))





