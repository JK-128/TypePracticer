#File to classify a list of words based on their letters.

homeRow   = ['a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l']
topRow    = ['q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p']
bottomRow = ['z', 'x', 'c', 'v', 'b', 'n', 'm']

def inRow(word, row, returnVal):
    for letter in row:
        if letter in word:
            return returnVal
    return 0

wordList = open("lowercaseAll.txt", "r")

values = []

count = 0
numLines = sum(1 for line in open('lowercaseAll.txt', 'r'))
previous = 0

for word in wordList:
    value = inRow(word, bottomRow, 2)

    if(value == 0):
        value = inRow(word, topRow, 1)

    values.append(value)
    
    count += 1

    percent = int((count / numLines) * 100)

    if (percent != previous):
        print(percent)
        previous = percent

with open("rowClassified.txt", "w") as myfile:
    myfile.write('\n'.join(str(value) for value in values))

