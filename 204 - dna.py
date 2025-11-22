import csv
import sys

found = True
def main():
    # TODO: Check for command-line usage

    if len(sys.argv) != 3:
        print("Usage: python dna.py 'CSV file' 'text file' ")
        exit()

    # TODO: Read database file into a variable

    with open(sys.argv[1] , "r") as csvfile:
        reader = csv.DictReader(csvfile)
        chart = list(reader)
        dnas = reader.fieldnames[1:] # the first fieldname is "name"
        dnas2 = reader.fieldnames[1:]

    # TODO: Read DNA sequence file into a variable

    with open(sys.argv[2] , "r") as textfile:
        dnaseq = textfile.read()

    # TODO: Find longest match of each STR in DNA sequence

    # get the lenght of the seq
    dnaseqlen = len(dnaseq)

    #create the loop
    y = 0
    for dna in dnas:

        longest = 0
        current = 0
        dnalen = len(dna)

        i = 0
        while i < dnaseqlen:

            #check if the first letter matches
            if dnaseq[i] == dna[0]:

                #check if the whole dna matches
                if dnaseq[i : i + dnalen] == dna:
                    current += 1
                    i += dnalen

                # if there is no match
                else:

                    #check if we found a longer string
                    if current > longest:
                        longest = current

                    current = 0
                    i += 1

            else:

                #check if we found a longer string
                if current > longest:
                    longest = current

                current = 0
                i += 1

        #save the value of the longest sequence
        dnas2[y] = longest
        y+=1


    # TODO: Check database for matching profiles

    for person in chart:
        x = 0
        found = True

        for dna in dnas2:

            if dna == int(person[dnas[x]]):
                x += 1
                continue

            else:
                found = False
                break

        #check if there is a match and end the fucntion if there is 
        if found == True:
            print(person["name"])
            return

    #print no match if there is no match
    print("No Match")


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
