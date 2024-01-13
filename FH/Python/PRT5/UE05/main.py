import csv

results = list()
scores = list()
with open('DBResult.csv', 'r') as csv_file:
    csv_file.readline()
    csv_file.readline()
    csv_reader = csv.reader(csv_file, delimiter=';', quotechar='"')
    for row in csv_reader:
        scores.append(float(row[4]))
        results.append(True if 'REVERSED' in row[3] else False)

results = [x[1] for x in sorted(zip(scores, results), key=lambda pair: pair[0], reverse=True)]
scores = sorted(scores, reverse=True)

targets = 0
decoys = 0
cur_index = 0
while cur_index < len(results) and (decoys/targets if targets>0 else 0) <= 0.01:
    if results[cur_index]:
        decoys += 1
    else:
        targets += 1
    cur_index += 1

print(f"{targets}/{decoys-1}: {decoys/targets}")
print(f"{scores[cur_index-1]}")