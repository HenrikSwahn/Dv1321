import math

def get_average(data): 
	return (sum(data) / 2)

def calc_deviation(data, average):
	deviations = []
	for number in data:
		deviations.append(number - average)

	return deviations

def calc_pow(data):
	powResults = []
	for number in data:
		powResults.append(math.pow(number, 2))
	return powResults

def standardDeviation(data):
	average = get_average(data)
	deviations = calc_deviation(data, average)
	powDev = calc_pow(deviations)
	devAverage = get_average(powDev)
	return math.sqrt(devAverage)

floats = []

with open("result.txt", "r") as f:
	for line in f:
		floats.append(float(line))

print(standardDeviation(floats))