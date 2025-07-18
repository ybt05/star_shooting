#include "main.h"
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

void title(void) {
    int mode = 1;
    int prev_mode = mode;
    int ch = 0;
    timeout(-1);
    clear();
    draw_box();
    draw_title();
    draw_cursor(mode);
    refresh();
    while (1) {
        ch = getch();
        if ((ch == 'w' || ch == KEY_UP) && mode > 1) {
            mode--;
        } else if ((ch == 's' || ch == KEY_DOWN) && mode < 3) {
            mode++;
        } else if ((ch == 10 || ch == 13)) {
            if (mode == 1) {
                normal_game();
                mode = 1;
                prev_mode = 0;
            } else if (mode == 2) {
                endless_game();
                mode = 1;
                prev_mode = 0;
            } else if (mode == 3) {
                break;
            }
        } else if (ch == 'h') {
            draw_high_score();
        } else if (ch == 'm') {
            if (key_mode == 1) {
                key_mode = 2;
                draw_key_mode();
                draw_title();
                draw_cursor(mode);
                refresh();
            } else {
                key_mode = 1;
                draw_key_mode();
                draw_title();
                draw_cursor(mode);
                refresh();
            }
        }
        if (mode != prev_mode || ch == 410) {
            timeout(-1);
            clear();
            draw_box();
            draw_title();
            draw_cursor(mode);
            refresh();
            prev_mode = mode;
        }
    }
}

void draw_title(void) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            // スターシューター
            if (su[i][j] == 1) {
                for (int dy = 0; dy < 3; dy++) {
                    for (int dx = 0; dx < 10; dx++) {
                        mvaddch(20 + i * 3 + dy, 100 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
                    }
                }
            }
            if (ta[i][j] == 1) {
                for (int dy = 0; dy < 3; dy++) {
                    for (int dx = 0; dx < 10; dx++) {
                        mvaddch(20 + i * 3 + dy, 180 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
                    }
                }
            }
            if (nobasibou[i][j] == 1) {
                for (int dy = 0; dy < 3; dy++) {
                    for (int dx = 0; dx < 10; dx++) {
                        mvaddch(20 + i * 3 + dy, 260 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
                    }
                }
            }
            if (shi[i][j] == 1) {
                for (int dy = 0; dy < 3; dy++) {
                    for (int dx = 0; dx < 10; dx++) {
                        mvaddch(20 + i * 3 + dy, 340 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
                    }
                }
            }
            if (xyu[i][j] == 1) {
                for (int dy = 0; dy < 3; dy++) {
                    for (int dx = 0; dx < 10; dx++) {
                        mvaddch(20 + i * 3 + dy, 420 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
                    }
                }
            }
            if (nobasibou[i][j] == 1) {
                for (int dy = 0; dy < 3; dy++) {
                    for (int dx = 0; dx < 10; dx++) {
                        mvaddch(20 + i * 3 + dy, 500 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
                    }
                }
            }
            if (ta[i][j] == 1) {
                for (int dy = 0; dy < 3; dy++) {
                    for (int dx = 0; dx < 10; dx++) {
                        mvaddch(20 + i * 3 + dy, 580 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
                    }
                }
            }
            if (nobasibou[i][j] == 1) {
                for (int dy = 0; dy < 3; dy++) {
                    for (int dx = 0; dx < 10; dx++) {
                        mvaddch(20 + i * 3 + dy, 640 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
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
    for (int x = 300; x <= 510; x++) {
        for (int y = 86; y <= 96; y++) {
            mvaddch(y, x, ' ' | COLOR_PAIR(WHITE));
        }
    }
    attrset(COLOR_PAIR(BLACK));
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            // ノーマルモード
            if (no[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(52 + i + dy, 310 + j * 3 + dx, ' ');
                    }
                }
            }
            if (nobasibou[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(52 + i + dy, 340 + j * 3 + dx, ' ');
                    }
                }
            }
            if (ma[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(52 + i + dy, 370 + j * 3 + dx, ' ');
                    }
                }
            }
            if (ru[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(52 + i + dy, 400 + j * 3 + dx, ' ');
                    }
                }
            }
            if (mo[i][j] == 1) {
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
            if (doo[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(52 + i + dy, 490 + j * 3 + dx, ' ');
                    }
                }
            }
            // エンドレスモード
            if (ee[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(70 + i + dy, 310 + j * 3 + dx, ' ');
                    }
                }
            }
            if (nn[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(70 + i + dy, 335 + j * 3 + dx, ' ');
                    }
                }
            }
            if (doo[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(70 + i + dy, 360 + j * 3 + dx, ' ');
                    }
                }
            }
            if (re[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(70 + i + dy, 385 + j * 3 + dx, ' ');
                    }
                }
            }
            if (su[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(70 + i + dy, 410 + j * 3 + dx, ' ');
                    }
                }
            }
            if (mo[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(70 + i + dy, 430 + j * 3 + dx, ' ');
                    }
                }
            }
            if (nobasibou[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(70 + i + dy, 460 + j * 3 + dx, ' ');
                    }
                }
            }
            if (doo[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(70 + i + dy, 490 + j * 3 + dx, ' ');
                    }
                }
            }
            // クローズ
            if (ku[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(88 + i + dy, 350 + j * 3 + dx, ' ');
                    }
                }
            }
            if (ro[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(88 + i + dy, 380 + j * 3 + dx, ' ');
                    }
                }
            }
            if (nobasibou[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(88 + i + dy, 410 + j * 3 + dx, ' ');
                    }
                }
            }
            if (su[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(88 + i + dy, 440 + j * 3 + dx, ' ');
                    }
                }
            }
            if (dakuon[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(88 + i + dy, 460 + j * 3 + dx, ' ');
                    }
                }
            }
        }
    }
}

void draw_high_score(void) {
    int data[10];
    read_score(data);
    attrset(COLOR_PAIR(WHITE));
    for (int n = 0; n < 10; n++) {
        int mag = 10000;
        for (int k = 0; k < 5; k++) {
            if (data[n] / mag % 10 == 1) {
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 6; j++) {
                        if (n1[i][j] == 1) {
                            for (int dy = 0; dy < 1; dy++) {
                                for (int dx = 0; dx < 3; dx++) {
                                    mvaddch(10 + i + dy + n * 8, 840 + j * 3 + dx + k * 25, ' ');
                                }
                            }
                        }
                    }
                }
            }
            if (data[n] / mag % 10 == 2) {
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 6; j++) {
                        if (n2[i][j] == 1) {
                            for (int dy = 0; dy < 1; dy++) {
                                for (int dx = 0; dx < 3; dx++) {
                                    mvaddch(10 + i + dy + n * 8, 840 + j * 3 + dx + k * 25, ' ');
                                }
                            }
                        }
                    }
                }
            }
            if (data[n] / mag % 10 == 3) {
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 6; j++) {
                        if (n3[i][j] == 1) {
                            for (int dy = 0; dy < 1; dy++) {
                                for (int dx = 0; dx < 3; dx++) {
                                    mvaddch(10 + i + dy + n * 8, 840 + j * 3 + dx + k * 25, ' ');
                                }
                            }
                        }
                    }
                }
            }
            if (data[n] / mag % 10 == 4) {
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 6; j++) {
                        if (n4[i][j] == 1) {
                            for (int dy = 0; dy < 1; dy++) {
                                for (int dx = 0; dx < 3; dx++) {
                                    mvaddch(10 + i + dy + n * 8, 840 + j * 3 + dx + k * 25, ' ');
                                }
                            }
                        }
                    }
                }
            }
            if (data[n] / mag % 10 == 5) {
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 6; j++) {
                        if (n5[i][j] == 1) {
                            for (int dy = 0; dy < 1; dy++) {
                                for (int dx = 0; dx < 3; dx++) {
                                    mvaddch(10 + i + dy + n * 8, 840 + j * 3 + dx + k * 25, ' ');
                                }
                            }
                        }
                    }
                }
            }
            if (data[n] / mag % 10 == 6) {
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 6; j++) {
                        if (n6[i][j] == 1) {
                            for (int dy = 0; dy < 1; dy++) {
                                for (int dx = 0; dx < 3; dx++) {
                                    mvaddch(10 + i + dy + n * 8, 840 + j * 3 + dx + k * 25, ' ');
                                }
                            }
                        }
                    }
                }
            }
            if (data[n] / mag % 10 == 7) {
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 6; j++) {
                        if (n7[i][j] == 1) {
                            for (int dy = 0; dy < 1; dy++) {
                                for (int dx = 0; dx < 3; dx++) {
                                    mvaddch(10 + i + dy + n * 8, 840 + j * 3 + dx + k * 25, ' ');
                                }
                            }
                        }
                    }
                }
            }
            if (data[n] / mag % 10 == 8) {
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 6; j++) {
                        if (n8[i][j] == 1) {
                            for (int dy = 0; dy < 1; dy++) {
                                for (int dx = 0; dx < 3; dx++) {
                                    mvaddch(10 + i + dy + n * 8, 840 + j * 3 + dx + k * 25, ' ');
                                }
                            }
                        }
                    }
                }
            }
            if (data[n] / mag % 10 == 9) {
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 6; j++) {
                        if (n9[i][j] == 1) {
                            for (int dy = 0; dy < 1; dy++) {
                                for (int dx = 0; dx < 3; dx++) {
                                    mvaddch(10 + i + dy + n * 8, 840 + j * 3 + dx + k * 25, ' ');
                                }
                            }
                        }
                    }
                }
            }
            if (data[n] / mag % 10 == 0) {
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 6; j++) {
                        if (n0[i][j] == 1) {
                            for (int dy = 0; dy < 1; dy++) {
                                for (int dx = 0; dx < 3; dx++) {
                                    mvaddch(10 + i + dy + n * 8, 840 + j * 3 + dx + k * 25, ' ');
                                }
                            }
                        }
                    }
                }
            }
            mag /= 10;
        }
    }
}

void draw_key_mode(void) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            for (int dy = 0; dy < 3; dy++) {
                for (int dx = 0; dx < 10; dx++) {
                    mvaddch(80 + i * 3 + dy, 700 + j * 10 + dx, ' ' | COLOR_PAIR(BLACK));
                }
            }
        }
    }
    if (key_mode == 1) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 6; j++) {
                if (AA[i][j] == 1) {
                    for (int dy = 0; dy < 3; dy++) {
                        for (int dx = 0; dx < 10; dx++) {
                            mvaddch(80 + i * 3 + dy, 700 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
                        }
                    }
                }
            }
        }
    }
    if (key_mode == 2) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 6; j++) {
                if (BB[i][j] == 1) {
                    for (int dy = 0; dy < 3; dy++) {
                        for (int dx = 0; dx < 10; dx++) {
                            mvaddch(80 + i * 3 + dy, 700 + j * 10 + dx, ' ' | COLOR_PAIR(WHITE));
                        }
                    }
                }
            }
        }
    }
}
