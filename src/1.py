from decimal import Decimal

number = Decimal("1.0") / Decimal("7922816240358387315128664064")
number = number.quantize(Decimal("1.0000000000000000000000000000"))
print(number)