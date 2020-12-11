def Zadanie_27():
    n=int(input())
    a=list(map(int, input().split()))
    for i in range(1, len(a)+1):
        for j in sorted(a[:i], reverse=True)[-5:]:
            print(j,' ' ,sep='', end='')
        print()


Zadanie_27()
