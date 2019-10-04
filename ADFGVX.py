# ADFGVX cipher

import sys


#   The first key, henceforth referred to as the substitution key,
# will be a 6x6 matrix, each row and column labeled
# with the letters A,D,F,G,V,X. The entries in the matrix will
# consist of elements in {r_1, ... ,r_n} where n = 36, and each
# r_i corresponds to a random, unique element in {a, b, ... ,z, 1, 2, ... ,9}
#
#      ___|___A___|___D___|___F___|___G___|___V___|___X___|
#       A |  r_1  |  r_2  |  r_3  |  r_4  |  r_5  |  r_6  |
#       D |  r_7  |  r_8  |  r_9  |  r_10 |  r_11 |  r_12 |
#       F |  r_13 |  r_14 |  r_15 |  r_16 |  r_17 |  r_18 |
#       G |  r_19 |  r_20 |  r_21 |  r_22 |  r_23 |  r_24 |
#       V |  r_25 |  r_26 |  r_26 |  r_28 |  r_29 |  r_30 |
#       X |  r_31 |  r_32 |  r_33 |  r_34 |  r_35 |  r_36 |
#
#   The second key, henceforth referred to as the transposition key,
# will be a combination of elements in {a, ... ,z}, also referred to
# by their ordinals {0, 26}.
#   In plain english, the transposition key is a word. Letters in the
# Key will be sorted alphabetically.


# Define these constants
ALPHABET_SIZE = 36
ASCII_FLOOR   = ord('A')    # Probably not needed
ASCII_CEIL    = ord('Z')    # ''
ENCRYPT_SYM   = '1'         # Symbol indicating a line to be encrypted
DECRYPT_SYM   = '2'         # Symbol indicating a line to be decrypted
TRANS_START   = 6           # Line to read substitution key.
SUBST_START   = 0           # Line to begin reading transposition key
SUBST_END     = 5           # Line to end reading transposition key
NUM_MSG_START = 7           # Line to read number of messages
TXT_MSG_START = 8           # Line to start reading the message to encrypt or decrypt
PAD = 'X'                   # Character to use for padding


ENUM_DICT = dict(enumerate("ADFGVX"))  # enumerate ADFGVX --> 012345

#   These values are specified as constants so as not to rely on order of execution in
# reading from the input.

# Obtain from file input a list of strings, each element representing a single line.


def get_usr_input(file_input):
    lst_input = []
    i = 0

    file_input = None
    while file_input == None:
        try:
            file_input = open(input("Enter a filename:\n\t>"))
        except FileNotFoundError:
            file_input = None

    try:
        for line in file_input:
            lst_input.append(line)
            i = i + 1

    except:
        print("Error getting input.\tline ", count, "\n\nThe program will exit.")
        return None

    return lst_input


# Return the substitution key as a 2D list of 36 letters.


def get_subst_key(usr_input):

    subst_key = []
    i = SUBST_START

    # Construct a list of columns
    try:
        while i <= SUBST_END:
            subst_key.append(usr_input[i].split())
            i = i + 1

    except:
        print("Error getting substitution key.\tline ", i, "\n\nThe program will exit.")
        return None

    return subst_key

# return the substitution key word


def get_keyword(usr_input):

    keyword = list(usr_input[TRANS_START].rstrip())

    return keyword

# Return the substitution key as a sorted list of integers


def get_trans_key(usr_input):
    trans_key = list(usr_input[TRANS_START].rstrip())
    j = 0

    for i in trans_key:
        trans_key[j] = ord(trans_key[j]) - ASCII_FLOOR
        j = j + 1

    return trans_key


def get_sorted_trans_key(usr_input):
    s_key = list(usr_input[TRANS_START].rstrip())
    j = 0

    for i in s_key:
        s_key[j] = ord(s_key[j]) - ASCII_FLOOR
        j = j + 1

    s_key.sort()

    return s_key

# Return the number of messages to be encrypted/decrypted as an integer.


def get_numbr_msg(usr_input):
    num = 0
    try:
        num = usr_input[NUM_MSG_START].rstrip()

    except:
        print("Error getting number of messages\n\nThe program will exit.")
        return None

    return int(num)


# Return the plaintexts to be encrypted as a list of strings.


def get_plaintext(usr_input, num_texts):
    i = TXT_MSG_START
    plaintexts = []
    line = []

    while i <= num_texts + TXT_MSG_START - 1:
        try:
            line = usr_input[i].split()
            i = i + 1

            if line[0] == ENCRYPT_SYM:
                plaintexts.append(line[1])

            elif line[0] == DECRYPT_SYM:
                continue

            else:
                print("Error getting plaintexts.\tline ", i, "\n\nThe program will exit.")
                return None

        except:
            print("Error getting plaintexts.\tline ", i, "\n\nThe program will exit.")
            return None

    return plaintexts


# Return the ciphertexts to be encrypted as a list of strings.
# It would be shorted and slightly more efficient to do this in one function,
# but I think it looks vvv beautyfyl this way.


def get_ciphertext(usr_input, num_texts):

    i = TXT_MSG_START
    ciphertexts = []
    line = []

    while i <= num_texts + TXT_MSG_START - 1:
        try:
            line = usr_input[i].split()
            i = i + 1

            if line[0] == ENCRYPT_SYM:
                continue

            elif line[0] == DECRYPT_SYM:
                ciphertexts.append(line[1])

            else:
                print("Error getting plaintexts.\tline ", i, "\n\nThe program will exit.")
                return None

        except:
            print("Error getting plaintexts.\tline ", i, "\n\nThe program will exit.")
            return None

    return ciphertexts


def display_polybius_square(key_subst):
    row_labels = ['A', 'D', 'F', 'G', 'V', 'X']  # testing
    print('      A   D   F   G   V   X')  # 6 x 6
    for row_label, row in zip(row_labels, key_subst):
        print(' %s [%s  ]' % (row_label, ' '.join('%03s' % i for i in row)))


def fractionate_message(plaintext, key_subst):
    #   for char in plaintext... loop thru 2d array until you find matching character. Use X Y to look up
    #    fractional characters and append them to "fraction"

    split = [c for c in plaintext[0]]  # split the characters from plaintext list by letter

    fraction = ""
    for x in split:
        for row in key_subst:
            for char in row:
                if x is char:
                    fraction += ENUM_DICT[key_subst.index(row)] + ENUM_DICT[row.index(char)]

    return fraction


def calculate_swaps(u_key, s_key):

    swap = (0, 0)
    swaps = []
    index = 0

    for i in range(len(u_key)):
        index = s_key.index(u_key[i])
        swap = (i, index)
        s_key[index] = - 1
        swaps.append(swap)

    #print(swaps)

    return swaps


def create_columns(keylen, fractions, swaps):
    i = 0
    columns = []
    ciphertext = []
    fractions = list(fractions.replace(' ', ''))
    j, k = 0, 0

    #print(''.join(fractions))
    for i in range(len(fractions)):
        # Beginning of substring
        if i % keylen == 0:
            for t in range(keylen):
                columns.append(PAD)
                ciphertext.append('')

        columns[i] = fractions[i]

        # End of substring
        if i % keylen == keylen - 1:
            # do swaps
            for swap in swaps:
                columns[(i - keylen + 1) + swap[1]] = fractions[(i - keylen + 1) + swap[0]]

    output_string = ''
    for col in columns:
        for char in col:
            output_string = output_string + ''.join(char)
    columns = [columns[i::keylen] for i in range(keylen)]  # transform columns with slice
    output_string = ''

    # convert to string

    for col in columns:
        for char in col:
            output_string = output_string + ''.join(char)
  #  print("encrypted string: ", output_string)


    # Return the ciphertext as a string.

    #print(''.join(ciphertext))
    return output_string


# Take the ciphertext as a string and return the plaintext.

def decrypt_ciphertext(ciphertext, key_subst, key_trans, swaps, keylen):

    i = 0
    plaintext = []
    split = []
    msglen = len(ciphertext)
 #   print("ENTERING DECRYPT")
   # print (keylen)
    columnheight = msglen // keylen
    if msglen % keylen != 0:
        columnheight += 1;

    ciphertext = [ciphertext[i:i + columnheight +1] for i in range(0, len(ciphertext),columnheight +1)]


    # ^ Ciphertext is split into columns ^
    for l in ciphertext:
        m = list(l)
        ciphertext[ciphertext.index(l)] = m

    #V Zip version of transpose V
    # Pad the rows with empty spaces so they can be transposed with zip
    for line in ciphertext:
        while len(line) != keylen:
            line += ' '
    #transpose rows into columns
    rotated = list(map(list, zip(*ciphertext[::1])))

  #  print("rotated:", rotated)


    swapped = []

    swapped = [None for r in rotated]

  #  print(swaps)
    for s in swaps:
        swapped[s[0]] = rotated[s[1]]
  #  print ("swapped:", swapped)
    swapped = list(map(list, zip(*swapped[::1])))
   # print ("swapped rotated:", swapped)
    # ^ Ciphertext is swapped ^

    for i in range (len(swapped)):
        swapped[i] = [x for x in swapped[i] if x != ' ']
    ciphertext = ''.join(list(map(''.join, swapped)))
   # print(ciphertext)

    split =  [ciphertext[i:i+2] for i in range(0, len(ciphertext), 2)]
  #  print(split)
    mp = {'A': 0, 'D': 1, 'F': 2, 'G': 3, 'V': 4, 'X': 5}

    # Get plaintext letter for each pair
    for s in split:
        try:
            plaintext.append(key_subst[mp[s[0]]][mp[s[1]]])
        except IndexError:
            continue
  #  print (plaintext)
    return ''.join(plaintext)


def main(args):

    usr_input = get_usr_input(sys.stdin)  # user input from stdin <lst<str>>
    key_subst = get_subst_key(usr_input)  # substitution key      <lst<lst>>
    key_trans = get_trans_key(usr_input)  # transposition key     <lst<int>>
    num_texts = get_numbr_msg(usr_input)  # number of messages    <int>

    plaintext = get_plaintext(usr_input, num_texts)  # plaintexts            <lst<str>
    ciphertext = get_ciphertext(usr_input, num_texts)  # ciphertexts            <lst<str>

    #fractions = fractionate_message(plaintext, key_subst)  # splits plaintext msg into fractionated forms


    if not usr_input or not key_trans or not key_subst:
        return 1

    if not (plaintext or ciphertext):
        return 1

    keylen = len(key_trans)

    pt_msgs = len(plaintext)

    i = 1
    while pt_msgs != 0:
       # print("plain text string", plaintext)

        fractions = fractionate_message(plaintext, key_subst)
        print("plaintext string ", i, ":", plaintext)
        swaps = calculate_swaps(key_trans, sorted(key_trans))
        output_string = create_columns(keylen, fractions, swaps)
        print("encrypted string ", i, ":", output_string)
        print("\n")

        pt_msgs = pt_msgs - 1
        plaintext.pop(0)
        i += 1
    i = 1
    ct_msgs = len(ciphertext)

    while ct_msgs != 0:
        print("cipher string ", i, ":", ciphertext[0])
        swaps = calculate_swaps(key_trans, sorted(key_trans))
        decrypted_ct = decrypt_ciphertext(ciphertext[0], key_subst, key_trans, swaps, keylen)
        print("Decrypted string", i, ":", decrypted_ct)
        ct_msgs = ct_msgs - 1
        ciphertext.pop(0)

        i += 1



    return 0


if __name__ == "__main__":
    main(sys.argv[1:])