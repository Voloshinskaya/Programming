import math
import enum
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
        self.x, self.y = self.r*math.cos(self.phi), self.r*math.sin(self.phi)

    def CalculatePolar(self):
        self.r   = math.sqrt(self.x*self.x + self.y*self.y)
        self.phi = math.atan2(self.y, self.x)

    def __eq__(self, Other):
        return abs(self.x - Other.x)<=delta and abs(self.y - Other.y)<=delta

    def __ne__(self, Other):
        return abs(self.x - Other.x)>delta or abs(self.y - Other.y)>delta

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

### Test part ######################################################
import copy
with open('data.txt') as fin:
    original = [Point(p) for p in fin.readline().split(', ')]
simulacrum = copy.deepcopy(original)

for p in simulacrum:
    print(p, end='')
    p.set_x(p.get_x() + 10)
    p.set_phi(p.get_phi() + 180*math.pi/180)
    p.set_y(-p.get_y())
    p.set_x(-p.get_x() - 10)
    print(p)

print('\nIt works!\n' if simulacrum == original else '\nIt not works!\n')



















#
