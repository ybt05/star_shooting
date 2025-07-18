#define BLACK 1
#define PINK 2
#define YELLOW 3
#define WHITE 4
#define RED 5
#define DARKRED 6
#define DARKBLUE 7
#define GREEN 8
#define LIGHTBLUE 9
#define BLUE 10
#define BOSS_SPAWN_TIME 1500
#define NORMAL_BOSS_MAX_HP 500
#define BULLET_NUM 150
#define ENEMY_NUM 15

typedef struct {
    int exist;
    int damage;
    int x;
    int y;
    int dir;
    int sp;
} Bullet;

typedef struct {
    int level;
    int score;
    int damage;
    int x;
    int y;
    int interval;
    int hp;
    int ex;
    int required_ex;
    int invincible;
    int invincible_time;
    int count;
    int defense;
    int regeneration;
    int max_hp;
} Player;

typedef struct {
    int ex;
    int damage;
    int x;
    int y;
    int interval;
    int hp;
    int exist;
    int count;
    int before_x;
    int before_y;
    int boss;
    int type;
} Enemy;

extern int key_mode;
extern int speed;
extern Player player;
extern Enemy enemy[ENEMY_NUM];
extern Enemy boss;

int main(int argc, char *argv[]);
void draw_help(void);
void init(void);
void set_color(void);

void title(void);
void draw_title(void);
void draw_high_score(void);
void draw_key_mode(void);

int my_pause(void);
void draw_pause(void);

void gameclear(void);
void draw_gameclear(void);

void gameover(void);
void draw_gameover(void);

void normal_game(void);
void endless_game(void);
void character_init(Bullet bullet[]);
int move_process(int *key);
void normal_spawn_process(int *enemy_spawn_count, int *enemy_count, int count);
int endless_spawn_process(int *enemy_spawn_count, int *enemy_count, int count, int *boss_count);
void calc_damage(Bullet bullet[], int count);
int check_alive(void);
void draw_all(Bullet bullet[], int count, int boss_max_hp);
void draw_data(void);
void draw_ex_bar(void);
void draw_boss_time_bar(int count);
void draw_boss_hp_bar(int boss_max_hp);

void player_init(void);
long get_millis(void);
int mv_player(int *key);
void draw_player(void);
void player_damaged(Bullet bullet[]);
void calc_player_inv(void);
int player_isalive(void);
void calc_player_lv(void);
void calc_regeneration(void);
void level_up(void);
void draw_level_up(void);

void enemy_init(void);
void make_enemy(int ex, int damage, int x, int y, int interval, int hp, int type);
void make_boss(int ex, int damage, int x, int y, int interval, int hp);
int is_no_enemy(void);
void mv_enemy(void);
void mv_boss(void);
void draw_enemy(void);
void draw_boss(void);
void enemy_damaged(Bullet bullet[]);
void boss_damaged(Bullet bullet[]);
void enemy_isalive(void);
void boss_isalive(void);

void bullet_init(Bullet bullet[]);
void bullet_process(int count, Bullet bullet[], int ch);
void break_bullet(Bullet bullet[]);
void draw_bullet(Bullet bullet[]);
void move_pl_bullet(Bullet bullet[]);
void pl_shoot(Bullet bullet[]);
void pl_sp_shoot(Bullet bullet[]);
void move_en_bullet(Bullet bullet[]);
void en_shoot(Bullet bullet[]);

void draw_box(void);
void draw_cursor(int flag);
void draw_score(void);

void hash(int data, char str[]);
int reverse_hash(char hash_data[]);
void insertion_sort(int data[], int n);
void save_score(void);
void read_score(int data[]);

extern int aa[5][6];
extern int ii[5][6];
extern int uu[5][6];
extern int ee[5][6];
extern int oo[5][6];
extern int ka[5][6];
extern int ki[5][6];
extern int ku[5][6];
extern int ke[5][6];
extern int ko[5][6];
extern int shi[5][6];
extern int su[5][6];
extern int ta[5][6];
extern int te[5][6];
extern int to[5][6];
extern int doo[5][6];
extern int ni[5][6];
extern int no[5][6];
extern int ha[5][6];
extern int hu[5][6];
extern int ho[5][6];
extern int ma[5][6];
extern int mu[5][6];
extern int mo[5][6];
extern int xyu[5][6];
extern int xyo[5][6];
extern int ri[5][6];
extern int ru[5][6];
extern int re[5][6];
extern int ro[5][6];
extern int nn[5][6];
extern int dakuon[5][6];
extern int handakuon[5][6];
extern int nobasibou[5][6];
extern int plus[5][6];
extern int n1[5][6];
extern int n2[5][6];
extern int n3[5][6];
extern int n4[5][6];
extern int n5[5][6];
extern int n6[5][6];
extern int n7[5][6];
extern int n8[5][6];
extern int n9[5][6];
extern int n0[5][6];
extern int AA[5][6];
extern int BB[5][6];
extern int EE[5][6];
extern int HH[5][6];
extern int LL[5][6];
extern int MM[5][6];
extern int PP[5][6];
extern int VV[5][6];
extern int XX[5][6];
extern int character[10][13];
extern int enemys[10][13];
extern int boss_image[10][13];
extern int star[7][13];