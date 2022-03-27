#include <stdio.h>
#include <stdlib.h> // malloc / free
#include <memory.h> // memset
#include <math.h> // floor, log2, pow
#include <string.h>

int shell_status=0;

void Stack_Num_Printer(long long int *stack_num, int idx_num, const char *description){
    printf("\n%s, Display \" Stack_Num \", Current idx_Num = %d:\n\n", description, idx_num);
    printf(" head_(arry_idx = 10) --> ");
    for(int i=10; i>0; i--){
        printf(" |%lld| ", stack_num[i-1]);
    }
    printf(" <-- tail_(arry_idx = 0)\n");
}

void Stack_Opr_Printer(char *stack_opr, int idx_opr, const char *description){
    printf("\n%s, Display \" Stack_Opr \", Current idx_Opr = %d:\n\n", description, idx_opr);
    printf(" head_(arry_idx = 10) --> ");
    for(int i=10; i>0; i--){
        printf(" |%c| ", stack_opr[i-1]);
    }
    printf(" <-- tail_(arry_idx = 0)\n");
}

void Stack_Printer(long long int *stack_num, int idx_num, char *stack_opr, int idx_opr, const char *description){
    shell_status = system("clear");
    Stack_Num_Printer(stack_num, idx_num, description);
    Stack_Opr_Printer(stack_opr, idx_opr, description);
    printf("\n\n");
    shell_status = system("pause");
}

int Num_c2i(char *c_num){ // 0 <= ai <= 10^8 => int is enough (range of int => -2,147,483,648 to 2,147,483,647)
    int i_num = 0;
    int digits = strlen(c_num); // 判斷有幾位
    // printf("%s, %d\n", c_num, digits);
    for(int i=0; i<digits; i++){
        i_num += (c_num[i]-'0')*pow(10,(digits-i-1)); //每一位各自乘上對應的10^後相加
        // printf("%d, %c, %d, %d\n", i, c_num[i], digits, (digits-i-1));
    }
    // printf("%d\n", i_num);
    return i_num;
}

int Compare_Prio(char operator){
    int order = 0;
    if(operator == '(' || operator == ')'){
        order = 3;
    }
    if(operator == '*' || operator == '/' || operator == '%'){
        order = 2;
    }
    if(operator == '+' || operator == '-'){
        order = 1;
    }
    return order;
}

long long int bottom_div(long long int a, long long int b){
    if(a < 0){
        if(a%b != 0){
            return a/b-1;
        }
        else{
            return a/b;
        }
    }
    else{
        return a/b;
    }
}

long long int Do_Opr(long long int a, long long int b, char operator){
    if(operator == '+'){
        return a+b;
    }
    if(operator == '-'){
        return a-b;
    }
    if(operator == '*'){
        return a*b;
    }
    if(operator == '/'){
        return bottom_div(a,b);
    }
    if(operator == '%'){
        return a%b;
    }
}

int Pop_Calcu(long long int *stack_num, int *idx_num, char *stack_opr, int *idx_opr){


    // pop top number in Stack_Num -> set 0 -> go down
    long long int b = stack_num[*idx_num]; stack_num[*idx_num]=0; *idx_num = *idx_num-1;
    if(*idx_num<0){ printf("\nidx_num<0, Index Error! Please check your input. --> exit(-1)\n"); exit(-1);} // exit(-1) = program stop abnormally
    printf("\nPop TOP Num = %lld\n", b); shell_status = system("pause");
    Stack_Printer(stack_num, *idx_num, stack_opr, *idx_opr, "After Number Pop -> set 0 -> go down");


    // pop second number in Stack_Num -> set 0 -> go down
    long long int a = stack_num[*idx_num]; stack_num[*idx_num]=0; *idx_num = *idx_num-1;
    if(*idx_num<0){ printf("\nidx_num<0, Index Error! Please check your input. --> exit(-1)\n"); exit(-1);} // exit(-1) = program stop abnormally
    printf("\nPop Second Num = %lld\n", a); shell_status = system("pause");
    Stack_Printer(stack_num, *idx_num, stack_opr, *idx_opr, "After Number Pop -> set 0 -> go down");


    // pop top operator in Stack_Opr -> set '\0' -> go down
    char top_operator = stack_opr[*idx_opr]; stack_opr[*idx_opr]='\0'; *idx_opr = *idx_opr-1;
    printf("\nPop TOP Opr = %c\n", top_operator); shell_status = system("pause");
    Stack_Printer(stack_num, *idx_num, stack_opr, *idx_opr, "After Operator Pop -> set '\\0' -> go down");
    

    long long int new_Num = Do_Opr(a, b, top_operator);
    printf("\nCalculated 2 pop_out number, new_Num = %lld\n", new_Num); shell_status = system("pause");


    // push calculate result to stack_num
    *idx_num = *idx_num+1;
    stack_num[*idx_num] = new_Num; // push "new Number" to Stack_Num
    printf("\nPush new_Num, Stack_Num[%d] = %lld\n", *idx_num, stack_num[*idx_num]); shell_status = system("pause");
    Stack_Printer(stack_num, *idx_num, stack_opr, *idx_opr, "After push \"new_Num\"");

}

long long int Calcu_Cell(){

    char LISA_IN = 0; // LISA 的輸入 => input line < 10^6

    char c_Num[10] = {'\0'}; // char to int 的暫存區
    int num_count = 0; // c_Num 的位移器

    long long int Stack_Num[10] = {0};
    int idx_Num = 0; // Stack_Num 的位移器

    char Stack_Opr[10] = {'\0'};
    int idx_Opr = 0; // Stack_Opr 的位移器

    long long int Ans = 0;

    Stack_Printer(Stack_Num, idx_Num, Stack_Opr, idx_Opr, "init");

    while(1){

        LISA_IN = getchar();
        if((LISA_IN > 47)&&(LISA_IN < 58)){ // 判斷 LISA_IN 目前是否為數字
            c_Num[num_count] = LISA_IN; // 將 LISA_IN 存到 char to int 的暫存區
            num_count++;
            // printf("Number = %s, num_count = %d\n", c_Num, num_count);
            continue; // 抓到數字後，沒抓到 operator 前過不去
        }
            
        // DO: push Number to Stack
        int nxt_Num = Num_c2i(c_Num); // change input char to integer
        if(nxt_Num!=0){ // input number isn't 0
            printf("\nget next Num, nxt_Num = %d\n", nxt_Num); shell_status = system("pause");
            idx_Num++; // Stack_Num shift up
            Stack_Num[idx_Num] = (long long int)nxt_Num; // push "next Number" to Stack_Num
            printf("\nPush nxt_Num, Stack_Num[%d] = %lld\n", idx_Num, Stack_Num[idx_Num]); shell_status = system("pause");
            Stack_Printer(Stack_Num, idx_Num, Stack_Opr, idx_Opr, "After push \"nxt_Num\"");
        }

        // DO: push Operator to Stack
        char nxt_Opr = LISA_IN;
        printf("\nget next Opr, nxt_Opr is \"%c\"\n", nxt_Opr); shell_status = system("pause");

        if(LISA_IN == '\n'){break;} // end of input

        if(LISA_IN == '('){
            printf("\nnxt_Opr is \"%c\", create new \"Calcu_Cell()\"\n", nxt_Opr); shell_status = system("pause");

            long long int parentheses_Ans = Calcu_Cell();
            printf("\nget parentheses answer , parentheses_Ans = %lld\n", parentheses_Ans); shell_status = system("pause");
            idx_Num++; // Stack_Num shift up
            Stack_Num[idx_Num] = parentheses_Ans; // push "next Number" to Stack_Num
            printf("\nPush parentheses_Ans, Stack_Num[%d] = %lld\n", idx_Num, Stack_Num[idx_Num]); shell_status = system("pause");
            Stack_Printer(Stack_Num, idx_Num, Stack_Opr, idx_Opr, "After push \"parentheses_Ans\"");
            continue;
        }

        if(LISA_IN == ')'){
            printf("\nnxt_Opr is \"%c\", Calculate parentheses answer & close \"Calcu_Cell()\"\n", nxt_Opr); shell_status = system("pause");

            while(idx_Opr>0){ // Operator remained
                printf("\nOperator remained, DO \"Pop_Calcu()\"!\n"); shell_status = system("pause");
                Pop_Calcu(Stack_Num, &idx_Num, Stack_Opr, &idx_Opr);
            }
            return Stack_Num[idx_Num];
        }

        if(nxt_Opr == '='){ // if read "=" -> calculate for all operator
            printf("\nnxt_Opr is \"%c\", calculate \"partial answer\"\n", nxt_Opr); shell_status = system("pause");

            while(idx_Opr>0){ // Operator remained
                printf("\nOperator remained, DO \"Pop_Calcu()\"!\n"); shell_status = system("pause");
                Pop_Calcu(Stack_Num, &idx_Num, Stack_Opr, &idx_Opr);
            }
            Ans = Stack_Num[idx_Num]; // store final calculation to Ans
            printf("Print: %lld\n", Ans); // Answer print in specific format
        }
        else{
            
            if(Stack_Opr[idx_Opr] == '\0'){ 
                
                printf("\n\"Stack_Opr\" is NULL, can push nxt_Opr directly\n"); shell_status = system("pause");
                idx_Opr++;
                Stack_Opr[idx_Opr] = nxt_Opr;
                printf("\nPush nxt_Opr, Stack_Opr[%d] = %c\n", idx_Opr, Stack_Opr[idx_Opr]); shell_status = system("pause");
                Stack_Printer(Stack_Num, idx_Num, Stack_Opr, idx_Opr, "After push \"nxt_Opr\"");
            }
            else{ 

                printf("\n\"Stack_Opr\" is NOT! NULL, compare Priority\n"); shell_status = system("pause");
                int nxt_Opr_prio = Compare_Prio(nxt_Opr);
                int top_Opr_prio = Compare_Prio(Stack_Opr[idx_Opr]);
                printf("\nnxt_Opr is %c, Priority = %d\n", nxt_Opr, nxt_Opr_prio);
                printf("\ntop_Opr is %c, Priority = %d\n", Stack_Opr[idx_Opr], top_Opr_prio); shell_status = system("pause");

                while((nxt_Opr_prio <= top_Opr_prio) && idx_Opr>0){

                    printf("\nnxt_Opr_prio <= top_Opr_prio, can DO \"Pop_Calcu()\"!\n"); shell_status = system("pause");
                    Pop_Calcu(Stack_Num, &idx_Num, Stack_Opr, &idx_Opr);
                    top_Opr_prio = Compare_Prio(Stack_Opr[idx_Opr]); // recheck Operator now on the top of Stack_Opr
                    printf("\nnxt_Opr is %c, Priority = %d\n", nxt_Opr, nxt_Opr_prio);
                    printf("\ntop_Opr is %c, Priority = %d\n", Stack_Opr[idx_Opr], top_Opr_prio); shell_status = system("pause");
                }

                printf("\n( nxt_Opr_prio NOT! <= top_Opr_prio ) || ( idx_Opr NOT! > 0 ), CAN'T DO \"Pop_Calcu()\"!\n"); shell_status = system("pause");
                idx_Opr++;
                Stack_Opr[idx_Opr] = nxt_Opr;
                printf("\nPush nxt_Opr, Stack_Opr[%d] = %c\n", idx_Opr, Stack_Opr[idx_Opr]); shell_status = system("pause");
                Stack_Printer(Stack_Num, idx_Num, Stack_Opr, idx_Opr, "After push \"nxt_Opr\"");
            }
        }
        num_count = 0;
        memset(c_Num, '\0', sizeof(c_Num));
    }
}

int main(){

    Calcu_Cell();
    
}
