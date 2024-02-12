#include "Stack_interface.h"
#include <stdio.h>

u8 IsCharahcter(u8 Copy_u8Elemet)
{
    if (Copy_u8Elemet >= 'A' && Copy_u8Elemet <= 'z')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

u8 Piriority(u8 Copy_u8Operation)
{
    switch (Copy_u8Operation)
    {
    case '+':
        return 1;
        break;
    case '-':
        return 1;
        break;
    case '*':
        return 2;
        break;
    case '/':
        return 3;
        break;
    case '^':
        return 4;
        break;
    }
}

u8 InfixToPrefix(u8 *ptr2operaion)
{
    Stack PrefixStack;
    u8 Output_Prefix[100];
    u8 Output_Prefix_Iterator = 0;
    u8 PrefixStackHead = 0;
    /*it may be ((   while (*pstr != '=')    ))*/
    while (*ptr2operaion != '\0')
    {
        /*check if the element is a space*/
        if (*ptr2operaion == ' ')
        {
            continue; // OR *pstr++;
        }
        /*check if the element is a charachter*/
        else if (IsCharahcter(*ptr2operaion))
        {
            if (!Stack_u8StackFull)
            {
                Output_Prefix[Output_Prefix_Iterator] = *ptr2operaion++;
            }
        }
        else if (*ptr2operaion == '(')
        {
            Stack_PushStack(*ptr2operaion, &PrefixStack);
        }

        else if (*ptr2operaion == ')')
        {
            do
            {
                Stack_voidGetStackTop(&PrefixStack, &PrefixStackHead);
                Stack_PopStack(&PrefixStack, &Output_Prefix[Output_Prefix_Iterator++]);
            } while (PrefixStackHead != '(');

            Stack_PopStack(&PrefixStack, &PrefixStackHead);
        }

        else if (*ptr2operaion == '+' || *ptr2operaion == '-' || *ptr2operaion == '*' || *ptr2operaion == '/' || *ptr2operaion == '^')
        {
            Stack_voidGetStackTop(&PrefixStack, &PrefixStackHead);
            if (Piriority(*ptr2operaion) > Piriority(PrefixStackHead))
            {
                if (!Stack_u8StackFull)
                {
                    Stack_PushStack(*ptr2operaion, &PrefixStack);
                }
            }
            else if (Piriority(*ptr2operaion) <= Piriority(PrefixStackHead))
            {
                do
                {
                    if (!Stack_u8StackEmpty)
                    {
                        Stack_PopStack(&PrefixStack, &Output_Prefix[Output_Prefix_Iterator]);
                    }

                } while (Piriority(*ptr2operaion) <= Piriority(PrefixStackHead));
            }
        }
    }
    // while (*ptr2operaion != '\0')
    // printf("%s", Output_Prefix);
    return &Output_Prefix;
}

void main(void)
{
    u8 i = 0;
    u8 arr[100] = "(3+2)+7/2*((7+3)*2)";
    u8 *out = InfixToPrefix(&arr);
    while (*out != '\0')
    {
        printf("%c", out[i]);
    }
}