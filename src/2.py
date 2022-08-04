from decimal import getcontext, Decimal

getcontext().prec = 29
number = Decimal("23142.739021437278912921463090") / Decimal("469971034644081275821.9146474")
#number = number.quantize(Decimal(".00000000000000000000000000000"))
print('{:.{}f}'.format(number, 28))
