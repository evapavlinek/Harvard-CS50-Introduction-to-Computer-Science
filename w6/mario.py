from cs50 import get_int

while True:
    n = get_int("Height: ")
    if n > 0:
        break

for i in range(n):
    print((i + 1) * "#")

print()

for i in range(3):
    print("#" * 3)
