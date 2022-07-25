from decimal import getcontext, Decimal

getcontext().prec = 29
number = Decimal("5") / Decimal("3")
#number = number.quantize(Decimal(".0000000000000000000000000000"))
print('{:f}'.format(number))
