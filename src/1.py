from decimal import getcontext, Decimal

getcontext().prec = 29
number = Decimal("0.000000000000000000000000001") / Decimal("6")
number = number.quantize(Decimal(".0000000000000000000000000000"))
print('{:f}'.format(number))