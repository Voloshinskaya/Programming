import math, enum

class Cords(enum.IntEnum):
    Cartesian = enum.auto()
    Polar = enum.auto()

delta = 10**-10

class Point():

    def __init__(self, a1=0, a2=0, coord_system=Cords.Cartesian):

        self.r = None
        if isinstance(a1, str):
            try:
                self.x,  self.y = map(float, a1[1:-1].split(','))
                self.CalculatePolar()
            except:
                self.x = 0
                self.y = 0
                self.CalculatePolar()
        elif isinstance(a1, (int, float)) and isinstance(a2, (int, float)):
            if coord_system==Cords.Cartesian:
                self.x = a1
                self.y = a2
                self.CalculatePolar()
            else:
                self.x = a1 * math.cos(a2)
                self.y = a1 * math.sin(a2)
                self.r = a1
                self.phi = a2
        else:
            self.x = 0
            self.y = 0
            self.CalculatePolar()

    def CalculateCartesian(self):
        self.x = self.r * math.cos(self.phi)
        self.y = self.r * math.sin(self.phi)

    def CalculatePolar(self):
        self.r   = math.sqrt(self.x * self.x + self.y * self.y)
        self.phi = math.atan2(self.y, self.x)

    def __eq__(self, d):
        return abs(self.x - d.x) <= delta and abs(self.y - d.y) <= delta

    def __ne__(self, d):
        return abs(self.x - d.x) > delta or abs(self.y - d.y) > delta

    def __repr__(self):
        return "(" + str(self.x) + "," + str(self.y) + ")"

    def __str__(self):
        return "(" + str(self.x) + "," + str(self.y) + ")"

    def get_x(self):
        return self.x

    def get_y(self):
        return self.y

    def get_r(self):
        return self.r

    def get_phi(self):
        return self.phi

    def set_x(self, x):
        self.x = x
        self.CalculatePolar()

    def set_y(self, y):
        self.y = y
        self.CalculatePolar()

    def set_r(self, r):
        self.r = r
        self.CalculateCartesian()

    def set_phi(self, phi):
        self.phi = phi
        self.CalculateCartesian()

##################################### Задание 37 ###################
class Vector():
    def __init__(self, a=None, b=None ):
        if not isinstance(a, Point) and not isinstance(b, Point):
            self.begin = Point(0.0, 0.0)
            self.end = Point(1.0, 0.0)
        elif not isinstance(b, Point):
            self.begin, self.end = Point(0.0, 0.0), a
        else:
            self.begin, self.end = a, b

        self.cord = [self.end.x - self.begin.x, self.end.y - self.begin.y]
        self.len  = math.hypot(*self.cord)
        self.phi  = math.atan2(self.cord[1], self.cord[0])

    def __eq__(self, d):
        return self.cord == d.cord

    def length(self):
        return self.len

    def __mul__(self, d):
        if isinstance(d, (int, float)):
            return Vector(self.begin, Point(self.begin.x + self.cord[0] * d, self.begin.y + self.cord[1] * d))
        elif isinstance(d, Vector):
            return self.len * d.len * math.cos(self.phi - d.phi)
        return self

    def __neg__(self):
        return Vector(self.begin, Point(self.begin.x - self.cord[0], self.begin.y - self.cord[1]))

    def __add__(self, d):
        return Vector(self.begin, Point(self.end.x + d.cord[0], self.end.y + d.cord[1]))

    def __sub__(self, d):
        return self.__add__(d.__neg__())



import math
def equal(a, b, e=1E-10):
    if -e < a - b < e: return True
    else: return False

a = Vector(Point(1, 2))
b = Vector(Point(-2, 0), Point(-1, 2))

if a == b and b == a: print('Equality test passed')
else: print('Equality test failed')

na  = Vector(Point(-1, -2))
ox  = Vector(Point( 1,  0))
nox = Vector(Point(-1,  0))
oy  = Vector(Point( 0,  1))
noy = Vector(Point( 0, -1))

if a == -na and na == -a and -ox == nox and -oy == noy: print('Invert test passed')
else: print('Invert test failed')

if ox + oy + oy == a and -ox == -a + oy + oy: print('Summation test passed')
else: print('Summation test failed')

if -ox + oy == oy - ox and -oy + ox == ox - oy: print('Subtraction test passed')
else: print('Subtraction test failed')

if (ox * 3 == ox + ox + ox and
    oy * 3 == oy + oy + oy and
    ox * (-3) == -ox - ox - ox and
    oy * (-3) == -oy - oy - oy): print('Multiplication by number test passed')
else: print('Multiplication by number test failed')

if (equal(ox.length(), 1) and
    equal(oy.length(), 1) and
    equal((ox * 3 + oy * 4).length(), 5)): print('Length test passed')
else: print('Length test failed')

if (equal(ox*ox, ox.length()**2) and
    equal(oy*oy, oy.length()**2) and
    equal((ox*3 + oy*4)*(ox*3 + oy*4), (ox*3 + oy*4).length()**2)): print('Multiplication by Vector test passed')
else: print('Multiplication by Vector test failed')
