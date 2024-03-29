#CFLAGS = -ggdb3 -Wall -Wextra

graf: main.o incidence.o randval.o to_file.o from_file.o dijkstra.o bfs.o cohesion.o
	$(CC) -ggdb3 -o graf $^

test: main.o incidence.o randval.o to_file.o from_file.o dijkstra.o bfs.o cohesion.o	
	$(CC) -ggdb3 -o graf $^
	$(CC) -ggdb3 -o test_in_out test_in_out.c
	$(CC) -ggdb3 -o test_kolejka test_kolejka.c bfs.c
	@echo ""
	@echo Test niespojnego grafu
	@echo ""
	./graf --in test_data/bfs_cut
	@echo ""
	@echo Test spojnego grafu
	@echo ""
	./graf --in test_data/bfs_nocut
	@echo ""
	@echo Test bez mozliwego przejscia pomiedzy wezlami
	@echo ""
	./graf --in test_data/dijkstra_nopath
	@echo ""
	@echo Test grafu z mozliwa sciezka miedzy wezlami
	@echo ""
	./graf --in test_data/dijkstra_path
	./test_in_out test_data/compare_bfs1 test_data/compare_bfs2 test_data/compare_dij1 test_data/compare_dij2
	./test_kolejka

test_in_out: test_in_out.o
	$(CC) -ggdb3 -o test_in_out $^
	./test_in_out test_data/compare_bfs1 test_data/compare_bfs2 test_data/compare_dij1 test_data/compare_dij2

test_kolejka: test_kolejka.o bfs.o
	$(CC) -ggdb3 -o test_kolejka $^
	./test_kolejka

test_badformat: main.o incidence.o randval.o to_file.o from_file.o dijkstra.o bfs.o cohesion.o
	$(CC) -ggdb3 -o graf $^
	@echo ""
	@echo Test niepoprawnego formatu pliku wejsciowego
	@echo ""
	./graf --in test_data/wrong_format

test_wrongdimensions: main.o incidence.o randval.o to_file.o from_file.o dijkstra.o bfs.o cohesion.o
	$(CC) -ggdb3 -o graf $^
	@echo ""
	@echo Test niepoprawnych wymiarow grafu w pliku wejsciowego
	@echo ""
	./graf --in test_data/wrong_dimensions

gen150x150: main.o incidence.o randval.o to_file.o from_file.o dijkstra.o bfs.o cohesion.o
	$(CC) -ggdb3 -o graf $^
	./graf -x 150 -y 150 --out 150x150

test_dijkstra: main.o incidence.o randval.o to_file.o from_file.o dijkstra.o bfs.o cohesion.o
	$(CC) -ggdb3 -o graf $^
	./graf --in test_data/dijkstra_nopath
	./graf --in test_data/dijkstra_path

test_bfs: main.o incidence.o randval.o to_file.o from_file.o dijkstra.o bfs.o cohesion.o
	$(CC) -ggdb3 -o graf $^
	./graf --in test_data/bfs_cut
	./graf --in test_data/bfs_nocut
	
.PHONY: clean clean_tests

clean:
	rm -f *.o graf test_in_out test_kolejka test test_badformat test_wrongdimensions gen150x150 test_dijkstra

clean_tests:
	rm -f test*.o test_in_out test_kolejka test test_badformat test_wrongdimensions gen150x150 test_dijkstra
