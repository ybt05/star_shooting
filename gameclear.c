#include "main.h"
#include <ncurses.h>
#include <unistd.h>

void gameclear(void) {
    int mode = 1;
    int ch = 0;
    clear();
    draw_box();
    draw_gameclear();
    draw_cursor(mode);
    draw_score();
    refresh();
    timeout(-1);
    save_score();
    while (1) {
        ch = getch();
        if ((ch == 10 || ch == 13) && mode == 1) {
            break;
        }
    }
}

void draw_gameclear(void) {
    for (int x = 100; x <= 720; x++) {
        for (int y = 20; y <= 95; y++) {
            mvaddch(y, x, ' ' | COLOR_PAIR(DARKBLUE));
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            // ゲームクリア
            if (ke[i][j] == 1) {
                for (int dy = 0; dy < 3; dy++) {
                    for (int dx = 0; dx < 10; dx++) {
                        mvaddch(23 + i * 3 + dy, 150 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
                    }
                }
            }
            if (dakuon[i][j] == 1) {
                for (int dy = 0; dy < 3; dy++) {
                    for (int dx = 0; dx < 10; dx++) {
                        mvaddch(23 + i * 3 + dy, 210 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
                    }
                }
            }
            if (nobasibou[i][j] == 1) {
                for (int dy = 0; dy < 3; dy++) {
                    for (int dx = 0; dx < 10; dx++) {
                        mvaddch(23 + i * 3 + dy, 240 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
                    }
                }
            }
            if (mu[i][j] == 1) {
                for (int dy = 0; dy < 3; dy++) {
                    for (int dx = 0; dx < 10; dx++) {
                        mvaddch(23 + i * 3 + dy, 320 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
                    }
                }
            }
            if (ku[i][j] == 1) {
                for (int dy = 0; dy < 3; dy++) {
                    for (int dx = 0; dx < 10; dx++) {
                        mvaddch(23 + i * 3 + dy, 410 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
                    }
                }
            }
            if (ri[i][j] == 1) {
                for (int dy = 0; dy < 3; dy++) {
                    for (int dx = 0; dx < 10; dx++) {
                        mvaddch(23 + i * 3 + dy, 480 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
                    }
                }
            }
            if (aa[i][j] == 1) {
                for (int dy = 0; dy < 3; dy++) {
                    for (int dx = 0; dx < 10; dx++) {
                        mvaddch(23 + i * 3 + dy, 560 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
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
    attrset(COLOR_PAIR(BLACK));
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            // タイトル
            if (ta[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(52 + i + dy, 350 + j * 3 + dx, ' ');
                    }
                }
            }
            if (ii[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(52 + i + dy, 380 + j * 3 + dx, ' ');
                    }
                }
            }
            if (to[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(52 + i + dy, 410 + j * 3 + dx, ' ');
                    }
                }
            }
            if (ru[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(52 + i + dy, 440 + j * 3 + dx, ' ');
                    }
                }
            }
            // スコア
            if (su[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(70 + i + dy, 310 + j * 3 + dx, ' ');
                    }
                }
            }
            if (ko[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(70 + i + dy, 335 + j * 3 + dx, ' ');
                    }
                }
            }
            if (aa[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(70 + i + dy, 360 + j * 3 + dx, ' ');
                    }
                }
            }
        }
    }
}
