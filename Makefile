COMMON_FLAGS = -DRHR_FINAL_CONSONANTS_PRECEDENCE -DEFINE_DEF=static -pedantic-errors -Werror=implicit-function-declaration -Werror=vla -Wall -Wextra -Wpedantic -Wshadow

rr: main.c efine_helpers.h efine_fsync.h efine_portability_base.h
	$(CC) $(COMMON_FLAGS) -DNDEBUG -fstrict-aliasing -Os -Wstrict-aliasing -Wno-unused-function -Wno-unused-parameter -Wno-unused-label -Wno-parentheses -o $@ main.c

rr_test: main.c efine_helpers.h efine_fsync.h efine_portability_base.h
	$(CC) $(COMMON_FLAGS) -fsanitize=address,undefined -g -fno-strict-aliasing -o $@ main.c
