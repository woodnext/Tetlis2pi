#include "Field.h"

Field::Field(int x, int y) : Blocks({ x, y }, FIELD_ASIDE_X, FIELD_ASIDE_Y, BLOCK_SIZE)
{
	int i, j;
	for (i = 0; i < FIELD_ASIDE_Y; i++) {
		for (j = 0; j < FIELD_ASIDE_X; j++) {
			if ((j == 0 || j == FIELD_ASIDE_X - 1 || i == 0 || i == FIELD_ASIDE_Y - 1)) {
				this->layout[i][j] = -1;
			}
		}
	}
	color = GetColor(255, 255, 255);
	grid_color = GetColor(64, 64, 64);
}

void Field::InitField()
{
	int i, j;
	for (i = 0; i < FIELD_ASIDE_Y; i++) {
		for (j = 0; j < FIELD_ASIDE_X; j++) {
			if ((j == 0 || j == FIELD_ASIDE_X - 1 || i == 0 || i == FIELD_ASIDE_Y - 1)) {
				this->layout[i][j] = -1;
			}
			else {
				this->layout[i][j] = 0;
			}
		}
	}
}

bool Field::judgeLineFull(int line_num)
{
	int i = 1;
	while (layout[line_num][i] != 0) {
		if (i == FIELD_SIDE_X)
			return true;
		i++;
	}
	return false;
}

void Field::OneLineErase(int line_num)
{
	for (int i = 1; i <= FIELD_SIDE_X; i++) {
		this->layout[line_num][i] = 0;
	}
}

void Field::shiftLine(int line_num)
{
	int i, j;
	int tmpline[FIELD_SIDE_X + 1] = { 0 };
	for (i = line_num; i > 0; i--) {
		for (j = 1; j <= FIELD_SIDE_X; j++) {
			tmpline[j] = layout[i - 1][j];
			layout[i][j] = 0;
			layout[i - 1][j] = 0;
			layout[i][j] = tmpline[j];
		}
	}
}

/// <summary>
/// ��̏����ƈړ�
/// </summary>
/// <returns>����������̐�</returns>
int Field::LineEraseAndShift()
{
	int erase_linenum = 0;
	for (int i = 1; i <= FIELD_SIDE_Y; i++) {
		if (judgeLineFull(i)) {
			OneLineErase(i);
			shiftLine(i);
			erase_linenum++;
		}
	}
	return erase_linenum;
}

/// <summary>
/// �t�B�[���h�z���x�v�f���E�B���h�Ex���W�ɕϊ�
/// </summary>
/// <param name="elem_x">�t�B�[���h�z���x�v�f</param>
/// <returns>�E�B���h�Ex���W</returns>
int Field::elemXToCoordX(int elem_x)
{
	return window.x + elem_x * block_size();
}

/// <summary>
/// �t�B�[���h�z���y�v�f���E�B���h�Ey���W�ɕϊ�
/// </summary>
/// <param name="elem_y">�t�B�[���h�z���y�v�f</param>
/// <returns>�E�B���h�Ey���W</returns>
int Field::elemYToCoordY(int elem_y)
{
	return window.y + elem_y * block_size();
}

/// <summary>
/// �E�B���h�Ex���W���t�B�[���h�z���x�v�f�ɕϊ�
/// </summary>
/// <param name="coord_x">�E�B���h�Ex���W</param>
/// <returns>�t�B�[���h�z���x�v�f</returns>
int Field::coordXToElemX(int x)
{
	int size = block_size();
	return (x - window.x) / size;
}

/// <summary>
/// �E�B���h�Ey���W���t�B�[���h�z���y�v�f�ɕϊ�
/// </summary>
/// <param name="coord_y">�E�B���h�Ey���W</param>
/// <returns>�t�B�[���h�z���y�v�f</returns>
int Field::coordYToElemY(int y)
{
	int size = block_size();
	return (y - window.y) / size;
}

/// <summary>
/// �w��z��v�f�̃t�B�[���h�̒l��Ԃ�
/// </summary>
/// <param name="elem_x">�t�B�[���h�z���x�v�f</param>
/// <param name="elem_y">�t�B�[���h�z���y�v�f</param>
/// <returns></returns>
int Field::getFieldValue(int elem_x, int elem_y)
{
	if (elem_x < 0 || elem_x > FIELD_ASIDE_X || elem_y < 0 || elem_y > FIELD_ASIDE_Y) return -1;
	else return this->layout[elem_y][elem_x];
}

/// <summary>
/// �t�B�[���h�̎w��z��v�f�ɒl����������
/// </summary>
/// <param name="elem_x">�t�B�[���h�z���x�v�f</param>
/// <param name="elem_y">�t�B�[���h�z���y�v�f</param>
/// <param name="value">�������ޒl</param>
void Field::setFieldValue(int elem_x, int elem_y, int value)
{
	layout[elem_y][elem_x] = value;
}

/// <summary>
/// �t�B�[���h�̎w��v�f�Ƀ~�m�����݂��邩����
/// </summary>
/// <param name="elem_x">�@�t�B�[���h�z���x�v�f</param>
/// <param name="elem_y">�@�t�B�[���h�z���y�v�f</param>
/// <returns>
/// �~�m�����݂��� true�@�~�m�����݂��Ȃ� false
/// </returns>
bool Field::containMino(int elem_x, int elem_y)
{
	if (this->layout[elem_y][elem_x] > 0)return true;
	else return false;
}

void Field::drawField()
{
	int i, j;

	for (i = 5; i <= FIELD_SIDE_Y; i++) {
		for (j = 1; j <= FIELD_SIDE_X; j++) {
			DrawBox(this->window.x + block_size() * j, this->window.y + block_size() * i,
				this->window.x + block_size() * (j + 1), window.y + block_size() * (i + 1), GetColor(0, 0, 0), TRUE);
			if (this->layout[i][j] > 0) {
				DrawBox(window.x + block_size() * j, window.y + block_size() * i,
					window.x + block_size() * (j + 1) - 1, window.y + block_size() * (i + 1) - 1, selectColor(this->layout[i][j]), TRUE);
			}
			else if(this->layout[i][j] == -1){
				DrawBox(window.x + block_size() * j, window.y + block_size() * i,
					window.x + block_size() * (j + 1) - 1, window.y + block_size() * (i + 1) - 1, GetColor(255,255,255), TRUE);
			}
			DrawBox(window.x + block_size() * j, window.y + block_size() * i,
				window.x + block_size() * (j + 1), window.y + block_size() * (i + 1), this->grid_color, FALSE);
		}
	}
}