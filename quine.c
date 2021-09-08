#include <stdio.h>
#include <stdlib.h>

void escape(const char *restrict in, char *restrict out);

int main(void)
{
	char escaped_prologue[1143];
	const char *prologue =
		"#include <stdio.h>\n"
		"#include <stdlib.h>\n"
		"\n"
		"void escape(const char *restrict in, char *restrict out);\n"
		"\n"
		"int main(void)\n"
		"{\n"
		"\tchar escaped_prologue[1143];\n"
		"\tconst char *prologue =\n"
		"%s\";\n"
		"\n"
		"\tescape(prologue, escaped_prologue);\n"
		"\tprintf(prologue, escaped_prologue);\n"
		"\n"
		"\treturn 0;\n"
		"}\n"
		"\n"
		"char *newline(char *out)\n"
		"{\n"
		"\t*out++ = 92;\n"
		"\t*out++ = 110;\n"
		"\t*out++ = 34;\n"
		"\t*out++ = 10;\n"
		"\t*out++ = 9;\n"
		"\t*out++ = 9;\n"
		"\t*out++ = 34;\n"
		"\n"
		"\treturn out;\n"
		"}\n"
		"\n"
		"void escape(const char *restrict in, char *restrict out)\n"
		"{\n"
		"\t*out++ = 9;\n"
		"\t*out++ = 9;\n"
		"\t*out++ = 34;\n"
		"\n"
		"\twhile (*in) {\n"
		"\t\tif (*in == 34 || *in == 92) {\n"
		"\t\t\t*out++ = 92;\n"
		"\t\t} else if (*in == 10) {\n"
		"\t\t\tout = newline(out);\n"
		"\t\t\t++in;\n"
		"\t\t\tcontinue;\n"
		"\t\t} else if (*in == 9) {\n"
		"\t\t\t*out++ = 92;\n"
		"\t\t\t*out++ = 116;\n"
		"\t\t\t++in;\n"
		"\t\t\tcontinue;\n"
		"\t\t}\n"
		"\n"
		"\t\t*out++ = *in++;\n"
		"\t}\n"
		"\t*out++ = 0;\n"
		"}\n"
		"";

	escape(prologue, escaped_prologue);
	printf(prologue, escaped_prologue);

	return 0;
}

char *newline(char *out)
{
	*out++ = 92;
	*out++ = 110;
	*out++ = 34;
	*out++ = 10;
	*out++ = 9;
	*out++ = 9;
	*out++ = 34;

	return out;
}

void escape(const char *restrict in, char *restrict out)
{
	*out++ = 9;
	*out++ = 9;
	*out++ = 34;

	while (*in) {
		if (*in == 34 || *in == 92) {
			*out++ = 92;
		} else if (*in == 10) {
			out = newline(out);
			++in;
			continue;
		} else if (*in == 9) {
			*out++ = 92;
			*out++ = 116;
			++in;
			continue;
		}

		*out++ = *in++;
	}
	*out++ = 0;
}
