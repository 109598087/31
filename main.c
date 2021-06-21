#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    int value;
} stack_data;

int Permutations(int *data, stack_data *stack, int n, int *all_perm) {
    int k, j;
    for (j = 0; j < n; ++j) {
        data[j] = j + 1;
        stack[j].index = -1;
    }
    k = 0; //k代表跑到第幾層
    int x = 0;
    while (k >= 0) {
        if (k >= n) {
            for (j = 0; j < n; ++j) {
                printf("%d ", stack[j].value + 1);
                all_perm[x] = stack[j].value + 1;
                x++;
            }
            printf("\n");
            if (--k >= 0) //回到上一層，要將資料還原
                data[stack[k].index] = stack[k].value;
            continue;
        }
        for (j = stack[k].index + 1; j < n && data[j] < 0; ++j);
        if (j >= n) {
            if (--k >= 0) //回到上一層，要將資料還原
                data[stack[k].index] = stack[k].value;
            continue;
        }
        if (stack[k].index >= 0)
            data[stack[k].index] = stack[k].value;
        stack[k].index = j;
        stack[k].value = data[j];
        data[j] = -data[j]; //取負值代表被選過
        if (++k < n) //到下一層，index從頭開始
            stack[k].index = -1;
    }
    return x;
}

int get_Permutations_num(int *data, stack_data *stack, int n) {
    int k, j;
    for (j = 0; j < n; ++j) {
        data[j] = j + 1;
        stack[j].index = -1;
    }
    k = 0; //k代表跑到第幾層
    int x = 0;
    while (k >= 0) {
        if (k >= n) {
            for (j = 0; j < n; ++j) {
                x++;
            }
            if (--k >= 0) //回到上一層，要將資料還原
                data[stack[k].index] = stack[k].value;
            continue;
        }
        for (j = stack[k].index + 1; j < n && data[j] < 0; ++j);
        if (j >= n) {
            if (--k >= 0) //回到上一層，要將資料還原
                data[stack[k].index] = stack[k].value;
            continue;
        }
        if (stack[k].index >= 0)
            data[stack[k].index] = stack[k].value;
        stack[k].index = j;
        stack[k].value = data[j];
        data[j] = -data[j]; //取負值代表被選過
        if (++k < n) //到下一層，index從頭開始
            stack[k].index = -1;
    }
    return x;
}

int main() {
    int i, n;
    int *a;
    scanf(" %d", &n);
    a = (int *) malloc((sizeof(int) + sizeof(stack_data)) * n);
    int x = get_Permutations_num(a, (stack_data *) (a + n), n);
    int all_perm[100000] = {0};
    Permutations(a, (stack_data *) (a + n), n, all_perm);

//    printf("%d", x);
//    for (int i = 0; i < x; i++) {
//        printf("%d ", all_perm[i]);
//    }
//    printf("\n");

    int all_perm_2[x / n][n + 1];
    int row = 0;
    for (int i = 0; i < x; i++) {
        all_perm_2[row][0] = 1;
        int j = i % n;
        all_perm_2[row][j + 1] = all_perm[i];
        if (j == n - 1) {
            row++;
        }
    }

    printf("------------------------\n");
    for (int i = 0; i < x / n; i++) {
        for (int j = 0; j < n + 1; j++) {
            printf("%d ", all_perm_2[i][j]);
        }
        printf("\n");
    }




//    free(a);
    return 0;
}