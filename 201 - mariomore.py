
height = int(input("Height = "))
space = height - 1
hash = 1

for i in range(height):
    #print the spaces
    print(" " * space, end = "")

    #print the hashes
    print("#" * hash, end = "")

    #print 1 space
    print(" " , end = "")

    #print the hashes
    print("#" * hash, end = "")
    print()

    hash += 1
    space -= 1
