// header.h: ǥ�� �ý��� ���� ����
// �Ǵ� ������Ʈ Ư�� ���� ������ ��� �ִ� ���� �����Դϴ�.
//

#pragma once
#pragma comment(lib, "gdiplus")
#pragma comment (lib, "winmm.lib")    //����

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#include <Ole2.h>
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <mmsystem.h>
//#include <iostream>
#include "Singleton.h"

using namespace std;

#define RAD2DEG			180/PI
#define PI				3.1415926535

#define GLOBAL_CLOCK	11
#define SCR_X			480
#define SCR_Y			280

#define MAX_LOADSTRING 100
#define IDI_MY202311189CDYVODKAFLAPPYBIRD
#define IDC_MY202311189CDYVODKAFLAPPYBIRD