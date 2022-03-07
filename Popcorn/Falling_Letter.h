#pragma once

#include "Active_Brick.h"

//------------------------------------------------------------------------------------------------------------
enum ELetter_Type
{
	ELT_None,

	ELT_O,  // "Отмена"
	ELT_I,  // "Инверсия"
	ELT_C,  // "Скорость"
	ELT_M,  // "Монстры"
	ELT_G,  // "Жизнь"
	ELT_K,  // "Клей"
	ELT_W,  // "Шире"
	ELT_P,  // "Пол"
	ELT_L,  // "Лазер"
	ELT_T,  // "Три"
	ELT_Plus  // Переход на следующий уровень
};
//------------------------------------------------------------------------------------------------------------

enum EFalling_Letter_State
{
	EFLS_Normal,
	EFLS_Finalizing,  // Начинаем удалять объект
	EFLS_Finished  // Когда объект можно удалять
};
//------------------------------------------------------------------------------------------------------------
class AFalling_Letter: public AGraphics_Object
{
public:
	AFalling_Letter(EBrick_Type brick_type, ELetter_Type letter_type, int x, int y);

	virtual void Act();
	virtual void Draw(HDC hdc, RECT &paint_area);
	virtual bool Is_Finished();
	void Get_Letter_Cell(RECT &rect);
	void Finalize();
	void Test_Draw_All_Steps(HDC hdc);

	const EBrick_Type Brick_Type;
	const ELetter_Type Letter_Type;

private:
	void Set_Brick_Letter_Colors(bool is_switch_color, HPEN &front_pen, HBRUSH &front_brush, HPEN &back_pen, HBRUSH &back_brush);
	void Draw_Brick_Letter(HDC hdc);
	void Draw_Line(HDC hdc, int x_1, int y_1, int x_2, int y_2);

	EFalling_Letter_State Falling_Letter_State;
	int X, Y;
	int Rotation_Step;
	int Next_Rotation_Tick;
	RECT Letter_Cell, Prev_Letter_Cell;

	static const int Ticks_Per_Step = 4;
	static const int Max_Rotation_Step = 16;
	static const int Brick_Half_Height = AsConfig::Brick_Height * AsConfig::Global_Scale / 2;

};
//------------------------------------------------------------------------------------------------------------
