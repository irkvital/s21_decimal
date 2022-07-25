from decimal import getcontext, Decimal

getcontext().prec = 29
number = Decimal("0.0000000000000000000000000001") / Decimal("10")
number = number.quantize(Decimal(".0000000000000000000000000000"))
print('{:f}'.format(number))