from decimal import getcontext, Decimal

getcontext().prec = 29
number = Decimal("792.2816129677922868576387072") * Decimal("792281624.95817593523395886061")
#number = number.quantize(Decimal(".00000000000000000000000000000"))
print('{:f}'.format(number))

#738787.10447154875133568397872 c
#738787.10447154875133568405795 p
