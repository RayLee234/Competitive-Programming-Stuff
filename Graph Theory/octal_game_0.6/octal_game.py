import numpy as np

file = open("1.txt", "r")

str = file.read().split(" ")
for i in range(len(str)):
	str[i] = int(str[i])
	

print(str)