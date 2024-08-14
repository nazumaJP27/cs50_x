def main():
    text = input("Text: ")
    grade = round(coleman(text))

    if grade:
        if (grade < 1):
            print("Before Grade 1")
        elif (grade > 16):
            print("Grade 16+")
        else:
            print(f"Grade {grade}")
    else:
        print("Fail to check text.")


# Returns the Coleman-Liau Index of string text
def coleman(text):
    # Check if argument only contains digits
    if text.isdecimal():
        return False

    letters = 0
    words = 1  # Need to be initialized with 1
    sentences = 0
    ponct = ['.', '!', '?']

    # Loop to every char in the text
    for i in range(len(text)):
        c = text[i].lower()
        # Increment number of letters on every char a-z
        if c.isalpha():
            letters += 1
        # Increment number of words on every white space char
        elif c.isspace():
            words += 1
        # Increment number of sentences on every period, exclamation point, or question mark
        elif c in ponct:
            if i > 0 and text[i - 1].isalpha():
                sentences += 1

    L = (letters / words) * 100.0
    S = (sentences / words) * 100.0
    index = (0.0588 * L) - (0.296 * S) - 15.8

    print(index / 1)
    return index / 1


if __name__ == "__main__":
    main()
