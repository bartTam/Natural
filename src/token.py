
tokens = (
    'PLUS', 'MINUS', 'NUMBER'
)

t_PLUS = r'\+'
t_MINUS = r'-'

def t_NUMBER(t):
    r'\d+(.\d+)?'
    t.value = float(t.value)
    return t

t_ignore = ' \t'

def t_newline(t):
    r'(\r?\n)+'
    t.lexer.lineno += t.value.count('\n')

def t_error(t):
    print(f'Illegal character {t.value[0]}')
    t.lexer.skip(1)

import ply.lex as lex
lex.lex()

precedence = (
    ('left', 'PLUS', 'MINUS')
)

def p_statement_expr(p):
    'statement : expression'
    print(p[1])

def p_expression_binop(p):
    '''expression : expression PLUS expression
                  | expression MINUS expression'''
    if p[2] == '+'  : p[0] = p[1] + p[3]
    elif p[2] == '-': p[0] = p[1] - p[3]

def p_expression_number(p):
    'expression : NUMBER'
    p[0] = p[1]

def p_error(p):
    print(f'Syntax error at {p.value}')

import ply.yacc as yacc
yacc.yacc()

while True:
    try:
        s = input('entar those nums > ')
    except EOFError:
        break
    yacc.parse(s)
