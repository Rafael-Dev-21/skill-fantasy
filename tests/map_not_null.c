#include <map.h>

int main(void)
{
	struct tile **map = create_map();

	if (map == NULL) {
		return -1;
	} else {
		free_map(map);
		return 0;
	}
}
