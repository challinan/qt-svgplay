#ifndef KEYBUTILS
#define KEYBUTILS
#include <termios.h>
#include <QThread>

class KeyHandler : public QThread
{
    Q_OBJECT

public:
    KeyHandler();
    virtual ~KeyHandler();
    virtual void run();

private:
    void reset_terminal_mode(void);
    void set_conio_terminal_mode(void);
    int serial_port_char_avail(int fd);
    int kbhit(void);
    int getch(void);
    int send_char(int fd, int c);

    struct termios orig_termios;

signals:
    void KeyPressed(char ch);
};



#endif // KEYBUTILS

