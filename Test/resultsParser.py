with open("Test/test_output.txt", 'r') as f:
    data = f.read().split(sep=" ")

frequencies = dict()
keys = set(data[:-1])
for i in keys:
    frequencies[i] = data.count(i) / (len(data)-1)
print(frequencies)