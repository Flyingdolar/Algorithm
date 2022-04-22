all:
	gcc hw0201.c -o hw0201
	gcc hw0202.c -o hw0202
	gcc hw0203.c -o hw0203
	# gcc hw0204.c -o hw0204

debug:
	gcc -D _DEBUG_ hw0203.c

clear:
	rm hw0201
	rm hw0202
	rm hw0203
	rm hw0204
	rm test
	rm a.out