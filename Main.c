#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct Cislo {
	int znak;
	char* cislo;
	char* fractional;
}typedef number;

char* zeroTrim(char* number);

int isSmaller(char* a,char* b) {
	if (strlen(a) < strlen(b))
		return 1;
	if (strlen(a) > strlen(b))
		return 0;
	for (int i = 0; i < (int)strlen(a); i++) {
		if (a[i] > b[i])
			return 0;
		else if (a[i] < b[i])
			return 1;
	}
	return 0;
}

//Reverse
char* strRev(char* a) {
	int revIndex = strlen(a)-1;
	if (!a || !*a)
		return a;
	for ( int i=0; i< (int)strlen(a)/2; i++)
	{
		char tmp = a[i];
		a[i] = a[revIndex];
		a[revIndex] = tmp;
		revIndex--;
	}
	return a;
}

//Soucet cisel podfunkce
char* findSum(char* a, char* b) {
	int prenos = 0;
	int soucet = 0;
	int delkaVys = 0;
	char* vys = NULL;

	if (isSmaller(b, a)) {
		char* tmp = a;
		a = b;
		b = tmp;
	}

	a=strRev(a);
	b=strRev(b);

	for (int i = 0; i < (int) strlen(a); i++)
	{
		soucet = (a[i] - '0') + (b[i] - '0') + prenos;
		vys = (char*)realloc(vys, sizeof(char) * (delkaVys + 1));
		delkaVys++;
		vys[delkaVys-1] = soucet%10 + '0';
		prenos = soucet / 10;
	}

	for (int i = strlen(a); i < (int) strlen(b); i++)
	{
		soucet = (b[i] - '0') + prenos;
		vys = (char*)realloc(vys, sizeof(char) * (delkaVys+1));
		delkaVys++;
		vys[delkaVys - 1] = soucet % 10 + '0';
		prenos = soucet / 10;
	}

	if (prenos > 0) {
		vys = (char*)realloc(vys, sizeof(char) * (delkaVys + 1));
		delkaVys++;
		vys[delkaVys - 1] = prenos+'0';
	}

    vys = (char*)realloc(vys, sizeof(char) * (delkaVys + 1));
    delkaVys++;
    vys[delkaVys - 1] = '\0';
    vys = strRev(vys);
	if(strcmp(vys,"0")!=0)
		vys = zeroTrim(vys);
	return vys;
}

//Rozdil mezi cisly
char* findDiff(char* a, char* b) {
	int prenos = 0;
	int diff = 0;
	int delkaVys = 0;
	char* vys = NULL;

	if (isSmaller(a, b)) {
		char* tmp = a;
		a = b;
		b = tmp;
	}

	a = strRev(a);
	b = strRev(b);

	for (int i = 0; i < (int) strlen(b); i++)
	{
		diff = (a[i] - '0') - (b[i] - '0') - prenos;
		if (diff < 0) {
			diff += 10;
			prenos = 1;
		}
		else prenos = 0;
		vys = (char*)realloc(vys, sizeof(char) * (delkaVys + 1));
		delkaVys++;
		vys[delkaVys - 1] = diff + '0';
	}

	for (int i = strlen(b); i < (int) strlen(a); i++)
	{
		diff = (a[i] - '0') - prenos;
		if (diff < 0) {
			diff += 10;
			prenos = 1;
		}
		else prenos = 0;
		vys = (char*)realloc(vys, sizeof(char) * (delkaVys + 1));
		delkaVys++;
		vys[delkaVys - 1] = diff + '0';
	}
    vys = (char*)realloc(vys, sizeof(char) * (delkaVys + 1));
    delkaVys++;
    vys[delkaVys - 1] = '\0';
    vys = strRev(vys);
	if (strcmp(vys, "0") != 0)
		vys = zeroTrim(vys);
	return vys;
}

//Soucet cisel
number addNum(number a, number b) {
	number vys;
	if (a.znak == b.znak) { 
		vys.znak = a.znak;
		vys.cislo = findSum(a.cislo, b.cislo);
		return vys;
	}
	else {
		if ((a.znak == 1 && isSmaller(b.cislo, a.cislo)) || (b.znak == 1 && isSmaller(a.cislo, b.cislo))) 
			vys.znak = 1;
		vys.cislo = findDiff(a.cislo, b.cislo);
		return vys;
	}
}

//Zero trimmer
char* zeroTrim(char* number) {
	int index = 0;
	int len = 0;
	char* newString;
	while (number[index] == '0')
		index++;
	len = strlen(number) - index;
	newString = (char*)malloc(sizeof(char) * (len + 1));
	memcpy(newString, &number[index], len);
	newString[len] = '\0';
	free(number);
	return newString;
}

//Nasobeni cisel
number findNas(number a, number b) {
	number vys;
	vys.znak = 0;
	int posun = 0;
	vys.cislo = (char*)malloc(sizeof(char) * 2);
	vys.cislo[0] = '0';
	vys.cislo[1] = '\0';
	if (!strcmp(a.cislo,"0") || !strcmp(b.cislo, "0"))
		return vys;
 
	a.cislo = strRev(a.cislo);
	b.cislo = strRev(b.cislo);
	for (int i = 0; i < (int) strlen(a.cislo); i++)
	{
		int prenos = 0;  
		char* tmpVys = NULL; 
		int tmpVysDelka = 0;
		number tmp;
		tmp.znak = 0;

		for (int j = 0; j < (int) strlen(b.cislo); j++)
		{
			int meziVys = 0;
			int cifra = 0;
			meziVys = (a.cislo[i] - '0') * (b.cislo[j] - '0') + prenos;
			prenos = meziVys / 10;
			cifra = meziVys % 10;
			tmpVys = (char*)realloc(tmpVys, sizeof(char) * (tmpVysDelka + 1));
			tmpVysDelka++;
			tmpVys[tmpVysDelka - 1] = cifra + '0';
		}

		if (prenos != 0) {
			tmpVys = (char*)realloc(tmpVys, sizeof(char) * (tmpVysDelka + 1));
			tmpVysDelka++;
			tmpVys[tmpVysDelka - 1] = prenos+'0';
		}

		tmpVys = (char*)realloc(tmpVys, sizeof(char) * (tmpVysDelka + 1));
		tmpVysDelka++;
		tmpVys[tmpVysDelka - 1] = '\0';
		tmpVys = strRev(tmpVys);

		for (int k = 0; k < posun; k++)
		{
			tmpVys = (char*)realloc(tmpVys, sizeof(char) * (tmpVysDelka + 1));
			tmpVysDelka++;
			tmpVys[tmpVysDelka - 2] = '0';
			tmpVys[tmpVysDelka - 1] = '\0';

		}

		posun++;
		tmp = vys;
		vys.cislo = findSum(vys.cislo, tmpVys);
		free(tmp.cislo);
		free(tmpVys);
	}
	if (a.znak != b.znak)
		vys.znak = 1;
	return vys;
}

//Data validation
int validation(int len, char** data) {
	int znak = 0;
	int strLen = 0;

	if (strcmp(data[1], "-s")!=0 && strcmp(data[1], "-m")!=0)
		return 1;

	for (int i = 2; i < len; i++)
	{
		strLen = strlen(data[i]);
		for (int j = 0; j < strLen; j++)
		{
			if (data[i][j] == '-' && j == 0)
				continue;
			znak = data[i][j];
			if ((znak < 48 || znak > 57) && znak != 46)
				return 1;
		}
	}
	return 0;
}

number* initNumber(int count, char** data) {
	number* poleCisel = (number*)malloc(sizeof(number) * (count - 2));
	for (int i = 2; i < count; i++) {
		int dotIndex = 0;
		for (int j = 0; j < strlen(data[i]); j++)
		{
			if (data[i][j] == '.')
				dotIndex = j;
		}
		if (data[i][0] == '-') {
			poleCisel[i - 2].znak = 1;

			if (dotIndex == 0) { // -15\0
				poleCisel[i - 2].cislo = (char*)malloc(sizeof(char) * (strlen(data[i])));
				memcpy(poleCisel[i - 2].cislo, &data[i][1], sizeof(char) * (strlen(data[i])));
			}
			else {
				poleCisel[i - 2].cislo = (char*)malloc(sizeof(char) * dotIndex);
				memcpy(poleCisel[i - 2].cislo, &data[i][1],sizeof(char)*(dotIndex-1));// -126.4
				poleCisel[i - 2].cislo[dotIndex - 1] = '\0';
			}
		}
		else {
			poleCisel[i - 2].znak = 0;
			                        
			if (dotIndex == 0) {//15
				poleCisel[i - 2].cislo = (char*)malloc(sizeof(char) * (strlen(data[i])+1));
				memcpy(poleCisel[i - 2].cislo, &data[i][0], sizeof(char) * (strlen(data[i])+1));
			}
			else {
				poleCisel[i - 2].cislo = (char*)malloc(sizeof(char) * (dotIndex + 1));
				memcpy(poleCisel[i - 2].cislo, &data[i][0], sizeof(char) * dotIndex); // 126.4
				poleCisel[i - 2].cislo[dotIndex] = '\0';
			}

		}
		if (dotIndex == 0) {
			poleCisel[i - 2].fractional = (char*)malloc(sizeof(char) * 2);
			strcpy(poleCisel[i - 2].fractional, "0\0");
		}
		else {
			poleCisel[i - 2].fractional = (char*)malloc(sizeof(char) * ((strlen(data[i]) - dotIndex+1) + 1)); //126.4
			memcpy(poleCisel[i - 2].fractional, &data[i][dotIndex + 1],(strlen(data[i]) - dotIndex+1));
			poleCisel[i - 2].fractional[(strlen(data[i]) - dotIndex+1)] = '\0';
		}
	}
	return poleCisel;
}

void printNum(number cislo) {
	
		if (cislo.znak == 1)
			printf("-");
		printf("%s", cislo.cislo);
		if (strcmp(cislo.fractional,"0") != 0)
			printf(".%s\n", cislo.fractional);
		else printf("\n");
}

void addZero(number* a, number* b) {
	int frLenA = strlen(a->fractional);
	int frLenB = strlen(b->fractional);
	int rozdil = 0;
	if (frLenA > frLenB) {
		rozdil = frLenA - frLenB;
		for (int i = 0; i < rozdil; i++)
		{
			b->fractional = (char*)realloc(b->fractional, sizeof(char) * (frLenB + 2));
			b->fractional[frLenB] = '0';
			b->fractional[frLenB+1] = '\0';
			frLenB++;
		}
	}
	else if (frLenA < frLenB) {
		rozdil = frLenB - frLenA;
		for (int i = 0; i < rozdil; i++)
		{
			a->fractional = (char*)realloc(a->fractional, sizeof(char) * (frLenA + 2));
			a->fractional[frLenA] = '0';
			a->fractional[frLenA + 1] = '\0';
			frLenA++;
		}
	}
		
}

number fracSum(number* num1, number* num2) {
	number vys;
	vys.znak = 0;
	int delkaDes = 0;
	char* prenos = "1";
	char* tmp;
	char* tmp2;

	//Kladne
	if (num1->znak == num2->znak) {
		vys.znak = num1->znak;
		addZero(num1, num2);
		delkaDes = strlen(num1->fractional);
		tmp = findSum(num1->fractional, num2->fractional); //14.500 + 15.641

		if (strlen(tmp) > delkaDes) {
			vys.fractional = (char*)malloc(sizeof(char) * delkaDes + 1);
			memcpy(vys.fractional, &tmp[1], delkaDes + 1);
			free(tmp);
			tmp2 = findSum(num2->cislo, prenos);
			vys.cislo = findSum(num1->cislo, tmp2);
			free(tmp2);
		}
		else {
			vys.fractional = tmp;
			vys.cislo = findSum(num1->cislo, num2->cislo);
		}

		return vys;
	}

	//Zaporne
	else {
		addZero(num1, num2);
		delkaDes = strlen(num1->fractional);
		if ((num1->znak == 1 && isSmaller(num2->cislo, num1->cislo)) || (num2->znak == 1 && isSmaller(num1->cislo, num2->cislo)))
			vys.znak = 1;

		char* numString1 = (char*) malloc(sizeof(char)*(strlen(num1->cislo)+strlen(num1->fractional)+1));
		strcpy(numString1, num1->cislo);
		strcat(numString1, num1->fractional);

		char* numString2 = (char*) malloc(sizeof(char) * (strlen(num2->cislo) + strlen(num2->fractional) + 1));
		strcpy(numString2, num2->cislo);
		strcat(numString2, num2->fractional);

		tmp = findDiff(numString1, numString2);
		vys.cislo = (char*)malloc(sizeof(char) * (strlen(tmp) - delkaDes+1));
		memcpy(vys.cislo, tmp, (strlen(tmp) - delkaDes));
		vys.cislo[strlen(tmp) - delkaDes] = '\0';

		vys.fractional = (char*)malloc(sizeof(char) * delkaDes+1);
		memcpy(vys.fractional, &tmp[(strlen(tmp) - delkaDes)], delkaDes);
		vys.fractional[delkaDes] = '\0';

		free(numString1);
		free(numString2);
		free(tmp);
	}
	return vys;
}

number fracNas(number num1, number num2) {
	int delkaDes = 0;
	number tmp;
	number tmp1;
	number tmp2;
	number vys;
	vys.znak = 0;

	if (((strcmp(num1.cislo, "0") == 0 && strcmp(num1.fractional, "0") == 0) || ((strcmp(num2.cislo, "0") == 0) && strcmp(num2.fractional, "0") == 0))) {
		vys.cislo = (char*)malloc(sizeof(char) * 2);
		strcpy(vys.cislo, "0\0");
		vys.fractional = (char*)malloc(sizeof(char) * 2);
		strcpy(vys.fractional, "0\0");
		return vys;
	}
	char* numString1 = (char*)malloc(sizeof(char) * (strlen(num1.cislo) + strlen(num1.fractional) + 1));
	strcpy(numString1, num1.cislo);
	strcat(numString1, num1.fractional);
	tmp1.znak = 0;
	tmp1.cislo = numString1;
	tmp1.fractional = "0";

	char* numString2 = (char*)malloc(sizeof(char) * (strlen(num2.cislo) + strlen(num2.fractional) + 1));
	strcpy(numString2, num2.cislo);
	strcat(numString2, num2.fractional);
	tmp2.znak = 0;
	tmp2.cislo = numString2;
	tmp2.fractional = "0";

	tmp = findNas(tmp1, tmp2);
	delkaDes = strlen(num1.fractional) + strlen(num2.fractional);
	if (strlen(tmp.cislo - delkaDes) == 0) {
		vys.cislo = (char*)malloc(sizeof(char) * 2);//0.4
		vys.cislo[0] = '0';
		vys.cislo[1] = '\0';
	}
	else {
		vys.cislo = (char*)malloc(sizeof(char)*(strlen(tmp.cislo) - delkaDes+1));//0.4
		memcpy(vys.cislo, tmp.cislo, (strlen(tmp.cislo) - delkaDes));
		vys.cislo[strlen(tmp.cislo) - delkaDes] = '\0';
	}

	vys.fractional = (char*)malloc(sizeof(char) * delkaDes + 1);
	memcpy(vys.fractional, &tmp.cislo[(strlen(tmp.cislo) - delkaDes)], delkaDes);
	vys.fractional[delkaDes] = '\0';

	free(numString1);
	free(numString2);
	free(tmp.cislo);

	if (num1.znak != num2.znak)
		vys.znak = 1;

	return vys;
}

int main(int argc, char** argv) { 
	int valid = validation(argc, argv);
	if (valid == 1) {
		printf("You have entered wrong data or command format\n");
		return 1;
	}

	number* poleCisel = initNumber(argc, argv);
	number vys;
	number tmp;

	//Soucet
	if (strcmp(argv[1], "-s")==0) {
		vys = poleCisel[0];
		for (int i = 1; i < argc - 2; i++) {
			tmp = fracSum(&vys, &poleCisel[i]);
			free(vys.cislo);
			free(vys.fractional);
			vys = tmp;
			free(poleCisel[i].cislo);
			free(poleCisel[i].fractional);
		}

		printNum(vys);
		free(poleCisel);
		free(vys.cislo);
		free(vys.fractional);
		return 0;
	}

	// Nasobeni
	if (strcmp(argv[1], "-m")==0) {
		vys = poleCisel[0];
		for (int i = 1; i < argc - 2; i++) {
			tmp = fracNas(vys, poleCisel[i]);
			free(vys.cislo);
			free(vys.fractional);
			vys = tmp;
			free(poleCisel[i].cislo);
			free(poleCisel[i].fractional);
		}

		printNum(vys);
		free(poleCisel);
		free(vys.cislo);
		free(vys.fractional);
		return 0;
	}
	return 0;
}