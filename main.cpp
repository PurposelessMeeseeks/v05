#include <windows.h>
#include <tchar.h>
#include <list>
#include "nwpwin.h"
#define AREA 1

class MainWindow : public Window
{
private:
	std::list<POINT> points;
protected:
	void OnPaint(HDC hdc)  
	{ 
		if (points.empty())
			return;
		::MoveToEx(hdc, points.front().x, points.front().y, nullptr);
		for (POINT p : points) {
			::LineTo(hdc, p.x, p.y);
		}
	}

	void OnLButtonDown(POINT p)
	{
		POINT prev;
		if (!points.empty())
		{
			prev = points.back();
		}
		points.push_back(p);
		if (points.size() > 1)
		{	
			RECT rc = { min(prev.x,p.x)-AREA, min(prev.y, p.y)-AREA, max(prev.x,p.x)+AREA, max(prev.y, p.y)+AREA };
			InvalidateRect(*this, &rc, TRUE);
		}
	}

	void OnKeyDown(int vk) 
	{
		if (points.empty())
			return;
		if (vk == VK_ESCAPE)
			points.clear();
		else if (vk == VK_BACK)
			points.pop_back();
		else
			return;
		InvalidateRect(*this, nullptr, TRUE);
	}
	void OnDestroy()
	{
		::PostQuitMessage(0);
	}
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP 5"));
	return app.Run();
}
