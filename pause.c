#include "main.h"
#include <ncurses.h>
#include <unistd.h>

int my_pause(void) {
    int mode = 1;
    int prev_mode = mode;
    int ch = 0;
    timeout(-1);
    clear();
    draw_box();
    draw_pause();
    draw_cursor(mode);
    refresh();
    while (1) {
        ch = getch();
        if ((ch == 'w' || ch == KEY_UP) && mode > 1) {
            mode--;
        } else if ((ch == 's' || ch == KEY_DOWN) && mode < 2) {
            mode++;
        } else if ((ch == 10 || ch == 13) && mode == 1) {
            return 0;
        } else if ((ch == 10 || ch == 13) && mode == 2) {
            return 1;
        }
        if (mode != prev_mode) {
            clear();
            draw_box();
            draw_pause();
            draw_cursor(mode);
            refresh();
            prev_mode = mode;
        }
    }
}

void draw_pause(void) {
    for (int x = 100; x <= 720; x++) {
        for (int y = 20; y <= 95; y++) {
            mvaddch(y, x, ' ' | COLOR_PAIR(DARKBLUE));
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            // ポーズ
            if (ho[i][j] == 1) {
                for (int dy = 0; dy < 3; dy++) {
                    for (int dx = 0; dx < 10; dx++) {
                        mvaddch(23 + i * 3 + dy, 270 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
                    }
                }
            }
            if (handakuon[i][j] == 1) {
                for (int dy = 0; dy < 3; dy++) {
                    for (int dx = 0; dx < 10; dx++) {
                        mvaddch(22 + i * 3 + dy, 330 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
                    }
                }
            }
            if (nobasibou[i][j] == 1) {
                for (int dy = 0; dy < 3; dy++) {
                    for (int dx = 0; dx < 10; dx++) {
                        mvaddch(23 + i * 3 + dy, 380 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
                    }
                }
            }
            if (su[i][j] == 1) {
                for (int dy = 0; dy < 3; dy++) {
                    for (int dx = 0; dx < 10; dx++) {
                        mvaddch(23 + i * 3 + dy, 470 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
                    }
                }
            }
            if (dakuon[i][j] == 1) {
                for (int dy = 0; dy < 3; dy++) {
                    for (int dx = 0; dx < 10; dx++) {
                        mvaddch(23 + i * 3 + dy, 530 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
                    }
                }
            }
        }
    }
    for (int x = 300; x <= 510; x++) {
        for (int y = 50; y <= 60; y++) {
            mvaddch(y, x, ' ' | COLOR_PAIR(WHITE));
        }
    }
    for (int x = 300; x <= 510; x++) {
        for (int y = 68; y <= 78; y++) {
            mvaddch(y, x, ' ' | COLOR_PAIR(WHITE));
        }
    }
    attrset(COLOR_PAIR(BLACK));
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            // コンテニュー
            if (ko[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(52 + i + dy, 310 + j * 3 + dx, ' ');
                    }
                }
            }
            if (nn[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(52 + i + dy, 340 + j * 3 + dx, ' ');
                    }
                }
            }
            if (te[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(52 + i + dy, 370 + j * 3 + dx, ' ');
                    }
                }
            }
            if (ni[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(52 + i + dy, 400 + j * 3 + dx, ' ');
                    }
                }
            }
            if (xyu[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(52 + i + dy, 430 + j * 3 + dx, ' ');
                    }
                }
            }
            if (nobasibou[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(52 + i + dy, 460 + j * 3 + dx, ' ');
                    }
                }
            }
            // リタイア
            if (ri[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(70 + i + dy, 340 + j * 3 + dx, ' ');
                    }
                }
            }
            if (ta[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(70 + i + dy, 370 + j * 3 + dx, ' ');
                    }
                }
            }
            if (ii[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(70 + i + dy, 400 + j * 3 + dx, ' ');
                    }
                }
            }
            if (aa[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(70 + i + dy, 430 + j * 3 + dx, ' ');
                    }
                }
            }
        }
    }
}