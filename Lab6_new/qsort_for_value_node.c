#include "qsort_for_value_node.h"

static int compare_values_amount(ValueNode node1, ValueNode node2){
    return node2.amount - node1.amount;
}

static void swap(ValueNode* v[], int i, int j){
    ValueNode* temp = malloc(sizeof(ValueNode));
    *temp = *v[j];
    *v[j] = *v[i];
    *v[i] = *temp;
    free(temp);
};

void value_node_qsort(ValueNode** v, int left, int right){
    int last;
    
    if (left >= right)
        return;
    swap(v, left, (left + right)/2);
    last = left;
    for (int i = left+1; i <= right; i++)
        if (compare_values_amount(*v[i], *v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    value_node_qsort(v, left, last-1);
    value_node_qsort(v, last+1, right);
};
