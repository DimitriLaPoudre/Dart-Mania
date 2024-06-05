/*
** EPITECH PROJECT, 2023
** my_list
** File description:
** struct of my list
*/

#ifndef MY_LIST_
    #define MY_LIST_

typedef struct linked_list {
    void *data;
    struct linked_list *next;
} linked_list_t;

#endif /* MY_LIST_ */
