import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    data = []
    filename_csv = sys.argv[1]
    with open(filename_csv) as file:
        reader = csv.DictReader(file)
        for datum in reader:
            data.append(datum)

    # TODO: Read DNA sequence file into a variable
    filename_txt = sys.argv[2]
    with open(filename_txt) as f:
        dna = f.read()

    # TODO: Find longest match of each STR in DNA sequence
    target = {}
    for key in data[0]:
        if key == "name":
            pass
        else:
            target[key] = longest_match(dna, key)

    # TODO: Check database for matching profiles
    answer = "No match"
    n_subsequence = len(target)
    counter = 0
    for datum in data:
        for key in datum:
            if key == "name":
                answer = datum[key]
            elif target[key] == int(datum[key]):
                counter += 1
            else:
                if target[key] != int(datum[key]):
                    answer = "No match"
                    counter = 0
                    break
            if counter == n_subsequence:
                answer = datum["name"]
                print(answer)
                return
    print(answer)

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
