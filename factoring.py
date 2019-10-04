"""
NOTE: this program has a horrid runtime, taking upwards of 85 minutes to finish factoring all hardcoded values of n. 
The loop counter variables increase run time. 
"""

import time

sqrtCount = 0           # global counter for every time isqrt runs


def isqrt(n):           # integer square root

    global sqrtCount
    count = 0
    x = n
    y = (x + n // x) // 2

    while y < x:
        count += 1
        x = y
        y = (x + n // x) // 2

    sqrtCount += 1

    return x


def fermat(n):          # fermat factoring

    global sqrtCount
    totalCount = 0
    count = 0

    a = isqrt(n)

    b2 = a * a - n
    b = isqrt(n)

    while b * b != b2:

        a = a + 1
        b2 = a * a - n
        b = isqrt(b2)
        count += 1

    p = a + b
    q = a - b
    assert n == p * q

    totalCount = sqrtCount + count
    print("Fermat loop ran", count, "times and isqrt loop ran", sqrtCount, "times for a total of", totalCount, "\n")

    print(n, '=', p, 'x', q, '\n')
    return


def factor(n):      # trial division factoring

    countOut = 0
    countIn = 0
    countTotal = 0

    f, fs = 2, []
    while f * f <= n:
        countOut += 1   # outer  loop counter
        while n % f == 0:
            countIn += 1    # inner loop counter
            fs.append(f)
            n /= f
        f += 1
    if n > 1: fs.append(int(n))

    countTotal = countOut + countIn
    print("Trial division outer loop ran", countOut, "times and inner loop ran", countIn, "times for a total of", countTotal, "\n")
    print(fs, "\n")
    return


n = 441075437627829133

start = time.clock()
fermat(n)
print("Fermat run time", time.clock() - start, '\n')

start = time.clock()
factor(n)
print("Trial division run time", time.clock() - start, '\n')

n = 733561193479131791

start = time.clock()
fermat(n)
print("Fermat run time", time.clock() - start, '\n')

start = time.clock()
factor(n)
print("Trial division run time", time.clock() - start, '\n')

n = 611217877192686991  

start = time.clock()
fermat(n)
print("Fermat run time", time.clock() - start, '\n')

start = time.clock()
factor(n)
print("Trial division run time", time.clock() - start, '\n')

n = 1442059257386438303

start = time.clock()
fermat(n)
print("Fermat run time", time.clock() - start, '\n')

start = time.clock()
factor(n)
print("Trial division run time", time.clock() - start, '\n')


n = 3008502085141882717

start = time.clock()
fermat(n)
print("Fermat run time", time.clock() - start, '\n')

start = time.clock()
factor(n)
print("Trial division run time", time.clock() - start, '\n')


'''
#  TESTING
n = 26441

start = time.clock()
fermat(n)
print("Fermat run time", time.clock() - start, '\n')

start = time.clock()
factor(n)
print("Trial division run time", time.clock() - start, '\n')

'''
