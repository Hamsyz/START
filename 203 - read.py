#get the text
text = input("Text: ")

#variables
letters = 0
words = 1 #there are 1 more sentences than spaces
sentences = 0

for i in range(len(text)):

    #count letters
    if text[i].isalpha() == True:
        letters += 1

    #count words
    elif text[i] == " ":
        words += 1

    #count sentences
    elif text[i] in ['?', '!', '.']:
        sentences += 1

L = (100 / words) * letters
S = (100 / words) * sentences

index = round(0.0588 * L - 0.296 * S - 15.8)

if index > 16 or index == 16:

    print('"Grade 16+"')

elif index < 1:
    print('"Before Grade 1"')

else:
    print(index)

