//  Poker_Hand
#include <stdio.h>
#include <stdlib.h>
#define NUMBER_CARDS 5
#define NUMBER_PLAYERS 4
typedef struct{
    struct CARDS{
        int rank;
        int suit;
    }cards[NUMBER_CARDS];
    int category;
    int rank_moment;
    int suit_moment;
    char Player;
}PH;
PH ph[NUMBER_PLAYERS];
void read_cards(void);
void test_category(void);
int cmp(const void*, const void*);
int final_cmp(const void*, const void*);
int main(void){
    read_cards();
    
//    for(int i=0;i<NUMBER_PLAYERS;i++){
//        for(int j=0;j<NUMBER_CARDS;j++){
//            printf("%2d %d, ",ph[i].cards[j].rank,ph[i].cards[j].suit);
//        }
//        printf(" %d",ph[i].category);
//        printf(" %2d %d/",ph[i].rank_moment,ph[i].suit_moment);
//        printf(" %c",ph[i].Player);
//        printf("\n");
//    }
//
//    printf("////////////////////////////////////////////////\n");
    
    for(int i=0;i<NUMBER_PLAYERS;i++)
        qsort(ph[i].cards,NUMBER_CARDS,sizeof(ph[0].cards[0]),cmp);
    
    test_category();
    
//    for(int i=0;i<NUMBER_PLAYERS;i++){
//        for(int j=0;j<NUMBER_CARDS;j++){
//            printf("%2d %d, ",ph[i].cards[j].rank,ph[i].cards[j].suit);
//        }
//        printf(" %d",ph[i].category);
//        printf(" %2d %d/",ph[i].rank_moment,ph[i].suit_moment);
//        printf(" %c",ph[i].Player);
//        printf("\n");
//    }
//
//    printf("////////////////////////////////////////////////\n");
    
    qsort(ph,NUMBER_PLAYERS,sizeof(ph[0]),final_cmp);
    
//    for(int i=0;i<NUMBER_PLAYERS;i++){
//        for(int j=0;j<NUMBER_CARDS;j++){
//            printf("%2d %d, ",ph[i].cards[j].rank,ph[i].cards[j].suit);
//        }
//        printf(" %d",ph[i].category);
//        printf(" %2d %d/",ph[i].rank_moment,ph[i].suit_moment);
//        printf(" %c",ph[i].Player);
//        printf("\n");
//    }
    printf("%c",ph[0].Player);
    for(int i=1;i<NUMBER_PLAYERS;i++){
        printf(" %c",ph[i].Player);
    }
    printf("\n");
    return 0;
}
int final_cmp(const void* pa, const void* pb){
    int category_a = ((PH *)pa)->category, category_b = ((PH *)pb)->category;
    if(category_a != category_b) return category_b - category_a;
    else{
        int rank_a = ((PH *)pa)->rank_moment, rank_b = ((PH *)pb)->rank_moment;
        if(rank_a != rank_b) return rank_b - rank_a;
        else{
            int suit_a = ((PH *)pa)->suit_moment, suit_b = ((PH *)pb)->suit_moment;
            return suit_b - suit_a;
        }
    }
}
void test_category(void){
    int flag_straight, flag_flush;
    for(int i=0;i<NUMBER_PLAYERS;i++){
        //straight flush or straight
        flag_straight = 0;
        for(int j=1;j<NUMBER_CARDS;j++){
            if(ph[i].cards[j].rank != ph[i].cards[0].rank + j){
                flag_straight = 1;
                break;
            }
        }
        if(!flag_straight){
            flag_flush = 0;
            for(int j=1;j<NUMBER_CARDS;j++){
                if(ph[i].cards[0].suit != ph[i].cards[j].suit){
                    flag_flush = 1;
                    break;
                }
            }
            if(!flag_flush){
                ph[i].rank_moment = ph[i].cards[4].rank;
                ph[i].suit_moment = ph[i].cards[4].suit;
                ph[i].category = 8;
                continue;
            }else{
                ph[i].rank_moment = ph[i].cards[4].rank;
                ph[i].suit_moment = ph[i].cards[4].suit;
                ph[i].category = 4;
                continue;
            }
        }
        //four-of-a-kind
        if(ph[i].cards[0].rank == ph[i].cards[3].rank){
            ph[i].rank_moment = ph[i].cards[3].rank;
            ph[i].suit_moment = ph[i].cards[3].suit;
            ph[i].category = 7;
            continue;
        }else if(ph[i].cards[1].rank == ph[i].cards[4].rank){
            ph[i].rank_moment = ph[i].cards[4].rank;
            ph[i].suit_moment = ph[i].cards[4].suit;
            ph[i].category = 7;
            continue;
        }
        //full house
        if(ph[i].cards[0].rank == ph[i].cards[1].rank && ph[i].cards[2].rank == ph[i].cards[4].rank){
            ph[i].rank_moment = ph[i].cards[4].rank;
            ph[i].suit_moment = ph[i].cards[4].suit;
            ph[i].category = 6;
            continue;
        }else if(ph[i].cards[0].rank == ph[i].cards[2].rank && ph[i].cards[3].rank == ph[i].cards[4].rank){
            ph[i].rank_moment = ph[i].cards[2].rank;
            ph[i].suit_moment = ph[i].cards[2].suit;
            ph[i].category = 6;
            continue;
        }
        //flush
        flag_flush = 0;
        for(int j=1;j<NUMBER_CARDS;j++){
            if(ph[i].cards[0].suit != ph[i].cards[j].suit){
                flag_flush = 1;
                break;
            }
        }
        if(!flag_flush){
            ph[i].rank_moment = ph[i].cards[4].rank;
            ph[i].suit_moment = ph[i].cards[4].suit;
            ph[i].category = 5;
            continue;
        }
        //three-of-a-kind
        if(ph[i].cards[0].rank == ph[i].cards[2].rank){
            ph[i].rank_moment = ph[i].cards[2].rank;
            ph[i].suit_moment = ph[i].cards[2].suit;
            ph[i].category = 3;
            continue;
        }else if(ph[i].cards[1].rank == ph[i].cards[3].rank){
            ph[i].rank_moment = ph[i].cards[3].rank;
            ph[i].suit_moment = ph[i].cards[3].suit;
            ph[i].category = 3;
            continue;
        }else if(ph[i].cards[2].rank == ph[i].cards[4].rank){
            ph[i].rank_moment = ph[i].cards[4].rank;
            ph[i].suit_moment = ph[i].cards[4].suit;
            ph[i].category = 3;
            continue;
        }
        //two_pair, pair or high card
        if(ph[i].cards[0].rank == ph[i].cards[1].rank){
            if(ph[i].cards[2].rank == ph[i].cards[3].rank){
                ph[i].rank_moment = ph[i].cards[3].rank;
                ph[i].suit_moment = ph[i].cards[3].suit;
                ph[i].category = 2;
                continue;
            }else if(ph[i].cards[3].rank == ph[i].cards[4].rank){
                ph[i].rank_moment = ph[i].cards[4].rank;
                ph[i].suit_moment = ph[i].cards[4].suit;
                ph[i].category = 2;
                continue;
            }else{
                ph[i].rank_moment = ph[i].cards[1].rank;
                ph[i].suit_moment = ph[i].cards[1].suit;
                ph[i].category = 1;
                continue;
            }
        }else if(ph[i].cards[1].rank == ph[i].cards[2].rank){
            if(ph[i].cards[3].rank == ph[i].cards[4].rank){
                ph[i].rank_moment = ph[i].cards[4].rank;
                ph[i].suit_moment = ph[i].cards[4].suit;
                ph[i].category = 2;
                continue;
            }else{
                ph[i].rank_moment = ph[i].cards[2].rank;
                ph[i].suit_moment = ph[i].cards[2].suit;
                ph[i].category = 1;
                continue;
            }
        }else if(ph[i].cards[2].rank == ph[i].cards[3].rank){
            ph[i].rank_moment = ph[i].cards[3].rank;
            ph[i].suit_moment = ph[i].cards[3].suit;
            ph[i].category = 1;
            continue;
        }else if(ph[i].cards[3].rank == ph[i].cards[4].rank){
            ph[i].rank_moment = ph[i].cards[4].rank;
            ph[i].suit_moment = ph[i].cards[4].suit;
            ph[i].category = 1;
            continue;
        }else{
            ph[i].rank_moment = ph[i].cards[4].rank;
            ph[i].suit_moment = ph[i].cards[4].suit;
            ph[i].category = 0;
            continue;
        }
    }
}
int cmp(const void* pa, const void* pb){
    int rank_a = ((struct CARDS*)pa)->rank, rank_b = ((struct CARDS*)pb)->rank;
    
    if(rank_a != rank_b) return rank_a - rank_b;
    else{
        int suit_a = ((struct CARDS*)pa)->suit, suit_b = ((struct CARDS*)pb)->suit;
        return suit_a - suit_b;
    }
}
void read_cards(void){
    for(int i=0;i<NUMBER_PLAYERS;i++){
        ph[i].Player = 'A' + i;
        for(int j=0;j<NUMBER_CARDS;j++){
            char rank, suit;
            scanf("%c%c",&rank,&suit);
            getchar();
            
            switch (rank){
                case 't':
                    ph[i].cards[j].rank = 8;
                    break;
                case 'j':
                    ph[i].cards[j].rank = 9;
                    break;
                case 'q':
                    ph[i].cards[j].rank = 10;
                    break;
                case 'k':
                    ph[i].cards[j].rank = 11;
                    break;
                case 'a':
                    ph[i].cards[j].rank = 12;
                    break;
                default:
                    ph[i].cards[j].rank = rank - '2';
            }
            switch (suit){
                case 'c':
                    ph[i].cards[j].suit = 0;
                    break;
                case 'd':
                    ph[i].cards[j].suit = 1;
                    break;
                case 'h':
                    ph[i].cards[j].suit = 2;
                    break;
                default:
                    ph[i].cards[j].suit = 3;
            }
        }
    }
}
/*
 Ranks: 2 3 4 5 6 7 8 9 t j q k a
 Suits: c d h s
 Category:
 1.straight flush
 2.four-of-a-kind
 3.full house
 4.flush
 5.straight
 6.three-of-a-kind
 7.two pairs
 8.pair
 9.high card
 
 Note:aces are highest rank.
 */

/*
 for(int i=0;i<NUMBER_PLAYERS;i++){
     for(int j=0;j<NUMBER_CARDS;j++){
         printf("%2d %d/",ph[i].cards[j].rank,ph[i].cards[j].suit);
     }
     printf(" %d",ph[i].category);
     printf(" %2d %d/",ph[i].rank_moment,ph[i].suit_moment);
     printf(" %c",ph[i].Player);
     printf("\n");
 }
 */