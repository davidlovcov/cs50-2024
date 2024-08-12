import csv
import sys


def main():

    ERROR_CODE = {
        1: "Error: Invalid argument count! (Usage: python dna.py [file_path/to/str_counts_database] [file_path/to/dna_sequence)]",
        2: "Error: STR DNA database file couldn't be opened!",
        3: "Error: DNA sequence file coudn't be opened!"
    }

    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit(ERROR_CODE[1])

    # Store DNA and STR counts database file paths in variables
    str_counts_file_path = sys.argv[1]
    dna_sequence_file_path = sys.argv[2]

    # Variable in which the STR database will be stored to
    str_counts_database = []

    # Open the STR database file and store its contents into a variable
    try:
        with open(str_counts_file_path) as str_file:
            reader = csv.DictReader(str_file)
            for row in reader:
                str_counts_database.append(row)
    except:
        sys.exit(ERROR_CODE[2])

    # Open the DNA sequence file and store its contents into a variable
    dna_sequence = ""
    try:
        with open(dna_sequence_file_path) as dna_sequence_file:
            dna_sequence = dna_sequence_file.read()
    except:
        sys.exit(ERROR_CODE[3])

    # Dictionary to store the longest match of the DNA sequence
    sequences_counter = {
        "AGATC": 0,
        "TTTTTTCT": 0,
        "AATG": 0,
        "TCTAG": 0,
        "GATA": 0,
        "TATC": 0,
        "GAAA": 0,
        "TCTG": 0
    }

    # Store the longest match of the sample in the sequence counter
    for current_sub_sequence in sequences_counter:
        sequences_counter[current_sub_sequence] = longest_match(dna_sequence, current_sub_sequence)

    # Check the STR DNA database with the longest matches
    for current_row in str_counts_database:
        is_match = True
        for key in list(current_row.keys())[1:]:
            # If the sequences don't have the same longest runs
            if int(current_row[key]) != int(sequences_counter[key]):
                is_match = False
                break
        # If the sequences have the same longest runs
        if is_match:
            sys.exit(current_row['name'])

    print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
