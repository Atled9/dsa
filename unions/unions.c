#include <stdio.h>
#include <stdlib.h>

typedef union {
	double val;
	char *str;
} Data;

int main()
{
	/* only the last assigned member holds a valid value */
	Data data0;
	data0.val = 273.15;

	Data data1;
	data1.str = "Sphinx of black quart judge my vow";

	printf("%lf\n", data0.val);
	printf("%s\n", data1.str);
	printf("\n");

	Data *dataarr = (Data *)malloc(4 * sizeof(Data));

	dataarr->val = 3.14159;
	(dataarr + 1)->str = "The quick brown fox";
	(dataarr + 2)->val = 2.71828;
	(dataarr + 3)->str = "jumps over the lazy dog";

	printf("%lf\n", dataarr->val);
	printf("%s\n", (dataarr + 1)->str);
	printf("%lf\n", (dataarr + 2)->val);
	printf("%s\n", (dataarr + 3)->str);

	free(dataarr);

	return 0;
}
