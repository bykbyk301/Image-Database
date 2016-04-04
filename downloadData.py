#! python3.5
# downloadGodTitle.py - Downloads description of the drawings on every page 

import requests, os, csv, bs4, csv

# list to store all drawing data
allData = []

for i in range(1, 244): 
	print("Downloading page" + str(i))
	baseUrl = 'http://ddd.unil.ch/index.php?recherche=&page=' + str(i) + '&tri=dateinsertion&presentation=liste'

	res = requests.get(baseUrl)
	res.raise_for_status()
	soup = bs4.BeautifulSoup(res.text)

	# find table 
	table = soup.find("table", {"class": "table"})
	imgUrl = table.select('img')
	for j in range(len(imgUrl)):
		# array to store data per image
		data = []
		# download image
		imgSrc = imgUrl[j].get('src')
		lowRez = imgSrc.replace("&resolution=1280x960","&resolution=133x100")
		imgLink = 'http://ddd.unil.ch/' + lowRez
		print('Downloading image %s...' % (imgLink))
		res = requests.get(imgLink)
		res.raise_for_status()
		# find image id and add to data array
		imgId = imgSrc.replace("image.php?id=","").replace("&resolution=1280x960","")
		data.append(imgId)
		# save the image
		imageFile = open(os.path.join('imgs_s', str(imgId)) + '.jpg', 'wb')
		for chunk in res.iter_content(10000):
			imageFile.write(chunk)
		imageFile.close()
		# find other data and add to data array
		drawings = table.find_all("table", {"class": "liste"})
		name = drawings[j].find_all('td')
		for k in range(len(name)):
			pInfo = name[k].string
			data.append(pInfo)
		# store the drawing data to the list
		allData.append(data)

with open("data.csv", "w") as outfile:
	writer = csv.writer(outfile, lineterminator='\n')
	writer.writerows(allData)

print("Done!")


