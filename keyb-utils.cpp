#include "keyb-utils.h"
#include <sys/select.h>
#include <unistd.h>
#include <errno.h>
#include <QDebug>
#if 0
#include <QString>
#endif

#define DEBUG_TERMINAL_DEV "/dev/ttys000"
#define DEBUG 1

KeyHandler::KeyHandler()
{
    qDebug("KeyHandler started");
    set_conio_terminal_mode();
    qDebug() << "Types:" << QString("String") << QChar('x');
}

KeyHandler::~KeyHandler()
{
    qDebug("Closing - resetting terminal mode");
    reset_terminal_mode();
}

void KeyHandler::reset_terminal_mode()
{
    qDebug("Closing - in function 'resetting terminal mode'");
    tcsetattr(0, TCSANOW, &orig_termios);
}

void KeyHandler::set_conio_terminal_mode()
{
    int rc;
    struct termios new_termios;
    qDebug() << "set_conio_terminal_mode(): setting mode";

    /* take two copies - one for now, one for later */
    rc = tcgetattr(0, &orig_termios);
    if ( rc != 0 ) {
        rc = errno;
        perror("tcgetattr() failed");
        qDebug() << "set_conio_terminal_mode(): " << errno;
    }
    memcpy((void *)&new_termios, (void *)&orig_termios, (size_t) sizeof(new_termios));

    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

int KeyHandler::serial_port_char_avail(int fd) {
    struct timeval tv = { 0L, 25000L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(fd, &fds);
    return select(fd+1, &fds, NULL, NULL, &tv);
}

int KeyHandler::kbhit()
{
    // Check stdin for key available
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

int KeyHandler::getch()
{
    int r;
    unsigned char c;
    if ((r = (int) read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}

void KeyHandler::run()
{
    char c;
    while ( 1 ) {
        if ( kbhit() ) {
            c = getch();
            switch(c) {
            case 'Q':
                break;
            default:
                break;
            }
        }
    }
}

#if 0

int main_loop(int argc, char **argv) {

    char buf[512];
    int fd, rc, c;
    int start_timeout = 0, timeout = 0;
    speed_t baud = B1200; /* baud rate */
    struct termios settings;

    qDebug("Opening terminal device\n");
    fd = open(DEBUG_TERMINAL_DEV, O_RDWR);
    if ( fd == -1 ) {
        perror("Error opening serial port\n");
        exit(1);
    }
    qDebug("USB Serial port opened successfully on %d\n\r", fd);

    /* set the other settings (in this case, baud, 1200/8N2) */
    tcgetattr(fd, &settings);
    settings.c_cflag = 0;
    settings.c_cflag = CSTOPB | CS8 | CREAD | CLOCAL;
    cfmakeraw(&settings);
    cfsetspeed(&settings, baud);

    /* Now enable the settings */
    rc = tcsetattr(fd, TCSANOW, &settings);
    if ( rc == -1 ) {
        close(fd);
        printf("main: tcsetattr returned %d\n", rc);
        perror("main: tcsetattr failed\n");
    }

    printf("Current input baud rate is %d\n", (int) cfgetispeed(&settings));
    printf("Current output baud rate is %d\n", (int) cfgetospeed(&settings));

    qDebug("USB Serial port closed\n\r");
    close(fd);

    return 0;
}
#endif
