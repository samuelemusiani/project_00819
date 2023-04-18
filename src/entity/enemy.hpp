class Enemy : public Entity {
protected:
  int hp;
  double ms;
  int damg;
  bool isAlive;
public:

  Enemy(int hp, int ms, int damg);

  void init_enemy(int hp, int ms, int damg);
  void set_hp(int hp);
  void got_hit(int damGot);
  void set_state(bool s);
}
