CLIBS= 		-lm -lglut -lGL -lGLU -lX11 -lGLEW # 2016
CPATHS=		-I/usr/include -L/usr/lib # 2016
CFLAGS=		$(CPATHS)$(CLIBS)

P4:		P4.cpp
		g++ P4.cpp -o P4 $(CFLAGS)
bird:		bird.cpp
		g++ bird.cpp -o bird $(CFLAGS)
xliuG4:		xliuG4.cpp
		g++ xliuG4.cpp -o xliuG4 $(CFLAGS)
xliuG41:	xliuG41.cpp
		g++ xliuG41.cpp -o xliuG41 $(CFLAGS)


clean:
		rm *.o
