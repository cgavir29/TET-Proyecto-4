import sys
import random


def is_int(num):
    try:
        int(num)
        return True
    except ValueError:
        return False


def generate(n):
    with open(f'test_{n}.txt', 'w') as test_file:
        for _ in range(n):
            rnd_int = random.randint(1, n)
            test_file.write(str(rnd_int) + '\n')


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Please enter the size of the dataset you wish to generate')
    else:
        if is_int(sys.argv[1]):
            generate(int(sys.argv[1]))
        else:
            print('Size arguement must be an integer')
