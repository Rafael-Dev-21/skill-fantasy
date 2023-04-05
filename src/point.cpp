#include "point.hpp"

Point2D::Point2D(int y, int x) :
	m_y(y),
	m_x(x)
{}

void Point2D::move(int dy, int dx)
{
	m_y += dy;
	m_x += dx;
}

void Point2D::set(int ny, int nx)
{
	m_y = ny;
	m_x = nx;
}

void Point2D::setY(int ny)
{
	m_y = ny;
}

void Point2D::setX(int nx)
{
	m_x = nx;
}

int Point2D::y()
{
	return m_y;
}

int Point2D::x()
{
	return m_x;
}
