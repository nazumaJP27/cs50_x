def main():
    # Prompt for a credit card number
    while True:
        try:
            number = int(input("Number: "))
            break
        except ValueError:
            pass

    # Check if number is a valid credit card number
    flag = card_flag(number)

    if flag and luhn(number):
        # Print credit card flag name
        print(flag)
    else:
        print("INVALID")


# Algorithm used to validate credit card numbers
def luhn(card):
    card = str(card)  # Converts argument to str
    stl_digits = []  # Stores every-other-digit from second to last
    total_sum = 0

    # Iterate through every digit in card_number, starting from the last
    i = len(card) - 1  # Set i to last index of card_numbe
    while i >= 0:
        total_sum += int(card[i])
        if i > 0:
            stl_digits.append(card[i - 1])
        i -= 2

    # Multiply each stl_digits by 2 and sum the products
    for n in stl_digits:
        n = int(n) * 2
        # If the product have two digits
        if n > 9:
            # Sum the first and second digit
            n = int(n / 10) + int(n % 10)
        # Add number to total_sum
        total_sum += n

    # Check if total_sum's last digit is 0
    if total_sum % 10 == 0:
        return True
    else:
        return False


def card_flag(card):
    # Check if the number of digits is between 13 and 16 (inclusive)
    card = str(card)  # Convert argument to str
    n_digits = len(card)

    if (12 < n_digits < 17):
        # Check if number matches with some card flag (AMEX, MASTERCARD, VISA)
        if n_digits in [13, 16] and int(card[0]) == 4:
            return "VISA"
        elif n_digits == 15 and int(card[0] + card[1]) in [34, 37]:
            return "AMEX"
        elif n_digits == 16 and int(card[0] + card[1]) in [51, 52, 53, 54, 55]:
            return "MASTERCARD"
        else:
            return False


if __name__ == "__main__":
    main()
