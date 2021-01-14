//
//  bit_operation.hpp
//  my_crypto
//
//  Created by qTp on 12/22/20.
//  Copyright © 2020 qTp. All rights reserved.
//

#ifndef bit_operation_hpp
#define bit_operation_hpp

#include <stdio.h>

#endif /* bit_operation_hpp */

#include "linked_list.hpp"
#include <string>

int CompareBit(LinkedList *l, LinkedList *r);
LinkedList *AddBit(LinkedList *x, LinkedList *y);
LinkedList *SubBit(LinkedList *x, LinkedList *y);
LinkedList *ShiftLeftBit(LinkedList *x, int shift);
LinkedList *MulMod(LinkedList *x, LinkedList *y, LinkedList *m);
LinkedList *PowMod(LinkedList *x, LinkedList *p, LinkedList *m);
bool CheckPrime(LinkedList *x);

string ToDecString(LinkedList *l);
string X2Dec(string desc);
string X2a1Dec(string desc);

