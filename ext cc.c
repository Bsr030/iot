////////////////////////-----DO NOT CHANGE ANY THING JUST ADD AT THE BOTTOM AND UPDATE IN INDEX------//////////////////////////////////////////////////////////


1. all lex programs
2. LL(1) parser code in python
3. First and Follow
4. FIRST
5. FOLLOW
6. Parser in lex
7. Predictive parser in C
8. Recursive descent parser 
9. Scanner in C
10. Parser in C
11. Parser generator using YACC (Calculator)
12. C program for Three address code generation
13. YACC program for generate Quadruple.
14. LL(1)
15. SLR
16. CLR




///////////////////////hu///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
1.Problem Statement : Lex programs to recognize Keywords.
Description : token can look like anything that is useful for processing an input text stream or
text file.
Source Code:
%{
#include<stdio.h>
%}
%%
int|float|char { printf(" data type: %s",yytext); }
%%
int main()
{ 
yylex();
return(0);
}
int yywrap()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
2.Problem Statement : Lex programs to recognize String ending with 00.
Description : token can look like anything that is useful for processing an input text stream or
text file.
Source Code:
%{
#include<stdio.h>
%}
%%
[a-z A-Z 0-9]+00 { printf("%s is acepted",yytext);}
.* { printf("not acepted",yytext);}
%%
int main()
{
yylex();
return(0);
}
int yywrap()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
3.Problem Statement : Program to recognize the strings which are starting or ending with ‘k’.
Description : token can look like anything that is useful for processing an input text stream or
text file.
Source Code:
%{
#include<stdio.h>
%}
begin-with-k k.*
end-with-k .*k
%%
{begin-with-k} { printf(" %s is a word that begin with k",yytext);}
{end-with-k} { printf(" %s is a word that end with k",yytext);}
%%
int main()
{
yylex();
return(0);
}
int yywrap()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
4.Problem Statement : program to assign line numbers for source code.
Description : token can look like anything that is useful for processing an input text stream or
text file.
Source Code:
%{
#include<stdio.h>
int lineno=0;
%}
line .*\n
%%
{line} { printf("%d,%s",lineno++,yytext); }
%%
int main(int argc,char **argv)
{
if(argc>1)
{
FILE *file;
file=fopen(argv[1],"r");
if(!file)
{
printf("could not open %s\n",argv[1]);
exit(0);
}
yyin=file;
}
yylex();
printf("\n\n");
return 0;
}
int yywrap()
{
return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
5.Problem Statement : Program to recognize the numbers which has 1 in its 5th position from
right.
Description : token can look like anything that is useful for processing an input text stream or
text file.
Source Code:
%{
#include<stdio.h>
%}
%%
[0-9]*1[0-9]{4}[^0-9] { printf("acepted:%s\n",yytext);}
[0-9]+ { printf("NOT acepted:%s\n",yytext);}
%%
int main()
{
yylex();
return(0);
}
int yywrap()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
6.Lex Specification to Replace Space with $

%{
#include <stdio.h>
%}
%%
[ ]     { printf("$"); }  // Replaces each space with a dollar sign
%%
int main()
{
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
7.Lex Specification to Identify the Number Divisible by 9

%{
#include <stdio.h>
%}
%%
[0-9]+  { int num = atoi(yytext); if (num % 9 == 0) printf("%s is divisible by 9\n", yytext); }
%%
int main()
{
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

8. Lex Specification to Identify Identifier and Functional Identifier

%{
#include <stdio.h>
%}
%%
[a-zA-Z_][a-zA-Z0-9_]*        { printf("Identifier: %s\n", yytext); } // var name - ex: var_name1
[a-zA-Z_][a-zA-Z0-9_]*\(      { printf("Functional Identifier: %s\n", yytext); }  //function names-ex: myFunc(
%%
int main()
{
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

                        
                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

9.Lex Specification to Identify Comments

%{
#include <stdio.h>
%}
%%
"//".*   { printf("Comment: %s\n", yytext); }  // Matches single line comments
/\*[^*]*\*+([^/*][^*]*\*+)*/ { printf("Comment: %s\n", yytext); } // Matches multiline comments
%%
int main()
{
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

10.Lex Specification to Identify Real Numbers

%{
#include <stdio.h>
%}
%%
[0-9]+\.[0-9]+([eE][-+]?[0-9]+)?  { printf("Real Number: %s\n", yytext); }  // Matches floating point numbers with optional exponent
%%
int main()
{
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
11.Problem Statement : Implement lexical analyzer in Lex.
Description : The lexical analysis programs written with Lex accept ambiguous specifications
and choose the longest match possible at each input point. If necessary, substantial look a head is
performed on the input, but the input stream will be backed up to the end of the current partition,
so that the user has general freedom to manipulate it.

Source Code:
%{
int COMMENT=0;
%}
identifier [a-z A-Z][a-z A-Z 0-9]*
%%
#.* {printf("\n %s is a PREPROCESSOR DIRECTIVE",yytext);}
int|float|char|double|while|for|do|if|break|continue|void|switch|case|long|struc
t|const|typedef|return|else|goto|main {printf("\n\t %s is a KEYWORD",yytext);}
"%*" {COMMENT=1;}
"*/" {COMMENT=0;}
{identifier}\( {if(!COMMENT) printf("\n\n FUNCTION \n\t%s",yytext); }
\{ {if(!COMMENT) printf("\n BLOCK BEGINS");}
\} {if(!COMMENT) printf("\n BLOCK ENDS");}
{identifier}(\ [[0-9]*\])? {if(!COMMENT) printf("\n %s IDENTIFIER",yytext);}
\".*\" { if(!COMMENT) printf("\n\t%s is a STRING",yytext);}
[0-9]+ { if(!COMMENT) printf("\n\t%s is a NUMBER",yytext);}
\)(\;)? {if(!COMMENT) printf("\n\t");
ECHO;
printf("\n");}
\(ECHO;
= {if(!COMMENT) printf("\n\t is an ASSIGNMENT OPERATOR",yytext);}
\<=|\>=|\<|==|\> {if(!COMMENT) printf("\n\t %s is a RELATIONAL OPERATOR",yytext)
;}
\b|\t {if(!COMMENT) printf("\n white space",yytext);}
\n { ; }
%%
int main(int argc,char **argv)
{
if(argc>1)
{
FILE *file;
file=fopen(argv[1],"r");
if(!file)
{
printf("could not open %s\n",argv[1]);
exit(0);
}
yyin=file;
}
yylex();
printf("\n\n");
return 0;
}
int yywrap()
{
return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# LL(1) parser code in python

def removeLeftRecursion(rulesDiction):
	store = {}
	for lhs in rulesDiction:
		alphaRules = []
		betaRules = []
		allrhs = rulesDiction[lhs]
		for subrhs in allrhs:
			if subrhs[0] == lhs:
				alphaRules.append(subrhs[1:])
			else:
				betaRules.append(subrhs)
		if len(alphaRules) != 0:
			lhs_ = lhs + "'"
			while (lhs_ in rulesDiction.keys()) \
					or (lhs_ in store.keys()):
				lhs_ += "'"
			for b in range(0, len(betaRules)):
				betaRules[b].append(lhs_)
			rulesDiction[lhs] = betaRules
			for a in range(0, len(alphaRules)):
				alphaRules[a].append(lhs_)
			alphaRules.append(['#'])
			store[lhs_] = alphaRules
	for left in store:
		rulesDiction[left] = store[left]
	return rulesDiction


def LeftFactoring(rulesDiction):
	newDict = {}
	for lhs in rulesDiction:
		allrhs = rulesDiction[lhs]
		temp = dict()
		for subrhs in allrhs:
			if subrhs[0] not in list(temp.keys()):
				temp[subrhs[0]] = [subrhs]
			else:
				temp[subrhs[0]].append(subrhs)
		new_rule = []
		tempo_dict = {}
		for term_key in temp:
			allStartingWithTermKey = temp[term_key]
			if len(allStartingWithTermKey) > 1:
				lhs_ = lhs + "'"
				while (lhs_ in rulesDiction.keys()) \
						or (lhs_ in tempo_dict.keys()):
					lhs_ += "'"
				new_rule.append([term_key, lhs_])
				ex_rules = []
				for g in temp[term_key]:
					ex_rules.append(g[1:])
				tempo_dict[lhs_] = ex_rules
			else:
				new_rule.append(allStartingWithTermKey[0])
		newDict[lhs] = new_rule
		for key in tempo_dict:
			newDict[key] = tempo_dict[key]
	return newDict
def first(rule):
	global rules, nonterm_userdef, \
		term_userdef, diction, firsts
	if len(rule) != 0 and (rule is not None):
		if rule[0] in term_userdef:
			return rule[0]
		elif rule[0] == '#':
			return '#'
	if len(rule) != 0:
		if rule[0] in list(diction.keys()):
			fres = []
			rhs_rules = diction[rule[0]]
			for itr in rhs_rules:
				indivRes = first(itr)
				if type(indivRes) is list:
					for i in indivRes:
						fres.append(i)
				else:
					fres.append(indivRes)
			if '#' not in fres:
				return fres
			else:
				newList = []
				fres.remove('#')
				if len(rule) > 1:
					ansNew = first(rule[1:])
					if ansNew != None:
						if type(ansNew) is list:
							newList = fres + ansNew
						else:
							newList = fres + [ansNew]
					else:
						newList = fres
					return newList
				fres.append('#')
				return fres
def follow(nt):
	global start_symbol, rules, nonterm_userdef, \
		term_userdef, diction, firsts, follows

	solset = set()
	if nt == start_symbol:
		solset.add('$')
	for curNT in diction:
		rhs = diction[curNT]
		for subrule in rhs:
			if nt in subrule:
				while nt in subrule:
					index_nt = subrule.index(nt)
					subrule = subrule[index_nt + 1:]
					if len(subrule) != 0:
						res = first(subrule)
						if '#' in res:
							newList = []
							res.remove('#')
							ansNew = follow(curNT)
							if ansNew != None:
								if type(ansNew) is list:
									newList = res + ansNew
								else:
									newList = res + [ansNew]
							else:
								newList = res
							res = newList
					else:
						if nt != curNT:
							res = follow(curNT)

					# add follow result in set form
					if res is not None:
						if type(res) is list:
							for g in res:
								solset.add(g)
						else:
							solset.add(res)
	return list(solset)


def computeAllFirsts():
	global rules, nonterm_userdef, \
		term_userdef, diction, firsts
	for rule in rules:
		k = rule.split("->")
		# remove un-necessary spaces
		k[0] = k[0].strip()
		k[1] = k[1].strip()
		rhs = k[1]
		multirhs = rhs.split('|')
		for i in range(len(multirhs)):
			multirhs[i] = multirhs[i].strip()
			multirhs[i] = multirhs[i].split()
		diction[k[0]] = multirhs

	print(f"\nRules: \n")
	for y in diction:
		print(f"{y}->{diction[y]}")
	print(f"\nAfter elimination of left recursion:\n")

	diction = removeLeftRecursion(diction)
	for y in diction:
		print(f"{y}->{diction[y]}")
	print("\nAfter left factoring:\n")

	diction = LeftFactoring(diction)
	for y in diction:
		print(f"{y}->{diction[y]}")
	for y in list(diction.keys()):
		t = set()
		for sub in diction.get(y):
			res = first(sub)
			if res != None:
				if type(res) is list:
					for u in res:
						t.add(u)
				else:
					t.add(res)
		firsts[y] = t

	print("\nCalculated firsts: ")
	key_list = list(firsts.keys())
	index = 0
	for gg in firsts:
		print(f"first({key_list[index]}) "
			f"=> {firsts.get(gg)}")
		index += 1


def computeAllFollows():
	global start_symbol, rules, nonterm_userdef,\
		term_userdef, diction, firsts, follows
	for NT in diction:
		solset = set()
		sol = follow(NT)
		if sol is not None:
			for g in sol:
				solset.add(g)
		follows[NT] = solset

	print("\nCalculated follows: ")
	key_list = list(follows.keys())
	index = 0
	for gg in follows:
		print(f"follow({key_list[index]})"
			f" => {follows[gg]}")
		index += 1
def createParseTable():
	import copy
	global diction, firsts, follows, term_userdef
	print("\nFirsts and Follow Result table\n")
	mx_len_first = 0
	mx_len_fol = 0
	for u in diction:
		k1 = len(str(firsts[u]))
		k2 = len(str(follows[u]))
		if k1 > mx_len_first:
			mx_len_first = k1
		if k2 > mx_len_fol:
			mx_len_fol = k2

	print(f"{{:<{10}}} "
		f"{{:<{mx_len_first + 5}}} "
		f"{{:<{mx_len_fol + 5}}}"
		.format("Non-T", "FIRST", "FOLLOW"))
	for u in diction:
		print(f"{{:<{10}}} "
			f"{{:<{mx_len_first + 5}}} "
			f"{{:<{mx_len_fol + 5}}}"
			.format(u, str(firsts[u]), str(follows[u])))
	ntlist = list(diction.keys())
	terminals = copy.deepcopy(term_userdef)
	terminals.append('$')
	mat = []
	for x in diction:
		row = []
		for y in terminals:
			row.append('')
		mat.append(row)
	grammar_is_LL = True
	for lhs in diction:
		rhs = diction[lhs]
		for y in rhs:
			res = first(y)
			if '#' in res:
				if type(res) == str:
					firstFollow = []
					fol_op = follows[lhs]
					if fol_op is str:
						firstFollow.append(fol_op)
					else:
						for u in fol_op:
							firstFollow.append(u)
					res = firstFollow
				else:
					res.remove('#')
					res = list(res) +\
						list(follows[lhs])
			ttemp = []
			if type(res) is str:
				ttemp.append(res)
				res = copy.deepcopy(ttemp)
			for c in res:
				xnt = ntlist.index(lhs)
				yt = terminals.index(c)
				if mat[xnt][yt] == '':
					mat[xnt][yt] = mat[xnt][yt] \
								+ f"{lhs}->{' '.join(y)}"
				else:
					if f"{lhs}->{y}" in mat[xnt][yt]:
						continue
					else:
						grammar_is_LL = False
						mat[xnt][yt] = mat[xnt][yt] \
									+ f",{lhs}->{' '.join(y)}"
	print("\nGenerated parsing table:\n")
	frmt = "{:>12}" * len(terminals)
	print(frmt.format(*terminals))

	j = 0
	for y in mat:
		frmt1 = "{:>12}" * len(y)
		print(f"{ntlist[j]} {frmt1.format(*y)}")
		j += 1

	return (mat, grammar_is_LL, terminals)


def validateStringUsingStackBuffer(parsing_table, grammarll1,
								table_term_list, input_string,
								term_userdef,start_symbol):

	print(f"\nValidate String => {input_string}\n")
	if grammarll1 == False:
		return f"\nInput String = " \
			f"\"{input_string}\"\n" \
			f"Grammar is not LL(1)"

	stack = [start_symbol, '$']
	buffer = []
	input_string = input_string.split()
	input_string.reverse()
	buffer = ['$'] + input_string

	print("{:>20} {:>20} {:>20}".
		format("Buffer", "Stack","Action"))

	while True:
		if stack == ['$'] and buffer == ['$']:
			print("{:>20} {:>20} {:>20}"
				.format(' '.join(buffer),
						' '.join(stack),
						"Valid"))
			return "\nValid String!"
		elif stack[0] not in term_userdef:
			x = list(diction.keys()).index(stack[0])
			y = table_term_list.index(buffer[-1])
			if parsing_table[x][y] != '':
				entry = parsing_table[x][y]
				print("{:>20} {:>20} {:>25}".
					format(' '.join(buffer),
							' '.join(stack),
							f"T[{stack[0]}][{buffer[-1]}] = {entry}"))
				lhs_rhs = entry.split("->")
				lhs_rhs[1] = lhs_rhs[1].replace('#', '').strip()
				entryrhs = lhs_rhs[1].split()
				stack = entryrhs + stack[1:]
			else:
				return f"\nInvalid String! No rule at " \
					f"Table[{stack[0]}][{buffer[-1]}]."
		else:
			if stack[0] == buffer[-1]:
				print("{:>20} {:>20} {:>20}"
					.format(' '.join(buffer),
							' '.join(stack),
							f"Matched:{stack[0]}"))
				buffer = buffer[:-1]
				stack = stack[1:]
			else:
				return "\nInvalid String! " \
					"Unmatched terminal symbols"

sample_input_string = None
rules=["S -> A k O",
	"A -> A d | a B | a C",
	"C -> c",
	"B -> b B C | r"]

nonterm_userdef=['A','B','C']
term_userdef=['k','O','d','a','c','b','r']
sample_input_string="a r k O"
diction = {}
firsts = {}
follows = {}
computeAllFirsts()
start_symbol = list(diction.keys())[0]
computeAllFollows()

(parsing_table, result, tabTerm) = createParseTable()
if sample_input_string != None:
	validity = validateStringUsingStackBuffer(parsing_table, result,
											tabTerm, sample_input_string,
											term_userdef,start_symbol)
	print(validity)
else:
	print("\nNo input String detected")
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FIRST AND FOLLOW
import re

def cal_follow(s, productions, first):
    follow = set()
    if len(s)!=1 :
        return {}
    if(s == list(productions.keys())[0]):
        follow.add('$') 
    
    for i in productions:
        for j in range(len(productions[i])):
            if(s in productions[i][j]):
                idx = productions[i][j].index(s)
                
                if(idx == len(productions[i][j])-1):
                    if(productions[i][j][idx] == i):
                        break
                    else:
                        f = cal_follow(i, productions, first)
                        for x in f:
                            follow.add(x)
                else:
                    while(idx != len(productions[i][j]) - 1):
                        idx += 1
                        if(not productions[i][j][idx].isupper()):
                            follow.add(productions[i][j][idx])
                            break
                        else:
                            f = cal_first(productions[i][j][idx], productions)
                            
                            if('ε' not in f):
                                for x in f:
                                    follow.add(x)
                                break
                            elif('ε' in f and idx != len(productions[i][j])-1):
                                f.remove('ε')
                                for k in f:
                                    follow.add(k)
                            
                            elif('ε' in f and idx == len(productions[i][j])-1):
                                f.remove('ε')
                                for k in f:
                                    follow.add(k)
                                
                                f = cal_follow(i, productions, first)
                                for x in f:
                                    follow.add(x)
                            
    return follow
   
def cal_first(s, productions):
    
    first = set()
    
    for i in range(len(productions[s])):
        
        for j in range(len(productions[s][i])):
            
            c = productions[s][i][j]
            
            if(c.isupper()):
                f = cal_first(c, productions)
                if('ε' not in f):
                    for k in f:
                        first.add(k)
                    break
                else:
                    if(j == len(productions[s][i])-1):
                        for k in f:
                            first.add(k)
                    else:
                        f.remove('ε')
                        for k in f:
                            first.add(k)
            else:
                first.add(c)
                break
                
    return first
                       
def main():
    productions = {}
    grammar = open("grammar9.txt", "r")
    
    first = {}
    follow = {}
    
    for prod in grammar:
        l = re.split("( /->/\n/)*", prod)
        m = []
        for i in l:
            if (i == "" or i == None or i == '\n' or i == " " or i == "-" or i == ">"):
                pass
            else:
                m.append(i)
        
        left_prod = m.pop(0)
        right_prod = []
        t = []
        
        for j in m:
            if(j != '|'):
                t.append(j)
            else:
                right_prod.append(t)
                t = []
        
        right_prod.append(t)
        productions[left_prod] = right_prod
    
    for s in productions.keys():
        first[s] = cal_first(s, productions)
    
    print("*****FIRST*****")
    for lhs, rhs in first.items():
        print(lhs, ":" , rhs)
    
    print("")
    
    for lhs in productions:
        follow[lhs] = set()
    
    for s in productions.keys():
        follow[s] = cal_follow(s, productions, first)
    
    print("*****FOLLOW*****")
    for lhs, rhs in follow.items():
        print(lhs, ":" , rhs)
    
    grammar.close()

if __name__ == "__main__":
    main()



E -> TX
X -> +TX | ε
T -> FY
Y -> *FY | ε
F -> id | (E)


*****FIRST*****
E : {'i', '('}
X : {'+', 'ε'}
T : {'i', '('}
Y : {'*', 'ε'}
F : {'i', '('}

*****FOLLOW*****
E : {')', '$'}
X : {')', '$'}
T : {'+', ')', '$'}
Y : {'+', ')', '$'}
F : {'+', ')', '$', '*'}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

First

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_RULES 10 // Maximum number of grammar rules
#define MAX_SYMBOLS 10 // Maximum number of symbols in each rule
 
char grammar[MAX_RULES][100] = {
    "S -> aB",
    "A -> a | #",
    "B -> b | #"
}; // Hardcoded grammar rules
int numRules = 3; // Number of grammar rules

bool isNonTerminal(char symbol) {
    return symbol >= 'A' && symbol <= 'Z';
}

bool isTerminal(char symbol) {
    return !isNonTerminal(symbol);
}

void addFirst(char symbol, char firstSet[]) {
    int i;
    for (i = 0; firstSet[i] != '\0'; i++) {
        if (firstSet[i] == symbol)
            return;
    }
    firstSet[i] = symbol;
    firstSet[i + 1] = '\0';
}

void findFirst(char nonTerminal, char firstSet[]) {
    int i, j;
    for (i = 0; i < numRules; i++) {
        if (grammar[i][0] == nonTerminal) {
            if (isTerminal(grammar[i][5]))
                addFirst(grammar[i][5], firstSet);
            else if (isNonTerminal(grammar[i][5])) {
                char tempFirstSet[MAX_SYMBOLS];
                findFirst(grammar[i][5], tempFirstSet);
                for (j = 0; tempFirstSet[j] != '\0'; j++) {
                    addFirst(tempFirstSet[j], firstSet);
                }
            }
        }
    }
}

int main() {
    char nonTerminal = 'S'; // Hardcoded non-terminal to find FIRST for

    char firstSet[MAX_SYMBOLS] = {'\0'};
    findFirst(nonTerminal, firstSet);

    printf("FIRST(%c) = {%s}\n", nonTerminal, firstSet);

    return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
-------------------------------------------------------------------------------------------------------------------------------------------------------------
FOLLOW

#include<stdio.h>
#include<string.h>
int n,m=0,p,i=0,j=0;
char a[10][10],f[10];
void follow(char c);
void first(char c);
int main()
{
 int i,z;
 char c,ch;
 printf("Enter the no.of productions:");
 scanf("%d",&n);
 printf("Enter the productions(epsilon=$):\n");
 for(i=0;i<n;i++)
  scanf("%s%c",a[i],&ch);

 do
 {
  m=0;
  printf("Enter the element whose FOLLOW is to be found:");

  scanf("%c",&c);
  follow(c);
  printf("FOLLOW(%c) = { ",c);
  for(i=0;i<m;i++)
   printf("%c ",f[i]);
  printf(" }\n");
  printf("Do you want to continue(0/1)?");
  scanf("%d%c",&z,&ch);
 }
 while(z==1);
}
void follow(char c)
{

 if(a[0][0]==c)f[m++]='$';
 for(i=0;i<n;i++)
 {
  for(j=2;j<strlen(a[i]);j++)
  {
   if(a[i][j]==c)
   {
    if(a[i][j+1]!='\0')first(a[i][j+1]);

    if(a[i][j+1]=='\0'&&c!=a[i][0])
     follow(a[i][0]);

   }
  }
 }
}
void first(char c)
{
      int k;
                 if(!(isupper(c)))f[m++]=c;
                 for(k=0;k<n;k++)
                 {
                 if(a[k][0]==c)
                 {
                 if(a[k][2]=='$') follow(a[i][0]);
                 else if(islower(a[k][2]))f[m++]=a[k][2];
                 else first(a[k][2]);
                 }
                 }

}





SAMPLE OUTPUT:

productions:
E=TD
D=+TD
D=$
T=FS
S=*FS
S=$
F=(E)
F=a

FOLLOW(E)=FOLLOW(D)={),$}
FOLLOW(T)=FOLLOW(S)={+,),$}
FOLLOW(F)={+,*,),$}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------------

Parser in Lex

%{
#include <stdio.h>
#include <string.h>

char s_comments[100][100];
char m_comments[100][100];
int s_num = 0;
int m_num = 0;


char operators[100][10];
int op_num = 0;

%}

%%
"//"[a-zA-Z0-9\t/.,;:"!@#$%^&() ]"\n" {
strcpy(s_comments[s_num], yytext);
s_num++;
}

"/"[a-zA-Z0-9\t\n/.,;:"!@#$%^&() ]"/" {
strcpy(m_comments[m_num], yytext);
m_num++;
}

[-+/=]|[-+\/]=|[<>!=][=]  {
strcpy(operators[op_num], yytext);
op_num++;
}



%%

int yywrap() {} no

int main(int argc, char* argv[])
{
        if(argc == 2)
                yyin = fopen(argv[1], "r");
        yylex();
        fclose(yyin);

        int i;
        printf("Single Line Comments:\n");
        for(i = 0; i < s_num; i++)
                printf("%s\n", s_comments[i]);
        printf("Total: %d\n", s_num);

       
        printf("Multi Line Comments:\n");
        for(i = 0; i < m_num; i++)
                printf("%s\n", m_comments[i]);
        printf("Total: %d\n", m_num);

        printf("Operators:\n");
        for(i = 0; i < op_num; i++)
                printf("%s\n", operators[i]);
        printf("Total: %d\n", op_num);

        return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
------------------------------------------------------------------------
Predictive parser in C

#include <stdio.h>
#include <string.h>
 
char prol[7][10] = { "S", "A", "A", "B", "B", "C", "C" };
char pror[7][10] = { "A", "Bb", "Cd", "aB", "@", "Cc", "@" };
char prod[7][10] = { "S->A", "A->Bb", "A->Cd", "B->aB", "B->@", "C->Cc", "C->@" };
char first[7][10] = { "abcd", "ab", "cd", "a@", "@", "c@", "@" };
char follow[7][10] = { "$", "$", "$", "a$", "b$", "c$", "d$" };
char table[5][6][10];
 
int numr(char c)
{
   switch (c)
   {
      case 'S':
         return 0;
 
      case 'A':
         return 1;
 
      case 'B':a
         return 2;
 
      case 'C':
         return 3;
 
      case 'a':
         return 0;
 
      case 'b':
         return 1;
 
      case 'c':
         return 2;

      case 'd':
         return 3;
 
      case '$':
         return 4;
   }
 
   return (2);
}
 
int main()
{
   int i, j, k;
 
   for (i = 0; i < 5; i++)
      for (j = 0; j < 6; j++)
         strcpy(table[i][j], " ");
 
   printf("The following grammar is used for Parsing Table:\n");
 
   for (i = 0; i < 7; i++)
      printf("%s\n", prod[i]);
 
   printf("\nPredictive parsing table:\n");
 
   fflush(stdin);
 
   for (i = 0; i < 7; i++)
   {
      k = strlen(first[i]);
      for (j = 0; j < 10; j++)
         if (first[i][j] != '@')
            strcpy(table[numr(prol[i][0]) + 1][numr(first[i][j]) + 1], prod[i]);
   }
 
   for (i = 0; i < 7; i++)
   {
      if (strlen(pror[i]) == 1)
      {
         if (pror[i][0] == '@')
         {
            k = strlen(follow[i]);
            for (j = 0; j < k; j++)
               strcpy(table[numr(prol[i][0]) + 1][numr(follow[i][j]) + 1], prod[i]);
         }
      }
   }
 
   strcpy(table[0][0], " ");
 
   strcpy(table[0][1], "a");
 
   strcpy(table[0][2], "b");
 
   strcpy(table[0][3], "c");
 
   strcpy(table[0][4], "d");
 
   strcpy(table[0][5], "$");
 
   strcpy(table[1][0], "S");
 
   strcpy(table[2][0], "A");
 
   strcpy(table[3][0], "B");
 
   strcpy(table[4][0], "C");
 
   printf("\n--------------------------------------------------------\n");
 
   for (i = 0; i < 5; i++)
      for (j = 0; j < 6; j++)
      {
         printf("%-10s", table[i][j]);
         if (j == 5)
            printf("\n--------------------------------------------------------\n");
      }
}

------------------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
Recursive descent parser : 
 
#include<stdio.h> 
#include<string.h> 
#include<ctype.h> 
  
char input[10]; 
int i,error; 
void E(); 
void T(); 
void Eprime(); 
void Tprime(); 
void F();  
 
main() { 
    i=0; 
    error=0; 
    printf("Enter an arithmetic expression   :  "); // Eg: a+a*a 
    gets(input); 
    E(); 
    if(strlen(input)==i && error==0) 
        printf("\nAccepted..!!!\n"); 
    else  
        printf("\nRejected..!!!\n"); 
} 
 
void E() { 
    T(); 
    Eprime(); 
} 
 
void Eprime() { 
    if(input[i] == '+') { 
        i++; 
        T(); 
        Eprime(); 
    } 
} 
 
void T() { 
    F(); 
    Tprime(); 
}
 
void Tprime() { 
    if(input[i] == '*') { 
        i++; 
        F(); 
        Tprime(); 
    } 
} 
 
void F() { 
    if(isalnum(input[i])) 
        i++; 
    else if(input[i] == '(') { 
        i++; 
        E(); 
        if(input[i] == ')') 
            i++; 
        else  
            error = 1; 
    } else  
        error = 1; 
} 
 
 
Output: 
 
a+(a*a)  a+a*a , (a), a , a+a+a*a+a.... etc are  accepted 
++a, a***a, +a, a*, ((a . . . etc are rejected. 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
---------------------------------------------------------------------------
Scanner in C:
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
bool isValidDelimiter(char ch) {
   if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
   ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
   ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
   ch == '[' || ch == ']' || ch == '{' || ch == '}')
   return (true);
   return (false);
}
bool isValidOperator(char ch){
   if (ch == '+' || ch == '-' || ch == '*' ||
   ch == '/' || ch == '>' || ch == '<' ||
   ch == '=')
   return (true);
   return (false);
}
// Returns 'true' if the string is a VALID IDENTIFIER.
bool isvalidIdentifier(char* str){
   if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
   str[0] == '3' || str[0] == '4' || str[0] == '5' ||
   str[0] == '6' || str[0] == '7' || str[0] == '8' ||
   str[0] == '9' || isValidDelimiter(str[0]) == true)
   return (false);
   return (true);
}
bool isValidKeyword(char* str) {
   if (!strcmp(str, "if") || !strcmp(str, "else") || !strcmp(str, "while") || !strcmp(str, "do") ||    !strcmp(str, "break") || !strcmp(str, "continue") || !strcmp(str, "int")
   || !strcmp(str, "double") || !strcmp(str, "float") || !strcmp(str, "return") || !strcmp(str,    "char") || !strcmp(str, "case") || !strcmp(str, "char")
   || !strcmp(str, "sizeof") || !strcmp(str, "long") || !strcmp(str, "short") || !strcmp(str, "typedef") || !strcmp(str, "switch") || !strcmp(str, "unsigned")
   || !strcmp(str, "void") || !strcmp(str, "static") || !strcmp(str, "struct") || !strcmp(str, "goto"))
   return (true);
   return (false);
}
bool isValidInteger(char* str) {
   int i, len = strlen(str);
   if (len == 0)
   return (false);
   for (i = 0; i < len; i++) {
      if (str[i] != '0' && str[i] != '1' && str[i] != '2'&& str[i] != '3' && str[i] != '4' && str[i] != '5'
      && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' || (str[i] == '-' && i > 0))
      return (false);
   }
   return (true);
}
bool isRealNumber(char* str) {
   int i, len = strlen(str);
   bool hasDecimal = false;
   if (len == 0)
   return (false);
   for (i = 0; i < len; i++) {
      if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i]       != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8'
      && str[i] != '9' && str[i] != '.' || (str[i] == '-' && i > 0))
      return (false);
         if (str[i] == '.')
      hasDecimal = true;
   }
   return (hasDecimal);
}
char* subString(char* str, int left, int right) {
   int i;
   char* subStr = (char*)malloc( sizeof(char) * (right - left + 2));
   for (i = left; i <= right; i++)
      subStr[i - left] = str[i];
   subStr[right - left + 1] = '\0';
   return (subStr);
}
void detectTokens(char* str) {
   int left = 0, right = 0;
   int length = strlen(str);
   while (right <= length && left <= right) {
      if (isValidDelimiter(str[right]) == false)
      right++;
      if (isValidDelimiter(str[right]) == true && left == right) {
         if (isValidOperator(str[right]) == true)
         printf("Valid operator : '%c'
", str[right]);
         right++;
         left = right;
      } else if (isValidDelimiter(str[right]) == true && left != right || (right == length && left !=       right)) {
         char* subStr = subString(str, left, right - 1);
         if (isValidKeyword(subStr) == true)
            printf("Valid keyword : '%s'
", subStr);
         else if (isValidInteger(subStr) == true)
            printf("Valid Integer : '%s'
", subStr);
         else if (isRealNumber(subStr) == true)
            printf("Real Number : '%s'
", subStr);
         else if (isvalidIdentifier(subStr) == true
            && isValidDelimiter(str[right - 1]) == false)
         printf("Valid Identifier : '%s'
", subStr);
         else if (isvalidIdentifier(subStr) == false
            && isValidDelimiter(str[right - 1]) == false)
         printf("Invalid Identifier : '%s'
", subStr);
         left = right;
      }
   }
   return;
}
int main(){
   char str[100] = "float x = a + 1b; ";
   printf("The Program is : '%s' 
", str);
   printf("All Tokens are : 
");
   detectTokens(str);
   return (0);
}
          ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
------------------------------------------------------------------------------------------------------
Parser in C:
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Function to skip whitespaces
void skipWhitespace(const char **expr) {
    while (**expr && isspace(**expr)) {
        (*expr)++;
    }
}

// Function to parse a number
double parseNumber(const char **expr) {
    double result = 0.0;
    while (**expr && isdigit(**expr)) {
        result = result * 10.0 + (**expr - '0');
        (*expr)++;
    }
    if (**expr == '.') {
        (*expr)++;
        double decimal = 0.1;
        while (**expr && isdigit(**expr)) {
            result += (**expr - '0') * decimal;
            decimal *= 0.1;
            (*expr)++;
        }
    }
    return result;
}

// Function to parse factors (numbers or expressions in parenthesis)
double parseFactor(const char **expr) {
    skipWhitespace(expr);
    if (**expr == '(') {
        (*expr)++;
        double result = parseExpression(expr);
        skipWhitespace(expr);
        if (**expr == ')') {
            (*expr)++;
            return result;
        } else {
            fprintf(stderr, "Expected closing parenthesis\n");
            exit(1);
        }
    } else {
        return parseNumber(expr);
    }
}

// Function to parse multiplication and division
double parseTerm(const char **expr) {
    double result = parseFactor(expr);
    skipWhitespace(expr);
    while (**expr == '*' || **expr == '/') {
        char op = **expr;
        (*expr)++;
        double nextFactor = parseFactor(expr);
        if (op == '*') {
            result *= nextFactor;
        } else {
            if (nextFactor == 0) {
                fprintf(stderr, "Division by zero\n");
                exit(1);
            }
            result /= nextFactor;
        }
        skipWhitespace(expr);
    }
    return result;
}

// Function to parse addition and subtraction
double parseExpression(const char **expr) {
    double result = parseTerm(expr);
    skipWhitespace(expr);
    while (**expr == '+' || **expr == '-') {
        char op = **expr;
        (*expr)++;
        double nextTerm = parseTerm(expr);
        if (op == '+') {
            result += nextTerm;
        } else {
            result -= nextTerm;
        }
        skipWhitespace(expr);
    }
    return result;
}

int main() {
    const char *expr = "2.5 * (3 + 4) - 6 / 2";
    double result = parseExpression(&expr);
    printf("Result: %lf\n", result);
    return 0;
}

          
          

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          

11.Parser generator using YACC (Calculator)
Code:
Calculator.l
%{
#include "y.tab.h"
#include<math.h>
%}
%%
[0-9]+ {yylval.dval=atof(yytext);
return NUMBER;
}
log|LOG {return LOG;}
ln {return nLOG;}
sin|SIN {return SINE;}
cos|COS {return COS;}
tan|TAN {return TAN;}
mem {return MEM;}
[\t];
\$; {return 0;}
\n|. {return yytext[0];}
%%

Calculator.y
%{
#include<stdio.h>
#include<math.h>
double memvar;
%}
%union
{
double dval;
}
%token<dval>NUMBER
%token<dval>MEM
%token LOG SINE nLOG COS TAN
%left '-''+'
%left '*''/'
%right '^'
%left LOG SINE nLOG COS TAN
%nonassoc UMINUS
%type<dval> expression
%%
start: statement '\n'
|start statement '\n'
;
statement: MEM'='expression { memvar=$3;}
|expression {printf("answer=%g\n",$1);}
;
expression:expression'+'expression {$$=$1+$3;}
|expression'-'expression {$$=$1+$3;}
|expression'*'expression {$$=$1*$3;}
|expression'/'expression 
{
if($3==0)
yyerror("divide by zero");
else
$$=$1/$3;}
|expression'^'expression {$$=pow($1,$3);}
;
expression: '-' expression %prec UMINUS {$$=-$2;}
|'('expression')' {$$=$2;}
|LOG expression {$$=log($2)/log(10);}
|nLOG expression {$$=log($2);}
|SINE expression {$$=sin($2*3.14159/180);}
|COS expression {$$=cos($2*3.14159/180);}
|TAN expression {$$=tan($2*3.14159/180);}
|NUMBER { $$ = $1;}
|MEM {$$=memvar;}
;
%%
main()
{
printf("enter expression:");
yyparse();
}
int yyerror(char *error)
{
fprintf(stderr,"%s\n",error);
}
yywrap() {  return 1; }

OUTPUT:

$ ./calculator
Enter expression:
12 + 24
answer=36
Enter expression:
sin 30
answer=0.5
Enter expression:
log 100
answer=2
Enter expression:
10 / 0
divide by zero
Enter expression:
mem = 15
Enter expression:
mem + 5
answer=20
Enter expression:
$




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
12.C program for Three address code generation	
Code: 
three.l
%{
#include "y.tab.h"
extern char yyval;
%}
number [0-9]+
letter [a-zA-Z]+
%%
{number} {yylval.sym=(char)yytext[0];return number;}
{letter} {yylval.sym=(char)yytext[0]; return letter; }
\n {return 0;}
.  {return yytext[0];}
%%

Three.y
%{
#include<stdio.h>
#include<string.h>
int nIndex=0;
struct Intercode
{
char operand1;
char operand2;
char opera;
};
%}
%union
{
char sym;
}
%token <sym> letter number
%type  <sym> expr
%left '-' '+'
%right '*' '/'
%%
statement: letter '=' expr ';' { addtotable((char)$1,(char)$3,'=' ); }
              | expr ;
              ;
expr: expr '+' expr  { $$=addtotable((char)$1,(char)$3,'+');}
         | expr '-'  expr { $$=addtotable((char)$1,(char)$3,'-');}
         | expr '*'  expr { $$=addtotable((char)$1,(char)$3, '*');}
         | expr '/'  expr { $$=addtotable((char)$1,(char)$3,'/');}
         | '(' expr ')' { $$= (char)$2;}
         |  number  { $$= (char)$1;}
         | letter { $$= (char)$1;}
%%
yyerror(char *s)
{
printf("%s",s);
exit (0);
}
struct Intercode code[20];
char addtotable(char operand1, char operand2,char opera)
{
char temp = 'A';
code[nIndex].operand1 = operand1;
code[nIndex].operand2 = operand2;
code[nIndex].opera = opera;
nIndex++;
temp++;
return temp;
}
threeaddresscode()
{
int nCnt=0;
char temp='A';
printf("\n\n\t three addrtess codes\n\n");
temp++;
while(nCnt<nIndex)
{
printf("%c:=\t",temp);
if (isalpha(code[nCnt].operand1))
printf("%c\t", code[nCnt].operand1);
else
printf("%c\t",temp);
printf("%c\t", code[nCnt].opera);
if (isalpha(code[nCnt].operand2))
printf("%c\t", code[nCnt].operand2);
else
printf("%c\t",temp);
printf("\n");
nCnt++;
temp++;
}}
main()
{
printf("enter expression");
yyparse();
threeaddresscode();
}
yywrap()
{
return 1;
}

Output:
$ lex three.l
$ yacc -d three.y
$ gcc lex.yy.c y.tab.c -ll -lm
$ ./a.out
enter expression (a*b)+(c*d)
         three addrtess codes

B:=     a       *       b
C:=     c       *       d
D:=     B       +       B


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




13.YACC program for generate Quadruple.
Code: 
/* lex program */
%{
#include "y.tab.h"
extern char yyval;
%}
number [0-9]+
letter [a-zA-Z]+
%%
{number} {yylval.sym=(char)yytext[0];return number;}
{letter} {yylval.sym=(char)yytext[0]; return letter; }
\n {return 0;}
.  {return yytext[0];}
%%

/*yaac program */

%{
#include<stdio.h>
#include<string.h>
int nIndex=0;
struct Intercode
{
char operand1;
char operand2;
char opera;
};
%}
%union
{
char sym;
}
%token <sym> letter number
%type  <sym> expr
%left '-' '+'
%right '*' '/'
%%
Statement: letter '=' expr ';' { addtotable((char)$1,(char)$3,'=' ); }
              | expr ;
              ;
expr: expr '+' expr  { $$=addtotable((char)$1,(char)$3,'+');}
         | expr '-'  expr { $$=addtotable((char)$1,(char)$3,'-');}
         | expr '*'  expr { $$=addtotable((char)$1,(char)$3, '*');}
         | expr '/'  expr { $$=addtotable((char)$1,(char)$3,'/');}
         | '(' expr ')' { $$= (char)$2;}
         |  number  { $$= (char)$1;}
         | letter { $$= (char)$1;}
%%

yyerror(char *s)
{
printf("%s",s);
exit (0);
}
struct Intercode code[20];
char addtotable(char operand1, char operand2,char opera)
{
char temp = 'A';
code[nIndex].operand1 = operand1;
code[nIndex].operand2 = operand2;
code[nIndex].opera = opera;
nIndex++;
temp++;
return temp;
}
threeaddresscode()
{
int nCnt=0;
char temp='A';
printf("\n\n\t three addrtess codes\n\n");
temp++;
while(nCnt<nIndex)
{
printf("%c:=\t",temp);
if (isalpha(code[nCnt].operand1))
printf("%c\t", code[nCnt].operand1);
else
printf("%c\t",temp);
printf("%c\t", code[nCnt].opera);
if (isalpha(code[nCnt].operand2))  
printf("%c\t", code[nCnt].operand2);
else
printf("%c\t",temp);
printf("\n");
nCnt++;
temp++;
}
}
void quadruples()
{
int nCnt=0;
char temp = 'A';
temp++;
printf("\n\n\t Quardruples \n");
printf("\n ID OPERATOR OPERAND1 OPERAND2\n");
while(nCnt<nIndex)
{
printf("\n (%d) \t %c \t",nCnt,code[nCnt].opera);
if(isalpha(code[nCnt].operand1))
printf("%c\t", code[nCnt].operand1);
else
printf("%c\t",temp);
printf("%c\t", code[nCnt].opera);
if(isalpha(code[nCnt].operand2))
printf("%c\t", code[nCnt].operand2);
else
printf("%c\t",temp);
printf("%c\t",temp);
printf("\n");
nCnt++;
temp++;
}
}
main()
{
printf("enter expression");
yyparse();
threeaddresscode();
quadruples();
}
yywrap()
{
return 1;
}

Output:

$ lex lexfile.l
$ yacc –d  yaccfile.y
$cc lex.yy.c y.tab.c –ll –ly –lm
$./a.out
Enter expr a+b*c+d
Three address code
B=b*c
C=a+B
D=B+d

ID     OPERATOR          OPERAND1      OPERAND2
(0)		*		b			c		B
(1)		+		a			B		C
(2)		+		B			d		D



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


1.Implementation of LL(1) parser.
Code:

def removeLeftRecursion(rulesDiction):
	store = {}
	for lhs in rulesDiction:
		alphaRules = []
		betaRules = []
		allrhs = rulesDiction[lhs]
		for subrhs in allrhs:
			if subrhs[0] == lhs:
				alphaRules.append(subrhs[1:])
			else:
				betaRules.append(subrhs)
		if len(alphaRules) != 0:
			lhs_ = lhs + "'"
			while (lhs_ in rulesDiction.keys()) \
					or (lhs_ in store.keys()):
				lhs_ += "'"
			for b in range(0, len(betaRules)):
				betaRules[b].append(lhs_)
			rulesDiction[lhs] = betaRules
			for a in range(0, len(alphaRules)):
				alphaRules[a].append(lhs_)
			alphaRules.append(['#'])
			store[lhs_] = alphaRules
	for left in store:
		rulesDiction[left] = store[left]
	return rulesDiction


def LeftFactoring(rulesDiction):
	newDict = {}
	for lhs in rulesDiction:
		allrhs = rulesDiction[lhs]
		temp = dict()
		for subrhs in allrhs:
			if subrhs[0] not in list(temp.keys()):
				temp[subrhs[0]] = [subrhs]
			else:
				temp[subrhs[0]].append(subrhs)
		new_rule = []
		tempo_dict = {}
		for term_key in temp:
			allStartingWithTermKey = temp[term_key]
			if len(allStartingWithTermKey) > 1:
				lhs_ = lhs + "'"
				while (lhs_ in rulesDiction.keys()) \
						or (lhs_ in tempo_dict.keys()):
					lhs_ += "'"
				new_rule.append([term_key, lhs_])
				ex_rules = []
				for g in temp[term_key]:
					ex_rules.append(g[1:])
				tempo_dict[lhs_] = ex_rules
			else:
				new_rule.append(allStartingWithTermKey[0])
		newDict[lhs] = new_rule
		for key in tempo_dict:
			newDict[key] = tempo_dict[key]
	return newDict
def first(rule):
	global rules, nonterm_userdef, \
		term_userdef, diction, firsts
	if len(rule) != 0 and (rule is not None):
		if rule[0] in term_userdef:
			return rule[0]
		elif rule[0] == '#':
			return '#'
	if len(rule) != 0:
		if rule[0] in list(diction.keys()):
			fres = []
			rhs_rules = diction[rule[0]]
			for itr in rhs_rules:
				indivRes = first(itr)
				if type(indivRes) is list:
					for i in indivRes:
						fres.append(i)
				else:
					fres.append(indivRes)
			if '#' not in fres:
				return fres
			else:
				newList = []
				fres.remove('#')
				if len(rule) > 1:
					ansNew = first(rule[1:])
					if ansNew != None:
						if type(ansNew) is list:
							newList = fres + ansNew
						else:
							newList = fres + [ansNew]
					else:
						newList = fres
					return newList
				fres.append('#')
				return fres
def follow(nt):
	global start_symbol, rules, nonterm_userdef, \
		term_userdef, diction, firsts, follows

	solset = set()
	if nt == start_symbol:
		solset.add('$')
	for curNT in diction:
		rhs = diction[curNT]
		for subrule in rhs:
			if nt in subrule:
				while nt in subrule:
					index_nt = subrule.index(nt)
					subrule = subrule[index_nt + 1:]
					if len(subrule) != 0:
						res = first(subrule)
						if '#' in res:
							newList = []
							res.remove('#')
							ansNew = follow(curNT)
							if ansNew != None:
								if type(ansNew) is list:
									newList = res + ansNew
								else:
									newList = res + [ansNew]
							else:
								newList = res
							res = newList
					else:
						if nt != curNT:
							res = follow(curNT)

					# add follow result in set form
					if res is not None:
						if type(res) is list:
							for g in res:
								solset.add(g)
						else:
							solset.add(res)
	return list(solset)


def computeAllFirsts():
	global rules, nonterm_userdef, \
		term_userdef, diction, firsts
	for rule in rules:
		k = rule.split("->")
		# remove un-necessary spaces
		k[0] = k[0].strip()
		k[1] = k[1].strip()
		rhs = k[1]
		multirhs = rhs.split('|')
		for i in range(len(multirhs)):
			multirhs[i] = multirhs[i].strip()
			multirhs[i] = multirhs[i].split()
		diction[k[0]] = multirhs

	print(f"\nRules: \n")
	for y in diction:
		print(f"{y}->{diction[y]}")
	print(f"\nAfter elimination of left recursion:\n")

	diction = removeLeftRecursion(diction)
	for y in diction:
		print(f"{y}->{diction[y]}")
	print("\nAfter left factoring:\n")

	diction = LeftFactoring(diction)
	for y in diction:
		print(f"{y}->{diction[y]}")
	for y in list(diction.keys()):
		t = set()
		for sub in diction.get(y):
			res = first(sub)
			if res != None:
				if type(res) is list:
					for u in res:
						t.add(u)
				else:
					t.add(res)
		firsts[y] = t

	print("\nCalculated firsts: ")
	key_list = list(firsts.keys())
	index = 0
	for gg in firsts:
		print(f"first({key_list[index]}) "
			f"=> {firsts.get(gg)}")
		index += 1


def computeAllFollows():
	global start_symbol, rules, nonterm_userdef,\
		term_userdef, diction, firsts, follows
	for NT in diction:
		solset = set()
		sol = follow(NT)
		if sol is not None:
			for g in sol:
				solset.add(g)
		follows[NT] = solset

	print("\nCalculated follows: ")
	key_list = list(follows.keys())
	index = 0
	for gg in follows:
		print(f"follow({key_list[index]})"
			f" => {follows[gg]}")
		index += 1
def createParseTable():
	import copy
	global diction, firsts, follows, term_userdef
	print("\nFirsts and Follow Result table\n")
	mx_len_first = 0
	mx_len_fol = 0
	for u in diction:
		k1 = len(str(firsts[u]))
		k2 = len(str(follows[u]))
		if k1 > mx_len_first:
			mx_len_first = k1
		if k2 > mx_len_fol:
			mx_len_fol = k2

	print(f"{{:<{10}}} "
		f"{{:<{mx_len_first + 5}}} "
		f"{{:<{mx_len_fol + 5}}}"
		.format("Non-T", "FIRST", "FOLLOW"))
	for u in diction:
		print(f"{{:<{10}}} "
			f"{{:<{mx_len_first + 5}}} "
			f"{{:<{mx_len_fol + 5}}}"
			.format(u, str(firsts[u]), str(follows[u])))
	ntlist = list(diction.keys())
	terminals = copy.deepcopy(term_userdef)
	terminals.append('$')
	mat = []
	for x in diction:
		row = []
		for y in terminals:
			row.append('')
		mat.append(row)
	grammar_is_LL = True
	for lhs in diction:
		rhs = diction[lhs]
		for y in rhs:
			res = first(y)
			if '#' in res:
				if type(res) == str:
					firstFollow = []
					fol_op = follows[lhs]
					if fol_op is str:
						firstFollow.append(fol_op)
					else:
						for u in fol_op:
							firstFollow.append(u)
					res = firstFollow
				else:
					res.remove('#')
					res = list(res) +\
						list(follows[lhs])
			ttemp = []
			if type(res) is str:
				ttemp.append(res)
				res = copy.deepcopy(ttemp)
			for c in res:
				xnt = ntlist.index(lhs)
				yt = terminals.index(c)
				if mat[xnt][yt] == '':
					mat[xnt][yt] = mat[xnt][yt] \
								+ f"{lhs}->{' '.join(y)}"
				else:
					if f"{lhs}->{y}" in mat[xnt][yt]:
						continue
					else:
						grammar_is_LL = False
						mat[xnt][yt] = mat[xnt][yt] \
									+ f",{lhs}->{' '.join(y)}"
	print("\nGenerated parsing table:\n")
	frmt = "{:>12}" * len(terminals)
	print(frmt.format(*terminals))

	j = 0
	for y in mat:
		frmt1 = "{:>12}" * len(y)
		print(f"{ntlist[j]} {frmt1.format(*y)}")
		j += 1

	return (mat, grammar_is_LL, terminals)


def validateStringUsingStackBuffer(parsing_table, grammarll1,
								table_term_list, input_string,
								term_userdef,start_symbol):

	print(f"\nValidate String => {input_string}\n")
	if grammarll1 == False:
		return f"\nInput String = " \
			f"\"{input_string}\"\n" \
			f"Grammar is not LL(1)"

	stack = [start_symbol, '$']
	buffer = []
	input_string = input_string.split()
	input_string.reverse()
	buffer = ['$'] + input_string

	print("{:>20} {:>20} {:>20}".
		format("Buffer", "Stack","Action"))

	while True:
		if stack == ['$'] and buffer == ['$']:
			print("{:>20} {:>20} {:>20}"
				.format(' '.join(buffer),
						' '.join(stack),
						"Valid"))
			return "\nValid String!"
		elif stack[0] not in term_userdef:
			x = list(diction.keys()).index(stack[0])
			y = table_term_list.index(buffer[-1])
			if parsing_table[x][y] != '':
				entry = parsing_table[x][y]
				print("{:>20} {:>20} {:>25}".
					format(' '.join(buffer),
							' '.join(stack),
							f"T[{stack[0]}][{buffer[-1]}] = {entry}"))
				lhs_rhs = entry.split("->")
				lhs_rhs[1] = lhs_rhs[1].replace('#', '').strip()
				entryrhs = lhs_rhs[1].split()
				stack = entryrhs + stack[1:]
			else:
				return f"\nInvalid String! No rule at " \
					f"Table[{stack[0]}][{buffer[-1]}]."
		else:
			if stack[0] == buffer[-1]:
				print("{:>20} {:>20} {:>20}"
					.format(' '.join(buffer),
							' '.join(stack),
							f"Matched:{stack[0]}"))
				buffer = buffer[:-1]
				stack = stack[1:]
			else:
				return "\nInvalid String! " \
					"Unmatched terminal symbols"

sample_input_string = None
rules=["S -> A k O",
	"A -> A d | a B | a C",
	"C -> c",
	"B -> b B C | r"]

nonterm_userdef=['A','B','C']
term_userdef=['k','O','d','a','c','b','r']
sample_input_string="a r k O"
diction = {}
firsts = {}
follows = {}
computeAllFirsts()
start_symbol = list(diction.keys())[0]
computeAllFollows()

(parsing_table, result, tabTerm) = createParseTable()
if sample_input_string != None:
	validity = validateStringUsingStackBuffer(parsing_table, result,
											tabTerm, sample_input_string,
											term_userdef,start_symbol)
	print(validity)
else:
	print("\nNo input String detected")

OUTPUT:

Rules: 
S->[['A', 'k', 'O']]
A->[['A', 'd'], ['a', 'B'], ['a', 'C']]
C->[['c']]
B->[['b', 'B', 'C'], ['r']]

After elimination of left recursion:
S->[['A', 'k', 'O']]
A->[['a', 'B', "A'"], ['a', 'C', "A'"]]
C->[['c']]
B->[['b', 'B', 'C'], ['r']]
A'->[['d', "A'"], ['#']]

After left factoring:
S->[['A', 'k', 'O']]
A->[['a', "A''"]]
A''->[['B', "A'"], ['C', "A'"]]
C->[['c']]
B->[['b', 'B', 'C'], ['r']]
A'->[['d', "A'"], ['#']]

Calculated firsts: 
first(S) => {'a'}
first(A) => {'a'}
first(A'') => {'c', 'r', 'b'}
first(C) => {'c'}
first(B) => {'r', 'b'}
first(A') => {'d', '#'}

Calculated follows: 
follow(S) => {'$'}
follow(A) => {'k'}
follow(A'') => {'k'}
follow(C) => {'d', 'c', 'k'}
follow(B) => {'d', 'c', 'k'}
follow(A') => {'k'}

Firsts and Follow Result table

Non-T      FIRST                FOLLOW              
S          {'a'}                {'$'}               
A          {'a'}                {'k'}               
A''        {'c', 'r', 'b'}      {'k'}               
C          {'c'}                {'d', 'c', 'k'}     
B          {'r', 'b'}           {'d', 'c', 'k'}     
A'         {'d', '#'}           {'k'}               

Generated parsing table:

           k           O           d           a           c           b           r           $
S                                         S->A k O                                                
A                                         A->a A''                                                
A''                                                    A''->C A'   A''->B A'   A''->B A'            
C                                                         C->c                                    
B                                                                 B->b B C        B->r            
A'        A'->#                A'->d A'                                                            
Validate String => a r k O

              Buffer                Stack               Action
           $ O k r a                  S $        T[S][a] = S->A k O
           $ O k r a              A k O $        T[A][a] = A->a A''
           $ O k r a          a A'' k O $            Matched:a
             $ O k r            A'' k O $     T[A''][r] = A''->B A'
             $ O k r           B A' k O $            T[B][r] = B->r
             $ O k r           r A' k O $            Matched:r
               $ O k             A' k O $          T[A'][k] = A'->#
               $ O k                k O $            Matched:k
                 $ O                  O $            Matched:O
                   $                    $                Valid

Valid String!
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

1.Implementation of SLR parser.
Code:

import copy
def grammarAugmentation(rules, nonterm_userdef, start_symbol):

    newRules = []

    newChar = start_symbol + "'"
    while newChar in nonterm_userdef:
        newChar += "'"

    newRules.append([newChar, [".", start_symbol]])

    for rule in rules:

        k = rule.split("->")
        lhs = k[0].strip()
        rhs = k[1].strip()

        multirhs = rhs.split("|")
        for rhs1 in multirhs:
            rhs1 = rhs1.strip().split()

            rhs1.insert(0, ".")
            newRules.append([lhs, rhs1])
    return newRules


def findClosure(input_state, dotSymbol):
    global start_symbol, separatedRulesList, statesDict

    closureSet = []

    if dotSymbol == start_symbol:
        for rule in separatedRulesList:
            if rule[0] == dotSymbol:
                closureSet.append(rule)
    else:

        closureSet = input_state

    prevLen = -1
    while prevLen != len(closureSet):
        prevLen = len(closureSet)

        tempClosureSet = []

        for rule in closureSet:
            indexOfDot = rule[1].index(".")
            if rule[1][-1] != ".":
                dotPointsHere = rule[1][indexOfDot + 1]
                for in_rule in separatedRulesList:
                    if dotPointsHere == in_rule[0] and in_rule not in tempClosureSet:
                        tempClosureSet.append(in_rule)

        for rule in tempClosureSet:
            if rule not in closureSet:
                closureSet.append(rule)
    return closureSet


def compute_GOTO(state):
    global statesDict, stateCount

    generateStatesFor = []
    for rule in statesDict[state]:

        if rule[1][-1] != ".":
            indexOfDot = rule[1].index(".")
            dotPointsHere = rule[1][indexOfDot + 1]
            if dotPointsHere not in generateStatesFor:
                generateStatesFor.append(dotPointsHere)

    if len(generateStatesFor) != 0:
        for symbol in generateStatesFor:
            GOTO(state, symbol)
    return


def GOTO(state, charNextToDot):
    global statesDict, stateCount, stateMap

    newState = []
    for rule in statesDict[state]:
        indexOfDot = rule[1].index(".")
        if rule[1][-1] != ".":
            if rule[1][indexOfDot + 1] == charNextToDot:

                shiftedRule = copy.deepcopy(rule)
                shiftedRule[1][indexOfDot] = shiftedRule[1][indexOfDot + 1]
                shiftedRule[1][indexOfDot + 1] = "."
                newState.append(shiftedRule)

    addClosureRules = []
    for rule in newState:
        indexDot = rule[1].index(".")

        if rule[1][-1] != ".":
            closureRes = findClosure(newState, rule[1][indexDot + 1])
            for rule in closureRes:
                if rule not in addClosureRules and rule not in newState:
                    addClosureRules.append(rule)

    for rule in addClosureRules:
        newState.append(rule)

    stateExists = -1
    for state_num in statesDict:
        if statesDict[state_num] == newState:
            stateExists = state_num
            break

    if stateExists == -1:

        stateCount += 1
        statesDict[stateCount] = newState
        stateMap[(state, charNextToDot)] = stateCount
    else:

        stateMap[(state, charNextToDot)] = stateExists
    return


def generateStates(statesDict):
    prev_len = -1
    called_GOTO_on = []

    while len(statesDict) != prev_len:
        prev_len = len(statesDict)
        keys = list(statesDict.keys())

        for key in keys:
            if key not in called_GOTO_on:
                called_GOTO_on.append(key)
                compute_GOTO(key)
    return


def first(rule):
    global rules, nonterm_userdef, term_userdef, diction, firsts

    if len(rule) != 0 and (rule is not None):
        if rule[0] in term_userdef:
            return rule[0]
        elif rule[0] == "#":
            return "#"

    if len(rule) != 0:
        if rule[0] in list(diction.keys()):

            fres = []
            rhs_rules = diction[rule[0]]

            for itr in rhs_rules:
                indivRes = first(itr)
                if type(indivRes) is list:
                    for i in indivRes:
                        fres.append(i)
                else:
                    fres.append(indivRes)

            if "#" not in fres:
                return fres
            else:

                newList = []
                fres.remove("#")
                if len(rule) > 1:
                    ansNew = first(rule[1:])
                    if ansNew != None:
                        if type(ansNew) is list:
                            newList = fres + ansNew
                        else:
                            newList = fres + [ansNew]
                    else:
                        newList = fres
                    return newList

                fres.append("#")
                return fres


def follow(nt):
    global start_symbol, rules, nonterm_userdef, term_userdef, diction, firsts, follows

    solset = set()
    if nt == start_symbol:

        solset.add("$")

    for curNT in diction:
        rhs = diction[curNT]

        for subrule in rhs:
            if nt in subrule:

                while nt in subrule:
                    index_nt = subrule.index(nt)
                    subrule = subrule[index_nt + 1 :]

                    if len(subrule) != 0:

                        res = first(subrule)

                        if "#" in res:
                            newList = []
                            res.remove("#")
                            ansNew = follow(curNT)
                            if ansNew != None:
                                if type(ansNew) is list:
                                    newList = res + ansNew
                                else:
                                    newList = res + [ansNew]
                            else:
                                newList = res
                            res = newList
                    else:

                        if nt != curNT:
                            res = follow(curNT)

                    if res is not None:
                        if type(res) is list:
                            for g in res:
                                solset.add(g)
                        else:
                            solset.add(res)
    return list(solset)


def createParseTable(statesDict, stateMap, T, NT):
    global separatedRulesList, diction

    rows = list(statesDict.keys())
    cols = T + ["$"] + NT

    Table = []
    tempRow = []
    for y in range(len(cols)):
        tempRow.append("")
    for x in range(len(rows)):
        Table.append(copy.deepcopy(tempRow))

    for entry in stateMap:
        state = entry[0]
        symbol = entry[1]

        a = rows.index(state)
        b = cols.index(symbol)
        if symbol in NT:
            Table[a][b] = Table[a][b] + f"{stateMap[entry]} "
        elif symbol in T:
            Table[a][b] = Table[a][b] + f"S{stateMap[entry]} "

    numbered = {}
    key_count = 0
    for rule in separatedRulesList:
        tempRule = copy.deepcopy(rule)
        tempRule[1].remove(".")
        numbered[key_count] = tempRule
        key_count += 1

    addedR = f"{separatedRulesList[0][0]} -> " f"{separatedRulesList[0][1][1]}"
    rules.insert(0, addedR)
    for rule in rules:
        k = rule.split("->")

        k[0] = k[0].strip()
        k[1] = k[1].strip()
        rhs = k[1]
        multirhs = rhs.split("|")

        for i in range(len(multirhs)):
            multirhs[i] = multirhs[i].strip()
            multirhs[i] = multirhs[i].split()
        diction[k[0]] = multirhs

    for stateno in statesDict:
        for rule in statesDict[stateno]:
            if rule[1][-1] == ".":

                temp2 = copy.deepcopy(rule)
                temp2[1].remove(".")
                for key in numbered:
                    if numbered[key] == temp2:

                        follow_result = follow(rule[0])
                        for col in follow_result:
                            index = cols.index(col)
                            if key == 0:
                                Table[stateno][index] = "Accept"
                            else:
                                Table[stateno][index] = (
                                    Table[stateno][index] + f"R{key} "
                                )

    print("\nSLR(1) parsing table:\n")
    frmt = "{:>8}" * len(cols)
    print(" ", frmt.format(*cols), "\n")
    ptr = 0
    j = 0
    for y in Table:
        frmt1 = "{:>8}" * len(y)
        print(f"{{:>3}} {frmt1.format(*y)}".format("I" + str(j)))
        j += 1


def printResult(rules):
    for rule in rules:
        print(f"{rule[0]} ->" f" {' '.join(rule[1])}")


def printAllGOTO(diction):
    for itr in diction:
        print(f"GOTO ( I{itr[0]} ," f" {itr[1]} ) = I{stateMap[itr]}")


rules = ["E -> E + T | T", "T -> T * F | F", "F -> ( E ) | id"]
nonterm_userdef = ["E", "T", "F"]
term_userdef = ["id", "+", "*", "(", ")"]
start_symbol = nonterm_userdef[0]

print("\nOriginal grammar input:\n")
for y in rules:
    print(y)

print("\nGrammar after Augmentation: \n")
separatedRulesList = grammarAugmentation(rules, nonterm_userdef, start_symbol)
printResult(separatedRulesList)

start_symbol = separatedRulesList[0][0]
print("\nCalculated closure: I0\n")
I0 = findClosure(0, start_symbol)
printResult(I0)

statesDict = {}
stateMap = {}

statesDict[0] = I0
stateCount = 0

generateStates(statesDict)

print("\nStates Generated: \n")
for st in statesDict:
    print(f"State = I{st}")
    printResult(statesDict[st])
    print()

print("Result of GOTO computation:\n")
printAllGOTO(stateMap)

diction = {}

createParseTable(statesDict, stateMap, term_userdef, nonterm_userdef)

Output:

Original grammar input:

E -> E + T | T
T -> T * F | F
F -> ( E ) | id

Grammar after Augmentation: 

E' -> . E
E -> . E + T
E -> . T
T -> . T * F
T -> . F
F -> . ( E )
F -> . id

Calculated closure: I0

E' -> . E
E -> . E + T
E -> . T
T -> . T * F
T -> . F
F -> . ( E )
F -> . id

States Generated: 

State = I0
E' -> . E
E -> . E + T
E -> . T
T -> . T * F
T -> . F
F -> . ( E )
F -> . id

State = I1
E' -> E .
E -> E . + T

State = I2
E -> T .
T -> T . * F

State = I3
T -> F .

State = I4
F -> ( . E )
E -> . E + T
E -> . T
T -> . T * F
T -> . F
F -> . ( E )
F -> . id

State = I5
F -> id .

State = I6
E -> E + . T
T -> . T * F
T -> . F
F -> . ( E )
F -> . id

State = I7
T -> T * . F
F -> . ( E )
F -> . id

State = I8
F -> ( E . )
E -> E . + T

State = I9
E -> E + T .
T -> T . * F

State = I10
T -> T * F .

State = I11
F -> ( E ) .

Result of GOTO computation:

GOTO ( I0 , E ) = I1
GOTO ( I0 , T ) = I2
GOTO ( I0 , F ) = I3
GOTO ( I0 , ( ) = I4
GOTO ( I0 , id ) = I5
GOTO ( I1 , + ) = I6
GOTO ( I2 , * ) = I7
GOTO ( I4 , E ) = I8
GOTO ( I4 , T ) = I2
GOTO ( I4 , F ) = I3
GOTO ( I4 , ( ) = I4
GOTO ( I4 , id ) = I5
GOTO ( I6 , T ) = I9
GOTO ( I6 , F ) = I3
GOTO ( I6 , ( ) = I4
GOTO ( I6 , id ) = I5
GOTO ( I7 , F ) = I10
GOTO ( I7 , ( ) = I4
GOTO ( I7 , id ) = I5
GOTO ( I8 , ) ) = I11
GOTO ( I8 , + ) = I6
GOTO ( I9 , * ) = I7

SLR(1) parsing table:

         id       +       *       (       )       $       E       T       F 

 I0      S5                      S4                       1       2       3 
 I1              S6                           Accept                        
 I2              R2      S7              R2      R2                         
 I3              R4      R4              R4      R4                         
 I4      S5                      S4                       8       2       3 
 I5              R6      R6              R6      R6                         
 I6      S5                      S4                               9       3 
 I7      S5                      S4                                      10 
 I8              S6                     S11                                 
 I9              R1      S7              R1      R1                         
I10              R3      R3              R3      R3                         
I11              R5      R5              R5      R5   
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

1.Implementation of CLR parser.(this does not work)
Code:

from collections import deque
from collections import OrderedDict
from pprint import pprint
import firstfollow
from firstfollow import production_list, nt_list as ntl, t_list as tlnt_list, t_list=[], []

class State:

    _id=0
    def __init__(self, closure):
        self.closure=closure
        self.no=State._id
        State._id+=1

class Item(str):
    def __new__(cls, item, lookahead=list()):
        self=str.__new__(cls, item)
        self.lookahead=lookahead
        return self

    def __str__(self):
        return super(Item, self).__str__()+", "+'|'.join(self.lookahead)
        

def closure(items):

    def exists(newitem, items):

        for i in items:
            if i==newitem and sorted(set(i.lookahead))==sorted(set(newitem.lookahead)):
                return True
        return False


    global production_list

    while True:
        flag=0
        for i in items: 
            
            if i.index('.')==len(i)-1: continue

            Y=i.split('->')[1].split('.')[1][0]

            if i.index('.')+1<len(i)-1:
                lastr=list(firstfollow.compute_first(i[i.index('.')+2])-set(chr(1013)))
                
            else:
                lastr=i.lookahead
            
            for prod in production_list:
                head, body=prod.split('->')
                
                if head!=Y: continue
                
                newitem=Item(Y+'->.'+body, lastr)

                if not exists(newitem, items):
                    items.append(newitem)
                    flag=1
        if flag==0: break

    return items

def goto(items, symbol):

    global production_list
    initial=[]

    for i in items:
        if i.index('.')==len(i)-1: continue

        head, body=i.split('->')
        seen, unseen=body.split('.')


        if unseen[0]==symbol and len(unseen) >= 1:
            initial.append(Item(head+'->'+seen+unseen[0]+'.'+unseen[1:], i.lookahead))

    return closure(initial)


def calc_states():

    def contains(states, t):

        for s in states:
            if len(s) != len(t): continue

            if sorted(s)==sorted(t):
                for i in range(len(s)):
                        if s[i].lookahead!=t[i].lookahead: break
                else: return True

        return False

    global production_list, nt_list, t_list

    head, body=production_list[0].split('->')


    states=[closure([Item(head+'->.'+body, ['$'])])]
    
    while True:
        flag=0
        for s in states:

            for e in nt_list+t_list:
                
                t=goto(s, e)
                if t == [] or contains(states, t): continue

                states.append(t)
                flag=1

        if not flag: break
    
    return states 

def make_table(states):
    global nt_list, t_list
    def getstateno(t):

        for s in states:
            if len(s.closure) != len(t): continue

            if sorted(s.closure)==sorted(t):
                for i in range(len(s.closure)):
                        if s.closure[i].lookahead!=t[i].lookahead: break
                else: return s.no

        return -1

    def getprodno(closure):

        closure=''.join(closure).replace('.', '')
        return production_list.index(closure)

    SLR_Table=OrderedDict()
    
    for i in range(len(states)):
        states[i]=State(states[i])

    for s in states:
        SLR_Table[s.no]=OrderedDict()

        for item in s.closure:
            head, body=item.split('->')
            if body=='.': 
                for term in item.lookahead: 
                    if term not in SLR_Table[s.no].keys():
                        SLR_Table[s.no][term]={'r'+str(getprodno(item))}
                    else: SLR_Table[s.no][term] |= {'r'+str(getprodno(item))}
                continue

            nextsym=body.split('.')[1]
            if nextsym=='':
                if getprodno(item)==0:
                    SLR_Table[s.no]['$']='accept'
                else:
                    for term in item.lookahead: 
                        if term not in SLR_Table[s.no].keys():
                            SLR_Table[s.no][term]={'r'+str(getprodno(item))}
                        else: SLR_Table[s.no][term] |= {'r'+str(getprodno(item))}
                continue

            nextsym=nextsym[0]
            t=goto(s.closure, nextsym)
            if t != []: 
                if nextsym in t_list:
                    if nextsym not in SLR_Table[s.no].keys():
                        SLR_Table[s.no][nextsym]={'s'+str(getstateno(t))}
                    else: SLR_Table[s.no][nextsym] |= {'s'+str(getstateno(t))}

                else: SLR_Table[s.no][nextsym] = str(getstateno(t))

    return SLR_Table
def augment_grammar():

    for i in range(ord('Z'), ord('A')-1, -1):
        if chr(i) not in nt_list:
            start_prod=production_list[0]
            production_list.insert(0, chr(i)+'->'+start_prod.split('->')[0]) 
            return
def main():

    global production_list, ntl, nt_list, tl, t_list    

    firstfollow.main()

    print("\tFIRST AND FOLLOW OF NON-TERMINALS")
    for nt in ntl:
        firstfollow.compute_first(nt)
        firstfollow.compute_follow(nt)
        print(nt)
        print("\tFirst:\t", firstfollow.get_first(nt))
        print("\tFollow:\t", firstfollow.get_follow(nt), "\n")  
    

    augment_grammar()
    nt_list=list(ntl.keys())
    t_list=list(tl.keys()) + ['$']

    print(nt_list)
    print(t_list)

    j=calc_states()

    ctr=0
    for s in j:
        print("Item{}:".format(ctr))
        for i in s:
            print("\t", i)
        ctr+=1

    table=make_table(j)
    print('_____________________________________________________________________')
    print("\n\tCLR(1) TABLE\n")
    sym_list = nt_list + t_list
    sr, rr=0, 0
    print('_____________________________________________________________________')
    print('\t|  ','\t|  '.join(sym_list),'\t\t|')
    print('_____________________________________________________________________')
    for i, j in table.items():
            
        print(i, "\t|  ", '\t|  '.join(list(j.get(sym,' ') if type(j.get(sym))in (str , None) else next(iter(j.get(sym,' ')))  for sym in sym_list)),'\t\t|')
        s, r=0, 0

        for p in j.values():
            if p!='accept' and len(p)>1:
                p=list(p)
                if('r' in p[0]): r+=1
                else: s+=1
                if('r' in p[1]): r+=1
                else: s+=1      
        if r>0 and s>0: sr+=1
        elif r>0: rr+=1
    print('_____________________________________________________________________')
    print("\n", sr, "s/r conflicts |", rr, "r/r conflicts")
    print('_____________________________________________________________________')
    print("Enter the string to be parsed")
    Input=input()+'$'
    try:
        stack=['0']
        a=list(table.items())
        '''print(a[int(stack[-1])][1][Input[0]])
        b=list(a[int(stack[-1])][1][Input[0]])
        print(b[0][0])
        print(a[0][1]["S"])'''
        print("productions\t:",production_list)
        print('stack',"\t \t\t \t",'Input')
        print(*stack,"\t \t\t \t",*Input,sep="")
        while(len(Input)!=0):
            b=list(a[int(stack[-1])][1][Input[0]])
            if(b[0][0]=="s" ):
                #s=Input[0]+b[0][1:]
                stack.append(Input[0])
                stack.append(b[0][1:])
                Input=Input[1:]
                print(*stack,"\t \t\t \t",*Input,sep="")
            elif(b[0][0]=="r" ):
                s=int(b[0][1:])
                #print(len(production_list),s)
                l=len(production_list[s])-3
                #print(l)
                prod=production_list[s]
                l*=2
                l=len(stack)-l
                stack=stack[:l]
                s=a[int(stack[-1])][1][prod[0]]
                #print(s,b)
                stack+=list(prod[0])
                stack.append(s)
                print(*stack,"\t \t\t \t",*Input,sep="")
            elif(b[0][0]=="a"):
                print("\n\tString Accepted\n")
                break
    except:
        print('\n\tString INCORRECT for given Grammar!\n')
    return 

if __name__=="__main__":
    main()

Output:

Enter the grammar productions (enter 'end' or return to stop)
#(Format: "A->Y1Y2..Yn" {Yi - single char} OR "A->" {epsilon})
S->AA
         A->aA
         A->b
         end
        FIRST AND FOLLOW OF NON-TERMINALS
S
        First:   {'a', 'b'}
        Follow:  {'$'} 

A
        First:   {'a', 'b'}
        Follow:  {'$', 'a', 'b'} 

['S', 'A']
['a', 'b', '$']
Item0:
         Z->.S, $
         S->.AA, $
         A->.aA, a|b
         A->.b, a|b
Item1:
         Z->S., $
Item2:
         S->A.A, $
         A->.aA, $
         A->.b, $
Item3:
         A->a.A, a|b
         A->.aA, a|b
         A->.b, a|b
Item4:
         A->b., a|b
Item5:
         S->AA., $
Item6:
         A->a.A, $
         A->.aA, $
         A->.b, $
Item7:
         A->b., $
Item8:
         A->aA., a|b
Item9:
         A->aA., $
_____________________________________________________________________

        CLR(1) TABLE

_____________________________________________________________________
        |   S   |  A    |  a    |  b    |  $            |
_____________________________________________________________________
0       |   1   |  2    |  s3   |  s4   |               |
1       |       |         |       |         |  accept       |
2       |       |  5    |  s6   |  s7   |               |
3       |       |  8    |  s3   |  s4   |               |
4       |       |       |  r3   |  r3    |               |
5       |       |       |       |          |  r1           |
6       |       |  9    |  s6   |  s7   |               |
7       |       |       |       |          |  r3           |
8       |       |       |  r2   |  r2   |               |
9       |       |       |       |          |  r2           |
_____________________________________________________________________

 0 s/r conflicts | 0 r/r conflicts
_____________________________________________________________________
Enter the string to be parsed
aaabab
productions     : ['Z->S', 'S->AA', 'A->aA', 'A->b']
stack                            Input
0                               aaabab$
0a3                             aabab$
0a3a3                           abab$
0a3a3a3                         bab$
0a3a3a3b4                               ab$
0a3a3a3A8                               ab$
0a3a3A8                         ab$
0a3A8                           ab$
0A2                             ab$
0A2a6                           b$
0A2a6b7                         $
0A2a6A9                         $
0A2A5                           $
0S1                             $

        String Accepted

      
      from re import *
from collections import OrderedDict

t_list=OrderedDict()
nt_list=OrderedDict()
production_list=[]

# ------------------------------------------------------------------

class Terminal:

    def __init__(self, symbol):
        self.symbol=symbol

    def __str__(self):
        return self.symbol

# ------------------------------------------------------------------

class NonTerminal:

    def __init__(self, symbol):
        self.symbol=symbol
        self.first=set()
        self.follow=set()

    def __str__(self):
        return self.symbol

    def add_first(self, symbols): self.first |= set(symbols) #union operation

    def add_follow(self, symbols): self.follow |= set(symbols)

# ------------------------------------------------------------------

def compute_first(symbol): #chr(1013) corresponds (ϵ) in Unicode

    global production_list, nt_list, t_list

# if X is a terminal then first(X) = X
    if symbol in t_list:
        return set(symbol)

    for prod in production_list:
        head, body=prod.split('->')
        
        if head!=symbol: continue

# if X -> is a production, then first(X) = epsilon
        if body=='':
            nt_list[symbol].add_first(chr(1013))
            continue

        

        for i, Y in enumerate(body):
# for X -> Y1 Y2 ... Yn, first(X) = non-epsilon symbols in first(Y1)
# if first(Y1) contains epsilon, 
#   first(X) = non-epsilon symbols in first(Y2)
#   if first(Y2) contains epsilon
#   ...
            if body[i]==symbol: continue
            t=compute_first(Y)
            nt_list[symbol].add_first(t-set(chr(1013)))
            if chr(1013) not in t:
                break 
# for i=1 to n, if Yi contains epsilon, then first(X)=epsilon
            if i==len(body)-1: 
                nt_list[symbol].add_first(chr(1013))

    return nt_list[symbol].first

# ------------------------------------------------------------------

def get_first(symbol): #wrapper method for compute_first

    return compute_first(symbol)

# ------------------------------------------------------------------

def compute_follow(symbol):

    global production_list, nt_list, t_list

# if A is the start symbol, follow (A) = $
    if symbol == list(nt_list.keys())[0]: #this is okay since I'm using an OrderedDict
        nt_list[symbol].add_follow('$')

    for prod in production_list:    
        head, body=prod.split('->')

        for i, B in enumerate(body):        
            if B != symbol: continue

# for A -> aBb, follow(B) = non-epsilon symbols in first(b)
            if i != len(body)-1:
                nt_list[symbol].add_follow(get_first(body[i+1]) - set(chr(1013)))

# if A -> aBb where first(b) contains epsilon, or A -> aB then follow(B) = follow (A)
            if i == len(body)-1 or chr(1013) in get_first(body[i+1]) and B != head: 
                nt_list[symbol].add_follow(get_follow(head))

# ------------------------------------------------------------------

def get_follow(symbol):

    global nt_list, t_list

    if symbol in t_list.keys():
        return None
    
    return nt_list[symbol].follow

# ------------------------------------------------------------------    

def main(pl=None):

    print('''Enter the grammar productions (enter 'end' or return to stop)
#(Format: "A->Y1Y2..Yn" {Yi - single char} OR "A->" {epsilon})''')

    global production_list, t_list, nt_list
    ctr=1

    #t_regex, nt_regex=r'[a-z\W]', r'[A-Z]'

    if pl==None:

        while True:

            #production_list.append(input('{})\t'.format(ctr)))
            
            production_list.append(input().replace(' ', ''))

            if production_list[-1].lower() in ['end', '']: 
                del production_list[-1]
                break

            head, body=production_list[ctr-1].split('->')

            if head not in nt_list.keys():
                nt_list[head]=NonTerminal(head)

            #for all terminals in the body of the production
            for i in body:
                if not 65<=ord(i)<=90:
                    if i not in t_list.keys(): t_list[i]=Terminal(i)
            #for all non-terminals in the body of the production
                elif  i not in nt_list.keys(): nt_list[i]=NonTerminal(i)
                
            ctr+=1

    '''if pl!=None:

        for i, prod in enumerate(pl):

            if prod.lower() in ['end', '']:
                del pl[i:]
                break

            head, body=prod.split('->')

            if head not in nt_list.keys():
                nt_list[head]=NonTerminal(head)

            #for all terminals in the body of the production
            for i in finditer(t_regex, body):
                s=i.group()
                if s not in t_list.keys(): t_list[s]=Terminal(s)

            #for all non-terminals in the body of the production
            for i in finditer(nt_regex, body):
                s=i.group()
                if s not in nt_list.keys(): nt_list[s]=NonTerminal(s)'''
                
    return pl
# ------------------------------------------------------------------

if __name__=='__main__':
    
    main()

      
      
          
          
          
S->AA
A->aA
A->b
end
          
         
  
      
          
          
          
          %{
#include <stdio.h>

int lines = 0, words = 0, chars = 0;
%}

%%

\n          { lines++; chars++; }
[ \t]+      { chars += yyleng; }
[^ \t\n]+   { words++; chars += yyleng; }

%%

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        FILE *file;
        file = fopen(argv[1], "r");
        if (!file)
        {
            printf("could not open %s\n", argv[1]);
            exit(0);
        }
        yyin = file;
    }
    yylex();
    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);
    printf("Characters: %d\n", chars);
    return 0;
}

int yywrap()
{
    return 1;
}

      
      
          
          
          
          
   YACC Commands:
$ lex three.l
$ yacc -d three.y
$ gcc lex.yy.c y.tab.c -ll -lm
$ ./a.out       
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
      