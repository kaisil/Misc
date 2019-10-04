import sys

alphabet_size = 26
ASCII_FLOOR = ord('a')
MAX_KEYLEN = 10  # cap key length size


def init(alphabet_size, alphabet):
    for i in range(alphabet_size):
        alphabet.append(None)

    return alphabet


def reset(alphabet):
    for i in range(alphabet_size):
        alphabet[i] = None

    return alphabet


def remove(strn, alphabet):
    letters = list(strn)
    for i in range(len(letters)):
        alphabet[ord(letters[i]) - ASCII_FLOOR] = None


def show_alpha(alphabet):
    for i in range(26):
        if (alphabet[i] == None):
            sys.stdout.write('_')

        else:
            sys.stdout.write(chr(ord(alphabet[i]) - 32))

        sys.stdout.write(' ')

    print("")


def get_freq(str_s):
    str_l = list(str_s)
    freq = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

    for i in range(len(str_l) - 1):
        freq[ord(str_l[i]) - ASCII_FLOOR] = freq[ord(str_l[i]) - ASCII_FLOOR] + 1

    return freq


def get_bins(num_bins, str_s):
    bins = []

    for j in range(num_bins):
        bins.append([])

    for i in range(len(str_s) - 1):
        bins[i % num_bins].append(str_s[i])

    return bins


def get_num_bins():
    return int(input("How many bins?"))


def print_bins(bins, num_bins, l):
    for i in range(num_bins):
        print('\n', ''.join(bins[i]), '\n')
        freq = get_freq(bins[i])
        for i in range(26):
            print(chr(i + ASCII_FLOOR), ":\t", freq[i] / l * 100 * num_bins)

        print("\n----------------------------\n")


def get_text(filename):
    try:
        input_file = open(filename)

    except:
        input_file = None
        while input_file == None:
            try:
                input_file = open(input("Enter a filename:\n\t>"))
            except FileNotFoundError:
                input_file = None

    return input_file.read()


def add(position, letter, alphabet):
    # replace <1> in the ciphertext with <2>.
    try:
        if alphabet.__contains__(letter):
            print(letter, " already used.")
            return

        alphabet[ord(position) - ASCII_FLOOR] = letter

    except:
        print("invalid input")
        return


def show_guess(ciphertext, l, alphabet):
    clist = list(ciphertext)

    for i in range(l - 1):
        r = alphabet[ord(clist[i]) - ASCII_FLOOR]

        if r == None:
            clist[i] = '_'

        else:
            clist[i] = r

    print(''.join(clist))


def repeatingSequences(ciphertext):  # function finds number of space inbetween repeating sequences

    seqspacings = {}
    for seqLen in range(3, 6):
        for seqStart in range(len(ciphertext) - seqLen):
            seq = ciphertext[seqStart:seqStart + seqLen]
            for i in range(seqStart + seqLen, len(ciphertext) - seqLen):
                if ciphertext[i:i + seqLen] == seq:
                    if seq not in seqspacings:
                        seqspacings[seq] = []  # blank list initialized
                    seqspacings[seq].append(i - seqStart)
    return seqspacings

def relevantFactors(val):

    if val < 2:
        return []

    factors = []

    for i in range(2, MAX_KEYLEN + 1):
        if val % i == 0:
            factors.append(i)
            factors.append(int(val / i))
    if 1 in factors:
        factors.remove(1)
    return list(set(factors))


def firstIndex(x):
    return x[1]


def commonFactors(factors):

    factcount = {}

    for seq in factors:
        factorlist = factors[seq]
        for factor in factorlist:
            if factor not in factcount:
                factcount[factor] = 0
            factcount[factor] += 1

    countedfactors = []
    for factor in factcount:
        if factor <= MAX_KEYLEN:
            countedfactors.append((factor, factcount[factor]))

    countedfactors.sort(key=firstIndex, reverse=True)

    return countedfactors


def kasiski(ciphertext):  # calculates possible key lengths according to relevant factors

    repeatedseqs = repeatingSequences(ciphertext)

    factors = {}
    for seq in repeatedseqs:
        factors[seq] = []
        for spacing in repeatedseqs[seq]:
            factors[seq].extend(relevantFactors(spacing))

    countedfactors = commonFactors(factors)

    possiblekeylens = []
    for twoIntTuple in countedfactors:
        possiblekeylens.append(twoIntTuple[0])

    return possiblekeylens




def main(args):
    alphabet = []
    alphabet = init(alphabet_size, alphabet)
    userIn = ""
    history = []
    ciphertext = ""

    try:
        ciphertext = get_text(args[0])

    except IndexError:
        ciphertext = get_text("")

    l = len(ciphertext)
    freq = get_freq(ciphertext)

    while userIn != "-1":
        userIn = input("\t>")

        if userIn == "reset" or userIn == "rs":
            reset(alphabet)

        elif userIn == "undo" or userIn == 'z':
            alphabet = history.pop()

        elif userIn == "exit" or userIn == 'x':
            break

        elif userIn == "remove" or userIn == "rm":
            remove(input("remove what?\n\t>"), alphabet)

        elif userIn == "freq" or userIn == "frequency" or userIn == 'f':
            for i in range(26):
                print(chr(i + ASCII_FLOOR), ":\t", freq[i] / l * 100)

        elif userIn == "bins" or userIn == 'b':
            num_bins = get_num_bins()
            print_bins(get_bins(num_bins, ciphertext), num_bins, l)

        elif userIn == "ciphertext" or userIn == "ct":
            print(ciphertext)

        elif len(userIn) == 3:
            userIn = list(userIn)
            add(userIn[0], userIn[2], alphabet)

        elif userIn == "seq spacing" or userIn == "ss":
            repeatingseqs = repeatingSequences(ciphertext)
            print(repeatingseqs)

        elif userIn == "keylen":
            keylens = kasiski(ciphertext)
            print(keylens)

        show_guess(ciphertext, l, alphabet)
        history.append(alphabet)

    return 0


if __name__ == "__main__":
    main(sys.argv[1:])
