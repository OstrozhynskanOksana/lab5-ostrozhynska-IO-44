/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Lab 5: interface exported by the hello1 module
 */

#ifndef HELLO1_H
#define HELLO1_H

/*
 * print_hello() - print "Hello, world!" and remember in a list
 * the time just before and just after the print.
 *
 * Return: 0 on success, -ENOMEM if a list element can't be allocated.
 */
int print_hello(void);

#endif /* HELLO1_H */
