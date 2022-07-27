from decimal import getcontext, Decimal

getcontext().prec = 29
number = Decimal("0.0000000000000000000000000050") / Decimal("79228162495817593519834398720")
#number = number.quantize(Decimal(".0000000000000000000000000000"))
print('{:f}'.format(number))
