#include "keyb-utils.h"
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <QDebug>
#include <QKeyEvent>

#define DEBUG_TERMINAL_DEV "/dev/ttys000"
#define DEBUG 1
#if 0
KeyHandler::KeyHandler()
{
    qDebug("KeyHandler started - Opening terminal device%s", DEBUG_TERMINAL_DEV);
    fd = open(DEBUG_TERMINAL_DEV, O_RDWR);
    if ( fd == -1 ) {
        perror(DEBUG_TERMINAL_DEV " Error opening serial port\n");
        QThread::exit(7);
    }
    qDebug("Port opened successfully on %d", fd);
    fp = fdopen(fd, "rw");
    if ( fp == nullptr )
        qDebug("Failed to associate fd with fp");
    set_conio_terminal_mode();
    // qDebug() << "Types:" << QString("String") << QChar('x');
    cycle_count = 0;
}

KeyHandler::~KeyHandler()
{
    qDebug("Closing - resetting terminal mode");
    reset_terminal_mode();
    close(fd);
}

void KeyHandler::reset_terminal_mode()
{
    qDebug("Closing - in function - resetting terminal mode");
    tcsetattr(0, TCSANOW, &orig_termios);
}

void KeyHandler::set_conio_terminal_mode()
{
    int rc;
    struct termios new_termios;
    qDebug() << "set_conio_terminal_mode(): setting mode";

    /* take two copies - one for now, one for later */
    rc = tcgetattr(fd, &orig_termios);
    if ( rc != 0 ) {
        rc = errno;
        perror("tcgetattr() failed");
        qDebug() << "set_conio_terminal_mode(): " << errno;
    }
    memcpy(static_cast<void *>(&new_termios), static_cast<void *>(&orig_termios), static_cast<size_t> (sizeof(new_termios)));

    cfmakeraw(&new_termios);
    tcsetattr(fd, TCSANOW, &new_termios);
}

int KeyHandler::serial_port_char_avail(int fd) {
    struct timeval tv = { 0L, 25000L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(fd, &fds);
    return select(fd+1, &fds, nullptr, nullptr, &tv);
}

int KeyHandler::kbhit()
{
    // Check stdin for key available
    int rc;
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(fd, &fds);
    rc = select(fd+1, &fds, nullptr, nullptr, &tv);
    if ( rc == -1 )
        qDebug("select failed ************%d", rc);
    if ( rc != 0 )
        qDebug("select found %d fds ready: ", rc);
    return rc;
}

int KeyHandler::getch()
{
    int rc;
    char c;
    qDebug("getch Entered - we have a key - cycle count = %d", cycle_count);
    rc =  static_cast<int>(read(fd, static_cast<void *>(&c), sizeof(c)));
    cycle_count++;

    if ( rc < 0 ) {
        qDebug("Error reading detected character %d", rc);
        return rc;
    } else {
        qDebug("Emit KeyPressed - rc = %d, character = %c", rc, c);
        emit KeyPressed(c);
        return c;
    }
}

void KeyHandler::run()
{
    char c;
    qDebug("KeyHandler worker thread entered");
    while ( 1 ) {
        fflush(fp);
        if ( kbhit() ) {
             c = static_cast<char>(getch());
            switch(c) {
            case 'Q':
                QThread::exit(0);
                break;
            default:
                break;
            }
        }
    }
}
#endif

#if 0

int main_loop(int argc, char **argv) {

    char buf[512];
    int fd, rc, c;
    int start_timeout = 0, timeout = 0;
    speed_t baud = B1200; /* baud rate */
    struct termios settings;

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
