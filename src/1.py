from decimal import getcontext, Decimal
import sys

getcontext().prec = 29
exp = int(sys.argv[3])
if exp > 28:
    number =  Decimal("79228162514264337593543950335")
else:
    number = Decimal(sys.argv[1]) * Decimal(sys.argv[2])
#number = number.quantize(Decimal(".00000000000000000000000000000"))
print('{:.{}f}'.format(number, exp))
