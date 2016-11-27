#include <stdio.h>

#ifdef TARGET_OS_MAC
#include <terms.h>
#elif __linux__
#include <termio.h>
#endif

int getch(void)
{
	int ch;
	struct termios buf, save;

	tcgetattr(0, &save);
	buf = save;
	buf.c_lflag &= ~(ICANON|ECHO);
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &buf);
	ch = getchar();
	tcsetattr(0, TCSAFLUSH, &save);
	return ch;
}

