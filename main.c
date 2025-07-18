#include "main.h"
#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

Player player;
Enemy enemy[ENEMY_NUM];
Enemy boss;

int key_mode = 1;
int speed = 40;

int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        init();
        draw_help();
        endwin();
        return 0;
    } else if (argc == 2 && strcmp(argv[1], "-s") == 0) {
        speed = 20;
    } else if (argc != 1) {
        fprintf(stderr, "プログラム引数が間違っています.\nヘルプ表示は[-h]です.\n");
        exit(1);
    }
    init();
    set_color();
    title();
    endwin();
    return 0;
}

void init(void) {
    srand(time(NULL));
    setlocale(LC_ALL, "");
    initscr();
    crmode();
    noecho();
    curs_set(0);
    start_color();
    keypad(stdscr, TRUE);
    cbreak();
    mousemask(ALL_MOUSE_EVENTS, NULL);
}

void set_color(void) {
    init_pair(BLACK, COLOR_WHITE, COLOR_BLACK);
    init_pair(WHITE, COLOR_BLACK, COLOR_WHITE);
    init_pair(YELLOW, COLOR_BLACK, COLOR_YELLOW);
    init_pair(PINK, COLOR_BLACK, 219);
    init_pair(RED, COLOR_BLACK, COLOR_RED);
    init_pair(DARKRED, COLOR_BLACK, 001);
    init_pair(DARKBLUE, COLOR_BLACK, 025);
    init_pair(GREEN, COLOR_BLACK, COLOR_GREEN);
    init_pair(LIGHTBLUE, COLOR_BLACK, 117);
    init_pair(BLUE, COLOR_BLACK, COLOR_BLUE);
}

void draw_help(void) {
    mvprintw(2, 5, "ヘルプ");
    mvprintw(3, 5, "Qキーで閉じる");
    mvprintw(5, 5, "ゲーム説明");
    mvprintw(6, 5, "ノーマルモード:ボスを倒すとクリアです.");
    mvprintw(7, 5, "エンドレスモード:できるだけ長く生き延びてスコアを競います.");
    mvprintw(9, 5, "操作方法(ゲームプレイ中 操作モードA)");
    mvprintw(10, 5, "Qキー:左上への移動 |Wキー:上への移動   |Eキー:右上への移動");
    mvprintw(11, 5, "Aキー:左への移動   |Sキー Fキー:停止   |Dキー:右への移動");
    mvprintw(12, 5, "Zキー:左下への移動 |Xキー:下への移動   |Cキー:右下への移動");
    mvprintw(13, 5, "←キー:左への移動  |↑キー:上への移動  |→キー:右への移動");
    mvprintw(14, 5, "↓キー:下への移動  |Spaceキー:特殊攻撃 |Escキー:ポーズ");
    mvprintw(15, 5, "※操作モードがBの場合はSキーとXキーの操作が入れ替わります.");
    mvprintw(16, 5, "操作方法(タイトル画面などの選択画面)");
    mvprintw(17, 5, "Wキー:カーソルを上に移動 |Sキー:カーソルを下に移動 |Enterキー:決定");
    mvprintw(18, 5, "↑キー:カーソルを上に移動|↓キー:カーソルを下に移動|");
    mvprintw(19, 5, "操作方法(タイトル画面)");
    mvprintw(20, 5, "Mキー:操作モードの切り替え|Hキー:ハイスコアの表示");
    mvprintw(22, 5, "実行時に[-s]のオプションをつけることで動きが速くなります.");
    mvprintw(23, 5, "「Ctrl」+「-キー」で文字サイズを調整してください.");

    refresh();
    while (getch() != 'q')
        ;
    return;
}