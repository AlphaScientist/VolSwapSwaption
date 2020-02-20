/* TaggedInput.h */

#ifndef _TAGGEDINPUT_H_
#define _TAGGEDINPUT_H_

#include "FAErrorCode.h"

/* Define macro for setting up the argument structure */
#undef setupargs
#define setupargs(inputtable,cnt,argname,arg,argtype)\
    strcpy((inputtable)[(cnt)].name,(argname));\
     (inputtable)[(cnt)].type = (argtype);\
     (inputtable)[(cnt)].init = 0;\
     (inputtable)[(cnt)].val = (void *)&(arg);

/* structure for storing information about each input argument */

typedef struct {
    char name[48];  /* name of argument */
    int type;       /* type of the argument, either double or int. */
    void *val;      /* pointer for the address of the actual value */
    short init;     /* flag to see whether this argument was read. */
} ArgumentRecord;

#define READINPUTSDOUBLE 1
#define READINPUTSINTEGER 2
#define READINPUTSBOOLEAN 2
#define READINPUTSFLOAT 3

static int ReadInputs(FILE *FH, ArgumentRecord *TaggedInputTable, int numInputs)
{
    int i;
    int scanned;          /* number of items read from line by sscanf */
    int consumed;         /* has an input line been used at all? */
    int totalconsumed;    /* number expected inputs successfully read */
    char line[1024];
    char val[48];
    char name[48];

    /* This is the main read loop. For named arguments, it does not care
     * about blank lines or extra lines. It will read inputs in any
     * order into the right named variable. For plain arguments
     * (no names), it reads arguments in order. */

    totalconsumed = 0;
    while (fgets(line, 1024, FH)) {
        /* read each line until EOF */ 
        /* scan the name of the variable, 2nd string */ 
        consumed = 0;
        scanned = sscanf(line,"%s %s",val,name);    
        /* Go through the array of arguments to find the right one.
         * When found, read it in appropriately.
         * Go around again if a blank line is read */
        if (scanned > 0) {
          /* Make sure the first thing on the line is numeric.  This
             also relieves having to test this later.  Use strspn to filter. */ 
          if (strspn(val,"+-1234567890.eE") != strlen(val)) { 
              printf("ReadInputs : bad input line beginning with %s.  Numeric expected.\n", val);
              return TaggedInputError; 
          }
          /* Test that the name is an appropriate identifier. */
          if (scanned == 2) {
              if (!((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z')) ||
                (strspn(name,"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890") != strlen(name))) {
                  printf("ReadInputs : bad input line containing label %s.\n", name);
                  printf("Identifier expected.\n");
                  return TaggedInputError; 
              }
		  }
          for (i=0; i<numInputs; i++) {
            /* The consumed flag allows us to skip further work on this
               line if the named variable has already been set */
            if (consumed == 0) {
                if (!TaggedInputTable[i].init && 
                    (scanned == 1 || (scanned == 2 && (strcmp(name, TaggedInputTable[i].name) == 0)))) {
                    consumed = 1;
                    totalconsumed++;
                    switch (TaggedInputTable[i].type) { 
                        case READINPUTSDOUBLE:
                        if (strchr(val,(int)'.')) {
                           *(double *)TaggedInputTable[i].val = atof(val);
                        }
                    else {
                        printf("ReadInputs : %s not a double\n",TaggedInputTable[i].name);
                        return TaggedInputError;
                    }
                    break;
                    case READINPUTSFLOAT:
                        if (strchr(val,(int)'.')) {
                           *(float *)TaggedInputTable[i].val = (float)atof(val);
                        }
                        else {
                            printf("ReadInputs : %s not a float\n",TaggedInputTable[i].name);
                            return TaggedInputError;
                        }
                        break;
                    case READINPUTSINTEGER:
                        /* use strspn to filter, which will arrest non-integer data */
                        if (!(strchr(val,(int)'.'))) {
                            *(int *)TaggedInputTable[i].val = atoi(val);
                        }
                        else {
                            printf("ReadInputs : %s not an integer\n", TaggedInputTable[i].name);
                            return TaggedInputError;
                        }
                        break;
                    default: {
                        printf("ReadInputs : bad input type %d\n", TaggedInputTable[i].type);
                        return TaggedInputError;
                    }
                    }
                    TaggedInputTable[i].init = 1;
                    break;
                }
                else if (TaggedInputTable[i].init && (scanned == 2 && (strcmp(name, TaggedInputTable[i].name) == 0))) {
					consumed = 1;}
                }
		  }
          /* Warn that a line was not consumed because its label was not expected. */
          /* The totalconsumed test is necessary because if we have already gotten all
		     the input we want, the current line will not be consumed*/
          if(!consumed && totalconsumed < numInputs) {
              printf("ReadInputs : bad input line beginning with %s.\n", val);
              printf("No input was expected for a variable named %s.\n", name);
          }
       }
    }
    
    for (i=0; i<numInputs; i++) {
        if (!TaggedInputTable[i].init) {
            printf("ReadInputs : %s was not initialized\n",TaggedInputTable[i].name);
            return TaggedInputError;
        }
    }
    return 0;
}
#endif /* _TAGGEDINPUT_H_ */
