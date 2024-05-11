// Darius-Florentin Neatu <neatudarius@gmail.com>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;


// This abomination exists to support both answers with and without decimals.
struct atom {
	union {
		double db;
		long long ll;
	} value;

	bool is_ll;
};

int read_db_atom(FILE *f, atom *a) {
	a->is_ll = false;
	return fscanf(f, "%lf", &a->value.db);
}

int read_ll_atom(FILE *f, atom *a) {
	a->is_ll = true;
	return fscanf(f, "%lld", &a->value.ll);
}

// Checks if a part of an answer is acceptable, by comparing it with the reference.
bool match(atom *a, atom *b) {
	if (a->is_ll != b->is_ll) {
		return false;
	}

	if (a->is_ll) {
		return a->value.ll == b->value.ll;
	}

	// Our tasks only require rough precision.
	return abs(a->value.db - b->value.db) < 1e-1;
}

// Peeks at the answer to determine if floating point numbers are expected.
bool input_uses_double(FILE *f) {
	// We just check if the answer contains a period.
	char some_input[101];
	fgets(some_input, 100, f);
	bool uses_double = (strchr(some_input, '.') != NULL);

	// Move the file pointer back to pretend this operation did not happen.
	fseek(f, 0, SEEK_SET);

	return uses_double;
}

void DIE(float points, const char *msg) {
	FILE *f;

	f = fopen("score.verif", "wt");
	fprintf(f, "%.1f", points);
	fclose(f);

	f = fopen("output.verif", "wt");
	fprintf(f, "%s", msg);
	fclose(f);

	exit(0);
}

int main(int argc, char **argv) {
	if (argc != 3) {
		DIE(0, "Usage ./verif problem_name test_points");
	}

	char name[100];
	strcpy(name, argv[1]);
	strcat(name, ".out");

	float points = atof(argv[2]);

	FILE *file_out = fopen(name, "rt"),
		 *file_ref = fopen("res.ok", "rt");

	if (file_ref == NULL) {
		DIE(0, "Nu exista fisierul de referinta");
	}

	if (file_out == NULL) {
		DIE(0, "Nu exista fisier de output");
	}

	bool use_double = input_uses_double(file_ref);
	int (*read_atom)(FILE*, atom*) = use_double ? read_db_atom : read_ll_atom;

	atom answer_ref, answer_out;
	while (read_atom(file_ref, &answer_ref) == 1) {
		int ret = read_atom(file_out, &answer_out);
		if (ret < 0) {
			DIE(0, "Fisierul de iesire nu contine un numar corespunzator de numere");
		}

		if (!match(&answer_out, &answer_ref)) {
			char c[100];

			#ifdef ONLINE_JUDGE
			sprintf(c, "WA ");
			#else
			if (use_double) {
				sprintf(c, "Raspuns gresit ba %.1lf vs %.1lf", answer_out.value.db, answer_ref.value.db);
			} else {
				sprintf(c, "Raspuns gresit ba %lld vs %lld", answer_out.value.ll, answer_ref.value.ll);
			}
			#endif

			DIE(0, c);
		}
	}

	DIE(points, "Forta Steaua Campionii <3 ");

	return 0;
}
