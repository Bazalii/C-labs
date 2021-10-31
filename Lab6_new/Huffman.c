#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Huffman.h"

// структура для построения дерева Хаффмана
struct s_zipc_hfm{
    int a[288];
    int b[288];
    int pl[288];
    int pr[288];
    int pp[288];
    int p[288];
    int bl_count[288];
};

// структура кодов Хаффмана
struct s_zipc_sym {
    int   freq; // частота символа
    int   hcod; // код Хаффмана
    int   bits; // длина кода Хаффмана
};


//-------------- zipc_haffman_code --------------------
// расчет кодов Хаффмана
int zipc_haffman_code(struct s_zipc_hfm *tree, struct s_zipc_sym *sym,
                      int Max_sym, int Max_bits)
{
    int i, j, k, k1, k2, n, t1, t2, fl, cod, bits, len, aa, ab, bb;
    int *a  = tree->a;  // частоты листьев отсортированы по нарастанию
    int *b  = tree->b;  // частоты узлов
    int *pl = tree->pl; // левый потомок узла
    int *pr = tree->pr; // правый потомок узла
    int *pp = tree->pp; // родительский узел
    int *p  = tree->p;  // номер символа, его значение
    int *bl_count = tree->bl_count; // счетчики числа кодов для разных длин
    int next_code[20];  // счетчики значений кодов для разных длин (из deflate)

    // зарядка исходных массивов
    memset(tree, 0, sizeof(struct s_zipc_hfm));
    for(i = 0, n=0; i < Max_sym; i++){
        if(sym[i].freq > 0){
            a[n] = sym[i].freq;
            p[n] = i;
            n++;
        }
    }
    if(n==0) return(0); // n -число используемых символов алфавита
    if(n > (1 << Max_bits)) return(-1);
    if(n==1){ bl_count[1]++; goto RET;}

    // сортировка по возрастанию частоты символов
    for(i=0; i<n; i++){
        for(j=n-1; j>i; j--){
            if(a[j] < a[j-1]){
                t1     = a[j];      t2     = p[j];
                a[j]   = a[j-1];    p[j]   = p[j-1];
                a[j-1] = t1;        p[j-1] = t2;
            }
        }
    }

    // создание дерева
    // aa, ab, bb -суммы частот двух текущих узлов или листьев
    // k -индекс вновь создаваемого узла
    // i -индекс текущего листа
    // j -индекс текущего узла
    for(k=0, i=0, j=0; k<(n-1); k++){
        if(i<(n-1))    aa = a[i] + a[i+1]; else aa = 1000000;
        if(i<n && j<k) ab = a[i] + b[j];   else ab = 1000000;
        if(j<(k-1))    bb = b[j] + b[j+1]; else bb = 1000000;

        if(aa <= ab && aa <= bb){
            b[k] = aa;
            pl[k] = pr[k] = -1; // оба потомка листья, -1 -признак листа
            i += 2;
        }
        else if(ab <= aa && ab <= bb){
            b[k] = ab;
            pl[k] = j;  // левый потомок
            pr[k] = -1; // правый потомок это лист, -1 -признак листа
            pp[j] = k;  // родительский узел в левом потомке
            i++;
            j++;
        }
        else{
            b[k] = bb;
            pl[k] = j;   // левый потомок
            pr[k] = j+1; // правый потомок
            pp[j] = pp[j+1] = k; // родительский узел в потомках
            j += 2;
        }
    }

    // обход дерева
    for(k--, len=0, fl=0, i=0; i<(2*n); i++){ // k -индекс корневого узла
        if(fl==0){ // вниз по дереву
            len++;
            k1 = pl[k]; k2 = pr[k];
            if(k2<0) bl_count[len]++;
            if(k1<0){ bl_count[len]++; fl=1;} // если слева лист, то вверх
            else k=k1; // в левую ветвь.
        }
        if(fl==1){ // вверх по дереву
            len--;
            if(len<=0) break;
            k = k1 = pp[k];  // k, k1 -индекс родителя
            if(pr[k1] >= 0){ // если правая ветвь не пройдена, то туда
                k = pr[k1];  // k -индекс правой ветви родителя
                pr[k1] = -1; // отмечаем правую ветвь как пройденную
                fl=0;
            }
        }
    }

    // уменьшение длин кодов
    for(i=n-1; i>Max_bits; i--){
        for(; bl_count[i]>0;){
            for(j=i-2; j>0 && bl_count[j]<=0; j--);
            bl_count[i] -= 2;
            bl_count[i-1]++;
            bl_count[j]--;
            bl_count[j+1] += 2;
        }
    }

RET:

    // зарядка выходного массива
    for(cod=0, i=n-1, bits=1; bits <= Max_bits; bits++){
        if(bl_count[bits] > 0){
            for(j=0; j < bl_count[bits]; j++){
                sym[p[i--]].bits = bits;
            }
        }
    }

    for(bits = 1; bits <= Max_bits; bits++){
        cod = (cod + bl_count[bits-1]) << 1;
        next_code[bits] = cod;
    }
    for(i = 0;  i < Max_sym; i++){
        len = sym[i].bits;
        if(len != 0){
            sym[i].hcod = next_code[len];
            next_code[len]++;
        }
    }
    return(n);
}




//============= Тестовая обертка ==================


// Запустить программу. Для выбора одного из тестовых массивов частот, которые
// есть в функции main (по умолчанию - первый массив), ввести:
// --> arr 2  (или другой номер массива от 1 до 6)
// Для изменения частот символов и для введения новых символов ввести:
// --> A 510  (A -это старый или вновь введенный символ, 510 -его частота)
// Для изменения максимальной длины кодов (по умолчанию 15) ввести:
// --> max 4  (4 -максимальная длина кодов)
// Для запуска вычисления кодов ввести пустую строку.
// Настройки arr и max держатся до явной их смены. Введённые символы и частоты
// держатся до смены массива.

//-------------- print_bits ----------------
// Распечатать число в двоичном виде. len -длина(бит).
int print_bits(int val, int len)
{
    int i, maska = 1 << (len - 1);
    if((val >> len) != 0) printf("Error: val=%d; len=%d; ", val, len);
    for(i=0; i<len; i++){
        if((val & maska) != 0) printf("1");
        else printf("0");
        maska = maska >> 1;
    }
    return(0);
}

//---------------- main -----------------------
//printf("\n");
int Huffman_realize(int *Main_Array) {

    char buf[100], flag = 0;
    unsigned char ch;
    int i, k, fr, len, S, S0, Nsym; //arrnum
    struct s_zipc_hfm tree[1];
    struct s_zipc_sym sym[286];
    int Max_sym = 286;
    int Max_bits = 15;
    int a1[2 * 286];

    Nsym = (sizeof(sym) / sizeof(struct s_zipc_sym)); // число элементов sym

    memset(sym, 0, sizeof(sym));
    for (k = 0; k < (int) (sizeof(Main_Array) / (sizeof(Main_Array[0]))); k = k + 2) {
        sym[Main_Array[k]].freq = Main_Array[k + 1];
    }
for (int j = 0; j <256; ++j) {
        // ввод данных
        while (1) {
            k = strlen(buf);
            if (k > 0 && buf[k - 1] == '\n') buf[--k] = 0;
            if (k == 0) break;
            if (strncmp(buf, "max", 3) == 0) {
                Max_bits = atoi(buf + 3);
                printf("Max_bits=%d\n", Max_bits);
            } else if (strncmp(buf, "arr", 3) == 0) {
                memset(a1, 0, sizeof(a1));
                memmove(a1, Main_Array, sizeof(Main_Array));
                memset(sym, 0, sizeof(sym));
                for (k = 0; k < (int) (sizeof(a1) / (sizeof(a1[0]))); k = k + 2) {
                    sym[a1[k]].freq = a1[k + 1];
                }
            } else {
                k = sscanf(buf, "%c %d", &ch, &fr);
                if (k != 2) {
                    printf("Error\n");
                    continue;
                }
                sym[(int) ch].freq = fr;
            }
        }

        for (i = 0; i < Nsym; i++) { //обнулить
            sym[i].bits = 0;
            sym[i].hcod = 0;
        }

        k = zipc_haffman_code(tree, sym, Max_sym, Max_bits); // рассчет кодов
        printf("k = zipc_haffman_code()=%d\n", k);

        // распечатка кодов Хаффмана
        S = 0;
        S0 = 0;
        len = 0;
        for (i = 0, k = 1; i < Max_sym; i++) {
            if (sym[i].freq > 0) {
                printf("%2d. %c  len=%2d  freq=%5d  ",
                       k++, i, sym[i].bits, sym[i].freq);
                print_bits(sym[i].hcod, sym[i].bits);
                printf("\n");
                if (len < sym[i].bits) len = sym[i].bits;
                S = S + (sym[i].bits * sym[i].freq);
                S0 = S0 + 8 * sym[i].freq;
            }
        }
        printf("S =%d\n", S);
        printf("S0=%d\n", S0);
        printf("L =%0.3f  bit/symbol; max_len=%d\n", 8.0 * S / S0, len);

    }
}

 // int a[] -содержит частоты символов, отсортированные по возрастанию
    // int b[] -сюда заносятся частоты узлов
    // pl[] -левый потомок.
    // pr[] -правый потомок.
    // pp[] -родительский узел.

    // создание дерева
    // aa, ab, bb -суммы частот двух текущих узлов или листьев
    // k -индекс вновь создаваемого узла
    // i -индекс текущего листа
    // j -индекс текущего узла
//    for(k=0, i=0, j=0; k<(n-1); k++){
//        if(i<(n-1))    aa = a[i] + a[i+1]; else aa = 1000000;
//        if(i<n && j<k) ab = a[i] + b[j];   else ab = 1000000;
//        if(j<(k-1))    bb = b[j] + b[j+1]; else bb = 1000000;
//
//        if(aa <= ab && aa <= bb){
//            b[k] = aa;
//            pl[k] = pr[k] = -1; // оба потомка листья, -1 -признак листа
//            i += 2;
//        }
//        else if(ab <= aa && ab <= bb){
//            b[k] = ab;
//            pl[k] = j;  // левый потомок
//            pr[k] = -1; // правый потомок это лист, -1 -признак листа
//            pp[j] = k;  // родительский узел в левом потомке
//            i++;
//            j++;
//        }
//        else{
//            b[k] = bb;
//            pl[k] = j;   // левый потомок
//            pr[k] = j+1; // правый потомок
//            pp[j] = pp[j+1] = k; // родительский узел в потомках
//            j += 2;
//        }
//    }

