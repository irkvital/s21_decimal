from decimal import getcontext, Decimal

getcontext().prec = 29
number = Decimal("2720.8342842897596503912611840") * Decimal("792281624.95817593520620044183")
#number = number.quantize(Decimal(".00000000000000000000000000000"))
print('{:f}'.format(number))

#738787.10447154875133568397872 c
#738787.10447154875133568405795 p
