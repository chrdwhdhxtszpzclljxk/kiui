//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_CURSOR_H
#define TOY_CURSOR_H

/* toy */
#include <toyobj/Util/Timer.h>
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>

namespace toy
{
	class _I_ TOY_UI_EXPORT Tooltip : public Overlay
	{
	public:
		Tooltip(RootSheet& rootSheet, const string& label);

		void setLabel(const string& label);

		static Type& cls() { static Type ty("Tooltip", Overlay::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Rectangle : public Decal
	{
	public:
		Rectangle(Wedge& parent, Type& type = cls());

		static Type& cls() { static Type ty("Rectangle", Decal::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Cursor : public Decal
	{
	public:
		Cursor(RootSheet& rootSheet);

		void nextFrame(size_t tick, size_t delta);

		void setPosition(float x, float y);

		void hover(Widget& hovered);
		void unhover(Widget& widget);
		void unhover();

		void tooltipOn();
		void tooltipOff();

		static Type& cls() { static Type ty("Cursor", Decal::cls()); return ty; }

	protected:
		bool m_dirty;
		Widget* m_hovered;
		Tooltip m_tooltip;
		Clock m_tooltipClock;
	};

	class TOY_UI_EXPORT ResizeCursorX
	{
	public:
		static Type& cls() { static Type ty("ResizeCursorX", Cursor::cls()); return ty; }
	};

	class TOY_UI_EXPORT ResizeCursorY
	{
	public:
		static Type& cls() { static Type ty("ResizeCursorY", Cursor::cls()); return ty; }
	};

	class TOY_UI_EXPORT MoveCursor
	{
	public:
		static Type& cls() { static Type ty("MoveCursor", Cursor::cls()); return ty; }
	};

	class TOY_UI_EXPORT ResizeCursorDiagLeft
	{
	public:
		static Type& cls() { static Type ty("ResizeCursorDiagLeft", Cursor::cls()); return ty; }
	};

	class TOY_UI_EXPORT ResizeCursorDiagRight
	{
	public:
		static Type& cls() { static Type ty("ResizeCursorDiagRight", Cursor::cls()); return ty; }
	};

	class TOY_UI_EXPORT CaretCursor
	{
	public:
		static Type& cls() { static Type ty("CaretCursor", Cursor::cls()); return ty; }
	};
}

#endif // TOY_CURSOR_H
