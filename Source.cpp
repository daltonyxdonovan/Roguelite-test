#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

//in the standard namespace
using namespace std;

//variables
const int window_width{ 1920 };
const int window_height{ 1080 };
const int map_width{ window_width/100 };
const int map_height{ window_height/100 };


int gamestate{ 1 };
bool room_changing = true;
int room {0};




class Tile
{
public:
	int x;
	int y;
	int type;
	sf::Texture texture;
	sf::Sprite sprite;


	Tile(int x, int y, int type)
	{
		this->x = x;
		this->y = y;
		this->type = type;
		this->texture = sf::Texture();
		this->sprite = sf::Sprite();




	}

	void draw(sf::RenderWindow& window)
	{
		if (type == 0 || type == 2 || type == 3)
			sprite.setPosition(x, y - 100);
		else
			sprite.setPosition(x, y);
		window.draw(sprite);
	}

	void set_texture(sf::Texture texture)
	{
		this->texture = texture;
		sprite.setTexture(texture);
	}
};

class Player
{
public:
	int x;
	int y;
	int power;
	int direction;
	int health;
	int speed;
	int bullets;
	bool left;
	bool right;
	bool up;
	bool down;
	bool paused;


	//store four textures to animate from, as well as it's animation_ticker
	sf::Texture left1;
	sf::Texture left2;
	sf::Texture left3;
	sf::Texture left4;
	sf::Texture left5;
	sf::Texture left6;
	
	sf::Texture right1;
	sf::Texture right2;
	sf::Texture right3;
	sf::Texture right4;
	sf::Texture right5;
	sf::Texture right6;

	sf::Texture idle_left1;
	sf::Texture idle_left2;
	sf::Texture idle_left3;
	sf::Texture idle_left4;
	sf::Texture idle_left5;
	sf::Texture idle_left6;


	sf::Texture idle_right1;
	sf::Texture idle_right2;
	sf::Texture idle_right3;
	sf::Texture idle_right4;
	sf::Texture idle_right5;
	sf::Texture idle_right6;
	

	sf::Sprite sprite;
	int animation_ticker;
	bool right_facing;
	bool idle;
	bool facing;
	int anim_timer;
	sf::Vector2f left_collider;
	sf::Vector2f right_collider;
	sf::Vector2f up_collider;
	sf::Vector2f down_collider;


	Player(int x, int y)
	{
		this->paused = false;
		this->x = x;
		this->y = y;
		this->power = 0;
		this->direction = 0;
		this->health = 5;
		this->speed = 10;
		this->bullets = 1;
		this->left = false;
		this->right = false;
		this->up = false;
		this->down = false;
		this->facing = false;
		this->anim_timer = 5;
		this->left_collider = sf::Vector2f(x - 25, y);
		this->right_collider = sf::Vector2f(x + 25, y);
		this->up_collider = sf::Vector2f(x, y - 25);
		this->down_collider = sf::Vector2f(x, y + 25);
		

		//load textures
		left1.loadFromFile("assets/player/walk_left1.png");
		left2.loadFromFile("assets/player/walk_left2.png");
		left3.loadFromFile("assets/player/walk_left3.png");
		left4.loadFromFile("assets/player/walk_left4.png");
		left5.loadFromFile("assets/player/walk_left5.png");
		left6.loadFromFile("assets/player/walk_left6.png");

		right1.loadFromFile("assets/player/walk_right1.png");
		right2.loadFromFile("assets/player/walk_right2.png");
		right3.loadFromFile("assets/player/walk_right3.png");
		right4.loadFromFile("assets/player/walk_right4.png");
		right5.loadFromFile("assets/player/walk_right5.png");
		right6.loadFromFile("assets/player/walk_right6.png");

		idle_left1.loadFromFile("assets/player/idle_left1.png");
		idle_left2.loadFromFile("assets/player/idle_left2.png");
		idle_left3.loadFromFile("assets/player/idle_left3.png");
		idle_left4.loadFromFile("assets/player/idle_left4.png");
		idle_left5.loadFromFile("assets/player/idle_left5.png");
		idle_left6.loadFromFile("assets/player/idle_left6.png");

		idle_right1.loadFromFile("assets/player/idle_right1.png");
		idle_right2.loadFromFile("assets/player/idle_right2.png");
		idle_right3.loadFromFile("assets/player/idle_right3.png");
		idle_right4.loadFromFile("assets/player/idle_right4.png");
		idle_right5.loadFromFile("assets/player/idle_right5.png");
		idle_right6.loadFromFile("assets/player/idle_right6.png");

		
		sprite.setTexture(left1);
		sprite.setPosition(x, y);
		animation_ticker = 0;
		right_facing = false;
		idle = true;
		

	}

	void draw(sf::RenderWindow& window)
	{

		//scale sprite to 3/4th it's size
		
		//sprite.setOrigin to exact center of sprite texture
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
		sprite.setPosition(x, y);
		window.draw(sprite);


	}



	void update(vector<vector<Tile>> tilemaps)
	{
		
		if (!paused)
		{
			animation_ticker++;
			if (idle)
			{
				if (animation_ticker == anim_timer * 0 && !right_facing)
				{
					sprite.setTexture(idle_left1);
				}
				else if (animation_ticker == anim_timer * 1 && !right_facing)
				{
					sprite.setTexture(idle_left2);
				}
				else if (animation_ticker == anim_timer * 2 && !right_facing)
				{
					sprite.setTexture(idle_left3);
				}
				else if (animation_ticker == anim_timer * 3 && !right_facing)
				{
					sprite.setTexture(idle_left4);
				}
				else if (animation_ticker == anim_timer * 4 && !right_facing)
				{
					sprite.setTexture(idle_left5);
				}
				else if (animation_ticker == anim_timer * 5 && !right_facing)
				{
					sprite.setTexture(idle_left6);
				}
				else if (animation_ticker == anim_timer * 0 && right_facing)
				{
					sprite.setTexture(idle_right1);
				}
				else if (animation_ticker == anim_timer * 1 && right_facing)
				{
					sprite.setTexture(idle_right2);
				}
				else if (animation_ticker == anim_timer * 2 && right_facing)
				{
					sprite.setTexture(idle_right3);
				}
				else if (animation_ticker == anim_timer * 3 && right_facing)
				{
					sprite.setTexture(idle_right4);
				}
				else if (animation_ticker == anim_timer * 4 && right_facing)
				{
					sprite.setTexture(idle_right5);
				}
				else if (animation_ticker == anim_timer * 5 && right_facing)
				{
					sprite.setTexture(idle_right6);
				}
				else if (animation_ticker == anim_timer * 6 && !right_facing)
				{
					sprite.setTexture(idle_left1);
					animation_ticker = 0;
				}
				else if (animation_ticker == anim_timer * 6 && right_facing)
				{
					sprite.setTexture(idle_right1);
					animation_ticker = 0;
				}

			}
			else
			{
				if (right_facing)
				{
					if (animation_ticker == anim_timer * 0)
					{
						sprite.setTexture(right1);
					}
					else if (animation_ticker == anim_timer * 1)
					{
						sprite.setTexture(right2);
					}
					else if (animation_ticker == anim_timer * 2)
					{
						sprite.setTexture(right3);
					}
					else if (animation_ticker == anim_timer * 3)
					{
						sprite.setTexture(right4);
					}
					else if (animation_ticker == anim_timer * 4)
					{
						sprite.setTexture(right5);
					}
					else if (animation_ticker == anim_timer * 5)
					{
						sprite.setTexture(right6);
					}
					else if (animation_ticker == anim_timer * 6)
					{
						sprite.setTexture(right1);
						animation_ticker = 0;
					}
				}
				else
				{
					if (animation_ticker == anim_timer * 0)
					{
						sprite.setTexture(left1);
					}
					else if (animation_ticker == anim_timer * 1)
					{
						sprite.setTexture(left2);
					}
					else if (animation_ticker == anim_timer * 2)
					{
						sprite.setTexture(left3);
					}
					else if (animation_ticker == anim_timer * 3)
					{
						sprite.setTexture(left4);
					}
					else if (animation_ticker == anim_timer * 4)
					{
						sprite.setTexture(left5);
					}
					else if (animation_ticker == anim_timer * 5)
					{
						sprite.setTexture(left6);
					}
					else if (animation_ticker == anim_timer * 6)
					{
						sprite.setTexture(left1);
						animation_ticker = 0;
					}
				}
			}

			//if left, move left
			if (left)
			{
				int coll_x = left_collider.x;
				int coll_y = left_collider.y;
				int left_tile_type = tilemaps[(coll_x) / 100][(coll_y) / 100].type;
				//if left_collider isn't in a tile.type 0
				if (left_tile_type == 1)
				{
					x -= speed;
				}

			}
			//if right, move right
			if (right)
			{
				int coll_x = right_collider.x;
				int coll_y = right_collider.y;
				int right_tile_type = tilemaps[(coll_x) / 100][(coll_y) / 100].type;
				//if right_collider isn't in a tile.type 0
				if (right_tile_type == 1)
				{
					x += speed;
				}
			}
			//if up, move up
			if (up)
			{
				int coll_x = up_collider.x;
				int coll_y = up_collider.y;
				int up_tile_type = tilemaps[(coll_x) / 100][(coll_y) / 100].type;
				//if up_collider isn't in a tile.type 0
				if (up_tile_type == 1 || up_tile_type == 3)
				{
					y -= speed;
				}
			}
			//if down, move down
			if (down)
			{
				int coll_x = down_collider.x;
				int coll_y = down_collider.y;
				int down_tile_type = tilemaps[(coll_x) / 100][(coll_y) / 100].type;
				//if down_collider isn't in a tile.type 0
				if (down_tile_type == 1 || down_tile_type == 3)
				{
					y += speed;
				}

			}
		}

		
	}

	bool collision(int x, int y)
	{
		//if x and y is within 25 of the enemy.x and enemy.y, collide = true;
		if (x >= this->x - 25 && x <= this->x + 25 && y >= this->y - 25 && y <= this->y + 25)
			return true;
		else
			return false;
	}
};

class Enemy
{
public:
	int x;
	int y;
	int power;
	int direction;
	int health;
	int speed;
	int type;

	bool left;
	bool right;
	bool up;
	bool down;
	bool paused;


	//store four textures to animate from, as well as it's animation_ticker
	sf::Texture left1;
	sf::Texture left2;
	sf::Texture left3;
	sf::Texture left4;
	sf::Texture left5;
	sf::Texture left6;

	sf::Texture right1;
	sf::Texture right2;
	sf::Texture right3;
	sf::Texture right4;
	sf::Texture right5;
	sf::Texture right6;

	sf::Texture idle_left1;
	sf::Texture idle_left2;
	sf::Texture idle_left3;
	sf::Texture idle_left4;
	sf::Texture idle_left5;
	sf::Texture idle_left6;


	sf::Texture idle_right1;
	sf::Texture idle_right2;
	sf::Texture idle_right3;
	sf::Texture idle_right4;
	sf::Texture idle_right5;
	sf::Texture idle_right6;


	sf::Sprite sprite;
	int animation_ticker;
	bool right_facing;
	bool idle;
	bool facing;
	int anim_timer;
	sf::Vector2f left_collider;
	sf::Vector2f right_collider;
	sf::Vector2f up_collider;
	sf::Vector2f down_collider;


	Enemy(int x, int y, int type)
	{
		this->paused = false;
		this->x = x;
		this->y = y;
		this->power = 0;
		this->direction = 0;
		this->health = 5;
		this->speed = 10;
		this->type = type;
		this->left = false;
		this->right = false;
		this->up = false;
		this->down = false;
		this->facing = false;
		this->anim_timer = 5;
		this->left_collider = sf::Vector2f(x - 25, y);
		this->right_collider = sf::Vector2f(x + 25, y);
		this->up_collider = sf::Vector2f(x, y - 25);
		this->down_collider = sf::Vector2f(x, y + 25);

		if (type == 0)
		{

			health = 10;
			speed = 1;


			left1.loadFromFile("assets/spider/walk_left1.png");
			left2.loadFromFile("assets/spider/walk_left2.png");
			left3.loadFromFile("assets/spider/walk_left3.png");
			left4.loadFromFile("assets/spider/walk_left4.png");
			left5.loadFromFile("assets/spider/walk_left5.png");
			left6.loadFromFile("assets/spider/walk_left6.png");

			right1.loadFromFile("assets/spider/walk_right1.png");
			right2.loadFromFile("assets/spider/walk_right2.png");
			right3.loadFromFile("assets/spider/walk_right3.png");
			right4.loadFromFile("assets/spider/walk_right4.png");
			right5.loadFromFile("assets/spider/walk_right5.png");
			right6.loadFromFile("assets/spider/walk_right6.png");

			idle_left1.loadFromFile("assets/spider/idle_left1.png");
			idle_left2.loadFromFile("assets/spider/idle_left2.png");
			idle_left3.loadFromFile("assets/spider/idle_left3.png");
			idle_left4.loadFromFile("assets/spider/idle_left4.png");
			idle_left5.loadFromFile("assets/spider/idle_left5.png");
			idle_left6.loadFromFile("assets/spider/idle_left6.png");

			idle_right1.loadFromFile("assets/spider/idle_right1.png");
			idle_right2.loadFromFile("assets/spider/idle_right2.png");
			idle_right3.loadFromFile("assets/spider/idle_right3.png");
			idle_right4.loadFromFile("assets/spider/idle_right4.png");
			idle_right5.loadFromFile("assets/spider/idle_right5.png");
			idle_right6.loadFromFile("assets/spider/idle_right6.png");
		}
		if (type == 1)
		{
			
			health = 5;
			speed = 2;
			
			left1.loadFromFile("assets/eye/walk_left1.png");
			left2.loadFromFile("assets/eye/walk_left2.png");
			left3.loadFromFile("assets/eye/walk_left3.png");
			left4.loadFromFile("assets/eye/walk_left4.png");
			left5.loadFromFile("assets/eye/walk_left5.png");
			left6.loadFromFile("assets/eye/walk_left6.png");

			right1.loadFromFile("assets/eye/walk_right1.png");
			right2.loadFromFile("assets/eye/walk_right2.png");
			right3.loadFromFile("assets/eye/walk_right3.png");
			right4.loadFromFile("assets/eye/walk_right4.png");
			right5.loadFromFile("assets/eye/walk_right5.png");
			right6.loadFromFile("assets/eye/walk_right6.png");

			idle_left1.loadFromFile("assets/eye/idle_left1.png");
			idle_left2.loadFromFile("assets/eye/idle_left2.png");
			idle_left3.loadFromFile("assets/eye/idle_left3.png");
			idle_left4.loadFromFile("assets/eye/idle_left4.png");
			idle_left5.loadFromFile("assets/eye/idle_left5.png");
			idle_left6.loadFromFile("assets/eye/idle_left6.png");

			idle_right1.loadFromFile("assets/eye/idle_right1.png");
			idle_right2.loadFromFile("assets/eye/idle_right2.png");
			idle_right3.loadFromFile("assets/eye/idle_right3.png");
			idle_right4.loadFromFile("assets/eye/idle_right4.png");
			idle_right5.loadFromFile("assets/eye/idle_right5.png");
			idle_right6.loadFromFile("assets/eye/idle_right6.png");
		}


		sprite.setTexture(left1);
		sprite.setPosition(x, y);
		animation_ticker = 0;
		right_facing = false;
		idle = true;


	}

	void draw(sf::RenderWindow& window)
	{

		//scale sprite to 3/4th it's size

		//sprite.setOrigin to exact center of sprite texture
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
		sprite.setPosition(x, y);
		window.draw(sprite);


	}



	void update(vector<vector<Tile>> tilemaps, int target_x, int target_y)
	{
		if (x < 150)
			x = 150;
		if (x > window_width - 150)
			x = window_width - 150;
		if (y < 150)
			y = 150;
		if (y > window_height - 150)
			y = window_height - 150;
		
		if (target_x < x)
		{
			left = true;
			right_facing = false;
		}
		else
			left = false;
		
		
		if (target_x > x)
		{
			right = true;
			right_facing = true;
		}
		else
			right = false;
		
		
		if (target_y < y)
			up = true;
		else
			up = false;
		
		
		if (target_y > y)
			down = true;
		else
			down = false;

		
		if (!paused)
		{
			animation_ticker++;
			if (idle)
			{
				if (animation_ticker == anim_timer * 0 && !right_facing)
				{
					sprite.setTexture(idle_left1);
				}
				else if (animation_ticker == anim_timer * 1 && !right_facing)
				{
					sprite.setTexture(idle_left2);
				}
				else if (animation_ticker == anim_timer * 2 && !right_facing)
				{
					sprite.setTexture(idle_left3);
				}
				else if (animation_ticker == anim_timer * 3 && !right_facing)
				{
					sprite.setTexture(idle_left4);
				}
				else if (animation_ticker == anim_timer * 4 && !right_facing)
				{
					sprite.setTexture(idle_left5);
				}
				else if (animation_ticker == anim_timer * 5 && !right_facing)
				{
					sprite.setTexture(idle_left6);
				}
				else if (animation_ticker == anim_timer * 0 && right_facing)
				{
					sprite.setTexture(idle_right1);
				}
				else if (animation_ticker == anim_timer * 1 && right_facing)
				{
					sprite.setTexture(idle_right2);
				}
				else if (animation_ticker == anim_timer * 2 && right_facing)
				{
					sprite.setTexture(idle_right3);
				}
				else if (animation_ticker == anim_timer * 3 && right_facing)
				{
					sprite.setTexture(idle_right4);
				}
				else if (animation_ticker == anim_timer * 4 && right_facing)
				{
					sprite.setTexture(idle_right5);
				}
				else if (animation_ticker == anim_timer * 5 && right_facing)
				{
					sprite.setTexture(idle_right6);
				}
				else if (animation_ticker == anim_timer * 6 && !right_facing)
				{
					sprite.setTexture(idle_left1);
					animation_ticker = 0;
				}
				else if (animation_ticker == anim_timer * 6 && right_facing)
				{
					sprite.setTexture(idle_right1);
					animation_ticker = 0;
				}

			}
			else
			{
				if (right_facing)
				{
					if (animation_ticker == anim_timer * 0)
					{
						sprite.setTexture(right1);
					}
					else if (animation_ticker == anim_timer * 1)
					{
						sprite.setTexture(right2);
					}
					else if (animation_ticker == anim_timer * 2)
					{
						sprite.setTexture(right3);
					}
					else if (animation_ticker == anim_timer * 3)
					{
						sprite.setTexture(right4);
					}
					else if (animation_ticker == anim_timer * 4)
					{
						sprite.setTexture(right5);
					}
					else if (animation_ticker == anim_timer * 5)
					{
						sprite.setTexture(right6);
					}
					else if (animation_ticker == anim_timer * 6)
					{
						sprite.setTexture(right1);
						animation_ticker = 0;
					}
				}
				else
				{
					if (animation_ticker == anim_timer * 0)
					{
						sprite.setTexture(left1);
					}
					else if (animation_ticker == anim_timer * 1)
					{
						sprite.setTexture(left2);
					}
					else if (animation_ticker == anim_timer * 2)
					{
						sprite.setTexture(left3);
					}
					else if (animation_ticker == anim_timer * 3)
					{
						sprite.setTexture(left4);
					}
					else if (animation_ticker == anim_timer * 4)
					{
						sprite.setTexture(left5);
					}
					else if (animation_ticker == anim_timer * 5)
					{
						sprite.setTexture(left6);
					}
					else if (animation_ticker == anim_timer * 6)
					{
						sprite.setTexture(left1);
						animation_ticker = 0;
					}
				}
			}

			//if left, move left
			if (left)
			{
				int coll_x = left_collider.x;
				int coll_y = left_collider.y;
				int left_tile_type = tilemaps[(coll_x) / 100][(coll_y) / 100].type;
				//if left_collider isn't in a tile.type 0
				if (left_tile_type ==1)
				{
					x -= speed;
				}

			}
			//if right, move right
			if (right)
			{
				int coll_x = right_collider.x;
				int coll_y = right_collider.y;
				int right_tile_type = tilemaps[(coll_x) / 100][(coll_y) / 100].type;
				//if right_collider isn't in a tile.type 0
				if (right_tile_type == 1)
				{
					x += speed;
				}
			}
			//if up, move up
			if (up)
			{
				int coll_x = up_collider.x;
				int coll_y = up_collider.y;
				int up_tile_type = tilemaps[(coll_x) / 100][(coll_y) / 100].type;
				//if up_collider isn't in a tile.type 0
				if (up_tile_type == 1)
				{
					y -= speed;
				}
			}
			//if down, move down
			if (down)
			{
				int coll_x = down_collider.x;
				int coll_y = down_collider.y;
				int down_tile_type = tilemaps[(coll_x) / 100][(coll_y) / 100].type;
				//if down_collider isn't in a tile.type 0
				if (down_tile_type == 1)
				{
					y += speed;
				}

			}
		}


	}

	bool collision(int x, int y)
	{
		//if x and y is within 25 of the enemy.x and enemy.y, collide = true;
		if (x >= this->x - 25 && x <= this->x + 25 && y >= this->y - 25 && y <= this->y + 25)
			return true;
		else
			return false;
	}
};


class Room
{
public:
	int number;
	int first_door;
	int second_door;
	int monsters_amount;
	bool locked;
	vector<vector<Tile>> room_mapped_out;

	Room(int number, int first_door, int second_door, int monsters_amount)
	{
		this->number = number;
		this->first_door = first_door;
		this->second_door = second_door;
		this->monsters_amount = monsters_amount;
		this->locked = true;

		for (int i = 0; i < map_width; i++)
		{
			vector<Tile> row;
			for (int j = 0; j < map_height; j++)
			{
				if (i == 0 || j == 0 || i == map_width - 1 || j == map_height - 1)
				{
					row.push_back(Tile(i * 100 + 10, j * 100 + 60, 0));

				}

				else
					row.push_back(Tile(i * 100 + 10, j * 100 + 60, 1));
			}
			room_mapped_out.push_back(row);
		}
		room_mapped_out[9][0].type = 2;
		
		first_door = 9;
		//room_mapped_out[9][room_mapped_out[0].size() - 1].type = 2;




	}

	Room(vector<vector<Tile>> current_tilemaps, int monsters_amount, vector<Enemy> enemies_list)
	{
		for (int i = 0; i < map_width; i++)
		{
			vector<Tile> row;
			for (int j = 0; j < map_height; j++)
			{
				if (i == 0 || j == 0 || i == map_width - 1 || j == map_height - 1)
				{
					row.push_back(Tile(i * 100 + 10, j * 100 + 60, 0));

				}

				else
					row.push_back(Tile(i * 100 + 10, j * 100 + 60, 1));
			}
			room_mapped_out.push_back(row);
		}
		locked = true;
		first_door = ((rand() % (current_tilemaps.size() - 2)) + 1);
		second_door = ((rand() % (current_tilemaps.size() - 2)) + 1);
		
		room_mapped_out[first_door][0].type = 2;

		for (int i = 0; i < room / 2; i++)
		{
			int x = ((rand() % (current_tilemaps.size() - 4)) + 2);
			int y = ((rand() % (current_tilemaps[0].size() - 4)) + 2);
			if (x != 0 && y != 0 && x != current_tilemaps.size() - 1 && y != current_tilemaps[0].size() - 1)
			{
				room_mapped_out[x][y].type = 4;
			}
		}
		
		room_mapped_out[second_door][room_mapped_out[0].size() - 1].type = 2;
		
	}





};

class Bullet
{
public:
	int x;
	int y;
	int direction;
	int type;
	int damage;
	bool shot;
	int speed;
	int ticker;
	int max_distance;
	sf::Texture texture;
	sf::Sprite sprite;

	Bullet(int x, int y, int direction, int type)
	{
		this->x = x;
		this->y = y;
		this->direction = direction;
		this->type = type;
		this->damage = 1;
		this->shot = false;
		this->speed = 30;
		this->texture = sf::Texture();
		this->sprite = sf::Sprite();
		this->ticker = 0;
		this->max_distance = 10;

	}

	void set_texture(sf::Texture texture)
	{
		this->texture = texture;
		sprite.setTexture(texture);
	}

	void draw(sf::RenderWindow& window)
	{
		sprite.setOrigin(10, 10);
		sprite.setPosition(x, y);
		window.draw(sprite);
	}

	void update()
	{
		if (shot)
		{
			ticker++;
			if (direction == 0)
				y -= speed;
			else if (direction == 1)
				y += speed;
			else if (direction == 2)
				x -= speed;
			else if (direction == 3)
				x += speed;
		}
		
		if (x < 130 || y < 150 || y > 900 || x > 1800)
		{
			shot = false;
			ticker = 0;
		}
		if (ticker > max_distance)
		{
			shot = false;
			ticker = 0;
		}
			

	}
};



vector<vector<Tile>> current_tilemap;
vector<Player> players;
vector<Room> room_map;
vector<Enemy> enemies;
vector<Bullet> bullets;
int alpha_ticker = 0;
bool alpha_increase = false;
bool shooting_up = false;
bool shooting_down = false;
bool shooting_left = false;
bool shooting_right = false;

int main()
{
//set up window
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "rogue_test", sf::Style::Fullscreen);
	//window.setPosition(sf::Vector2i(-1920, 40));
	sf::Event event;
	sf::Font font;
	font.loadFromFile("assets/Cascadia.ttf");

	sf::Text room_number;
	room_number.setCharacterSize(800);
	room_number.setFillColor(sf::Color(0, 0, 0, 100));
	room_number.setFont(font);
	

//load textures
	sf::Texture wall_tile_1;
	wall_tile_1.loadFromFile("assets/tiles/wall_1.png");

	sf::Texture floor_tile_1;
	floor_tile_1.loadFromFile("assets/tiles/floor_1.png");

	sf::Texture door_closed;
	door_closed.loadFromFile("assets/tiles/door1.png");
	
	sf::Texture door_open;
	door_open.loadFromFile("assets/tiles/door2.png");

	sf::Texture bullet_texture_heavy;
	bullet_texture_heavy.loadFromFile("assets/bullets/bullet_heavy.png");
	
	sf::Texture heart_texture_1;
	heart_texture_1.loadFromFile("assets/hearts/heart_1.png");




	room_map.push_back(Room(room, 9, 9, 0));
	current_tilemap = room_map[room].room_mapped_out;
	
	




	players.push_back(Player(960, 510));
	bullets.push_back(Bullet(players[0].x, players[0].y, 0, 0));
	bullets[0].sprite.setTexture(bullet_texture_heavy);
	
//look for events while the window is open
	while (window.isOpen())
	{
		room_number.setString(to_string(room));
		if (gamestate == 1)
		{
			//if player.x,player.y is inside a tile.type 3, generate_room
			if (current_tilemap[(players[0].x) / 100][(players[0].y) / 100].type == 3)
			{
				if (players[0].y < window_height / 2)
				{
					room_map.push_back(Room(current_tilemap, (rand() % 3) + 1, enemies));
					room_changing = true;
					room++;
					for (int i = 0; i < room; i++)
						enemies.push_back(Enemy((rand() % 1700) + 100, (rand() % 800) + 100, rand()%2 ));
					players[0].x = room_map[room].second_door*100+60;
					players[0].y = 870;
				}
				else
				{
					room--;
					room_changing = true;
					players[0].x = room_map[room].first_door * 100+60;
					players[0].y = 130;
				}
				
			}

			if (room_changing)
			{
				if (!alpha_increase && alpha_ticker == 0)
				{
					alpha_increase = true;
					players[0].paused = true;
				}
					
				if (alpha_increase)
					alpha_ticker += 20;
				if (alpha_ticker == 240)
					alpha_increase = false;
				if (!alpha_increase && alpha_ticker > 0)
					alpha_ticker -= 20;
				current_tilemap = room_map[room].room_mapped_out;
				//if tile.type == 0, set texture to pillar, else set texture to floor
				for (int i = 0; i < current_tilemap.size(); i++)
				{
					for (int j = 0; j < current_tilemap[i].size(); j++)
					{
						if (current_tilemap[i][j].type == 0)
							current_tilemap[i][j].sprite.setTexture(wall_tile_1);
						else if (current_tilemap[i][j].type == 2)
							current_tilemap[i][j].sprite.setTexture(door_closed);
						else if (current_tilemap[i][j].type == 3)
							current_tilemap[i][j].sprite.setTexture(door_open);
						else
							current_tilemap[i][j].sprite.setTexture(floor_tile_1);
					}
				}
				if (alpha_ticker == 0)
				{
					room_changing = false;
					players[0].paused = false;
				}
					
			}
			if (room_map[room].locked == false)
			{
				//if tile.type == 0, set texture to pillar, else set texture to floor
				for (int i = 0; i < current_tilemap.size(); i++)
				{
					for (int j = 0; j < current_tilemap[i].size(); j++)
					{
						if (current_tilemap[i][j].type == 2)
						{
							
							current_tilemap[i][j].type = 3;
							room_map[room].room_mapped_out[i][j].type = 3;
							current_tilemap[i][j].sprite.setTexture(door_open);
							room_map[room].room_mapped_out[i][j].sprite.setTexture(door_open);

							
						}
					}
				}
			}

			players[0].left_collider = sf::Vector2f(players[0].x - 50, players[0].y);
			players[0].right_collider = sf::Vector2f(players[0].x + 25, players[0].y);
			players[0].up_collider = sf::Vector2f(players[0].x, players[0].y - 30);
			players[0].down_collider = sf::Vector2f(players[0].x, players[0].y + 10);

			for (int i = 0; i < enemies.size(); i++)
			{
				enemies[i].left_collider = sf::Vector2f(enemies[i].x - 50, enemies[i].y);
				enemies[i].right_collider = sf::Vector2f(enemies[i].x + 25, enemies[i].y);
				enemies[i].up_collider = sf::Vector2f(enemies[i].x, enemies[i].y - 40);
				enemies[i].down_collider = sf::Vector2f(enemies[i].x, enemies[i].y + 10);
			}

			if (shooting_up)
			{
				bullets[0].direction = 0;
				bullets[0].shot = true;
			}
			if (shooting_down)
			{
				bullets[0].direction = 1;
				bullets[0].shot = true;
			}
			if (shooting_left)
			{
				bullets[0].direction = 2;
				bullets[0].shot = true;
			}
			if (shooting_right)
			{
				bullets[0].direction = 3;
				bullets[0].shot = true;
			}

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape)
						window.close();
					//wasd
					if (event.key.code == sf::Keyboard::W)
					{
						players[0].up = true;
						players[0].idle = false;
					}
					if (event.key.code == sf::Keyboard::S)
					{
						players[0].down = true;
						players[0].idle = false;
					}
					if (event.key.code == sf::Keyboard::A)
					{
						players[0].left = true;
						players[0].idle = false;
						players[0].right_facing = false;
					}
					if (event.key.code == sf::Keyboard::D)
					{
						players[0].right = true;
						players[0].idle = false;
						players[0].right_facing = true;
					}
					//if return is pressed
					if (event.key.code == sf::Keyboard::Return)
					{

						room_map[room].locked = false;
						
					}
					if (event.key.code == sf::Keyboard::Space)
					{
						cout << players[0].x << ", " << players[0].y << endl;
					}

					//numpad 8546 for bullets shooting direction 0123
					
					if (event.key.code == sf::Keyboard::Numpad8)
					{
						
							shooting_up = true;
							shooting_down = false;
							shooting_left = false;
							shooting_right = false;
						
						
					}
					else if (event.key.code == sf::Keyboard::Numpad5)
					{
						
							shooting_up = false;
							shooting_down = true;
							shooting_left = false;
							shooting_right = false;
						
					}
					else if (event.key.code == sf::Keyboard::Numpad4)
					{
						
							shooting_up = false;
							shooting_down = false;
							shooting_left = true;
							shooting_right = false;
						
					}
					else if (event.key.code == sf::Keyboard::Numpad6)
					{
						
							shooting_up = false;
							shooting_down = false;
							shooting_left = false;
							shooting_right = true;
						
					}
				}
				//if none of wasd are pressed, idle = true;
				if (event.type == sf::Event::KeyReleased)
				{
					//if w is released and no other keys are pressed
					if (event.key.code == sf::Keyboard::W)
					{
						players[0].up = false;
						if (!players[0].down && !players[0].left && !players[0].right)
							players[0].idle = true;
					}
					//if s is released and no other keys are pressed
					if (event.key.code == sf::Keyboard::S)
					{
						players[0].down = false;
						if (!players[0].up && !players[0].left && !players[0].right)
							players[0].idle = true;
					}
					//if a is released and no other keys are pressed
					if (event.key.code == sf::Keyboard::A)
					{
						players[0].left = false;
						if (!players[0].up && !players[0].down && !players[0].right)
							players[0].idle = true;
					}
					//if d is released and no other keys are pressed
					if (event.key.code == sf::Keyboard::D)
					{
						players[0].right = false;
						if (!players[0].up && !players[0].down && !players[0].left)
							players[0].idle = true;
					}
					
					if (event.key.code == sf::Keyboard::Numpad8)
					{
						shooting_up = false;
						
					}
					else if (event.key.code == sf::Keyboard::Numpad5)
					{
						shooting_down = false;
					}
					else if (event.key.code == sf::Keyboard::Numpad4)
					{
						shooting_left = false;
					}
					else if (event.key.code == sf::Keyboard::Numpad6)
					{
						shooting_right = false;
					}
					
					
				}

			}
			//clear the window /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			window.clear(sf::Color(0,0,0));
			
			//get tile players[0] is in
			int tile_x = players[0].x / 100;
			int tile_y = players[0].y / 100;

			for (int i = 0; i < current_tilemap.size(); i++)
			{
				for (int j = 0; j < current_tilemap[i].size(); j++)
				{
					//only draw if in view of window
					if (current_tilemap[i][j].type == 1)
						current_tilemap[i][j].draw(window);
					if (current_tilemap[i][j].type == 2 && j < tile_y)
						current_tilemap[i][j].draw(window);
					if (current_tilemap[i][j].type == 3 && j < tile_y)
						current_tilemap[i][j].draw(window);
					//only draw if in view of window
					if (current_tilemap[i][j].type == 0 && j < tile_y)
						current_tilemap[i][j].draw(window);

				}
			}

			

			room_number.setPosition(window_width/2-room_number.getGlobalBounds().width/2-50, 0);
			window.draw(room_number);




			//for enemy in enemies
			for (int i = 0; i < enemies.size(); i++)
			{
				enemies[i].update(current_tilemap, players[0].x,players[0].y);
				enemies[i].draw(window);
			}


			
			if (enemies.size() > 0)
			{


				//draw enemies
				for (int i = 0; i < enemies.size(); i++)
				{
					enemies[i].draw(window);
					//if bullets collide with enemy, lower health by 1
					for (int j = 0; j < bullets.size(); j++)
					{
						if (bullets[j].shot && enemies[i].collision(bullets[j].x, bullets[j].y))
						{
							enemies[i].health--;
							bullets[j].shot = false;
						}
						//if health < 1, remove from vector
						if (enemies[i].health < 1)
						{
							//remove enemy[i] from enemies
							enemies.erase(enemies.begin() + i);
							
						}
						
					}
				}
			}
			
			//for bullet in bullets
			for (int i = 0; i < bullets.size(); i++)
			{
				if (bullets[i].shot == false)
				{
					bullets[i].x = players[0].x;
					bullets[i].y = players[0].y;
				}
					
				
				bullets[i].update();
				bullets[i].draw(window);
			}

			players[0].update(current_tilemap);
			players[0].draw(window);

			for (int i = 0; i < map_width; i++)
			{
				for (int j = 0; j < map_height; j++)
				{
					//only draw if in view of window
					if (current_tilemap[i][j].type == 0 && j >= tile_y)
						current_tilemap[i][j].draw(window);
					if (current_tilemap[i][j].type == 2 && j >= tile_y)
						current_tilemap[i][j].draw(window);
					if (current_tilemap[i][j].type == 3 && j >= tile_y)
						current_tilemap[i][j].draw(window);

				}
			}


			

			if (room_changing)
				window.clear(sf::Color(0, 0, 0, alpha_ticker));
			
			if (enemies.size() == 0)
				room_map[room].locked = false;

			//health display
			for (int i = 0; i < players[0].health; i++)
			{

				sf::Sprite heart_sprite;

				heart_sprite.setTexture(heart_texture_1);
				heart_sprite.setPosition(i * 80 + 10, 10);

				window.draw(heart_sprite);
			}

			//draw the window////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			window.setFramerateLimit(60);
			window.display();
		}
	}

	
	

//return okay if the program exits properly
    return 0;
}