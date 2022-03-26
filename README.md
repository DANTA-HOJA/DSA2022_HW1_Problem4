# DSA2022_HW1_Problem4
110.2 CSIE1212_資料結構與演算法（DSA）：Calculate Simple Integers Easily （Integers_Calculator）


# Hint from email
```
There is a hint sample for Calculate Simple Integers Easily [CSIE] (Hw1 P4).

Input: 
> -7/3

Output: 
> Print: -3

We hope this will help you to debug. Good luck!
```

# Test_sample

- TAs
```
1+3-2*4=
> Print: -4 (Debug：total_step = 20)


1+2*(3+(8-6/3)*5)=
> Print: 67 (Debug：total_step = 42)


1+(2*3*(1+2+3*4/2*7+(1+8))+4)=/(11/5)+7-19*2=
> Print: 329 (Debug：total_step = 74)
> Print: 133 (Debug：total_step = 106)
```

- My
```
123+456*789=
> Print: 359907 (Debug：total_step = 14)


9999+1000*52+60=
> Print: 62059 (Debug：total_step = 20)


9999+1000*52+60=/10+9-3*11+44=
> Print: 62059 (Debug：total_step = 20)
> Print: 6225 (Debug：total_step = 50)


1+5*9++5+7=
> idx_num<0, Index Error! Please check your input. --> exit(-1)
```