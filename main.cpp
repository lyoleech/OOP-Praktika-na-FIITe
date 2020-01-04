//
//  main.cpp
//  sortirovka
//
//  Created by Olga Chernova on 08/07/2019.
//  Copyright © 2019 Olga Chernova. All rights reserved.
//
//вот здесь были деревья

#include <iostream>

using namespace std;

typedef struct NODE {
    int value;
    int balance;
    struct NODE * left;
    struct NODE * right;
    struct NODE * parent;
} NODE;

NODE * createTree() {
    NODE * tree = (NODE *)malloc(sizeof(NODE));
    tree->left = NULL;
    tree->right = NULL;
    tree->parent = NULL;
    tree->balance = 0;
    return tree;
}

NODE * createNode(int value) {
    NODE * node = (NODE *)malloc(sizeof(NODE));
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->value = value;
    node->balance = 0;
    return node;
}

int inTree(NODE * tree, int target);

NODE * balanceTree(NODE * node, int value);
NODE * balanceTree(NODE * node, int value) {
    NODE * p = NULL;
    switch (node->balance) {
        case 2:
            if (!(inTree(node->right->right, value))) {
                p = node->right;
                node->right = p->left;
                p->left = node->right->right;
                node->right->parent = node;
                p->left->parent = p;
                p->parent = node->right;
                node->right->right = p;
                node->right->balance = 1;
                p->balance = 0;
            }
            if (node->parent != NULL) {
                if (node->parent->left == node)
                    node->parent->left = node->right;
                else
                    node->parent->right = node->right;
            }
            p = node->right;
            p->parent = node->parent;
            if (p->left != NULL)
                p->left->parent = node;
            node->right = p->left;
            node->parent = p;
            p->left = node;
            p->balance = 0;
            node->balance = 0;
            if (p->parent != NULL)
                return balanceTree(p->parent, value);
            else
                return p;
            break;
        case -2:
            if (!(inTree(node->left->left, value))) {
                p = node->left;
                node->left = p->right;
                p->right = node->left->left;
                node->left->parent = node;
                p->right->parent = p;
                node->left->balance = -1;
                p->balance = 0;
            }
            if (node->parent != NULL) {
                if (node->parent->left == node)
                    node->parent->left = node->left;
                else
                    node->parent->right = node->left;
            }
            p = node->left;
            node->left = p->right;
            if (p->right != NULL)
                p->right->parent = node;
            p->parent = node->parent;
            node->parent = p;
            p->right = node;
            p->balance = 0;
            node->balance = 0;
            if (p->parent != NULL)
                return balanceTree(p->parent, value);
            else
                return p;
            break;
        default:
            if (node->parent != NULL)
                return balanceTree(node->parent, value);
            else
                return node;
            break;
    }
}

NODE * pushTree(NODE * tree, int value) {
    if (!(inTree(tree, value))) {
        NODE * p = tree;
        NODE * node = createNode(value);
        while (1) {
            if (value > p->value) {
                if (p->right == NULL) {
                    p->right = node;
                    node->parent = p;
                    p->balance += 1;
                    //return tree;
                    return balanceTree(node->parent, value);
                } else {
                    p->balance += 1;
                    p = p->right;
                }
            } else if (value < p->value) {
                if (p->left == NULL) {
                    p->left = node;
                    node->parent = p;
                    p->balance -= 1;
                    //return tree;
                    return balanceTree(node->parent, value);
                } else {
                    p->balance -= 1;
                    p = p->left;
                }
            }
        }
    }
    return tree;
}

int inTree(NODE * tree, int target) {
    NODE * pivet = tree;
    while (pivet != NULL) {
        if (pivet->value == target)
            return 1;
        if (pivet->value < target)
            pivet = pivet->right;
        else if (pivet->value > target)
            pivet = pivet->left;
    }
    return 0;
}

void deleteTree(NODE ** tree);
void deleteTree(NODE ** tree) {
    if ((*tree)->left != NULL)
        deleteTree(&((*tree)->left));
    if ((*tree)->right != NULL)
        deleteTree(&((*tree)->right));
    free(*tree);
    *tree = NULL;
}

typedef struct ARR {
    int * array;
    int size;
    int vars;
} ARR;

ARR * createArr(int size) {
    ARR * arr = (ARR *)malloc(sizeof(ARR));
    if (size != 0)
        arr->array = (int *)malloc(sizeof(int) * size);
    else
        arr->array = NULL;
    arr->size = size;
    arr->vars = 0;
    return arr;
}

void clearArr(ARR * arr) {
    arr->vars = 0;
}

void pushArr(ARR * arr, int value) {
    arr->array[arr->vars] = value;
    arr->vars++;
}

void deleteArr(ARR ** arr) {
    if ((*arr)->size != 0)
        free((*arr)->array);
    free(*arr);
    *arr = NULL;
}

void quickSort(ARR * obj, int left, int right) {
    int i = left, j = right, pivet;
    int pivot = obj->array[(left + right) / 2];
    while (i <= j) {
        while (obj->array[i] < pivot)
            i++;
        while (obj->array[j] > pivot)
            j--;
        if (i <= j) {
            pivet = obj->array[i];
            obj->array[i] = obj->array[j];
            obj->array[j] = pivet;
            i++;
            j--;
        }
    }
    if (left < j)   quickSort(obj, left, j);
    if (i < right)  quickSort(obj, i, right);
}

int main (int argc, char ** argv) {
    int size, pivet;
    NODE * A = createTree();
    NODE * B = createTree();
    
    //scanf("%d", &size);
    cin >> size;
    for (int i = 0; i < size; i++) {
        //scanf("%d", &pivet);
        cin >> pivet;
        A = pushTree(A, pivet);
    }
    //scanf("%d", &size);
    cin >> size;
    for (int i = 0; i < size; i++) {
        //scanf("%d ", &pivet);
        cin >> pivet;
        B = pushTree(B, pivet);
    }
    //scanf("%d", &size);
    cin >> size;
    ARR * C = createArr(size);
    for (int i = 0; i < size; i++) {
        //scanf("%d", &pivet);
        cin >> pivet;
        pushArr(C, pivet);
    }
    ARR * D = createArr(size);
    for (int j = 0; j < 4; j++) {
        switch (j) {
            case 0:
                for (int i = 0; i < size; i++)
                    if (inTree(A, C->array[i]) && inTree(B, C->array[i]))
                        pushArr(D, C->array[i]);
                break;
            case 1:
                for (int i = 0; i < size; i++)
                    if (inTree(A, C->array[i]) && !(inTree(B, C->array[i])))
                        pushArr(D, C->array[i]);
                break;
            case 2:
                for (int i = 0; i < size; i++)
                    if (!(inTree(A, C->array[i])) && inTree(B, C->array[i]))
                        pushArr(D, C->array[i]);
                break;
            case 3:
                for (int i = 0; i < size; i++)
                    if (!(inTree(A, C->array[i])) && !(inTree(B, C->array[i])))
                        pushArr(D, C->array[i]);
                break;

        }
        quickSort(D, 0, D->vars - 1);
        //printf("%d\n", D->vars);
        cout << D->vars << "\n";
        for (int i = 0; i < D->vars; i++)
            //printf("%d ", D->array[i]);
            cout << D->array[i] << " ";
        //printf("\n");
        cout << "\n";
        clearArr(D);
    }
    deleteTree(&A);
    deleteTree(&B);
    deleteArr(&C);
    deleteArr(&D);
    return 0;
}


/*class Foo
{
public:
    void Bar()
    {
        auto func = [=]() mutable
        {
            ++m_val;
        };
        
        std::cout << m_val << " ";
        func();
        std::cout << m_val << " ";
    };

private:
        int m_val = 0;
};

int main()
{
    Foo foo;
    foo.Bar();
    foo.Bar();
}*/





/*using namespace std;

void doSomething(vector<int>& v)
{
    for (auto it = v.begin(); it != v.size(); ++it)
    {
        for (auto it2 = it; (it2 != v.begin()) && (*it2 < *(it2 - 1)); --it2)
        {
            swap(*it2, *(it2 - 1));
        }
    }
}

int main(){
    vector<int> v1 = { 10, 8, 6, 4, 2, 1 };;

    doSomething(v1);
    
    for(int i = 0; i < v1.size(); i++) {
        cout << v1[i] << ' ';
    }
    
    return 0;
}*/
 
 
 
 
 
/*void ArrayOutput(const int *arr, int maxSize){
    for (int i = 0; i < maxSize; ++i){
        std::cout << arr[i] % 100 << ' ';
    }
    std::cout << std::endl;
}


void SortAscending(int *arr, int maxSize){
    for (int i = 1; i < maxSize-1; ++i){
        for (int j = 0; j < maxSize - i; ++j){
            if (arr[j] > arr[j + 1]){
                std::swap(arr[j], arr[j+1]);
            }
        }
    }
}


void SortDescending(int *arr, int maxSize){
    for (int i = maxSize-1; i >= 0; --i){
        std::cout << arr[i] % 100 << ' ';
    }
    std::cout << std::endl;
}


double AverageValue(const int *arr, int maxSize){
    int sum = 0;
    for (int i = 0; i < maxSize; ++i){
        sum += arr[i];
    }
    return static_cast<double>(sum)/maxSize;
}


int First( int*arr, int maxSize){
    return arr[0];
}


double GeometricMean(const int*arr, int maxSize){
    double p = 1;
    for (int i = 0; i < maxSize; ++i){
        p *=arr[i];
    }
    return pow(p, (1.)/maxSize);
}


int Last(int *arr, int maxSize){
    return  arr[maxSize-1];
}


int Getchar(int*arr, int maxSize, int num){
    for (int i = 0; i < maxSize; ++i){
        if (arr[i] == num){
            return i;
        }
    }
    return 0;
}

//unsigned int PRNG(){
//  static unsigned int seed = 5;
//
//  seed = (8253729 * seed + 2396403);
//
//    return seed % 100;
//}

int main(){
    std::srand(time(NULL));
    int  maxSize;
    
    for (int i = 0; i < 3; ++i){
        std::cout << "Enter right size of Array" << std::endl;
        std::cin >> maxSize;
        if (maxSize == 0)
            exit(1);
        
        int *arr = new int[maxSize];
        
        for (int i = 0; i < maxSize; ++i){
            arr[i] = rand() % 100;
            std::cout << arr[i] << ' ';
        }
        std::cout << std::endl;
        
        SortAscending(arr, maxSize);
        ArrayOutput(arr, maxSize);
        SortDescending(arr, maxSize);
        
        std::cout << "\nWrite number to find\n";
        
        int num;
        std::cin >> num;
        
        std::cout << "\nFound item index " << Getchar(arr, maxSize, num) << std::endl;
        std::cout << "\nFirst " << First(arr, maxSize) << std::endl;
        std::cout << "\nLast " << Last(arr, maxSize) << std::endl;
        std::cout << "\nAverage value " << AverageValue(arr, maxSize) << std::endl;
        std::cout << "\nGeometric Mean " << GeometricMean(arr, maxSize) << std::endl;
        
        //delete[] arr;
    }
}
*/
