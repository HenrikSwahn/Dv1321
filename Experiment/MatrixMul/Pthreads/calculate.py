import math
import numpy

def average(data):
	return sum(data) * 1.0/len(data)


floats = []

with open("result.txt", "r") as f:
	for line in f:
		floats.append(float(line))


avg = average(floats)
variance = map(lambda x:(x-avg)**2, floats)
standard_deviation = math.sqrt(average(variance))

print(standard_deviation)
print(sum(floats)*1.0/len(floats))
