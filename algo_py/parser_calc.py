from tools import *

def parseString(expr):
    exprMat = []
    (charList,typeList) = ([],[])
    i = 0
    while i < len(expr):
        charList.append(expr[i])
        typeList.append(parseCharType(expr[i]))
        i += 1
        
    exprMat.append(charList)
    exprMat.append(typeList)
    
    return exprMat

def parseMath(exprList):
    #TODO letter
    exprMat = []
    (mathElemList, mathTypeList) = ([],[])
    i = 0
    while i < len(exprList[0]):
        if exprList[1][i] == "digit":
            nb = 0
            j = 0
            while i + j < len(exprList[0]) and exprList[1][i + j] == "digit":
                nb = nb * 10 + int(exprList[0][i + j])
                j += 1
            i += j - 1
            mathElemList.append(str(nb))
            mathTypeList.append("number")

        elif exprList[1][i] == "letter":
            nb = 0
            j = 0
            while i + j < len(exprList[0]) and exprList[1][i + j] == "letter":
                nb = nb * 10 + int(exprList[0][i + j])
                j += 1
            i += j - 1
            mathElemList.append(str(nb))
            mathTypeList.append("variable")

        elif exprList[1][i] == "operator":
            if i + 1 < len(exprList[0]) and exprList[0][i + 1] == '=' and (exprList[0][i] == '='
                                            or exprList[0][i] == '<'
                                            or exprList[0][i] == '>'
                                            or exprList[0][i] == '!'): #for logical operators
                mathElemList.append(exprList[0][i] + exprList[0][i + 1])
                i += 1
            else:
                mathElemList.append(exprList[0][i])
            mathTypeList.append("operator")
        i += 1

    exprMat.append(mathElemList)
    exprMat.append(mathTypeList)
    
    return exprMat

'''def parseMath_(expr, exprList):
    #TODO letter, operator
    exprMat = []
    mathElemList = []
    mathTypeList = []
    i = 0
    while i < len(expr):
        if exprList[1][i] == "digit":
            nb = 0
            j = 0
            while i + j < len(expr) and exprList[1][i + j] == "digit":
                nb = nb * 10 + int(expr[i + j])
                j += 1
            i += j - 1
            mathElemList.append(str(nb))
            mathTypeList.append("number")
        elif exprList[1][i] == "letter":
            mathElemList.append(expr[i])
            mathTypeList.append("letter")
        elif exprList[1][i] == "operator":
            if expr[i + 1] == '=' and (expr[i] == '='
                                       or expr[i] == '<'
                                       or expr[i] == '>'
                                       or expr[i] == '!'):
                mathElemList.append(expr[i] + expr[i + 1])
                i += 1
            else:
                mathElemList.append(expr[i])
            mathTypeList.append("operator")
        i += 1
    exprMat.append(mathElemList)
    exprMat.append(mathTypeList)
    return exprMat'''

def parseCharType(car):
    ord_char = ord(car)
    if ord_char >= 0x30 and ord_char <= 0x39:
        return "digit"
    elif ord_char >= 0x61 and ord_char <= 0x7A or ord_char >= 0x41 and ord_char <= 0x5A:
        return "letter"
    elif ord_char >= 0x28 and ord_char <= 0x2B or ord_char >= 0x3C and ord_char <= 0x3E or ord_char == 0x2D or ord_char == 0x2F:
        return "operator"
    elif ord_char == 0x20:
        return "space"
    else:
        return "none"

def calc(exprList):
    print(exprList)
    while matchList('(', exprList[0]): #check if ( or ) (1/3)
        newList = [[],[]]
        calcList = [[],[]]

        i = 0
        while i < len(exprList[0]): #parenthese parsing
            if exprList[0][i] == '(':
                j = 1
                parnths = 1 #parenthese count
                while i + j < len(exprList[0]) and parnths > 0:
                    if exprList[0][i + j] == '(':
                        parnths += 1
                    elif exprList[0][i + j] == ')':
                        parnths -= 1
                    calcList[0].append(exprList[0][i + j])
                    calcList[1].append(exprList[1][i + j])
                    j += 1
                calcList[0].pop() #to remove the last parenthese
                calcList[1].pop()
                calcList = calc(calcList)
                newList[0].append(calcList[0][0])
                newList[1].append(calcList[1][0])
                i += j - 1
            else:
                newList[0].append(exprList[0][i])
                newList[1].append(exprList[1][i])
            i += 1
        exprList = newList
        print(exprList)

    while matchList('*', exprList[0]) or matchList('/', exprList[0]): #check if * or / (2/3)
        exprList = calcProd(exprList)

    exprList = calcSum(exprList) #only + and -, OK (3/3)
    
    return exprList

'''def calc(exprList):
    newList = [[],[]]
    while matchList('(', exprList[0]): #check if ( or ) (1/3)
        calcList = [[],[]]
        i = 0
        while i < len(exprList[0]):
            if exprList[0][i] == '(':
                j = 1
                while i + j < len(exprList[0]) and exprList[0][i + j] != ')':
                    calcList[0].append(exprList[0][i + j])
                    calcList[1].append(exprList[1][i + j])
                    j += 1
                calcList = calc(calcList)
                newList[0].append(calcList[0][0])
                newList[1].append(calcList[1][0])
                i += j
            else:
                newList[0].append(exprList[0][i])
                newList[1].append(exprList[1][i])
            i += 1
        exprList = newList
        print(exprList)
    while matchList('*', exprList[0]) or matchList('/', exprList[0]): #check if * or / (2/3)
        exprList = calcProd(exprList)
    exprList = calcSum(exprList) #only + and -, OK (3/3)
    return exprList
    '''

def calcSum(exprList):
    exprMat = []
    (mathElemList, mathTypeList) = ([],[])
    if exprList[1][0] == "number":
        nbSum = charConv(exprList[0][0])
    else:
        nbSum = 0
    i = 0
    
    while i < len(exprList[0]):
        if exprList[0][i] == '+' and exprList[1][i + 1] == "number":
            nbSum += charConv(exprList[0][i + 1])
        elif exprList[0][i] == '-' and exprList[1][i + 1] == "number":
            nbSum -= charConv(exprList[0][i + 1])
        i += 1
        
    mathElemList.append(str(nbSum))
    mathTypeList.append("number")
    
    exprMat.append(mathElemList)
    exprMat.append(mathTypeList)
    
    return exprMat

def calcProd(exprList):
    exprMat = []
    (mathElemList, mathTypeList) = ([],[])
    i = 0
    while i < len(exprList[0]):
        if i + 2 < len(exprList[0]) and (exprList[1][i] == "number"
                                    and exprList[0][i + 1] == '*'):
            if exprList[1][i + 2] == "number":
                nbProd = charConv(exprList[0][i]) * charConv(exprList[0][i + 2])
                mathElemList.append(str(nbProd))
                mathTypeList.append("number")
                i += 3
            elif i + 3 < len(exprList[0]) and exprList[0][i + 2] == '-' and exprList[1][i + 3] == "number":
                nbProd = charConv(exprList[0][i]) * charConv(exprList[0][i + 3])
                mathElemList.append('-')
                mathTypeList.append("operator")
                mathElemList.append(str(nbProd))
                mathTypeList.append("number")
                i += 4

        elif i + 2 < len(exprList[0]) and (exprList[1][i] == "number"
                                    and exprList[0][i + 1] == '/'):
            if exprList[1][i + 2] == "number":
                nbProd = charConv(exprList[0][i]) / charConv(exprList[0][i + 2])
                mathElemList.append(str(nbProd))
                mathTypeList.append("number")
                i += 3
            elif i + 3 < len(exprList[0]) and exprList[0][i + 2] == '-' and exprList[1][i + 3] == "number":
                nbProd = charConv(exprList[0][i]) / charConv(exprList[0][i + 3])
                mathElemList.append('-')
                mathTypeList.append("operator")
                mathElemList.append(str(nbProd))
                mathTypeList.append("number")
                i += 4
        else:
            mathElemList.append(exprList[0][i])
            mathTypeList.append(exprList[1][i])
            i += 1

    exprMat.append(mathElemList)
    exprMat.append(mathTypeList)
    
    return exprMat

def solve(exprList): #later...
    pass

def parse(exprList):
    pass

def returnNbResult(exprList):
    i = 0
    if len(exprList[1]) == 1 and exprList[1][0] == "number":
        return charConv(exprList[0][0])
    else:
        raise Exception("Value to return must be a number")
    return i

def removeSpace(expr):
    expr2 = ""
    i = 0
    while i < len(expr):
        if parseCharType(expr[i]) != "space":
            expr2 += expr[i]
        i += 1
        
    return expr2

'''for i in range(255):
    print('\'' + chr(i) + '\' == ' + parseCharType(chr(i)))
'''


expr = "56 * (4 + (13 - 7) / 3 + 4) * 2"

string = parseString(expr)
math = parseMath(string)
calcul = calc(math)
result = returnNbResult(calcul)


print(string)
print(math)
print(calcul)
print(result)
