#! python3.5
# find the most similar images

import math, csv

# arays to store calculated distance between images
indexAndDistance = []
distance = []

csvRows = []
csvFileObj = open('./data.csv')
readerObj = csv.reader(csvFileObj)
for row in readerObj:
	if readerObj.line_num == 0:
		continue
	csvRows.append(row)
print("Start calculating..")
# calculate the distance between images
for i in range(len(csvRows)):
	for j in range(1, len(csvRows)):
		if j > i :
			xA = float(csvRows[i][1])
			xB = float(csvRows[j][1])
			yA = float(csvRows[i][2])
			yB = float(csvRows[j][2])
			d = math.sqrt((xA - xB)**2 + (yA - yB)**2)
			whichImages = str(csvRows[i][0]) + " / " + str(csvRows[j][0])
			data = []
			data.append(whichImages)
			data.append(d)
			distance.append(d)
		indexAndDistance.append(data)

# find the smallest distance in the distance array
smallestDistance = min(distance)
smallestDistanceIndex = distance.index(smallestDistance)
print(smallestDistance)

# find which images the distance is
whichImages = indexAndDistance[smallestDistanceIndex][0]
print(whichImages)
csvFileObj.close()

