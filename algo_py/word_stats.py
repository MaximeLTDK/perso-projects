from tools import *

def nbChars(text):
    car = 0
    while car < len(text):
        car += 1
    return car

def nbWords(text):
    word = 1
    i = 0
    while i < len(text):
        if i + 1 < len(text) and text[i] == ' ' and isLetter(text[i + 1]):
            word += 1
        i += 1
    return word

def nbSentences(text):
    if len(text) == 0 or len(text) == 1 and not isLetter(text[0]):
        return 0
    else:
        sentence = 1
        i = 0
        text = removeSpace(text)
        while i < len(text):
            if i + 2 < len(text) and isPounct(text[i]) and isLetter(text[i + 2]): #if there is text after a comma
                sentence += 1
            i += 1
        return sentence

def nbLetters(text):
    letter = 0
    i = 0
    while i < len(text):
        if isLetter(text[i]):
            letter += 1
        i += 1
    return letter

def nbParagraphs(text):
    pass

def instaLetters(text): #number of instances
    insta = []
    (words, nbs) = ([],[])
    text = strtolower(text)
    for i in range(len(text)):
        nb = 0
        if not matchList(text[i], words) and isLetter(text[i]):
            for j in range(i + 1, len(text)):
                if text[i] == text[j]:
                    nb += 1
            words.append(text[i])
            nbs.append(nb)
    insta.append(words)
    insta.append(nbs)
    return insta

def statLetters(insta):
    stat = [[],[]]
    total = len(insta[0])
    i = 0
    while i < total:
        stat[0].append(insta[0][i])
        stat[1].append(insta[1][i] / total)
        i += 1
    return stat

def printStat(stat): #works with statLetters and instaLetters
    for i in range(len(stat[0])):
        print(stat[0][i] + " => " + str(stat[1][i]))
    print("\n")

'''
def mainInput():
    pass
    
def printStat(str_): #overload (broken)
    insta = instaLetters(str_)
    printStat(statLetters(insta))
    '''
    
def isPounct(car):
    return car == '.' or car == '!' or car == '?' #:hap: :noel:

def isLetter(car):
    return ord(car) >= 0x41 and ord(car) <= 0x5A \
            or ord(car) >= 0x61 and ord(car) <= 0x7A \
            or car == 'à' or car == 'é' or car == 'è' or car == 'ù' or car == 'ç' \
            or car == 'Â' or car == 'Ê' or car == 'Î' or car == 'Û' #caractères courants français (a little boring...)


strfoobar = "Ceci est une chaine de caractères tout à fait normale, pas vrai ? Linux et GNU ! Lorem ipsum sit amet."

nbc = nbChars(strfoobar)
nbl = nbLetters(strfoobar)
nbw = nbWords(strfoobar)
nbs = nbSentences(strfoobar)
insta = instaLetters(strfoobar)
stat = statLetters(insta)


print("Exemple de String: " + strfoobar)
print("Nombre de caractères: " + str(nbc))
print("Nombre de lettres: " + str(nbl))
print("Nombre de mots: " + str(nbw))
print("Nombre de phrases: " + str(nbs))
print("\nFréquence des lettres: (les lettres à 0.0 apparaissent rarement dans le texte)")

printStat(stat)
