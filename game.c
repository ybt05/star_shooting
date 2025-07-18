#include "main.h"
#include <ncurses.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

void normal_game(void) {
    int ch = 0;
    int key = ERR;
    int count = 0;
    int enemy_spawn_count = 250;
    int enemy_count = 0;
    Bullet bullet[BULLET_NUM];
    character_init(bullet);
    while (1) {
        ch = move_process(&key);
        if (ch == 27) {
            if (my_pause() == 1) {
                gameover();
                break;
            }
        }
        normal_spawn_process(&enemy_spawn_count, &enemy_count, count);
        bullet_process(count, bullet, ch);
        calc_damage(bullet, count);
        if (check_alive() == 1) {
            gameover();
            break;
        }
        calc_player_lv();
        draw_all(bullet, count, NORMAL_BOSS_MAX_HP);
        count++;
        if (count > BOSS_SPAWN_TIME + 10000) {
            count = BOSS_SPAWN_TIME;
        }
        if (count > BOSS_SPAWN_TIME && boss.exist == 0) {
            int i = 0;
            while (player.x < 830) {
                usleep(speed * 1000);
                player.x = player.x + 2 + i;
                i += 4;
                clear();
                draw_player();
                draw_box();
                draw_data();
                draw_ex_bar();
                refresh();
            }
            gameclear();
            break;
        }
    }
}

void endless_game(void) {
    int ch = 0;
    int key = ERR;
    int count = 0;
    int enemy_spawn_count = 250;
    int boss_count = 0;
    int enemy_count = 0;
    int endless_boss_max_hp;
    Bullet bullet[BULLET_NUM];
    character_init(bullet);
    while (1) {
        ch = move_process(&key);
        if (ch == 27) {
            if (my_pause() == 1) {
                gameover();
                break;
            }
        }
        endless_boss_max_hp = endless_spawn_process(&enemy_spawn_count, &enemy_count, count, &boss_count);
        bullet_process(count, bullet, ch);
        calc_damage(bullet, count);
        if (check_alive() == 1) {
            gameover();
            break;
        }
        calc_player_lv();
        draw_all(bullet, count, endless_boss_max_hp);
        count++;
        if (count > BOSS_SPAWN_TIME + 100000000) {
            count = BOSS_SPAWN_TIME;
        }
    }
}

void character_init(Bullet bullet[]) {
    player_init();
    enemy_init();
    bullet_init(bullet);
}

int move_process(int *key) {
    int ch;
    ch = mv_player(key);
    mv_enemy();
    mv_boss();
    return ch;
}

void normal_spawn_process(int *enemy_spawn_count, int *enemy_count, int count) {
    int ex = 4 + (*enemy_count) * 0.4;
    int damage = 2 + (*enemy_count) * 0.2;
    int x = 850;
    int y = 80 - rand() % 60;
    int interval = 15;
    int hp = 4 + (*enemy_count) * 3;
    int type = 1;
    if (*enemy_spawn_count == 0 || is_no_enemy()) {
        make_enemy(ex, damage, x, y, interval, hp, type);
        (*enemy_spawn_count) = 250 - (*enemy_count);
        (*enemy_count)++;
    }
    ex = 100;
    damage = 5;
    interval = 18;
    if (count == BOSS_SPAWN_TIME) {
        make_boss(ex, damage, x, y, interval, NORMAL_BOSS_MAX_HP);
    }
    (*enemy_spawn_count)--;
}

int endless_spawn_process(int *enemy_spawn_count, int *enemy_count, int count, int *boss_count) {
    int ex = 2 + (*enemy_count) * 0.6;
    int damage = 2 + (*enemy_count) * 0.4;
    int x = 850;
    int y = 80 - rand() % 60;
    int interval = 15;
    int hp = 4 + (*enemy_count) * 5;
    int enemy_type;
    int endless_boss_max_hp = NORMAL_BOSS_MAX_HP;
    if (*enemy_spawn_count == 0 || is_no_enemy()) {
        enemy_type = 1;
        if (*enemy_count % 3 == 2) {
            enemy_type = 2;
        }
        make_enemy(ex, damage, x, y, interval, hp, enemy_type);
        (*enemy_count)++;
        if (*enemy_count > 20) {
            enemy_type = 1;
            if (*enemy_count % 3 == 2) {
                enemy_type = 2;
            }
            make_enemy(ex, damage, x, y, interval, hp, enemy_type);
            (*enemy_count)++;
        }
        if (*enemy_count > 50) {
            enemy_type = 1;
            if (*enemy_count % 3 == 2) {
                enemy_type = 2;
            }
            make_enemy(ex, damage, x, y, interval, hp, enemy_type);
            (*enemy_count)++;
        }
        (*enemy_spawn_count) = 250 - (*enemy_count);
        if (*enemy_spawn_count < 100) {
            *enemy_spawn_count = 100;
        }
    }
    (*enemy_spawn_count)--;
    ex = 20 * ((*boss_count) + 0.5);
    damage = damage * 1.5;
    interval = 18;
    endless_boss_max_hp = NORMAL_BOSS_MAX_HP * ((*boss_count) + 0.5) * 1.2;
    if (count >= BOSS_SPAWN_TIME && count % BOSS_SPAWN_TIME == 0) {
        make_boss(ex, damage, x, y, interval, endless_boss_max_hp);
        (*boss_count)++;
    }
    return endless_boss_max_hp;
}

void calc_damage(Bullet bullet[], int count) {
    player_damaged(bullet);
    enemy_damaged(bullet);
    boss_damaged(bullet);
    calc_player_inv();
    if (count % 50 == 0) {
        calc_regeneration();
    }
}

int check_alive(void) {
    enemy_isalive();
    boss_isalive();
    return player_isalive();
}

void draw_all(Bullet bullet[], int count, int boss_max_hp) {
    clear();
    draw_player();
    draw_enemy();
    draw_boss();
    draw_bullet(bullet);
    draw_box();
    draw_data();
    draw_ex_bar();
    draw_boss_time_bar(count);
    draw_boss_hp_bar(boss_max_hp);
    refresh();
}

void draw_data(void) {
    // HP・LV
    attrset(COLOR_PAIR(WHITE));
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            if (HH[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(114 + i + dy, 30 + j * 3 + dx, ' ');
                    }
                }
            }
            if (PP[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(114 + i + dy, 50 + j * 3 + dx, ' ');
                    }
                }
            }
            if (LL[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(114 + i + dy, 250 + j * 3 + dx, ' ');
                    }
                }
            }
            if (VV[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(114 + i + dy, 270 + j * 3 + dx, ' ');
                    }
                }
            }
        }
    }
    int mag = 100;
    for (int k = 0; k < 3; k++) {
        if (player.hp / mag % 10 == 1) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (n1[i][j] == 1) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(114 + i + dy, 80 + j * 3 + dx + k * 25, ' ');
                            }
                        }
                    }
                }
            }
        }
        if (player.hp / mag % 10 == 2) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (n2[i][j] == 1) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(114 + i + dy, 80 + j * 3 + dx + k * 25, ' ');
                            }
                        }
                    }
                }
            }
        }
        if (player.hp / mag % 10 == 3) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (n3[i][j] == 1) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(114 + i + dy, 80 + j * 3 + dx + k * 25, ' ');
                            }
                        }
                    }
                }
            }
        }
        if (player.hp / mag % 10 == 4) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (n4[i][j] == 1) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(114 + i + dy, 80 + j * 3 + dx + k * 25, ' ');
                            }
                        }
                    }
                }
            }
        }
        if (player.hp / mag % 10 == 5) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (n5[i][j] == 1) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(114 + i + dy, 80 + j * 3 + dx + k * 25, ' ');
                            }
                        }
                    }
                }
            }
        }
        if (player.hp / mag % 10 == 6) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (n6[i][j] == 1) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(114 + i + dy, 80 + j * 3 + dx + k * 25, ' ');
                            }
                        }
                    }
                }
            }
        }
        if (player.hp / mag % 10 == 7) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (n7[i][j] == 1) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(114 + i + dy, 80 + j * 3 + dx + k * 25, ' ');
                            }
                        }
                    }
                }
            }
        }
        if (player.hp / mag % 10 == 8) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (n8[i][j] == 1) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(114 + i + dy, 80 + j * 3 + dx + k * 25, ' ');
                            }
                        }
                    }
                }
            }
        }
        if (player.hp / mag % 10 == 9) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (n9[i][j] == 1) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(114 + i + dy, 80 + j * 3 + dx + k * 25, ' ');
                            }
                        }
                    }
                }
            }
        }
        if (player.hp / mag % 10 == 0) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (n0[i][j] == 1) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(114 + i + dy, 80 + j * 3 + dx + k * 25, ' ');
                            }
                        }
                    }
                }
            }
        }
        if (player.level / mag % 10 == 1) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (n1[i][j] == 1) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(114 + i + dy, 300 + j * 3 + dx + k * 25, ' ');
                            }
                        }
                    }
                }
            }
        }
        if (player.level / mag % 10 == 2) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (n2[i][j] == 1) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(114 + i + dy, 300 + j * 3 + dx + k * 25, ' ');
                            }
                        }
                    }
                }
            }
        }
        if (player.level / mag % 10 == 3) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (n3[i][j] == 1) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(114 + i + dy, 300 + j * 3 + dx + k * 25, ' ');
                            }
                        }
                    }
                }
            }
        }
        if (player.level / mag % 10 == 4) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (n4[i][j] == 1) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(114 + i + dy, 300 + j * 3 + dx + k * 25, ' ');
                            }
                        }
                    }
                }
            }
        }
        if (player.level / mag % 10 == 5) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (n5[i][j] == 1) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(114 + i + dy, 300 + j * 3 + dx + k * 25, ' ');
                            }
                        }
                    }
                }
            }
        }
        if (player.level / mag % 10 == 6) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (n6[i][j] == 1) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(114 + i + dy, 300 + j * 3 + dx + k * 25, ' ');
                            }
                        }
                    }
                }
            }
        }
        if (player.level / mag % 10 == 7) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (n7[i][j] == 1) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(114 + i + dy, 300 + j * 3 + dx + k * 25, ' ');
                            }
                        }
                    }
                }
            }
        }
        if (player.level / mag % 10 == 8) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (n8[i][j] == 1) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(114 + i + dy, 300 + j * 3 + dx + k * 25, ' ');
                            }
                        }
                    }
                }
            }
        }
        if (player.level / mag % 10 == 9) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (n9[i][j] == 1) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(114 + i + dy, 300 + j * 3 + dx + k * 25, ' ');
                            }
                        }
                    }
                }
            }
        }
        if (player.level / mag % 10 == 0) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (n0[i][j] == 1) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(114 + i + dy, 300 + j * 3 + dx + k * 25, ' ');
                            }
                        }
                    }
                }
            }
        }
        mag /= 10;
    }
}

void draw_ex_bar(void) {
    int x = player.ex * 800 / player.required_ex + 10;
    if (x > 800) {
        x = 800;
    }
    for (int i = 10; i < x; i++) {
        mvaddch(108, i, ' ' | COLOR_PAIR(GREEN));
        mvaddch(109, i, ' ' | COLOR_PAIR(GREEN));
    }
}

void draw_boss_time_bar(int count) {
    if (count < BOSS_SPAWN_TIME) {
        int x = count * 800 / BOSS_SPAWN_TIME + 10;
        for (int i = 10; i < x; i++) {
            mvaddch(106, i, ' ' | COLOR_PAIR(RED));
            mvaddch(107, i, ' ' | COLOR_PAIR(RED));
        }
    }
}

void draw_boss_hp_bar(int boss_max_hp) {
    if (boss.exist == 1) {
        int x = boss.hp * 800 / boss_max_hp + 10;
        for (int i = 10; i < x; i++) {
            mvaddch(106, i, ' ' | COLOR_PAIR(RED));
            mvaddch(107, i, ' ' | COLOR_PAIR(RED));
        }
    }
}

int character[10][13] = {
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 2, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 3, 1, 0, 0, 0},
    {0, 0, 5, 5, 1, 1, 4, 4, 1, 1, 0, 0, 0},
    {0, 6, 5, 5, 5, 1, 1, 1, 1, 6, 6, 6, 0},
    {0, 0, 6, 5, 5, 5, 1, 1, 6, 6, 6, 0, 0},
    {0, 0, 0, 6, 5, 5, 6, 6, 6, 6, 0, 0, 0},
    {0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0},
    {0, 0, 6, 6, 6, 0, 0, 0, 6, 6, 6, 0, 0}
};

void player_init(void) {
    player.level = 1;
    player.score = 0;
    player.damage = 3;
    player.x = 10;
    player.y = 50;
    player.interval = 20;
    player.hp = 100;
    player.ex = 0;
    player.required_ex = 5;
    player.invincible = 0;
    player.invincible_time = 0;
    player.count = 0;
    player.defense = 0;
    player.regeneration = 0;
    player.max_hp = 100;
}

long get_millis(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000L) + (tv.tv_usec / 1000L);
}

int mv_player(int *key) {
    int ch = 0;
    long elapsed = 0;
    long after_time = 0;
    long before_time = get_millis();
    timeout(speed);
    ch = getch();
    if (ch != ERR) {
        while (ch == *key && elapsed < speed) {
            int next = getch();
            long now = get_millis();
            elapsed = now - before_time;
            if (next != ERR) {
                ch = next;
            }
        }
        long total_elapsed = get_millis() - before_time;
        if (total_elapsed < speed) {
            usleep((speed - total_elapsed) * 1000);
        }
    }
    if (ch == 'q' || ch == 'w' || ch == 'e' || ch == 'a' || ch == 's' || ch == 'd' || ch == 'z' || ch == 'x' || ch == 'c' || ch == 'f' ||
        ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_UP || ch == KEY_DOWN) {
        *key = ch;
    }
    if (*key == 'q') {
        if (player.y > 7) {
            player.y -= 2;
        }
        if (player.x > 19) {
            player.x -= 9;
        }
    } else if (*key == 'e') {
        if (player.y > 7) {
            player.y -= 2;
        }
        if (player.x < 500) {
            player.x += 9;
        }
    } else if (*key == 'z') {
        if (player.y < 93) {
            player.y += 2;
        }
        if (player.x > 19) {
            player.x -= 9;
        }
    } else if (*key == 'c') {
        if (player.y < 93) {
            player.y += 2;
        }
        if (player.x < 500) {
            player.x += 9;
        }
    } else if (*key == 'w' || *key == KEY_UP) {
        if (player.y > 8) {
            player.y -= 3;
        }
    } else if (*key == 'a' || *key == KEY_LEFT) {
        if (player.x > 23) {
            player.x -= 13;
        }
    } else if (*key == 'd' || *key == KEY_RIGHT) {
        if (player.x < 500) {
            player.x += 13;
        }
    } else if ((*key == 'x' && key_mode == 1) || (*key == 's' && key_mode == 2) || *key == KEY_DOWN) {
        if (player.y < 92) {
            player.y += 3;
        }
    } else if ((*key == 's' && key_mode == 1) || (*key == 'x' && key_mode == 2) || *key == 'f') {
    }
    return ch;
}

void draw_player(void) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 13; j++) {
            if (character[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(player.y + i * 1 + dy, player.x + j * 3 + dx, ' ' | COLOR_PAIR(LIGHTBLUE));
                    }
                }
            }
            if (character[i][j] == 2) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(player.y + i * 1 + dy, player.x + j * 3 + dx, ' ' | COLOR_PAIR(BLACK));
                    }
                }
            }
            if (character[i][j] == 3) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(player.y + i * 1 + dy, player.x + j * 3 + dx, ' ' | COLOR_PAIR(BLACK));
                    }
                }
            }
            if (character[i][j] == 4) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(player.y + i * 1 + dy, player.x + j * 3 + dx, ' ' | COLOR_PAIR(RED));
                    }
                }
            }
            if (character[i][j] == 5) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(player.y + i * 1 + dy, player.x + j * 3 + dx, ' ' | COLOR_PAIR(BLUE));
                    }
                }
            }
            if (character[i][j] == 6) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(player.y + i * 1 + dy, player.x + j * 3 + dx, ' ' | COLOR_PAIR(YELLOW));
                    }
                }
            }
        }
    }
}

void player_damaged(Bullet bullet[]) {
    for (int dx = 0; dx < 40; dx++) {
        for (int dy = 0; dy < 12; dy++) {
            for (int j = 0; j < BULLET_NUM; j++) {
                if (bullet[j].exist == 1 && bullet[j].dir == 2 && bullet[j].sp == 0 && player.x + dx == bullet[j].x && player.y + dy == bullet[j].y) {
                    if (player.invincible == 0) {
                        if (player.defense < bullet[j].damage) {
                            player.hp = player.hp + player.defense - bullet[j].damage;
                            player.invincible = 1;
                            player.invincible_time = 2;
                        } else {
                            player.hp--;
                            player.invincible = 1;
                            player.invincible_time = 2;
                        }
                    }
                    bullet[j].exist = 0;
                } else if (bullet[j].exist == 1 && bullet[j].dir == 2 && bullet[j].sp == 1) {
                    int hit = 0;
                    for (int ddx = 0; ddx < 40 && hit == 0; ddx++) {
                        for (int ddy = 0; ddy < 7 && hit == 0; ddy++) {
                            if (player.x + dx == bullet[j].x + ddx && player.y + dy == bullet[j].y + ddy) {
                                if (player.defense < bullet[j].damage) {
                                    player.hp = player.hp + player.defense - bullet[j].damage;
                                    player.invincible = 1;
                                    player.invincible_time = 2;
                                } else {
                                    player.hp--;
                                    player.invincible = 1;
                                    player.invincible_time = 2;
                                }
                                bullet[j].exist = 0;
                                hit = 1;
                            }
                        }
                    }
                }
            }
        }
    }
}

void calc_player_inv(void) {
    if (player.invincible == 1) {
        player.invincible_time--;
    }
    if (player.invincible_time == 0) {
        player.invincible = 0;
    }
}

int player_isalive(void) {
    if (player.hp <= 0) {
        return 1;
    } else {
        return 0;
    }
}

void calc_player_lv(void) {
    if (player.required_ex <= player.ex && player.level < 99) {
        player.ex -= player.required_ex;
        player.level++;
        player.damage = player.damage + 2;
        if (player.interval > 6) {
            player.interval--;
        }
        player.required_ex = (player.required_ex + 2) * 1.04;
        if (player.level % 5 == 0) {
            level_up();
        }
    }
}

void calc_regeneration(void) {
    player.hp = player.hp + player.regeneration;
    if (player.hp > player.max_hp) {
        player.hp = player.max_hp;
    }
}

void level_up(void) {
    int mode = 1;
    int prev_mode = mode;
    int ch = 0;
    clear();
    draw_box();
    draw_level_up();
    draw_cursor(mode);
    refresh();
    timeout(-1);
    while (1) {
        ch = getch();
        if ((ch == 'w' || ch == KEY_UP) && mode > 1) {
            mode--;
        } else if ((ch == 's' || ch == KEY_DOWN) && mode < 3) {
            mode++;
        } else if ((ch == 10 || ch == 13)) {
            if (mode == 1) {
                player.damage += 10;
                break;
            } else if (mode == 2) {
                player.defense += 8;
                break;
            } else if (mode == 3) {
                player.regeneration += 5;
                break;
            }
        }
        if (mode != prev_mode) {
            clear();
            draw_box();
            draw_level_up();
            draw_cursor(mode);
            refresh();
            prev_mode = mode;
        }
    }
}

void draw_level_up(void) {
    for (int x = 100; x <= 720; x++) {
        for (int y = 40; y <= 100; y++) {
            mvaddch(y, x, ' ' | COLOR_PAIR(DARKBLUE));
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
            // コウゲキ+
            if (ko[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(52 + i + dy, 310 + j * 3 + dx, ' ');
                    }
                }
            }
            if (uu[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(52 + i + dy, 340 + j * 3 + dx, ' ');
                    }
                }
            }
            if (ke[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(52 + i + dy, 370 + j * 3 + dx, ' ');
                    }
                }
            }
            if (dakuon[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(52 + i + dy, 390 + j * 3 + dx, ' ');
                    }
                }
            }
            if (ki[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(52 + i + dy, 400 + j * 3 + dx, ' ');
                    }
                }
            }
            if (plus[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(52 + i + dy, 430 + j * 3 + dx, ' ');
                    }
                }
            }
            // ボウギョ+
            if (ho[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(70 + i + dy, 310 + j * 3 + dx, ' ');
                    }
                }
            }
            if (dakuon[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(70 + i + dy, 330 + j * 3 + dx, ' ');
                    }
                }
            }
            if (uu[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(70 + i + dy, 345 + j * 3 + dx, ' ');
                    }
                }
            }
            if (ki[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(70 + i + dy, 370 + j * 3 + dx, ' ');
                    }
                }
            }
            if (dakuon[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(70 + i + dy, 395 + j * 3 + dx, ' ');
                    }
                }
            }
            if (xyo[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(72 + i + dy, 405 + j * 3 + dx, ' ');
                    }
                }
            }
            if (plus[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(70 + i + dy, 430 + j * 3 + dx, ' ');
                    }
                }
            }
            // カイフク+
            if (ka[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(88 + i + dy, 310 + j * 3 + dx, ' ');
                    }
                }
            }
            if (ii[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(88 + i + dy, 340 + j * 3 + dx, ' ');
                    }
                }
            }
            if (hu[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(88 + i + dy, 370 + j * 3 + dx, ' ');
                    }
                }
            }
            if (ku[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(88 + i + dy, 400 + j * 3 + dx, ' ');
                    }
                }
            }
            if (plus[i][j] == 1) {
                for (int dy = 0; dy < 1; dy++) {
                    for (int dx = 0; dx < 3; dx++) {
                        mvaddch(88 + i + dy, 430 + j * 3 + dx, ' ');
                    }
                }
            }
        }
    }
}

int enemys[10][13] = {
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 2, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 3, 1, 4, 4, 1, 1, 0, 0, 0},
    {0, 0, 4, 1, 1, 1, 1, 1, 1, 1, 4, 0, 0},
    {0, 4, 4, 4, 1, 1, 1, 1, 1, 4, 4, 4, 0},
    {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
    {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
    {0, 1, 1, 4, 4, 4, 4, 4, 4, 4, 1, 1, 0},
    {0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0}
};
int boss_image[10][13] = {
    {0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 2, 1, 1, 0, 0, 0, 1, 1, 1, 1},
    {1, 1, 1, 2, 1, 1, 0, 0, 1, 1, 1, 1, 3},
    {3, 3, 1, 1, 1, 1, 3, 0, 1, 1, 1, 3, 0},
    {3, 3, 1, 1, 1, 1, 3, 1, 1, 1, 3, 0, 0},
    {0, 1, 1, 1, 1, 3, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 4, 4, 4, 1, 1, 1, 1, 1, 1, 0, 1},
    {0, 0, 3, 3, 4, 4, 4, 1, 3, 3, 1, 1, 1},
    {0, 0, 3, 3, 4, 4, 4, 4, 3, 3, 1, 1, 0},
    {0, 0, 3, 3, 0, 0, 0, 0, 3, 3, 0, 0, 0}
};

void enemy_init(void) {
    for (int i = 0; i < ENEMY_NUM; i++) {
        enemy[i].exist = 0;
        boss.exist = 0;
    }
}

void make_enemy(int ex, int damage, int x, int y, int interval, int hp, int type) {
    for (int i = 0; i < ENEMY_NUM; i++) {
        if (enemy[i].exist == 0) {
            enemy[i].ex = ex;
            enemy[i].damage = damage;
            enemy[i].x = x;
            enemy[i].y = y;
            enemy[i].interval = interval;
            enemy[i].hp = hp;
            enemy[i].exist = 1;
            enemy[i].count = 0;
            enemy[i].before_x = x;
            enemy[i].before_y = y;
            enemy[i].boss = 0;
            enemy[i].type = type;
            break;
        }
    }
}

void make_boss(int ex, int damage, int x, int y, int interval, int hp) {
    if (boss.exist == 0) {
        boss.ex = ex;
        boss.damage = damage;
        boss.x = x;
        boss.y = y;
        boss.interval = interval;
        boss.hp = hp;
        boss.exist = 1;
        boss.count = 0;
        boss.before_x = x;
        boss.before_y = y;
        boss.boss = 1;
    }
}

int is_no_enemy(void) {
    int flag = 1;
    for (int i = 0; i < ENEMY_NUM; i++) {
        if (enemy[i].exist == 1) {
            flag = 0;
            break;
        }
    }
    return flag;
}

void mv_enemy(void) {
    int x, y;
    for (int i = 0; i < ENEMY_NUM; i++) {
        if (enemy[i].type == 1) {
            if (enemy[i].count % 10 == 0) {
                x = 5 - rand() % 11;
                y = 2 - rand() % 5;
                enemy[i].before_x = x;
                enemy[i].before_y = y;
            } else {
                x = enemy[i].before_x;
                y = enemy[i].before_y;
            }
            if (enemy[i].exist == 1) {
                if (enemy[i].x > 750) {
                    enemy[i].x -= 6;
                    enemy[i].before_x = -6;
                } else if (enemy[i].x < 400) {
                    enemy[i].x += 6;
                    enemy[i].before_x = 6;
                } else if (enemy[i].y < 15) {
                    enemy[i].y += 3;
                    enemy[i].before_y = 3;
                } else if (enemy[i].y > 90) {
                    enemy[i].y -= 3;
                    enemy[i].before_y = -3;
                } else {
                    enemy[i].x += x;
                    enemy[i].y += y;
                }
            }
        } else if (enemy[i].type == 2) {
            if (enemy[i].count % 15 == 0) {
                enemy[i].x = 750 - rand() % 350;
                enemy[i].y = player.y;
            }
        }
    }
}

void mv_boss(void) {
    int x, y;
    if (boss.count % 10 == 0) {
        x = 8 - rand() % 17;
        y = 3 - rand() % 7;
        boss.before_x = x;
        boss.before_y = y;
    } else {
        x = boss.before_x;
        y = boss.before_y;
    }
    if (boss.exist == 1) {
        if (boss.x > 750) {
            boss.x -= 6;
            boss.before_x = -6;
        } else if (boss.x < 400) {
            boss.x += 6;
            boss.before_x = 6;
        } else if (boss.y < 15) {
            boss.y += 3;
            boss.before_y = 3;
        } else if (boss.y > 90) {
            boss.y -= 3;
            boss.before_y = -3;
        } else {
            boss.x += x;
            boss.y += y;
        }
    }
}

void draw_enemy(void) {
    for (int k = 0; k < ENEMY_NUM; k++) {
        if (enemy[k].exist == 1) {
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 13; j++) {
                    if (enemys[i][j] == 1) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(enemy[k].y + i * 1 + dy, enemy[k].x + j * 3 + dx, ' ' | COLOR_PAIR(PINK));
                            }
                        }
                    }
                    if (enemys[i][j] == 2) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(enemy[k].y + i * 1 + dy, enemy[k].x + j * 3 + dx, ' ' | COLOR_PAIR(WHITE));
                            }
                        }
                    }
                    if (enemys[i][j] == 3) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(enemy[k].y + i * 1 + dy, enemy[k].x + j * 3 + dx, ' ' | COLOR_PAIR(BLACK));
                            }
                        }
                    }
                    if (enemys[i][j] == 4) {
                        for (int dy = 0; dy < 1; dy++) {
                            for (int dx = 0; dx < 3; dx++) {
                                mvaddch(enemy[k].y + i * 1 + dy, enemy[k].x + j * 3 + dx, ' ' | COLOR_PAIR(RED));
                            }
                        }
                    }
                }
            }
        }
    }
}

void draw_boss(void) {
    if (boss.exist == 1) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 13; j++) {
                if (boss_image[i][j] == 1) {
                    for (int dy = 0; dy < 1; dy++) {
                        for (int dx = 0; dx < 3; dx++) {
                            mvaddch(boss.y + i * 1 + dy, boss.x + j * 3 + dx, ' ' | COLOR_PAIR(RED));
                        }
                    }
                }
                if (boss_image[i][j] == 2) {
                    for (int dy = 0; dy < 1; dy++) {
                        for (int dx = 0; dx < 3; dx++) {
                            mvaddch(boss.y + i * 1 + dy, boss.x + j * 3 + dx, ' ' | COLOR_PAIR(BLACK));
                        }
                    }
                }
                if (boss_image[i][j] == 3) {
                    for (int dy = 0; dy < 1; dy++) {
                        for (int dx = 0; dx < 3; dx++) {
                            mvaddch(boss.y + i * 1 + dy, boss.x + j * 3 + dx, ' ' | COLOR_PAIR(DARKRED));
                        }
                    }
                }
                if (boss_image[i][j] == 4) {
                    for (int dy = 0; dy < 1; dy++) {
                        for (int dx = 0; dx < 3; dx++) {
                            mvaddch(boss.y + i * 1 + dy, boss.x + j * 3 + dx, ' ' | COLOR_PAIR(YELLOW));
                        }
                    }
                }
            }
        }
    }
}

void enemy_damaged(Bullet bullet[]) {
    for (int i = 0; i < ENEMY_NUM; i++) {
        if (enemy[i].exist == 1) {
            for (int dx = 0; dx < 40; dx++) {
                for (int dy = 0; dy < 12; dy++) {
                    for (int j = 0; j < BULLET_NUM; j++) {
                        if (bullet[j].exist == 1 && bullet[j].dir != 2 && bullet[j].sp == 0 && enemy[i].x + dx == bullet[j].x && enemy[i].y + dy == bullet[j].y) {
                            enemy[i].hp -= bullet[j].damage;
                            bullet[j].exist = 0;
                        } else if (bullet[j].exist == 1 && bullet[j].dir != 2 && bullet[j].sp == 1) {
                            int hit = 0;
                            for (int ddx = 0; ddx < 40 && hit == 0; ddx++) {
                                for (int ddy = 0; ddy < 7 && hit == 0; ddy++) {
                                    if (enemy[i].x + dx == bullet[j].x + ddx && enemy[i].y + dy == bullet[j].y + ddy) {
                                        enemy[i].hp -= bullet[j].damage;
                                        bullet[j].exist = 0;
                                        hit = 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void boss_damaged(Bullet bullet[]) {
    if (boss.exist == 1) {
        for (int dx = 0; dx < 40; dx++) {
            for (int dy = 0; dy < 12; dy++) {
                for (int j = 0; j < BULLET_NUM; j++) {
                    if (bullet[j].exist == 1 && bullet[j].dir != 2 && bullet[j].sp == 0 && boss.x + dx == bullet[j].x && boss.y + dy == bullet[j].y) {
                        boss.hp -= bullet[j].damage;
                        bullet[j].exist = 0;
                    } else if (bullet[j].exist == 1 && bullet[j].dir != 2 && bullet[j].sp == 1) {
                        int hit = 0;
                        for (int ddx = 0; ddx < 40 && hit == 0; ddx++) {
                            for (int ddy = 0; ddy < 7 && hit == 0; ddy++) {
                                if (boss.x + dx == bullet[j].x + ddx && boss.y + dy == bullet[j].y + ddy) {
                                    boss.hp -= bullet[j].damage;
                                    bullet[j].exist = 0;
                                    hit = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void enemy_isalive(void) {
    for (int i = 0; i < ENEMY_NUM; i++) {
        if (enemy[i].exist == 1 && enemy[i].hp <= 0) {
            enemy[i].exist = 0;
            player.ex += enemy[i].ex;
            player.score += enemy[i].ex;
            if (player.score > 99999) {
                player.score = 99999;
            }
        }
    }
}

void boss_isalive(void) {
    if (boss.exist == 1 && boss.hp <= 0) {
        boss.exist = 0;
        player.ex += boss.ex;
        player.score += boss.ex;
        if (player.score > 99999) {
            player.score = 99999;
        }
    }
}
