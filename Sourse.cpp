#include <iostream>
#include<stdio.h>
#include <string.h>
#include<cstring>
#include <fstream>
#include<ctype.h>
#include <iostream>
#include <iostream>
#include<stdio.h>
#include <string.h>
#include<cstring>
#include <fstream>
#include<ctype.h>
#include <regex>



using namespace std;


typedef enum TSymbolType
{
	ident, plusop,
	stringg, digitt, alpha,
	semicolon, period, quotas, othersy, colon, rSlash, lSlash, atsign, safe
}TSymbol; int Constant;
const int MAXINTEGER = 1000000;
const std::string fileName{ "filename" };


TSymbol Symbol;
char Char;
char Spelling[8];
string fName;
ifstream ifs;
int counter = 0;
char arr[100];




void GetNextChar() {
	std::ifstream ifs(fileName);


	if (ifs.is_open() == true) {


		char c; int i = 0;
		while (ifs.get(c)) {
			arr[i] = c;
			i++;


		}
		Char = arr[counter];
		counter++;


	}
	else
		cout << "File could not be open!" << endl;


}


void GetNextSymbol()
{
	int digit = 0;
	int k = 0;


	while (Char == ' ')
	{
		GetNextChar();
	}
	switch (toupper(Char))
	{
	case 65:case 66:case 67:
	case 68:
	case 69:
	case 70:
	case 71:
	case 72:
	case 73:
	case 74:
	case 75:
	case 76:
	case 77:
	case 78:
	case 79:
	case 80:
	case 81:
	case 82:
	case 83:
	case 84:
	case 85:
	case 86:
	case 87:
	case 88:
	case 89:
	case 90:
	{
		strcpy(Spelling, " ");
		do
		{
			if (k < 8)
			{
				Spelling[k] = toupper(Char);
				k++;
			}
			GetNextChar();
		} while ((Char >= 48) && (Char <= 57) || (toupper(Char) >= 65) && (toupper(Char) <= 90));
		Symbol = alpha;
		break;
	}
	case 48:
	case 49:
	case 50:
	case 51:
	case 52:
	case 53:
	case 54:
	case 55:
	case 56:
	case 57:
	{
		Constant = 0;
		do
		{
			digit = (unsigned int)(Char)-(unsigned int)(48);
			if ((Constant < (MAXINTEGER / 10)) || ((Constant == (MAXINTEGER / 10))
				&& (digit = (MAXINTEGER % 10))))
			{
				Constant = (10 * Constant) + digit;


			}
			else
			{
				printf("error: Int constant too large");
				Constant = 0;
			}GetNextChar();
		} while ((Char >= 48) && (Char <= 57));
		Symbol = digitt;
	}break;
	case 46:
	{
		Symbol = period;
		GetNextChar();
	}break;
	case 59:
	{
		Symbol = semicolon;
		GetNextChar();
	}break;
	case '"':
	{
		Symbol = quotas;
		GetNextChar();
	}break;
	case ':':
	{
		Symbol = colon;
		GetNextChar();
	}break;

	case '@':
	{
		Symbol = atsign;
		GetNextChar();
	}break;

	case '/':
	{

		Symbol = rSlash;
		GetNextChar();
	}break;

	case '$':
	{
		Symbol = safe;
		GetNextChar();
	}

	default:
	{
		Symbol = othersy;
		GetNextChar();
	}break;
	}
}


bool isValidURL(string url)
{
	const regex pattern("((http|ftp)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");

	if (url.empty())
	{
		return false;
	}

	if (regex_match(url, pattern))
	{
		return true;
	}
	else
	{
		return false;
	}
}





int accept(TSymbol sym)
{
	if (Symbol == sym)
	{
		GetNextSymbol();
		return 1;
	}
	return 0;
}
int expect(TSymbol sym)
{
	if (accept(sym))
	{

		return 1;
	}

	else
	{
		perror("URL: ");
	}
	return 0;

}

void xpalphas() {
	if (Symbol == alpha) {
		if (Symbol == alpha) {
			accept(alpha);
		}
		else if (Symbol == digitt) {
			accept(digitt);
		}
		else if (Symbol == safe) {
			accept(safe);
		}
		xpalphas();
	}

}

void Path() {
	xpalphas();
	if (Symbol == rSlash) {
		accept(rSlash);
		Path();
	}
}

void generic() {


}

void HostName() {
	accept(alpha);
	//ialpha();
	if (Symbol == period);
	accept(period);
	HostName();

}

void Digits() {
	accept(digitt);
	if (Symbol == digitt) {
		accept(digitt);
	}
}

void HostNumber() {
	Digits();
	expect(period);
	Digits();
	expect(period);
	Digits();
	expect(period);
	Digits();

}

bool Isxalpha()
{
	if (Symbol == alpha) {
		return alpha;
	}
	else if (Symbol == digitt) {
		return digitt;
	}
	else if (Symbol == safe) {
		return safe;
	}
	else
		perror("Not correct!");

}

void Password() {
	if (Symbol == alpha) {
		accept(alpha);
	}
	else if (Symbol == digitt) {
		accept(digitt);
	}
	else if (Symbol == safe) {
		accept(safe);
	}
	else
		perror("Not correct!");
	//xalphas();
}


void Login() {
	if (Isxalpha()) {
		{
			//User();
			accept(alpha);
			if (Symbol == colon) {
				accept(colon);
				Password();
			}
			accept(atsign);
		}
	}
	//HostPort();
	if (Symbol == alpha) {
		HostName();
	}
	else if (Symbol == digitt) {
		HostNumber();
	}
	/*else
		perror("Host Error");*/
	if (Symbol == colon) {
		accept(colon);
		//port();
		Digits();
	}
}


void port() {
	Digits();
}

void xalpha() {
	if (Symbol == alpha) {
		accept(alpha);
	}
	else if (Symbol == digitt) {
		accept(digitt);
	}
	else if (Symbol == safe) {
		accept(safe);
	}

}

void ialpha() {
	accept(alpha);
	/*if (Isxalpha) {
		xalphas();
	}*/
}


void Host() {
	if (Symbol == alpha) {
		HostName();
	}
	else if (Symbol == digitt) {
		HostNumber();
	}
	else
		perror("Host Error");
}

void HostPort() {
	Host();
	if (Symbol == colon) {
		accept(colon);
		port();
	}
}



void xalphas() {
	accept(alpha);
	//xalpha();
	/*if (Isxalpha()) {
		xalpha();

	}*/
}









bool URL() {
	if (Char == 'h') {
		accept(alpha);
		if (Char == 't') {
			accept(alpha);
			if (Char == 't') {
				accept(alpha);
				if (Char == 'p') {
					accept(alpha);
					accept(colon);
					accept(rSlash);
					accept(rSlash);
					HostPort();
				}
				else {
					ialpha();
					accept(colon);
					Path();
				}
			}
			else {
				ialpha();
				accept(colon);
				Path();
			}
		}
		else {
			ialpha();
			accept(colon);
			Path();
		}


	}
	else if (Char == 'f') {
		accept(alpha);
		if (Char == 't') {
			accept(alpha);
			if (Char == 'p') {
				accept(alpha);
				accept(colon);
				accept(rSlash);
				accept(rSlash);
				Login();
			}
			else {
				ialpha();
				accept(colon);
				Path();
			}
		}
		else {
			ialpha();
			accept(colon);
			Path();
		}


	}
	return URL;
}

void Field()
{
	//URL();
	if (URL())
	{
		;
	}
	else if (accept(quotas))
	{
		expect(alpha);
		expect(quotas);
	}
	else
	{
		perror("URL is not valid");
	}
}
void Record()
{
	Field();
	while ((Symbol == semicolon))
	{
		accept(semicolon);
		Field();
	}
	expect(period);
}
void DataFile(void)
{
	GetNextSymbol();
	//Record();
	while ((Symbol == alpha))
	{
		GetNextSymbol();
		//Record();
	}


}

void User() {
	xalphas();
}


int main() {

	string url = "http://abv.bg";


	/*GetNextSymbol();
	DataFile();*/

	if (isValidURL(url))
	{
		cout << "URL is valid" << endl;
	}
	else
	{
		cout << "URL not valid" << endl;
	}




	return 0;
}
