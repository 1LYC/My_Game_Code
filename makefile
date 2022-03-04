mybin:test.c main.c
		@gcc $^ -o $@ -g

.PHONY:clean
clean:
		@rm -f mybin
