from parser_calc import *

def test_parser_calc(expr, atmpt_result):
    string = parseString(expr)
    math = parseMath(string)
    calcul = calc(math)
    result = returnNbResult(calcul)

    return atmpt_result == result

print(test_parser_calc("2+2", 4)) #addition
print(test_parser_calc("195-45", 150)) #substraction
print(test_parser_calc("25*25", 625)) #multiplication
print(test_parser_calc("100/25", 4)) #int division
print(test_parser_calc("45/2", 22.5)) #float division
print(test_parser_calc(" 45 /2+3", 25.5)) #spaces
print(test_parser_calc("(25+5)", 30)) #simple parenthese
print(test_parser_calc("((25+5))", 30)) #useless parenthese
print(test_parser_calc("(25 + 5 * (9-3))", 55)) #imbriqued parentheses
print(test_parser_calc("(10+34) * (56-23)", 1452)) #pair of parentheses
print(test_parser_calc("(22+22) * (33-25) * ((1156-333) + (987*123))", 43022848)) #parentheses invasion
print(test_parser_calc("(10+34 * (67 + 5354))", 184324)) #many parentheses (1/2)
print(test_parser_calc("(10+34 * (67 + 5354)) * (56-23)", 6082692)) #many parentheses (2/2)
print(test_parser_calc("56 * (4 + (13 - 7) / 3 + 4) * 2", 1120.0)) #kd
print(test_parser_calc("(5 + 6) * 56 * (4 + (13 - 7) / 3 + 4) * 2", 12320.0)) #kd+
