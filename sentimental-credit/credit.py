# TODO

import sys

# input card number
flag = True
while (flag):
    string = input("number: ")
    if string.isdecimal():
        number = int(string)
        if number >= 0 or number <= 9999999999999999:
            flag = False


# get digit
digit = len(string)

# check card type
judge = 0
tmp_number = number
i = 0
while (i < digit - 2):
    tmp_number = int(tmp_number / 10)
    i += 1
if (digit == 15 and (tmp_number == 34 or tmp_number == 37)):
    judge = 1
elif (digit == 16 and (tmp_number == 51 or tmp_number == 52 or tmp_number == 53 or tmp_number == 54 or tmp_number == 55)):
    judge = 2
else:
    tmp_number = int(tmp_number / 10)
    if ((digit == 13 or digit == 16) and tmp_number == 4):
        judge = 3
    else:
        print("INVALID")
        sys.exit(0)

# Luhn
i = 1
sum_of_even = 0
sum_of_odd = 0
while (number != 0):
    tmp_number = number
    number = int(number / 10)
    number = int(number * 10)
    buz = int(tmp_number - number)
    number = int(number / 10)

    if (i % 2 == 0):
        buz = int(buz * 2)
        if (buz >= 10):
            tmp = buz
            buz = int(buz / 10)
            buz += tmp % 10
        sum_of_even += buz
    else:
        sum_of_odd += buz
    i += 1

tmp_sum = sum_of_even + sum_of_odd
if (tmp_sum % 10 != 0):
    judge = 0

if (judge == 1):
    print("AMEX")
elif (judge == 2):
    print("MASTERCARD")
elif (judge == 3):
    print("VISA")
else:
    print("INVALID")