/* 
 * The MIT License
 *
 * Copyright 2020 The OpenNARS authors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef H_DECISION
#define H_DECISION

////////////////////
//  NAR Decision  //
////////////////////
//Realization of goals

//References//
//----------//
#include <stdbool.h>
#include <stdio.h>
#include "Memory.h"
#include "NAR.h"
#include "Config.h"

//Parameters//
//----------//
extern double CONDITION_THRESHOLD;
extern double DECISION_THRESHOLD;
extern double ANTICIPATION_THRESHOLD;
extern double ANTICIPATION_CONFIDENCE;
extern double MOTOR_BABBLING_CHANCE;
extern int BABBLING_OPS;

//Data structure//
//--------------//
typedef struct
{
    double desire;
    bool execute;
    int operationID[MAX_COMPOUND_OP_LEN];
    Operation op[MAX_COMPOUND_OP_LEN];
    Term arguments[MAX_COMPOUND_OP_LEN];
    Implication missing_specific_implication;
    Event *reason;
}Decision;

//Methods//
//-------//
//Init module
void Decision_INIT();
//execute decision
void Decision_Execute(Decision *decision);
//assumption of failure, also works for "do nothing operator"
void Decision_Anticipate(int operationID, Term op_term, long currentTime);
//NAR decision making rule applying when goal is an operation
Decision Decision_Suggest(Concept *goalconcept, Event *goal, long currentTime);

#endif
