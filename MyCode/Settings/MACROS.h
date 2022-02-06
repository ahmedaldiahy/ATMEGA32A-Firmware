/*
 * MACROS.h
 *
 * Created: 11/17/2021 3:18:54 PM
 *  Author: ahmed
 */ 


#ifndef MACROS_H_
#define MACROS_H_

#define SETBIT(R,B) ((R)|=(1<<(B)))
#define CLEARBIT(R,B) ((R)&=~(1<<(B)))
#define TOGGLEBIT(R,B) ((R)^=(1<<(B)))

#define ISBITSET(R,B) (((R)>>(B))&1)
#define ISBITCLEAR(R,B) !ISBITSET(R,B)



#endif /* MACROS_H_ */