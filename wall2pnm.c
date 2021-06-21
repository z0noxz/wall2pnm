#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

static void
die(const char *errstr, ...)
{
	va_list ap;

	va_start(ap, errstr);
	vfprintf(stderr, errstr, ap);
	va_end(ap);
	exit(1);
}

static Pixmap
getrootpixmap(Display* display, Window *root)
{
	Pixmap pixmap = 0;
	Atom act_type;
	int act_format;
	unsigned long nitems, bytes_after;
	unsigned char *data = NULL;
	Atom _XROOTPMAP_ID = XInternAtom(display, "_XROOTPMAP_ID", False);

	if (XGetWindowProperty(display, *root, _XROOTPMAP_ID, 0, 1, False, XA_PIXMAP, &act_type, &act_format, &nitems, &bytes_after, &data) == Success && data) {
		pixmap = *((Pixmap *) data);
		XFree(data);
	}

	return pixmap;
}

static void
writepnm(XImage *img, FILE *outfile)
{
	int x, y;
	long pixel;

	fprintf(outfile, "P6\n%d %d\n255\n", img->width, img->height);
	for (y = 0; y < img->height; y++) {
		for (x = 0; x < img->width && (pixel = XGetPixel(img, x, y)); x++)
			fprintf(outfile, "%c%c%c",
				(char)(pixel>>16),
				(char)((pixel&0x00ff00)>>8),
				(char)(pixel&0x0000ff));
	}
}

int
main(int argc, const char *argv[])
{
	FILE *outfile;
	Window root;
	Display *display;
	XWindowAttributes wa;
	Pixmap bg;
	XImage *img = NULL;

	if (argc < 2)
		die("Usage: %s [filename]\n", argv[0]);

	if (!(display = XOpenDisplay(getenv("DISPLAY"))))
		die("Cannot connect to X Server %s\n", getenv("DISPLAY") ? getenv("DISPLAY") : "(default)");

	root = RootWindow(display, DefaultScreen(display));
	XGetWindowAttributes(display, root, &wa);

	if ((bg = getrootpixmap(display, &root))) {
		img = XGetImage(display, bg, 0, 0, wa.width, wa.height, ~0, ZPixmap);
		XFreePixmap(display, bg);
	}

	if (!img)
		die("Cannot create XImage\n");

	if (!(outfile = fopen(argv[1], "wb")))
		die("Cannot open output file %s", argv[1]);

	writepnm(img, outfile);
	XDestroyImage(img);
	fclose(outfile);

	return 0;
}
