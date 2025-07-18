#include "main.h"
#include <ncurses.h>
#include <unistd.h>

int star[7][13] = {
    {0, 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 6, 6, 6, 6, 6, 0, 0, 0, 0},
    {0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0},
    {0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0},
    {0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0},
    {0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0},
    {0, 0, 6, 6, 6, 0, 0, 0, 6, 6, 6, 0, 0}
};

void bullet_init(Bullet bullet[]) {
    for (int i = 0; i < BULLET_NUM; i++) {
        bullet[i].exist = 0;
    }
}

void bullet_process(int count, Bullet bullet[], int ch) {
    if (count % player.interval == 0) {
        pl_shoot(bullet);
    }
    player.count++;
    if (ch == 32 && player.count > (player.interval * 3)) {
        pl_sp_shoot(bullet);
        player.count = 0;
    }
    if (player.count > 10000) {
        player.count = 100;
    }
    en_shoot(bullet);
    move_pl_bullet(bullet);
    move_en_bullet(bullet);
    break_bullet(bullet);
}

void break_bullet(Bullet bullet[]) {
    for (int i = 0; i < BULLET_NUM; i++) {
        if (bullet[i].x > 810 || bullet[i].x < 10 || bullet[i].y < 5 || bullet[i].y > 98) {
            bullet[i].exist = 0;
        }
    }
}

void draw_bullet(Bullet bullet[]) {
    for (int i = 0; i < BULLET_NUM; i++) {
        if (bullet[i].exist == 1 && bullet[i].sp == 0 && bullet[i].dir == 1) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(bullet[i].y + j, bullet[i].x + k * 3 + dx, ' ' | COLOR_PAIR(LIGHTBLUE));
                    }
                }
            }
        }
        if (bullet[i].exist == 1 && bullet[i].sp == 0 && bullet[i].dir == 2) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(bullet[i].y + j, bullet[i].x + k * 3 + dx, ' ' | COLOR_PAIR(PINK));
                    }
                }
            }
        }
        if (bullet[i].exist == 1 && bullet[i].sp == 1 && bullet[i].dir != 2) {
            for (int k = 0; k < 7; k++) {
                for (int j = 0; j < 13; j++) {
                    if (star[k][j] == 6) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(bullet[i].y + k * 1 + dy, bullet[i].x + j * 3 + dx, ' ' | COLOR_PAIR(YELLOW));
                            }
                        }
                    }
                }
            }
        }
        if (bullet[i].exist == 1 && bullet[i].sp == 1 && bullet[i].dir == 2) {
            for (int k = 0; k < 7; k++) {
                for (int j = 0; j < 13; j++) {
                    if (star[k][j] == 6) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(bullet[i].y + k * 1 + dy, bullet[i].x + j * 3 + dx, ' ' | COLOR_PAIR(RED));
                            }
                        }
                    }
                }
            }
        }
    }
}

void move_pl_bullet(Bullet bullet[]) {
    for (int i = 0; i < BULLET_NUM; i++) {
        if (bullet[i].exist == 1 && bullet[i].dir == 1) {
            bullet[i].x += 20;
        }
        if (bullet[i].exist == 1 && bullet[i].dir == 3) {
            bullet[i].x += 19;
            bullet[i].y += 1;
        }
        if (bullet[i].exist == 1 && bullet[i].dir == 4) {
            bullet[i].x += 19;
            bullet[i].y -= 1;
        }
        if (bullet[i].exist == 1 && bullet[i].dir == 5) {
            bullet[i].x += 16;
            bullet[i].y += 2;
        }
        if (bullet[i].exist == 1 && bullet[i].dir == 6) {
            bullet[i].x += 16;
            bullet[i].y -= 2;
        }
    }
}

void pl_shoot(Bullet bullet[]) {
    for (int i = 0; i < BULLET_NUM; i++) {
        if (bullet[i].exist == 0) {
            bullet[i].exist = 1;
            bullet[i].x = player.x + 20;
            bullet[i].y = player.y + 6;
            bullet[i].damage = player.damage;
            bullet[i].dir = 1;
            bullet[i].sp = 0;
            break;
        }
    }
}

void pl_sp_shoot(Bullet bullet[]) {
    for (int i = 0; i < BULLET_NUM; i++) {
        if (bullet[i].exist == 0) {
            bullet[i].exist = 1;
            bullet[i].x = player.x + 20;
            bullet[i].y = player.y + 8;
            bullet[i].damage = player.damage * 3;
            bullet[i].dir = 1;
            bullet[i].sp = 1;
            break;
        }
    }
    if (player.level >= 5) {
        for (int i = 0; i < BULLET_NUM; i++) {
            if (bullet[i].exist == 0) {
                bullet[i].exist = 1;
                bullet[i].x = player.x + 20;
                bullet[i].y = player.y + 8;
                bullet[i].damage = player.damage * 2;
                bullet[i].dir = 3;
                bullet[i].sp = 1;
                break;
            }
        }
        for (int i = 0; i < BULLET_NUM; i++) {
            if (bullet[i].exist == 0) {
                bullet[i].exist = 1;
                bullet[i].x = player.x + 20;
                bullet[i].y = player.y + 8;
                bullet[i].damage = player.damage * 2;
                bullet[i].dir = 4;
                bullet[i].sp = 1;
                break;
            }
        }
    }
    if (player.level >= 10) {
        for (int i = 0; i < BULLET_NUM; i++) {
            if (bullet[i].exist == 0) {
                bullet[i].exist = 1;
                bullet[i].x = player.x + 20;
                bullet[i].y = player.y + 8;
                bullet[i].damage = player.damage * 1.5;
                bullet[i].dir = 5;
                bullet[i].sp = 1;
                break;
            }
        }
        for (int i = 0; i < BULLET_NUM; i++) {
            if (bullet[i].exist == 0) {
                bullet[i].exist = 1;
                bullet[i].x = player.x + 20;
                bullet[i].y = player.y + 8;
                bullet[i].damage = player.damage * 1.5;
                bullet[i].dir = 6;
                bullet[i].sp = 1;
                break;
            }
        }
    }
}

void move_en_bullet(Bullet bullet[]) {
    for (int i = 0; i < BULLET_NUM; i++) {
        if (bullet[i].exist == 1 && bullet[i].dir == 2) {
            bullet[i].x -= 20;
        }
    }
}

void en_shoot(Bullet bullet[]) {
    for (int j = 0; j < ENEMY_NUM; j++) {
        if (enemy[j].exist == 1) {
            enemy[j].count++;
            if (enemy[j].count == enemy[j].interval) {
                enemy[j].count = 0;
                for (int i = 0; i < BULLET_NUM; i++) {
                    if (bullet[i].exist == 0) {
                        bullet[i].exist = 1;
                        bullet[i].x = enemy[j].x - 10;
                        bullet[i].y = enemy[j].y + 8;
                        bullet[i].damage = enemy[j].damage;
                        bullet[i].dir = 2;
                        bullet[i].sp = 0;
                        break;
                    }
                }
            }
        }
    }
    if (boss.exist == 1) {
        boss.count++;
        if (boss.count == boss.interval) {
            boss.count = 0;
            for (int i = 0; i < BULLET_NUM; i++) {
                if (bullet[i].exist == 0) {
                    bullet[i].exist = 1;
                    bullet[i].x = boss.x - 10;
                    bullet[i].y = boss.y + 2;
                    bullet[i].damage = boss.damage;
                    bullet[i].dir = 2;
                    bullet[i].sp = 1;
                    break;
                }
            }
        }
    }
}