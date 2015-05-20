//jpms:bc
/*----------------------------------------------------------------------------*\
 * File:        utils.hh
 *
 * Description: 
 *
 * Author:      jpms
 * 
 *                                     Copyright (c) 2015, Joao Marques-Silva
\*----------------------------------------------------------------------------*/
//jpms:ec

#ifndef _UTILS_H
#define _UTILS_H 1

template <typename T>
void err_exit (T& outs, string const& msg) {
    outs << msg << "\n";
    exit(1);
}

#endif /* _UTILS_H */

/*----------------------------------------------------------------------------*/
