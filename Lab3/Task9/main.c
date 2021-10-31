#include <stdio.h>
#include <stdlib.h>

int main() {
    //Task9
    int range_end = 0;
    int last_prime_number = 2;
    char is_prime_flag = 0;

    int prime_numbers_amount = 1;
    int* prime_numbers = (int*)malloc(sizeof(int));
    prime_numbers[0] = 2;

    while (range_end <= 2){
        printf("Please, input number(end of output range):\n");
        scanf("%d", &range_end);
    }

    int val = 3;
    while(last_prime_number < range_end){
        is_prime_flag = 1;
        for (int i = 0; i < prime_numbers_amount; i++){
            if(val % prime_numbers[i] == 0){
                is_prime_flag = 0;
                break;
            }
        }
        if (is_prime_flag){
            prime_numbers = (int*) realloc(prime_numbers, sizeof(int) * ++prime_numbers_amount);
            prime_numbers[prime_numbers_amount - 1] = val;
            last_prime_number = val;
        }
        val++;
    }

    printf("Prime numbers:");
    int output_coef = (prime_numbers[prime_numbers_amount - 1] <= range_end) ? 0 : 1;
    for (int i = 0; i < prime_numbers_amount - output_coef; i++)
            printf(" %d", prime_numbers[i]);
    printf("\n\n");

    while (range_end <= 2){
        printf("Please, input number(end of output range):\n");
        scanf("%d", &range_end);
    }

//Bank programm
    float sum_in_bank = -1;
    int annual_interest_rate = -1;
    int month_amount = -1;
    float annual_interest_rate_coef;

    while (sum_in_bank < 0){
        printf("Please, input start sum of money in the bank:\n");
        scanf("%f", &sum_in_bank);
    }
    while (annual_interest_rate < 0 || annual_interest_rate > 100){
        printf("Please, input annual interest rate in bank (in percents (0-100%%)):\n");
        scanf("%d", &annual_interest_rate);
    }
    while (month_amount < 0){
        printf("Please, input amount of month when money were in the bank:\n");
        scanf("%d", &month_amount);
    }

    annual_interest_rate_coef = 1.0 + ((annual_interest_rate/100.0) / 12);
    for (int i=0; i < month_amount; i++){
        sum_in_bank *= annual_interest_rate_coef;
        printf("\nMonth #%d:\n\tSumm in bank: %f\n", i+1, sum_in_bank);
    }
    return 0;
}
