def main():
    # Prompt for an int between 1 and 8 (inclusive)
    while True:
        try:
            height = int(input("Height: "))
            if 0 < height < 9:
                print_pyramid(height)
                break
        except ValueError:
            pass


# Print two half-pyramids with a gap of two spaces in between
def print_pyramid(height):
    for i in range(height):
        # Print left half
        for j in range(height):
            if (i + j + 1) < height:
                print(" ", end="")
            else:
                print("#", end="")

        # Add space between halfs
        print("  ", end="")

        # Print right half
        for _ in range(i + 1):
            print("#", end="")

        # Add new line
        print()


if __name__ == "__main__":
    main()
