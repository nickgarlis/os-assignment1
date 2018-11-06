#include <sys/types.h>
#include "next_i.h"

off_t next_num (off_t i) {
	if ((i%2) == 0) {
		return i/2;
	}
	return (3*i) + 1;
}