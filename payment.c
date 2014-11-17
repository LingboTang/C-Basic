#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct payroll
{
	double salary;
	int numpaydays;
};
struct Employee
{
	struct payroll compensation;
	char firstName[10];
	char lastName[10];
	int age;
};

struct Employee record = {{34567,200},"Bob","Smith",29};

void displaysalar(struct Employee record)
{
	printf("%f\n",record.compensation.salary);
}

void payraise(struct Employee*record,double rate)
{
	record -> compensation.salary *= (1+rate);
}

int main()
{
	struct Employee record;
	printf("%f\n",record.compensation.salary);
	struct Employee e1, *e2;
	e2 = malloc(sizeof(struct Employee));
	*e2 = e1;
	payraise(&e1,.25);
	payraise(e2.25);
	return 0;
}
