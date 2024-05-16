import csv

from collections import Counter

with open("favorites.csv") as file:
    reader = csv.DictReader(file)
    counts = Counter()

    for row in reader:
        favorite = row["language"]
        # favorite = row["problem"]
        counts[favorite] += 1


#    counts = {}
#
#    for row in reader:
#        favorite = row["language"]
#        if favorite in counts:
#            counts[favorite] += 1
#        else:
#            counts[favorite] = 1

# sort by the counts
# for favorite, count in counts.most_common():
#     print(f"{favorite}: {count}")

# for favorite in sorted(counts, key = counts.get, reverse = True):
#     print(f"{favorite}: {counts[favorite]}")


# promt the user for the favorite and print the count value
favorite = input("Favorite: ")
print(f"{favorite}: {counts[favorite]}")
