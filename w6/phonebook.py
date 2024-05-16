# people = [
#     {"name": "Carter", "number": "123456789"},
#     {"name": "David", "number": "123456789"},
#     {"name": "John", "number": "456789"},
# ]

people = {
    "Carter" : "123456789",
    "David" : "123456789",
    "John" : "987654321",
}

name = input("Name: ")

if name in people:
    number = people[name]
    print(f"Found {number}")
else:
    print("Not found")


#for person in people:
#    if person["name"] == name:
#        print(f"Found {person['number']}")
#        break
#else:
#    print("Not found")
