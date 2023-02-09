import collections

line_counts = {}
with open('bouton.txt', 'r') as file:
    lines = file.readlines()
    line_counts = collections.Counter(lines)
    with open("boutonOutput.txt", "w") as output_file:
        for line, count in line_counts.items():
            if count == 2:
                output_file.write(line)