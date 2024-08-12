import re
import sys
import math

# Luhn's Algorithm
def luhns_algorithm(card_number):
    checksum = 0
    # Iterate through the card number reversed
    for index, number in enumerate(reversed(card_number)):
        number = int(number)

        # If the current number is at an even index
        if index % 2 == 0:
            checksum += number
        # If the current number is at an uneven index
        else:
            number *= 2
            # If the number has 2 digits, add the products digits, else just add the number
            checksum += number // 10 + number % 10 if number >= 10 else number
    # Return True if the checksum has a 0 at the end
    return checksum % 10 == 0

# Define Error Codes
ERROR_CODE = ["", "INVALID"]

# Prompt the user for a credit card number and store it in credit_number
credit_number = input("Please enter a VALID credit card number: ")

# If it got the AMEX starting digits
if re.match("34", credit_number) or re.match("37", credit_number):
    # Check the card numbers length and use Luhn's Algorithm to validate
    if len(credit_number) == 15 and luhns_algorithm(credit_number):
        print("AMEX")
    else:
        ERROR = True

# If it got the MASTERCARD starting digits
elif re.match("5[1-5]", credit_number):
    # Check the card numbers length and use Luhn's Algorithm to validate
    if len(credit_number) == 16 and luhns_algorithm(credit_number):
        print("MASTERCARD")
    else:
        ERROR = True

# If it got the VISA starting digits
elif re.match("4", credit_number):
    # Check the card numbers length and use Luhn's Algorithm to validate
    if (len(credit_number) == 13 or len(credit_number) == 16) and luhns_algorithm(credit_number):
            print("VISA")
    else:
        ERROR = True
# Card is invalid
else:
    ERROR = True

sys.exit(ERROR_CODE[1] if ERROR else ERROR_CODE[0])
