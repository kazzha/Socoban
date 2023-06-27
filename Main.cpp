#include <iostream>

/*
   W A S D �����¿� �̵�
   ��   #
   �÷��̾� p  P
   ����     o  O
   ������   .

   ��� ���ڸ� �������� ��ġ�ϸ� ����
   ���ڴ� �м��� �ְ� ��� ���� �����ϴ�.

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

//����� �۷ι� ����

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
void Draw(const Object* stage, int w, int h ); // �б�����(���� ����) -> const�� �̸��̸� ����
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
	const char* p = data; // ù��° �ּҸ� �����ͷ�
	int x = 0;    // 2���迭ó�� ���� ����
	int y = 0; 

	while (*p != '\0') // stage�� ó������ ������ �޷�� Ȯ��
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
			y++;  // y�� �ٲ�°� �ٹٲ�
			x = 0;
			t = OBJ_UNKNOWN;
			break;

		default:
			t = OBJ_UNKNOWN;
			break;
		}

		if (t != OBJ_UNKNOWN)
		{
			stage[y * w + x] == t;   // ������ y�� �ٹٲ��� ��� �ϱ� ������ ���⼭�� x�� ++�ϸ� ��
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


	// �÷��̾� ���� ��ġ

	int i{}; // i�� �ۿ���? �ʿ��ؼ�  i�� �ٱ����� �����ؼ� ��

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


	// ���ܻ�Ȳ

	if (tx < 0 || ty < 0 || tx >= w || ty >= h)// �迭�� 0���� �����̴� =�� �ݵ�� ���� ��
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
