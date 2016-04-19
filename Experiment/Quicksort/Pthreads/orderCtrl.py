import math

ints = []

with open("order.txt", "r") as f:
	for line in f:
		ints.append(int(line))


prev = -1
for number in ints:
	if number < prev:
		print("Error, number:", number, " is smaller than the previous number: ", prev)
		break
	prev = number