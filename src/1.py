from decimal import getcontext, Decimal

getcontext().prec = 29
number = Decimal("93.2480422615567883399331840") * Decimal("7922.8162495817593519834398720")
#number = number.quantize(Decimal(".0000000000000000000000000000"))
print('{:f}'.format(number))

#738787.10447154875133568397872 c
#738787.10447154875133568405795 p