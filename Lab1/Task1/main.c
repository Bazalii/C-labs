#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	int first_val, second_val;
    if (argc < 2){
		printf("ERROR: Not enough arguments");
		return 0;
	}
	if (argc > 2){
		printf("ERROR: Too many arguments");
		return 0;
	}
    char *name = argv[1];
	printf("%s", name);
    FILE *fin;
    fin = fopen(name, "r");
    char word;
    int k1 = 0, k2 = 0, sum = 0;
    while  (1){
        word = fgetc(fin);
        if (!(feof(word))) {
            if (word != ' ') {
                k1 += 1;
            }
            if (word == ' ') {
                sum += k1;
                k1 = 0;
                k2 += 1;
            }
            printf("%s", word);
        } else {
            break;
        }
    }
    printf("%d", sum/k2);
	return 0;
}



