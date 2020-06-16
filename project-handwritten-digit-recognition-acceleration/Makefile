.SILENT:

include C:/AndroXStudio/Tools/make_comm

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(EXEC_LDFLAGS) -save-temps -O2 -fPIE -pie -mfloat-abi=softfp -mfpu=neon -o main $(OBJECTS) \
$(LLIB)/libgcc.a

	echo
	echo "**** Install:" /data/local/tmp/main "****"
	$(ADB) push main /data/local/tmp
	$(ADB) push small.network /data/local/tmp
	$(ADB) push result.out /data/local/tmp
	$(ADB) push MNIST_image.bin /data/local/tmp
	$(ADB) push MNIST_label.bin /data/local/tmp
	$(ADB) shell chmod 755 /data/local/tmp/main
	
clean:
	rm -f *.o
	rm -f *.i
	rm -f *.s
	rm -f main