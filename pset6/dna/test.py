import csv
import sys

rows = []
with open("databases/large.csv") as file:
    reader = csv.DictReader(file)
    for row in reader:
        rows.append(row)

if len(sys.argv) > 3:
        print("Too many arguments")

dna_sequence = {}
with open("sequences/1.txt") as dna_sequence_file:
    dna_sequence = dna_sequence_file.read()

print(dna_sequence)

sequences_counter = {
    "AGATC": 0,
    "TTTTTTCT": 0,
    "AATG": 0,
    "TCTAG": 0,
    "GATA": 0,
    "TATC": 0,
    "GAAA": 0,
    "TCTG": 0
    }

for current_sub_sequence in sequences_counter:
    sequences_counter[current_sub_sequence] = longest_match(dna_sequence, current_sub_sequence)
    print sequenecs_counter
