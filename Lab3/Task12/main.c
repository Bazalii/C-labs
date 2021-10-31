#include <stdio.h>

int main(int argc, char **argv){
	int first_val, second_val;
	FILE *new_output_stream;
	if (argc < 4){
		printf("ERROR: Too low arguments");
		return 0;
	}
	if (argc > 4){
		printf("ERROR: Too more arguments");
		return 0;
	}

	sscanf(*++argv, "%d", &first_val);
	sscanf(*++argv, "%d", &second_val);

    if ((new_output_stream = freopen(*++argv, "w", stdout)) == NULL){
		printf("ERROR: Wrong open of output stream.");
		return 0;
	}

	printf("Answer: %d", first_val + second_val);
	return 0;
}




//int main2(int argc, char **argv){
//	int first_val, second_val;
//	char *Array[20];
//	FILE *new_output_stream;
//	if (argc < 4){
//		printf("ERROR: Not enough arguments");
//		return 0;
//	}
//	if (argc > 4){
//		printf("ERROR: Too many arguments");
//		return 0;
//	}
//	sscanf(*++argv, "%s", Array);
//	if ((new_output_stream = freopen(Array, "w", stdout)) == NULL){
//		printf("ERROR: Wrong open of output stream.");
//		return 0;
//	}
//	printf("Answer: %d", first_val+second_val);
//	return 0;
//	FILE *new_output_stream;
//	if (argc < 4){
//		printf("ERROR: Not enough arguments");
//		return 0;
//	}
//	if (argc > 4){
//		printf("ERROR: Too many arguments");
//		return 0;
//	}
//	if ((freopen(argv[3], "w", stdout)) == NULL){
//		printf("ERROR: Wrong open of output stream.");
//		return 0;
//	}
//	printf("Answer: %d", *argv[1] + *argv[2]);
//	return 0;
//}
