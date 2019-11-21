CFLAGS = -g -std=c99 -Wall -Werror -I ./include
LIB= -lSDL
LIB2= -lSDL2
.PHONY: clean doc

doc:
	doxygen conf/doxygen.conf

%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^ $(LIB)

read-file: read-file.o
	$(CC) $(CFLAGS) -o bin/$@ $^

write-fact: write-fact.o
	$(CC) $(CFLAGS) -o bin/$@ $^

conway-naive: conway-naive.o
	$(CC) $(CFLAGS) -o bin/$@ $^

app-test-cell: app_test_cell.o cell.o evolution.o load.o generate-image.o gui.o
	$(CC) $(CFLAGS)  -o bin/$@ $^ $(LIB)

launch-conway-naive: conway-naive
	./conway-naive

generate-animation:
	convert -delay 10 -loop 0 out/*.ppm out/animation.gif

app-conway:app-conway.o cell.o evolution.o load.o generate-image.o
	$(CC) $(CFLAGS) -o bin/$@ $^

app-rt-animation:app_rt_animation.o evolution.o cell.o load.o gui.o
	$(CC) $(CFLAGS) -o bin/$@ $^ $(LIB)

app-rt-animation2:app_rt_animation2.o evolution.o cell.o load.o gui2.o
	$(CC) $(CFLAGS) -o bin/$@ $^ $(LIB2)

add-files-svn:
	svn add --force src/*.c include/*.h data/*.txt --auto-props --parents --depth infinity -q

gif:
	convert -delay 10 -resize 400% -loop 0 out/*.ppm out/animation.gif
	rm -f out/*.ppm

clean:
	rm -f *.o read-file conway-naive write-fact app-test-cell
