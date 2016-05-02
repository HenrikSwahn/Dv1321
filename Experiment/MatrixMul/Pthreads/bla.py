import math

def average(data):
	return sum(data) * 1.0/len(data)


longs = []

with open("longs.txt", "r") as f:
	for line in f:
		longs.append(long(line))


avg = average(longs)
print(avg)
