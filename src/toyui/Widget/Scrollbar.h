//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_SCROLLBAR_H
#define TOY_SCROLLBAR_H

/* toy */
#include <toyobj/Id.h>
#include <toyobj/String/String.h>
#include <toyobj/Util/Updatable.h>
#include <toyui/Forward.h>
#include <toyui/Widget/Widget.h>
#include <toyui/Widget/Button.h>
#include <toyui/Widget/Slider.h>
#include <toyui/Frame/Stripe.h>

#include <memory>

namespace toy
{
	class TOY_UI_EXPORT Scroller : public Slider
	{
	public:
		Scroller(Dimension dim, StyleType& type);

		void sliderStep(float offset, bool ended);

		static StyleType& cls() { static StyleType ty("Scroller", Slider::cls()); return ty; }
	};

	class TOY_UI_EXPORT ScrollerX : public Scroller
	{
	public:
		ScrollerX();

		static StyleType& cls() { static StyleType ty("ScrollerX", Scroller::cls()); return ty; }
	};

	class TOY_UI_EXPORT ScrollerY : public Scroller
	{
	public:
		ScrollerY();

		static StyleType& cls() { static StyleType ty("ScrollerY", Scroller::cls()); return ty; }
	};

	class TOY_UI_EXPORT ScrollerKnob : public SliderKnob
	{
	public:
		ScrollerKnob(Dimension dim, StyleType& type);

		static StyleType& cls() { static StyleType ty("ScrollerKnob", SliderKnob::cls()); return ty; }
	};

	class TOY_UI_EXPORT ScrollerKnobX : public ScrollerKnob
	{
	public:
		ScrollerKnobX();

		static StyleType& cls() { static StyleType ty("ScrollerKnobX", ScrollerKnob::cls()); return ty; }
	};

	class TOY_UI_EXPORT ScrollerKnobY : public ScrollerKnob
	{
	public:
		ScrollerKnobY();

		static StyleType& cls() { static StyleType ty("ScrollerKnobY", ScrollerKnob::cls()); return ty; }
	};

	class TOY_UI_EXPORT ScrollUp : public Button
	{
	public:
		ScrollUp(const Trigger& trigger);

		static StyleType& cls() { static StyleType ty("ScrollUp", Button::cls()); return ty; }
	};

	class TOY_UI_EXPORT ScrollDown : public Button
	{
	public:
		ScrollDown(const Trigger& trigger);

		static StyleType& cls() { static StyleType ty("ScrollDown", Button::cls()); return ty; }
	};

	class TOY_UI_EXPORT ScrollLeft : public Button
	{
	public:
		ScrollLeft(const Trigger& trigger);

		static StyleType& cls() { static StyleType ty("ScrollLeft", Button::cls()); return ty; }
	};

	class TOY_UI_EXPORT ScrollRight : public Button
	{
	public:
		ScrollRight(const Trigger& trigger);

		static StyleType& cls() { static StyleType ty("ScrollRight", Button::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Scrollbar : public Sheet
	{
	public:
		Scrollbar(Sheet& frameSheet, Dimension dim, StyleType& type);
		~Scrollbar();

		float contentSize();
		float visibleSize();

		float overflow();

		void scrollup();
		void scrolldown();
		void scroll(float amount);
		void scrollTo(float offset);

		void nextFrame(size_t tick, size_t delta);

		static StyleType& cls() { static StyleType ty("Scrollbar", Sheet::cls()); return ty; }

	protected:
		Dimension m_dim;
		float d_cursor;
		Sheet& m_frameSheet;

		Button& m_up;
		Scroller& m_scroller;
		Button& m_down;

	};

	class TOY_UI_EXPORT ScrollbarX : public Scrollbar
	{
	public:
		ScrollbarX(Sheet& frameSheet);

		static StyleType& cls() { static StyleType ty("ScrollbarX", Scrollbar::cls()); return ty; }
	};

	class TOY_UI_EXPORT ScrollbarY : public Scrollbar
	{
	public:
		ScrollbarY(Sheet& frameSheet);

		static StyleType& cls() { static StyleType ty("ScrollbarY", Scrollbar::cls()); return ty; }
	};
}

#endif // TOY_SCROLLBAR_H
