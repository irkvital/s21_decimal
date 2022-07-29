from decimal import getcontext, Decimal

getcontext().prec = 29
number = Decimal("-7.886366") * Decimal("-78231657421398037481500.000000")
#number = number.quantize(Decimal(".00000000000000000000000000000"))
print('{:f}'.format(number))
