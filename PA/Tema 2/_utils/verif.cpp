// Darius-Florentin Neatu <neatudarius@gmail.com>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <vector>
using namespace std;


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

struct edge {
  int x, y, c;
};

void check_scandal(char *name) {
  int n, m;
  ifstream fin("scandal.in");

  fin >> n >> m;
  vector<edge> v;
  for (int i = 1; i <= m; ++i) {
    int x, y, c;
    fin >> x >> y >> c;
    v.push_back({x, y, c});
  }

  fin.close();

	strcat(name, ".out");
	FILE *file_out = fopen(name, "rt");

  if (file_out == NULL) {
		DIE(0, "Nu exista fisier de output");
	}

  vector<int> a(n + 1, 0);
  int k;
  int ret = fscanf(file_out, "%d", &k);
  if (ret < 0) {
    DIE(0, "Fisierul de iesire nu contine un numar corespunzator de numere");
  }

  for (int i = 1; i <= k; ++i) {
    int x;
    int ret = fscanf(file_out, "%d", &x);
    if (ret < 0) {
      DIE(0, "Fisierul de iesire nu contine un numar corespunzator de numere");
    }

    a[x] = 1;
  }

  for (auto it : v) {
    if (it.c == 0) {
      if (!(a[it.x] == 1 || a[it.y] == 1)) {
        DIE(0, "restrictie incalcata");
        return;
      }
    } else if (it.c == 1) {
      if (!(a[it.x] == 1 || a[it.x] + a[it.y] == 0)) {
        DIE(0, "restrictie incalcata");
        return;
      }
    } else if (it.c == 2) {
      if (!(a[it.y] == 1 || a[it.x] + a[it.y] == 0)) {
        DIE(0, "restrictie incalcata");
        return;
      }
    } else {
      if (!(a[it.x] == 0 || a[it.y] == 0)) {
        DIE(0, "restrictie incalcata");
        return;
      }
    }
  }
}

int main(int argc, char **argv) {
	if (argc != 3) {
		DIE(0, "Usage ./verif problem_name test_points");
	}

	char name[100];
	strcpy(name, argv[1]);
	float points = atof(argv[2]);

  if (strcmp(name, "scandal") == 0) {
    check_scandal(name);
	  DIE(points, "OK ");
    return 0;
  }

	strcat(name, ".out");

	FILE *file_out = fopen(name, "rt"),
		 *file_ref = fopen("res.ok", "rt");

	if (file_ref == NULL) {
		DIE(0, "Nu exista fisierul de referinta");
	}

	if (file_out == NULL) {
		DIE(0, "Nu exista fisier de output");
	}

	long long answer_out, answer_ref;
	while (fscanf(file_ref, "%lld", &answer_ref) == 1) {
		int ret = fscanf(file_out, "%lld", &answer_out);
		if (ret < 0) {
			DIE(0, "Fisierul de iesire nu contine un numar corespunzator de numere");
		}

		if (answer_ref != answer_out) {
			char c[100];

			#ifdef ONLINE_JUDGE
			sprintf(c, "WA ");
			#else
			sprintf(c, "WA %lld vs %lld", answer_out, answer_ref);
			#endif

			DIE(0, c);
		}
	}

	DIE(points, "OK ");

	return 0;
}
