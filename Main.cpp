#include <iostream>

/*
   W A S D 상하좌우 이동
   벽   #
   플레이어 p  P
   상자     o  O
   목적지   .

   모든 상자를 목적지에 배치하면 종료
   상자는 밀수만 있고 당길 수는 없습니다.

   */

const char gStageData[]
{
   "\
########\n\
# .. p #\n\
# oo   #\n\
#      #\n\
########"
};

//상수는 글로벌 괜찮

const int gStageWidth = 8;
const int gStageHeight = 5;

enum Object
{
	OBJ_SPACE,
	OBJ_WALL,
	OBJ_GOAL,
	OBJ_BLOCK,
	OBJ_BLOCK_ON_GOAL,
	OBJ_PLAYER,
	OBJ_PLAYER_0N_GOAL,

	OBJ_UNKNOWN // =OBJ_MAX, OBJ_COUNT
};

void Initialize(Object* stage, int w, int h, const char* data);
void Draw(const Object* stage, int w, int h ); // 읽기전용(수정 안함) -> const로 미리미리 구분
void Update(Object* stage, char input, int w, int h );
bool IsClear(const Object* stage, int w, int h );

int main()
{
	Object* stage = new Object[ gStageWidth * gStageHeight ];
	
	Initialize(stage, gStageWidth, gStageHeight, gStageData);

	while (true)
	{
		Draw(stage, gStageWidth, gStageHeight);
		
		if (IsClear(stage, gStageWidth, gStageHeight))
		{
			break;
		}

		std::cout << " a: left, d: right w:up, s:down. command?";
		char input;
		std::cin >> input;

		Update(stage, input, gStageWidth, gStageHeight);
	}
	
	std::cout << "Congraturation! You Win!" << std::endl;

	delete[] stage;
	stage = nullptr;

}

void Initialize(Object* stage, int w, int h, const char* data)
{
	const char* p = data; // 첫번째 주소를 데이터로
	int x = 0;    // 2차배열처럼 쓰게 선언
	int y = 0; 

	while (*p != '\0') // stage를 처음부터 끝까지 쭈루룩 확인
	{
		Object t;

		switch (*p)
		{
		case '#':
			t = OBJ_WALL;
			break;
		case ' ':
			t = OBJ_SPACE;
			break;
		case 'o':
			t = OBJ_BLOCK;
			break;
		case 'O':
			t = OBJ_BLOCK_ON_GOAL;
			break;
		case '.':
			t = OBJ_GOAL;
			break;
		case 'p':
			t = OBJ_PLAYER;
			break;
		case 'P':
			t = OBJ_PLAYER_0N_GOAL;
			break;
		case '\n':
			y++;  // y가 바뀌는게 줄바꿈
			x = 0;
			t = OBJ_UNKNOWN;
			break;

		default:
			t = OBJ_UNKNOWN;
			break;
		}

		if (t != OBJ_UNKNOWN)
		{
			stage[y * w + x] == t;   // 위에서 y가 줄바꿈을 모두 하기 때문에 여기서는 x만 ++하면 됨
			x++;
		}
		p++;
	}

}

void Draw(const Object* stage, int w, int h)
{

	const char table[]{ ' ', '#','.','o','O','p','P' }; 

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++) 
		{
			Object o = stage[y * w + x];
			std::cout << table[o];
		}
		std::cout << std::endl;
	}
}

void Update(Object* stage, char input, int w, int h)
{
	int dx{}, dy{};
	switch (input)
	{
	case 'a':
		dx = -1;
		break;
	case 'd':
		dx = 1;
		break;
	case 'w':
		dy = -1;
		break;
	case 's':
		dy = 1;
		break;
	default:
		break;
	}


	// 플레이어 현재 위치

	int i{}; // i가 밖에서? 필요해서  i를 바깥에서 선언해서 씀

	for (i = 0; i < w * h; i++) {
		if(stage[i]==OBJ_PLAYER|| stage[i]==OBJ_PLAYER_0N_GOAL)
		{
			break;
		}
	}

	int x = i % w;
	int y = i / w;

	int tx = x + dx;
	int ty = y + dy;


	// 예외상황

	if (tx < 0 || ty < 0 || tx >= w || ty >= h)// 배열은 0부터 시작이니 =이 반드시 들어가야 함
	{
		std::cerr << "Invalid player position" << std::endl;
		return;
	}
}


bool IsClear(const Object* stage, int w, int h)
{
	for (int i = 0; i < w * h; i++)
	{
		if (stage[i] == OBJ_BLOCK)
		{
			return false;
		}
	}
	return true;
}
