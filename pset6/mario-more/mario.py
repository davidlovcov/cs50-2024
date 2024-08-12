MIN_HEIGHT = 1
MAX_HEIGHT = 8

# Loop for user input
while True:
    try:
        # Prompt the user for height
        height = int(input("Height: "))

        # If the height is in the allowed range
        if MIN_HEIGHT <= height <= MAX_HEIGHT:
            break

    except ValueError:
        # Ignore invalid inputs and prompt again
        pass

# Iterate through each row
for i in range(1, height + 1):
    # Print spaces at the beginning of the row
    print(" " * (height - i), end="")

    # Print the left-hand side of the pyramid
    print("#" * i, end="")

    # Print the gap between the two sides
    print("  ", end="")

    # Print right-hand side of the pyramid
    print("#" * i)
