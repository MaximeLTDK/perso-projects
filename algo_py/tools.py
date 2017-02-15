'''some practice functions for word_stats.py and parser_calc.py'''

def removeSpace(text):
    text2 = ""
    i = 0
    while i < len(text):
        if text != 0x20:
            text2 += text[i]
        i += 1
    return text2

def matchList(elem, lst):
    for i in range(len(lst)):
        if lst[i] == elem:
            return True
    return False

def matchStr(elem, str_):
    for i in range(len(str_)):
        if str_[i] == elem:
            return True
    return False

def strtolower(str_):
    str2 = ""
    for i in range(len(str_)):
        if ord(str_[i]) >= 0x41 and ord(str_[i]) <= 0x5A:
            str2 += chr(ord(str_[i]) + 0x20)
        else:
            str2 += str_[i]
    return str2

def strtoupper(str_): #Warning with accents
    str2 = ""
    for i in range(len(str_)):
        if ord(str_[i]) >= 0x61 and ord(str_[i]) <= 0x7A:
            str2 += chr(ord(str_[i]) - 0x20)
        else:
            str2 += str_[i]
    return str2

def strlen(str_):
    i = 0
    dmp = 0
    while True: #loop while exception
        try:
            dmp = str_[i]
            i += 1
        except IndexError: #if out of range, then return
            return i

def rangeList(car, str_):
    for i in range(len(str_)):
        if str_[i] == car:
            return i

def charConv(car):
    if matchStr('.', car):
        return float(car)
    else:
        return int(car)
