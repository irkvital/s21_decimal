from decimal import getcontext, Decimal

getcontext().prec = 29
number = Decimal("-34408609108464854731690166446") / Decimal("-14.82910912776342005")
#number = number.quantize(Decimal(".00000000000000000000000000000"))
print('{:.{}f}'.format(number, 28))
