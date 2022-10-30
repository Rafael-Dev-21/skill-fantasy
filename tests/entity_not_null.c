#include <entity.h>
#include <colors.h>

int main(void)
{
	struct position pos = { 0, 0 };
	struct entity *entity = create_entity(pos, 'T', SKPAIR_PLAYER);

	if (entity == NULL) {
		return -1;
	} else {
		free_entity(entity);
		return 0;
	}
}
