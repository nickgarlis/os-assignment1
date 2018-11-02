#include "next_i.h"

int next_num(int i){
	if((i%2) == 0){
		return i/2;
	}
	return (3*i) + 1;
}
