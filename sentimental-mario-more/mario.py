# TODO
inputs = ["1", "2", "3", "4", "5", "6", "7", "8"]

while (True):
    string = input("Height: ")
    if string in inputs:
        height = int(string)
        break

i = 0
while (i < height):
    n_space = height - i - 1
    n_hash = height - n_space

    j = 0
    while (j < n_space):
        print(" ", end="")
        j += 1
    j = 0
    while (j < n_hash):
        print("#", end="")
        j += 1
    print("  ", end="")
    j = 0
    while (j < n_hash):
        print("#", end="")
        j += 1
    print("")
    i += 1