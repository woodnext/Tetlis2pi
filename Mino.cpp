#include "Mino.h"

Mino::Mino(Field* _field) : StaticMino(0, 0, BLOCK_SIZE)
{
	field = _field;
	this->field_x = 0, this->field_y = 0;
}

void Mino::initialize()
{
	fillLayout(0);
	this->rotate_dir = 0;
}

int Mino::getMinoNum()
{
	return num - 1;
}

int Mino::getMinoCoordX()
{
	return this->window.x;
}

int Mino::getMinoCoordY()
{
	return this->window.y;
}

void Mino::generateMinoWithPos(int generate_mino_num, int field_x, int field_y)
{
	fillLayout(0);
	this->field_x = field_x, this->field_y = field_y;
	this->window.x = field->elemXToCoordX(this->field_x);
	this->window.y = field->elemYToCoordY(this->field_y);
	this->rotate_dir = 0;

	this->generateMino(generate_mino_num);
}

void Mino::rotateMinoWithCollision(bool right_flag)
{
	Mino tmp_mino = *this;
	int tmp_rota_dir = this->rotate_dir;
	tmp_mino.rotate(right_flag);

	if (!tmp_mino.collisionField()) {
		this->rotate(right_flag);
	}
	else if(tmp_mino.superRotation(tmp_rota_dir, right_flag)) {
		this->rotate(right_flag);
		this->superRotation(tmp_rota_dir, right_flag);
	}
}

bool Mino::superRotation(int dir_old, bool right_flag)
{
	//�Q�l�i�قڊۃp�N���j:http://www.terasol.co.jp/%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0/6335
	//�Q�l�Q�iI�~�m�����̎����j�Fhttps://tetrisch.github.io/main/srs.html
	int dx = 0, dy = 0;
	int dir = this->rotate_dir;

	if (this->num != 1) //I�~�m�ȊO�̏ꍇ
	{
		// 1. �������E�ɓ�����
		// 0��90�x�iB�j�̏ꍇ�͍��C-90�x�iD�j�̏ꍇ�͉E�ֈړ�
		// 0��0�x�iA�j�C180�x�iC�j�̏ꍇ�͉�]�O�̕����̋t�����ֈړ�
		switch (dir) {
		case 1:
			dx = -1;
			break;
		case 3:
			dx = 1;
			break;
		case 0:
		case 2:
			switch (dir_old){
			case 1: // ��]�O���E����
				dx = 1;
				break;
			case 3: // ��]�O��������
				dx = -1;
				break;
			}
			break;
		}
		if (this->collisionField(dx, dy)) {
			// 2.���̏�Ԃ��玲���㉺�ɓ�����
			// 0��90�x�iB�j�C-90�x�iD�j�̏ꍇ�͏�ֈړ�
			// 0��0�x�iA�j�C180�x�iC�j�̏ꍇ�͉��ֈړ�
			switch (dir){
			case 1:
			case 3:
				dy = -1;
				break;
			case 0:
			case 2:
				dy = 1;
				break;
			}
			if (this->collisionField(dx, dy)) {
				// 3.���ɖ߂��A�����㉺��2�}�X������
				// 0��90�x�iB�j�C-90�x�iD�j�̏ꍇ�͉��ֈړ�
				// 0��0�x�iA�j�C180�x�iC�j�̏ꍇ�͏�ֈړ�
				dx = 0; dy = 0;
				switch (this->rotate_dir){
				case 1:
				case 3:
					dy = 2;
					break;
				case 0:
				case 2:
					dy = -2;
					break;
				}
				if (this->collisionField(dx, dy)) {
					// 4.���̏�Ԃ��玲�����E�ɓ�����
					// 0��90�x�iB�j�̏ꍇ�͍��C-90�x�iD�j�̏ꍇ�͉E�ֈړ�
					// 0��0�x�iA�j�C180�x�iC�j�̏ꍇ�͉�]���������̋t�ֈړ�
					switch (dir)
					{
					case 1:
						dx = -1;
						break;
					case 3:
						dx = 1;
						break;
					case 0:
					case 2:
						switch (dir_old)
						{
						case 1: // ��]�O���E����
							dx = 1;
							break;
						case 3: // ��]�O��������
							dx = -1;
							break;
						}
						break;
					}
					if (this->collisionField(dx, dy))return false;
				}
			}
		}
	}
	else {
		int p1dx, p2dx;
	
		// 1. �������E�ɓ�����
		// 0��90�x�iB�j�̏ꍇ�͉E�C-90�x�iD�j�̏ꍇ�͍��ֈړ��i�g�ɂ������j
		// 0��0�x�iA�j�C180�x�iC�j�̏ꍇ�͉�]���������̋t�ֈړ� 0�x�͂Q�}�X�ړ�
		switch (dir) {
		case 1:
			if (dir_old == 0)dx = -2;
			else dx = 1;
			break;
		case 3:
			if (dir_old == 2)dx = 2;
			else dx = -1;
			break;
		case 0:
		case 2:
			switch (dir_old) {
			case 1: // ��]�O���E����
				dx = -1;
				break;
			case 3: // ��]�O��������
				dx = 1;
				break;
			}
			if (dir == 0)dx *= -2;
			break;
		}
		p1dx = dx;
		if (this->collisionField(dx, dy)) {
			// 2. �������E�ɓ�����
			// 0��90�x�iB�j�̏ꍇ�͍��C-90�x�iD�j�̏ꍇ�͉E�ֈړ��i�g�ɂ������j
			// 0��0�x�iA�j�C180�x�iC�j�̏ꍇ�͉�]���������ֈړ� 180�x�͂Q�}�X�ړ�
			switch (dir) {
			case 1:
				if (dir_old == 2)dx = -2;
				else dx = 1;
				break;
			case 3:
				if (dir_old == 0)dx = 2;
				else dx = -1;
				break;
			case 0:
			case 2:
				switch (dir_old) {
				case 1: // ��]�O���E����
					dx = -1;
					break;
				case 3: // ��]�O��������
					dx = 1;
					break;
				}
				if (dir == 2)dx *= -2;
				break;
			}
			p2dx = dx;
			if (this->collisionField(dx, dy)) {
				// 3. �����㉺�ɓ�����
				// 0��90�x�iB�j�̏ꍇ��1�����C-90�x�iD�j�̏ꍇ��1����ֈړ�
				// 0��0�x�iA�j�C180�x�iC�j�̏ꍇ��
				// ��]�O�̃~�m���E�����ɂ���iB�j�Ȃ�1�����
				// ��]�O�̃~�m���������ɂ���iD�j�Ȃ�2�����ֈړ�
				// ����]�Ȃ�Q�}�X������
				switch (dir) {
				case 1:
					dx = p1dx;
					dy = 1;
					if ((dir_old == 0 && dir == 3) || (dir_old == 3 && dir == 2) ||
						(dir_old == 2 && dir == 1) || (dir_old == 1 && dir == 0))
						dy *= 2;
					break;
				case 3:
					dx = p1dx;
					dy = -1;
					if ((dir_old == 0 && dir == 3) || (dir_old == 3 && dir == 2) ||
						(dir_old == 2 && dir == 1) || (dir_old == 1 && dir == 0))
						dy *= 2;
					break;
				case 0:
				case 2:
					switch (dir_old) {
					case 1: // ��]�O���E����
						dx = p1dx;
						dy = -1;
						break;
					case 3: // ��]�O��������
						dx = p2dx;
						dy = 1;
						break;
					}
					if ((dir_old == 3 && dir == 0) || (dir_old == 0 && dir == 1) ||
						(dir_old == 1 && dir == 2) || (dir_old == 2 && dir == 3))
						dy *= 2;
					break;
				}
				
				if (this->collisionField(dx, dy)) {
					// 4. �����㉺�ɓ�����
					// 0��90�x�iB�j�̏ꍇ��2����C-90�x�iD�j�̏ꍇ��2�����ֈړ�
					// 0��0�x�iA�j�C180�x�iC�j�̏ꍇ��
					// ��]�O�̃~�m���E�����ɂ���iB�j�Ȃ�2������
					// ��]�O�̃~�m���������ɂ���iD�j�Ȃ�1����ֈړ�
					// �E��]�Ȃ�Q�}�X������
					switch (dir) {
					case 1:
						dx = p2dx;
						dy = -1;
						if ((dir_old == 3 && dir == 0) || (dir_old == 0 && dir == 1) ||
							(dir_old == 1 && dir == 2) || (dir_old == 2 && dir == 3))
							dy *= 2;
						break;
					case 3:
						dx = p2dx;
						dy = 1;
						if ((dir_old == 3 && dir == 0) || (dir_old == 0 && dir == 1) ||
							(dir_old == 1 && dir == 2) || (dir_old == 2 && dir == 3))
							dy *= 2;
						break;
					case 0:
					case 2:
						switch (dir_old) {
						case 1: // ��]�O���E����
							dx = p2dx;
							dy = 1;
							break;
						case 3: // ��]�O��������
							dx = p1dx;
							dy = -1;
							break;
						}
						if ((dir_old == 0 && dir == 3) || (dir_old == 3 && dir == 2) ||
							(dir_old == 2 && dir == 1) || (dir_old == 1 && dir == 0))
							dy *= 2;
						break;
					}
					if (this->collisionField(dx, dy))return false;
				}
			}
		}
	}
	this->moveMino(dx, dy);
	
	return true;
}

void Mino::moveMino(int dx, int dy)
{
	this->window.x = field->elemXToCoordX(field_x += dx);
	this->window.y = field->elemYToCoordY(field_y += dy);
}

void Mino::moveMinoWithCollision(int dx, int dy)
{
	if (!this->collisionField(dx,dy)) {
		this->moveMino(dx, dy);
	}
}

void Mino::dropToMaxBottom()
{
	while (!this->collisionField(0, 1)) 
	{
		this->moveMino(0, 1);
	}
}

bool Mino::collisionField()
{
	int x, y;
	for (y = 0; y < height(); y++) {
		for (x = 0; x < width(); x++) {
			int coll_x = field->coordXToElemX(this->window.x + block_size() *x);
			int coll_y = field->coordYToElemY(this->window.y + block_size() * y);
			if (this->layout[y][x] > 0 && field->getFieldValue(coll_x, coll_y) != 0) {
				return true;
			}
		}
	}
	return false;
}

bool Mino::collisionField(int dx, int dy)
{
	int x, y;
	for (y = 0; y < height(); y++) {
		for (x = 0; x < width(); x++) {
			int coll_x = field->coordXToElemX(this->window.x + block_size() * x) + dx;
			int coll_y = field->coordYToElemY(this->window.y + block_size() * y) + dy;
			if (this->layout[y][x] > 0 && field->getFieldValue(coll_x, coll_y) != 0) {
				return true;
			}
		}
	}
	return false;
}

void Mino::transcribeMinoToField()
{
	int i, j;
	for (i = 0; i < height(); i++) {
		for (j = 0; j < width(); j++) {
			int elem_x = field->coordXToElemX(this->window.x) + j;
			int elem_y = field->coordYToElemY(this->window.y) + i;
			if (layout[i][j] != 0) {
				field->setFieldValue(elem_x, elem_y, layout[i][j]);
			}
		}
	}
}

void Mino::drawStatus()
{
	//DrawFormatString(250, 0, GetColor(255, 255, 255), "window.x:%d, window.y:%d", window.x, window.y);
	//DrawFormatString(250, 20, GetColor(255, 255, 255), "field_x:%d, field_y:%d", field_x, field_y);
	DrawFormatString(250, 30, GetColor(255, 255, 255), "rotate_dir :%d",rotate_dir);
}
