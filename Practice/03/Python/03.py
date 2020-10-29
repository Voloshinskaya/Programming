while True:
    raw=input('Введите через пробел целые x1, x2 и вещественные x3, x4: ') 
   
    raw=raw.split() 

    try:
        x1 = int(   raw[0] )
        x2 = int(   raw[1] )
        x3 = float( raw[2] )
        x4 = float( raw[3] )
        if x2==0 or x4==0:
            print('error! x2 и x4 не могут быть нулями!')
            continue
        break

    except:
        print(' error!')
        continue

print()
print('int+int', x1+x2) 
print('int-int', x1-x2) 
print('int*int', x1*x2) 
print('int/int', x1/x2) 
print()
print('float+float', x3+x4) 
print('float+float', x3-x4) 
print('float+float', x3*x4) 
print('float+float', x3/x4) 
print()
print('int+float', x1+x3) 
print('int-float', x1-x3) 
print('int*float', x1*x3) 
print('int/float', x1/x3) 
print()
print('float+int', x3+x1) 
print('float+int', x3-x1) 
print('float+int', x3*x1) 
print('float+int', x3/x1) 