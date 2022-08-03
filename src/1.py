from decimal import getcontext, Decimal

getcontext().prec = 29
number = Decimal("-20905970900149574") / Decimal("71780112248297297370296977550")
#number = number.quantize(Decimal(".00000000000000000000000000000"))
print('{:f}'.format(number))
