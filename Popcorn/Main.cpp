// Popcorn.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Main.h"

#define MAX_LOADSTRING 100

// Global Variables:
AsEngine Engine;
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
//------------------------------------------------------------------------------------------------------------
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_POPCORN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
		return FALSE;

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_POPCORN));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}
//------------------------------------------------------------------------------------------------------------
//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_POPCORN));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = AsConfig::BG_Color.Get_Brush();
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_POPCORN);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}
//------------------------------------------------------------------------------------------------------------
//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	RECT window_rect;
	window_rect.left = 0;
	window_rect.top = 0;
	window_rect.right = 320 * 3;
	window_rect.bottom = 200 * 3;

	AdjustWindowRect(&window_rect, WS_OVERLAPPEDWINDOW, TRUE);

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, 0, 0, window_rect.right - window_rect.left, window_rect.bottom - window_rect.top, 0, 0, hInstance, 0);

	if (hWnd == 0)
		return FALSE;

	Engine.Init_Engine(hWnd);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}
//------------------------------------------------------------------------------------------------------------
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId;
	HDC hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	break;


	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		Engine.Draw_Frame(hdc, ps.rcPaint);
		EndPaint(hWnd, &ps);
	break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;


	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			return Engine.On_Key(EKT_Left, true);

		case VK_RIGHT:
			return Engine.On_Key(EKT_Right, true);

		case VK_SPACE:
			return Engine.On_Key(EKT_Space, true);
		}
		break;

	case WM_KEYUP:
		switch (wParam)
		{
		case VK_LEFT:
			return Engine.On_Key(EKT_Left, false);

		case VK_RIGHT:
			return Engine.On_Key(EKT_Right, false);

		case VK_SPACE:
			return Engine.On_Key(EKT_Space, false);
		}
		break;


	case WM_TIMER:
		if (wParam == Timer_ID)
			return Engine.On_Timer();
		break;


	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}


	return 0;
}
//------------------------------------------------------------------------------------------------------------
// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
//------------------------------------------------------------------------------------------------------------
/*

V Конец уровня при потере мяча
V 1. Анимация расплавления платформы
V 2. Анимация выкатывания новой
V 3. Анимация расширяющейся платформы
V 4. Пуск мяча пробелом и состояния мяча

V Кирпичи
V 1. Обычные кирпичи (синие или красные)
V 1.1. Могут быть с буквой или без
V 1.2. При попадании в кирпич он исчезает из уровня сразу, и если кирпич был:
V 1.2.1. Без буквы - создаётся активный кирпич
V 1.2.2. С буквой - создаётся падающая буква

V 2. Неразрушаемый кирпич
V 2.1. Анимация при попадании

V 3. Многоразовый кирпич
V 3.1. 4 состояния кирпича (1-4 удара до разрушения)
V 3.2. Переход по состояниям
V 3.3. Анимация приза при разрушении (кирпич исчезает, анимация - остаётся)

V 4. Кирпич с парашютом
V 4.1. Анимация парашюта - как вариант падающей буквы

V 5. Кирпич телепортации
V 5.1. Анимация при захвате и выпуске мяча

V 6. Кирпич рекламы
V 6.1. Анимация фрагмента "рекламы", скрывавшейся за кирпичом


V Взаимодействие особых кирпичей
V 1. Падающая буква - взаимодействует только с платформой
V 2. Активный кирпич - взаимодействует только с шариком


Действия букв
1. Простые:
1.1. О ("Отмена") — отмена действия символов К, Ш, П, Л и М.
V 1.2. И ("Инверсия")
V 1.3. С ("Скорость")
1.4. М ("Монстры")
V 1.5. Ж ("Жизнь")


2. Сложные:
V 2.1. К ("Клей")
V 2.1.1. Новое состояние платформы
V 2.1.2. Анимация растекающегося клея (прямая и обратная)
V 2.1.3. Фиксация шарика (+ новое состояние шарика)
V 2.1.4. Пуск шарика пробелом и по таймауту

V 2.2. Ш ("Шире")
V 2.2.1. Новое состояние платформы (+ изменение размера)
V 2.2.2. Анимация расширяющейся платформы (прямая и обратная)

V 2.3. П ("Пол")
V 2.3.1. Отрисовка пола
V 2.3.2. Шкала пола
V 2.3.3. Взаимодействие пола с мячом
V 2.3.4. Отбитие мяча нижней гранью платформы

V 2.4. Л ("Лазер")
V 2.4.1. Новое состояние платформы
V 2.4.2. Анимация превращения в пушку (прямая и обратная)
V 2.4.3. Стрельба пробелом:
V 2.4.3.1. Обработка пробела особым образом, когда платформа в режиме лазера
V 2.4.3.2. Объекты лазерных лучей - анимация, перемещение и взаимодействие с другими объектами

V 2.5. Т ("Три")
V 2.5.1. Добавить поддержку множества мячиков
V 2.5.2. Вывод множества мячиков
V 2.5.3. Взаимодействие множества мячиков с элементами игры

2.6. + (Переход на следующий уровень)
2.6.1. Анимация досрочного перехода на следующий уровень
2.6.2. Отдельный уровень перехода с особыми стенками (рамкой)

Движение мячика
V 1. Отскок мячика от рамки
V 2. Попадания в края платформы
V 3. Подсечка мяча платформой
4. Попадание в монстра

Попадание в кирпич
1. Попадание в кирпич - состояния кирпича
V 2. Выбивание падающей буквы
V 3. Перехват падающей буквы
4. Для каждой буквы - свои действия

Гейты
1. Вывод гейтов
2. Анимация открытия/закрытия гейтов
3. Состояния гейтов (закрыт, открывается, закрывается)


Монстры
1. Список монстров (глаз, "черепаха", "сатурн", голова, "бубен", аквариум, зажигалка)
2. Для каждого - сделать раскадровку
3. Перемещение, выбор направления + состояния (живой/пауза/исчезает)
4. Взаимодействие с мячом и платформой
5. Выход из гейта
6. Для каждого - анимация


Информационная панель
1. Логотип
2. Индикаторы
2.1. Имя игрока
2.2 Текущий счёт
3. Шкала монстров и пола
4. Изменение шкал
5. Окно дополнительных жизней
6. Учёт игровых действий и отображение на индикаторах


Игра и уровни
1. Список первых 10 уровней
2. Состояния игры (заставка, анимация начала уровня, играем уровень, потеря жизни, переход на следующий уровень (нормальный и досрочный), окончание игры)


*/
