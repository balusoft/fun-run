//
//  backtrack_basic.h
//  CPP Test9
//
//  Created by Balaji Cherukuri on 8/30/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#ifndef __CPP_Test9__backtrack_basic__
#define __CPP_Test9__backtrack_basic__

#include <iostream>
#include <stdio.h>

#define MAXCANDIDATES 100
#define NMAX 100

namespace backtrack_basic {
    //bool finished = false; /* found all solutions yet? */
    
    bool is_a_solution(int a[], int k, int n) {
        return k == n;
    }
    
    void construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
    {
        c[0] = true;
        c[1] = false;
        *ncandidates = 2;
    }
    
    void construct_candidates2(int a[], int k, int n, int c[], int *ncandidates)
    {
        int i;                       /* counter */
        bool in_perm[NMAX];          /* who is in the permutation? */
        for (i=1; i<NMAX; i++) in_perm[i] = false;
        for (i=0; i<k; i++) in_perm[ a[i] ] = true;
        *ncandidates = 0;
        for (i=1; i<=n; i++)
            if (in_perm[i] == false) {
                c[ *ncandidates] = i;
                *ncandidates = *ncandidates + 1;
            }
    }
    
    void process_solution(int a[], int k, int input)
    {
        int i;
        for (i=1; i<=k; i++) {
            std::cout << std::boolalpha << a[i] << " ";
        }
        
        printf("\n{");
        for (i=1; i<=k; i++)
        /* counter */
            if (a[i]) printf(" %d",i);
        printf(" }\n");
    }
    

    void backtrack(int a[], int k, int input)
    {
        int c[MAXCANDIDATES];
        int ncandidates;
        int i;
        /* candidates for next position */
        /* next position candidate count */
        /* counter */
        if (is_a_solution(a,k,input))
            process_solution(a,k,input);
        else {
            k = k+1;
            construct_candidates2(a,k,input,c,&ncandidates);
            for (i=0; i<ncandidates; i++) {
                a[k] = c[i];
                //make_move(a,k,input);
                backtrack(a,k,input);
                //unmake_move(a,k,input);
                //if (finished) return;
                /* terminate early */
            }
        }
    }
    
    void generate_subsets(int n)
    {
        int a[NMAX];
        backtrack(a,0,n);
        std::cout << "\n\n";
    }
    
    void unitTest()
    {
        {
            generate_subsets(1);
            generate_subsets(2);
            generate_subsets(3);
        }
    }
}

#endif /* defined(__CPP_Test9__backtrack_basic__) */
