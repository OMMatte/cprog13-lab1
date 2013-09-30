//
//  main.cpp
//  cprog13-vector
//
//  Created by Lucas Wiener on 9/30/13.
//  Copyright (c) 2013 cprog. All rights reserved.
//

#include <iostream>

int must_follow_a(char * start, int length, char a, char b) {
    int nr = 0;
    for (int i = 0; i < length; i++, ++start) {
        if (*start == a && *(start + 1) == b) // maintainers note: DANGER!
            nr += 1;
    }
    return nr;
}


