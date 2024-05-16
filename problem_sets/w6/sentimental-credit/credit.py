from cs50 import get_string, get_int
import re


def main():
    # Prompt the user for the card number
    number = get_int("Number: ")
    number = str(number)
    numberLen = len(number)

    valid = validateCardNumber(number, numberLen)
    detectCardNetwork(number, valid)


# Check whether the card number is valid
def validateCardNumber(number, numberLen):

    # Multiply every other digit by 2, starting with the number’s second-to-last digit,
    # and then add those products’ digits together
    digitProductSum = 0
    for i in range(numberLen - 2, -1, -2):
        multipliedDigit = int(number[i]) * 2
        digitProductSum += multipliedDigit // 10 + multipliedDigit % 10

    # Add the sum to the sum of the digits that weren’t multiplied by 2
    for i in range(numberLen - 1, -1, -2):
        digitProductSum += int(number[i])

    # If the total’s last digit is 0, the number is valid
    if digitProductSum % 10 == 0:
        return (True)
    else:
        return (False)


# If the card number is valid, detect the card network, with regex
def detectCardNetwork(number, valid):
    if valid:
        if re.match("^3[4|7][0-9]{13}", number):
            print("AMEX")
        elif re.match("5[1-5][0-9]{14}", number):
            print("MASTERCARD")
        elif re.match("4[[0-9]{12}|[0-9]{15}]", number):
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")


main()

# If the card number is valid, detect the card network, without the regex
# def detectCardNetwork(number, numberLen, valid):
#    if valid:
#        if numberLen == 15 and (number[0:2] in ["34", "37"]):
#            print("AMEX")
#        elif numberLen == 16 and (number[0:2] in ["51", "52", "53", "54", "55"]):
#            print("MASTERCARD")
#        elif numberLen in [13, 16] and number[0] == "4":
#            print("VISA")
#        else:
#            print("INVALID")
#    else:
#        print("INVALID")
