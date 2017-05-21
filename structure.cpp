#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stack> 
#include <math.h> 
#include <list>
#include <string>
#include <sstream>
#include <fstream>


using namespace std;



typedef struct fonction {
	double coefficient;
	char* fon;
	fonction *fx;
	fonction *gx;
	fonction *next;
	double puissance;
};

typedef struct pileVer {
	char par;
	pileVer* next;
};


fonction* initializeFonction()
{
	fonction* f = new fonction();
	f->fon = NULL;
	f->fx = NULL;
	f->gx = NULL;
	f->next = NULL;
	f->puissance = 1;
	f->coefficient = 1;
	return f;
}


pileVer* initializePileVer(char input)
{
	if (input == NULL) return NULL;
	pileVer* tmp = new pileVer;
	tmp->par = input;
	tmp->next = NULL;
	return tmp;

}

pileVer* empilerPileVer(pileVer* top, char input)
{
	if (input == NULL) return top;
	pileVer* tmp = initializePileVer(input);
	tmp->next = top;
	return tmp;
}

pileVer*  depilerPileVer(pileVer* top)
{
	return (top == NULL) ? NULL : top->next;
}

bool check(char* input)
{
	pileVer* pile = NULL;
	if (input == NULL) return true;

	while (*input != '\0')
	{
		if (*input == '(')
			pile = empilerPileVer(pile, *input);
		else
		{
			if (*input == ')')
			{
				if (pile == NULL)  return false;
				pile = depilerPileVer(pile);
			}
		}
		input++;
	}
	return (pile == NULL);
}


char* removeSpace(char* input)
{

	char* result = new char;
	char* start = result;
	if (input == NULL) return NULL;
	while (*input != '\0')
	{
		if (*input != ' ')
		{
			*result = *input;
			result++;
		}
		input++;
	}
	*result = '\0';
	return start;
}

bool isNumber(char x)
{
	return (x - '0' >= 0 && x - '0' <= 9);
}

char* getNum(char* input)
{
	char* num = new char;
	char* start = num;
	while (*input != '\0' && isNumber(*input))
	{
		*num = *input;
		num++;
		input++;
	}
	*num = '\0';
	return start;
}

char* getExpression(char* input)
{

	char* num = new char;
	char* start = num;
	if (input == NULL) return NULL;
	if (*input == '\0') return input;
	//if (isSymbol(input)) return parseInput(input);

	if (*input == 'x')
	{
		*num = *input;
		input++;
		num++;
		*num = '\0';
		return start;
	}
	*num = *input;
	input++;

	num++;
	*num = *input; //second letter
	input++;

	num++;
	*num = *input; //third letter
	input++;

	num++;
	*num = '\0';
	return start;
}

char* getEndArrow(char* input)
{

	int count = 1; //when 0 ==> arrow closed
	char* num = new char;
	char* start = num;
	//*num = *input; // (
	//input++;
	//num++;
	while (count > 0)
	{

		if (*input == '(')  count++;
		if (*input == ')')  count--;
		if (count == 0) break;

		*num = *input;
		input++;
		num++;
	}
	*num = '\0';
	return start;
}

bool have2Elements(char* expr)
{
	if (expr == NULL) return false;
	if (strcmp(expr, "div") == 0 || strcmp(expr, "mul") == 0) return true;
	return false;
}


bool isPow(char* input)
{
	if (input == NULL) return false;
	return (*input == '^');
}


bool isArrow(char* input)
{
	if (input == NULL) return false;
	return (*input == '(');
}

bool isSymbol(char* input)
{
	if (input == NULL) return false;
	return (*input == '-' || *input == '+' || *input == '*' || *input == '/');
}


int calculateCoefficient(char * tmp)
{
	if (tmp == NULL)   return 1;
	if (*tmp == '\0') return 1;
	if (*tmp == '-' && *tmp == '\0') return -1;
	if (*tmp == '+' && *tmp == '\0') return 1;

	return atoi(tmp);
}


char* getExp(char* input) 
{
	if (input == NULL) return NULL;
	if (*input == '\0') return NULL;
	if (*input != '^') return NULL;
	input++;
	char* tmp = new char;

	if (*input == '-' || *input == '+')
	{
		*tmp = *(input++);
		*(tmp + 1) = '\0';	
	}
	else
	*tmp = '\0';

		
	strcat(tmp, getNum(input));
	return tmp;
}


fonction* parseInput(char* input, fonction* fonc, fonction* old, char* tmp)
{





	if (input == NULL)
		return NULL;
	if (*input == '\0')
	{

		if (tmp == NULL || tmp == '\0') return NULL;
		fonction* f = initializeFonction();
		f->coefficient = calculateCoefficient(tmp);
		f->fon = new char;
		strcpy(f->fon, "idt");
		return f;
	} //return NULL;
	if (isNumber(*input))
	{
		char* cc = getNum(input);

		if (tmp == NULL)
		{
			tmp = new char;
			strcpy(tmp, "");
		}


		strcat(tmp, cc);
		//	strcpy
		//strcpy(tmp, cc);

		return parseInput(input + strlen(cc), fonc, old, tmp);
	}


	char* tmpz;

	//if (old == NULL) old = (fonction*)malloc(sizeof(fonction));

	int coeffInt = 0;
	char * coef;
	int z;



	switch (*input)
	{




	case '-':
		if (tmp != NULL)
		{
			fonc = parseInput("", NULL, NULL, tmp);
			tmp = new char;
			*tmp = '-';
			*(tmp + 1) = '\0';
			fonc->next = parseInput(++input, NULL, NULL, tmp);
			return fonc;
		}
		tmp = new char;
		*tmp = '-';
		*(tmp + 1) = '\0';
		return parseInput(++input, fonc, old, tmp);



	case '+':
		if (tmp != NULL)
		{
			fonc = parseInput("", NULL, NULL, tmp);
			tmp = new char;
			*tmp = '+';
			*(tmp + 1) = '\0';
			fonc->next = parseInput(++input, NULL, NULL, tmp);
			return fonc;
		}



		tmp = new char;
		*tmp = '+';
		*(tmp + 1) = '\0';

		return parseInput(++input, fonc, old, tmp);




	case '*':
		if (fonc == NULL)
			fonc = initializeFonction();
		fonc->fx = old;
		old = NULL;
		input = input + 2;
		tmpz = getEndArrow(input);
		fonc->gx = parseInput(tmpz, NULL, NULL, NULL);
		fonc->fon = new char;
		strcpy(fonc->fon, "mul");
		fonc->next = parseInput(input + strlen(tmpz) + 1, NULL, NULL, NULL);
		return fonc;


	case '/':
		if (fonc == NULL)
			fonc = initializeFonction();
		fonc->fx = old;
		old = NULL;
		input = input + 2;
		tmpz = getEndArrow(input);
		fonc->gx = parseInput(tmpz, NULL, NULL, NULL);
		fonc->fon = new char;
		strcpy(fonc->fon, "mul");
		fonc->next = parseInput(input + strlen(tmpz) + 1, NULL, NULL, NULL);
		return fonc;

	case '(':
		tmpz = getEndArrow(input + 1);
		old = parseInput(tmpz, NULL, NULL, NULL);
		return parseInput(input + strlen(tmpz) + 2, fonc, old, NULL);

	case ')':
		return parseInput(input++, fonc, old, NULL);

		//	case '^':



	default:
		if (fonc == NULL)
			fonc = (fonction*)malloc(sizeof(fonction));

		fonc->coefficient = calculateCoefficient(tmp);
		fonc->fon = getExpression(input);
		if (*(fonc->fon) == '\0')
		{
			strcpy(fonc->fon, "idt");
			fonc->next = parseInput(++input, NULL, NULL, NULL);
		}
		else
		{
			input += strlen(fonc->fon);
			if (*(fonc->fon) != 'x')
			{
				input++;
				tmpz = getEndArrow(input);
				fonc->fx = parseInput(tmpz, NULL, NULL, NULL);
				input += strlen(tmpz) + 1;
				char* exp = getExp(input);


				if (exp != NULL)
				{

					fonc->puissance = atoi(exp);
					input += strlen(exp) + 1;
				}
				else
					fonc->puissance = 1;

				fonc->next = parseInput(input, NULL, NULL, NULL);
			}
			else
			{
				fonc->fx = NULL;
				fonc->gx = NULL;

				char* exp = getExp(input);


				if (exp != NULL)
				{

					fonc->puissance =S atoi(exp);
					input += strlen(exp) + 1;
				}
				else
					fonc->puissance = 1;

				fonc->next = parseInput(input, NULL, NULL, NULL);
			}

		}

	}


	return fonc;



}


fonction* getDerive(fonction *  f) 
{
	//you can add more functions here
	 
	if (f == NULL) 
		return NULL;

	if (!strcmp(f->fon, "idt")) 		return getDerive(f->next);

	if (!strcmp(f->fon, "x"))
	{
		fonction* derive = initializeFonction();
		derive->puissance = f->puissance - 1;
		derive->fon = new char;
		if (derive->puissance == 0)
			strcpy(derive->fon, "idt");
		else
			strcpy(derive->fon, "x");
		derive->coefficient = f->coefficient * f->puissance;
		derive->next = getDerive(f->next);
		return derive;
	}

	if (!strcmp(f->fon, "mul"))
	{
		fonction* f1= initializeFonction();
		f1->fon = new char;
		strcpy(f1->fon, "mul");
		f1->fx = getDerive(f->fx);
		f1->gx = f->gx;


		fonction* f2 = initializeFonction();
		f2->fon = new char;
		strcpy(f2->fon, "mul");
		f2->fx = getDerive(f->gx);
		f2->gx = f->fx;

		f1->next = f2;
		f2->next = getDerive(f->next);



		return f1;


	}

	if (!strcmp(f->fon, "cos")) 
	{
		

		fonction* f1 = initializeFonction();
		f1->fon = new char;
		strcpy(f1->fon, "sin");
		

		f1->coefficient = - f->coefficient  ;
		f1->fx = f->fx;

		fonction* f2 = getDerive(f->fx);


		fonction* f3 = initializeFonction();
		f3->fon = new char;
		strcpy(f3->fon, "mul");
		f3->fx = f1;
		f3->gx = f2;
		
		
		
		if (f->puissance != 1)
		{
			f1->coefficient = -f->coefficient * f->puissance;
			f1->puissance = f->puissance - 1;


			fonction* f4 = initializeFonction();
			f4->fon = new char;
			strcpy(f4->fon, "mul");
			f4->fx = f3;
			f4->gx = f;
			f4->next = getDerive(f->next);
			return f4;

		}
		
		
		
		
		f3->next = getDerive( f->next );
		
		
		
		
		return f3;

	}

	if (!strcmp(f->fon, "sin"))
	{


		fonction* f1 = initializeFonction();
		f1->fon = new char;
		strcpy(f1->fon, "cos");


		f1->coefficient = f->coefficient * f->puissance;
		f1->fx = f->fx;

		fonction* f2 = getDerive(f->fx);


		fonction* f3 = initializeFonction();
		f3->fon = new char;
		strcpy(f3->fon, "mul");
		f3->fx = f1;
		f3->gx = f2;



		if (f->puissance != 1)
		{
			f1->puissance = f->puissance - 1;


			fonction* f4 = initializeFonction();
			f4->fon = new char;
			strcpy(f4->fon, "mul");
			f4->fx = f3;
			f4->gx = f;
			f4->next = getDerive(f->next);
			return f4;

		}
		



			f3->next = getDerive(f->next);




		return f3;

	}

	if (!strcmp(f->fon, "lon")) 
	{

		fonction* f1 = initializeFonction();
		f1->fon = new char;
		strcpy(f1->fon, "div");
		f1->fx = getDerive(f->fx);
		f1->fx->coefficient = f1->fx->coefficient ;
		f1->gx = f->gx;
		
		fonction* f2 = initializeFonction();
		f2->fon = new char;
		strcpy(f2->fon, "idt");
		f2->coefficient = f->coefficient *  f->puissance;



		fonction* f3 = initializeFonction();
		f3->fon = new char;
		strcpy(f3->fon, "mul");
		f3->fx = f1;
		f3->gx = f2;



		if (f->puissance != 1)
		{
			f1->puissance = f->puissance - 1;


			fonction* f4 = initializeFonction();
			f4->fon = new char;
			strcpy(f4->fon, "mul");
			f4->fx = f3;
			f4->gx = f;
			f4->next = getDerive(f->next);
			return f4;

		}


		f3->next = getDerive(f->next);

		return f3;







	}



	if (!strcmp(f->fon, "div")) 
	{


		fonction* f1 = initializeFonction();
		f1->fon = new char;
		strcpy(f1->fon, "mul");
		f1->fx = getDerive(f->fx);
		f1->gx = f->gx;


		fonction* f2 = initializeFonction();
		f2->fon = new char;
		strcpy(f2->fon, "mul");
		f2->fx = getDerive(f->gx);
		f2->gx = f->fx;
		f2->coefficient = -1;


		f1->next = f2;
		f2->next = NULL;



		fonction* f3 = initializeFonction();
		f3->fon = new char;
		strcpy(f3->fon, "mul");
		f3->fx = f->gx;
		f3->gx = f->gx;



		fonction* f4 = initializeFonction();
		f4->fon = new char;
		strcpy(f4->fon, "div");
		f4->fx = f1;
		f4->gx = f3;
		f4->next = getDerive(f->next);		
	}

	if (!strcmp(f->fon, "exp")) 
	{


		fonction* f1 = initializeFonction();
		f1->fon = new char;
		strcpy(f1->fon, "exp");


		f1->coefficient = f->coefficient * f->puissance;
		f1->fx = f->fx;

		fonction* f2 = getDerive(f->fx);


		fonction* f3 = initializeFonction();
		f3->fon = new char;
		strcpy(f3->fon, "mul");
		f3->fx = f1;
		f3->gx = f2;



		if (f->puissance != 1)
		{
			f1->puissance = f->puissance - 1;


			fonction* f4 = initializeFonction();
			f4->fon = new char;
			strcpy(f4->fon, "mul");
			f4->fx = f3;
			f4->gx = f;
			f4->next = getDerive(f->next);
			return f4;

		}




		f3->next = getDerive(f->next);




		return f3;


	}





	if (!strcmp(f->fon, "cot"))
	{

		std::string s = std::to_string(f->coefficient);
		char const *pchar = s.c_str();

		fonction* f1 = parseInput((char*)pchar , NULL , NULL , NULL);
		fonction* f2 = f;
		f2->next = NULL;
		f2->coefficient = 1;
		strcmp(f->fon, "tan");



		fonction* f3 = initializeFonction();
		f3->fon = new char;
		strcpy(f3->fon, "div");
		f3->fx = f1;
		f3->gx = f2;


		fonction* f4 = getDerive( f3);
		f4->next = getDerive(f->next);



	}



	return NULL;



}





void closeexpandcoef(fonction* f) 
{



	if (f->coefficient != 1)
	{
		cout << ")" ;
	}


	if (f->puissance != 1)
	{
		cout << ")^" << f->puissance << ")" ;
	}


	cout << ")";

}


void toString(fonction* f)
{

	if (f == NULL) return;
	if (f->coefficient == 0)
	{
		toString(f->next);
		return;
	}


	cout << "+(";

	

	if (!strcmp(f->fon, "idt"))
	{
		cout << f->coefficient;

		cout << ")";
		toString(f->next);
		return;
	}


	if (f->puissance != 1)
	{
		cout << "((";
	}


	if (f->coefficient != 1) 
	{
		cout << f->coefficient << "(";
	}



	if (!strcmp(f->fon, "mul")) 
	{

		cout << "(";

		toString(f->fx);

		cout << ")*(";


		toString(f->gx);
		cout << ")";


		closeexpandcoef(f);
		toString(f->next);
		return;


	}

	
	

	if (!strcmp(f->fon, "div"))
	{

		cout << "(";

		toString(f->fx);

		cout << ")/(";


		toString(f->gx);
		cout << ")";


		closeexpandcoef(f);

		toString(f->next);
		return;


	}




	if (!strcmp(f->fon, "x")) 
	{
		cout << f->fon ;
	

		closeexpandcoef(f);
		toString(f->next);
		return;
	}



	cout << f->fon << "(";
	toString(f->fx);
		cout << ")";


		closeexpandcoef(f);
		toString(f->next);
	







}



void main()
{
	int a = 1;

	
	ifstream infile("txt.txt");
	string line;
	while (getline(infile, line))
	{
		istringstream iss(line);
		cout << "input\n";
		cout << line;
		char* cs = new char[line.length() + 1];
		strcpy( cs , line.c_str()  );
		fonction* result =  parseInput(cs, NULL, NULL, NULL);
	    fonction* derive = getDerive(result);
		

		cout << "\nparsed : \n";
		toString(result);


		cout << "\nresult : \n";
		cout << "\n\n\n\n";
		toString(derive);


		int i = 2;
		delete []cs;

	}
	


	//cout << check("+((+(-1(sin(+(3(x))))))*(+(3)))");

	//cout << getExp("^3");

	

	//char z[1000];
	//scanf("%s", z);
	//cin >> z;
	//cout << "\n" << getExpression(z);

	//cout << atoi("-232");

	//parseInput(z, NULL, NULL, NULL);

}





