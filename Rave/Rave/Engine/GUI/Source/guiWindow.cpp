#pragma once
#include "Engine/GUI/Include/guiWindow.h"
#include "Engine/GUI/Include/EmptyCameraLock.h"

rave::gui::Window& rave::gui::Window::Load(Graphics& gfx, rave::Window& wnd, const wchar_t* t, const Box& b)
{
	EmptyCameraLock lock;

	title.pos = { b.left + 5 / (float)wnd.GetWidth(), b.top };
	title.string = t;
	title.Load(gfx, wnd.GetRenderTarget(), L"Consolas", defaultFontSize, FColors::White, { b.right, b.bottom });

	const float fontHeight = title.GetHeight(wnd.GetRenderTarget()) * 1.5f;
	box = b;

	centre = { (b.left + b.right) / 2, (b.top + b.bottom) / 2 };
	tboxcentre = { (b.left + b.right) / 2, b.top - fontHeight / 2 };

	background	= Rect(gfx, centre,		(b.right - b.left) / 2, (b.top - b.bottom)	/ 2, 0, defaultbg);
	titleBox	= Rect(gfx, tboxcentre,	(b.right - b.left) / 2, fontHeight			/ 2, 0, defaulttc);
	outline		= Rect(gfx, centre,		(b.right - b.left) / 2, (b.top - b.bottom)	/ 2, 0, defaultln, false);

	return *this;
}

void rave::gui::Window::Bind(Graphics& gfx, RenderTarget& target) const
{
	background.Bind(gfx);
	titleBox.Bind(gfx);
	outline.Bind(gfx);
	title.Bind(target);
}

void rave::gui::Window::Update(Graphics& gfx, rave::Window& wnd)
{
	Vector2 p = wnd.MousePos();
	Box headerCollider = box + p - mpos;
	headerCollider.bottom = headerCollider.top - (headerCollider.top - tboxcentre.y) * 2;
	if (wnd.mouse.LeftIsPressed() && headerCollider.Collides(p))
	{
		Vector2 d = p - mpos;
		box += p - mpos;

		EmptyCameraLock lock;

		centre += d;
		tboxcentre += d;

		background	.WriteTransform(gfx, Transform(centre,		1, 0));
		outline		.WriteTransform(gfx, Transform(centre,		1, 0));
		titleBox	.WriteTransform(gfx, Transform(tboxcentre,	1, 0));

		title.pos += d;
	}
	mpos = p;
}