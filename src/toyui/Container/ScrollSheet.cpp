//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Container/ScrollSheet.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>
#include <toyui/Frame/Grid.h>
#include <toyui/Frame/Layer.h>

#include <toyui/Container/Layout.h>

#include <toyui/Button/Scrollbar.h>
#include <toyui/Widget/RootSheet.h>

#include <toyui/UiLayout.h>

#include <toyobj/Iterable/Reverse.h>

namespace toy
{
	ScrollZone::ScrollZone(ScrollSheet& parent)
		: Layout(parent, cls())
		, m_scrollSheet(parent)
		, m_container(this->as<Wedge>())
	{}

	ScrollSheet::ScrollSheet(Wedge& parent, Type& type)
		: Container(parent, type, GRID)
		, m_scrollzone(*this)
		, m_scrollbarX(*this, m_scrollzone, m_scrollzone.container(), DIM_X)
		, m_scrollbarY(*this, m_scrollzone, m_scrollzone.container(), DIM_Y)
		, m_wrap(false)
	{
		m_containerTarget = &m_scrollzone.container();

		this->updateWrap();

		m_frame->as<Grid>().move(m_scrollzone.frame(), 0, 0);
		m_frame->as<Grid>().move(m_scrollbarY.frame(), 1, 0);
		m_frame->as<Grid>().move(m_scrollbarX.frame(), 0, 1);
	}

	void ScrollSheet::updateWrap()
	{
		m_frame->as<Grid>().resize(2);
		if(!m_wrap)
			m_frame->as<Grid>().line(0).setStyle(this->fetchStyle(Board::cls()));
		else
			m_frame->as<Grid>().line(0).setStyle(this->fetchStyle(Sheet::cls()));

		m_frame->as<Grid>().line(1).setStyle(this->fetchStyle(Row::cls()));
	}

	void ScrollSheet::clear()
	{
		m_scrollzone.clear();
	}

	bool ScrollSheet::mouseWheel(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		m_scrollbarX.scroll(mouseEvent.deltaX);
		m_scrollbarY.scroll(mouseEvent.deltaY);
		return true;
	}

	void ScrollSheet::enableWrap()
	{
		m_wrap = true;
		this->updateWrap();
		m_scrollzone.setStyle(NoScrollZone::cls());
	}

	void ScrollSheet::disableWrap()
	{
		m_wrap = false;
		this->updateWrap();
		m_scrollzone.setStyle(ScrollZone::cls());
	}

	Surface::Surface(Wedge& parent)
		: Sheet(parent, cls())
	{}

	ScrollPlan::ScrollPlan(Wedge& parent, Type& type)
		: ScrollSheet(parent, type)
		, m_plan(m_scrollzone.container())
		, m_surface(m_plan)
		, m_clamped(true)
	{
		m_plan.setStyle(Plan::cls());
		m_containerTarget = &m_surface;
		this->updateBounds();
	}

	void ScrollPlan::dirtyLayout()
	{
		this->updateBounds();
	}

	void ScrollPlan::updateBounds()
	{
		// @warning: if the plan contains an expand container, the size will keep increasing endlessly

		float margin = 1000.f;
		m_bounds = BoxFloat(-margin, -margin, +margin, +margin);

		for(Frame* frame : m_surface.stripe().contents())
		{
			m_bounds[DIM_X] = std::min(frame->dposition(DIM_X) - margin, m_bounds[DIM_X]);
			m_bounds[DIM_Y] = std::min(frame->dposition(DIM_Y) - margin, m_bounds[DIM_Y]);
			m_bounds[DIM_XX] = std::max(frame->dposition(DIM_X) + frame->dsize(DIM_X) + margin, m_bounds[DIM_XX]);
			m_bounds[DIM_YY] = std::max(frame->dposition(DIM_Y) + frame->dsize(DIM_Y) + margin, m_bounds[DIM_YY]);
		}

		m_surface.frame().setManualSize(m_bounds.x1() - m_bounds.x0(), m_bounds.y1() - m_bounds.y0());
	}

	bool ScrollPlan::middleDrag(MouseEvent& mouseEvent)
	{
		m_plan.frame().setPosition(std::min(0.f, m_plan.frame().dposition(DIM_X) + mouseEvent.deltaX), std::min(0.f, m_plan.frame().dposition(DIM_Y) + mouseEvent.deltaY));
		m_plan.frame().layer().setForceRedraw();
		return true;
	}

	bool ScrollPlan::mouseWheel(MouseEvent& mouseEvent)
	{
		float deltaScale = mouseEvent.deltaZ > 0.f ? 1.2f : 0.8333f;
		float scale = m_plan.frame().scale() * deltaScale;

		if(m_clamped)
		{
			float minScaleX = m_scrollzone.frame().dsize(DIM_X) / m_plan.frame().dsize(DIM_X);
			float minScaleY = m_scrollzone.frame().dsize(DIM_Y) / m_plan.frame().dsize(DIM_Y);
			scale = std::max(scale, std::max(minScaleX, minScaleY));
		}

		m_plan.frame().setScale(scale);
		m_plan.frame().layer().setForceRedraw();

		DimFloat absolute = m_plan.frame().absolutePosition();
		float distanceX = mouseEvent.posX - absolute[DIM_X];
		float distanceY = mouseEvent.posY - absolute[DIM_Y];

		float offsetX = distanceX - distanceX * deltaScale;
		float offsetY = distanceY - distanceY * deltaScale;

		if(m_clamped)
			m_plan.frame().setPosition(std::min(0.f, m_plan.frame().dposition(DIM_X) + offsetX), std::min(0.f, m_plan.frame().dposition(DIM_Y) + offsetY));
		else
			m_plan.frame().setPosition(m_plan.frame().dposition(DIM_X) + offsetX, m_plan.frame().dposition(DIM_Y) + offsetY);

		return true;
	}

	bool drawGrid(Frame& frame, Renderer& renderer)
	{
		float gridsizeX = 100.f;
		float gridsizeY = 50.f;
		float sizeX = frame.dsize(DIM_X);
		float sizeY = frame.dsize(DIM_Y);

		for(float x = 0.f; x < sizeX; x += gridsizeX)
		{
			renderer.pathLine(x, 0.f, x, sizeY);
			renderer.stroke(frame.content().inkstyle());
		}

		for(float y = 0.f; y < sizeY; y += gridsizeY)
		{
			renderer.pathLine(0.f, y, sizeX, y);
			renderer.stroke(frame.content().inkstyle());
		}

		return false;
	}
}
