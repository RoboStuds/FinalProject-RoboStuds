#ifndef ARROW_H
#define ARROW_H

    typedef struct Arrow {
        int af, ab, ar, al;
    } Arrow;

    extern Arrow arrows;

    void setup_arrows();
    void cleanup_arrows();
    void turn_on(int arrow);
    void turn_off(int arrow);
    
#endif