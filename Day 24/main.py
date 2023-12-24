from sympy import Symbol, nonlinsolve


x1, y1, z1 = 19, 13, 30
x2, y2, z2 = -2,  1, -2
x3, y3, z3 = 18, 19, 22
x4, y4, z4 =-1, -1, -2
x5, y5, z5 = 20, 25, 34
x6, y6, z6 =  -2, -2, -4
x7, y7, z7 = 12, 31, 28
x8, y8, z8 = -1, -2, -1

# Doesn't work??
x1, y1, z1 = 277903024391745, 368934106615824, 298537551311799
x2, y2, z2 =  -118, -107, 62

x1,y1,z1=213887387271813, 253994341853086, 349358413004203
x2, y2,z2= 32, 34, -68
x3, y3, z3 = 183412557215942, 418647008376557, 219970939624628
x4, y4, z4 = 72, -215, 133
x5, y5, z5 = 378231151165434, 338743238211338, 302779683441821
x6, y6, z6 = -118, -260, -344
x7, y7, z7 = 344747694290499, 385775363283903, 141297854009676
x8, y8, z8 = -5, -417, 277
t1, t2, t3, t4, k, r = Symbol("t1"), Symbol("t2"), Symbol("t3"), Symbol("t4"), Symbol("k"), Symbol("r")

f1 = x3 - x1 + x4 * t2 - t1 * x2 + k * (x1 - x5) + k * (t1 * x2 - x6 * t3)
f2 = y3 - y1 + y4 * t2 - t1 * y2 + k * (y1 - y5) + k * (t1 * y2 - y6 * t3)
f3 = z3 - z1 + z4 * t2 - t1 * z2 + k * (z1 - z5) + k * (t1 * z2 - z6 * t3)

f4 = x3 - x1 + x4 * t2 - t1 * x2 + r * (x1 - x7) + r * (t1 * x2 - x8 * t4)
f5 = y3 - y1 + y4 * t2 - t1 * y2 + r * (y1 - y7) + r * (t1 * y2 - y8 * t4)
f6 = z3 - z1 + z4 * t2 - t1 * z2 + r * (z1 - z7) + r * (t1 * z2 - z8 * t4)

s=list(nonlinsolve([f1, f2, f3, f4, f5, f6], [t1, t2, t3, t4, k, r]))[0]
s=[float(x) for x in s]
print(f"Point 1 at time {s[0]} is at {x1+x2*s[0]}, {y1+y2*s[0]}, {z1+z2*s[0]}")
print(f"Point 2 at time {s[1]} is at {x3+x4*s[1]}, {y3+y4*s[1]}, {z3+z4*s[1]}")
print(f"Point 3 at time {s[2]} is at {x5+x6*s[2]}, {y5+y6*s[2]}, {z5+z6*s[2]}")
print(f"Point 4 at time {s[3]} is at {x7+x8*s[3]}, {y7+y8*s[3]}, {z7+z8*s[3]}")

vx = (x3+x4*s[1]-x1-x2*s[0])/(s[1]-s[0])
vy = (y3+y4*s[1]-y1-y2*s[0])/(s[1]-s[0])
vz = (z3+z4*s[1]-z1-z2*s[0])/(s[1]-s[0])

print (vx, vy, vz)

x = x1+x2*s[0]-vx*s[0]
y = y1+y2*s[0]-vy*s[0]
z = z1+z2*s[0]-vz*s[0]

print(f"{x}+{y}+{z}={x+y+z}")


print ((x1+x2*s[0]-(x3+x4*s[1]))/(x1+x2*s[0]-(x5+x6*s[2])))
print ((y1+y2*s[0]-(y3+y4*s[1]))/(y1+y2*s[0]-(y5+y6*s[2])))
print ((z1+z2*s[0]-(z3+z4*s[1]))/(z1+z2*s[0]-(z5+z6*s[2])))

print ((x1+x2*s[0]-(x3+x4*s[1]))/(x1+x2*s[0]-(x7+x8*s[3])))
print ((y1+y2*s[0]-(y3+y4*s[1]))/(y1+y2*s[0]-(y7+y8*s[3])))
print ((z1+z2*s[0]-(z3+z4*s[1]))/(z1+z2*s[0]-(z7+z8*s[3])))
print (f"k={s[4]}")
print(f"r={s[5]}")